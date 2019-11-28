#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <vector>
#include <omp.h>
#include <stdio.h>
#include <string>
#include "Rezultatas.h"
#include "InformacijaDokumento.h"
#include "pugixml.hpp"
#include "DuomenuMasyvas.h"

using namespace std;
using namespace MPI;
const int informacijosDydis = 25;
void Zinute(int, string);
bool Ar_Tinka(int rusiavimas, InformacijaEilute informacija);
int main()
{
	Init();
	int gijos_nr = COMM_WORLD.Get_rank();
	switch (gijos_nr)
	{
	//Pagrindine Gija
	case 0:
	{
		bool stop;
		const char* ivesties_vieta = "IvestiesFailai/IFF77_SadleviciusE_L1_dat_2.xml";
		const char* isvesties_vieta = "IsvestiesFailai/IFF77_SadleviciusE_L1_rez_2.txt";
		InformacijaDokumento dokumentas(ivesties_vieta);
		//Siunciama duomenu masyvui
		while (true)
		{
			int info_dydis;
			InformacijaEilute* gaunamas = dokumentas.Gauti_Verte();
			if (gaunamas == NULL)
			{
				info_dydis = 0;
				COMM_WORLD.Send(&info_dydis, 1, INT, 2, 0);
				break;
			}
			string informacija = gaunamas->Paversti_XML();
			info_dydis = static_cast<int>(informacija.size());
			const char* informacija_chars = informacija.c_str();
			cout << "Pagrindine Gija: Issiunciau duomenys ir lauksiu atsakymo" << endl;
			COMM_WORLD.Send(&info_dydis, 1, INT, 2, 0);
			COMM_WORLD.Send(informacija_chars, info_dydis, CHAR, 2, 1);

			COMM_WORLD.Recv(&stop, 1, BOOL, 2, 2);//Del sustojimo
		}
		cout << "Pagrindine Gija: Visi duomenys išsiųsti" << endl;
		Zinute(gijos_nr, "Prie barjero");
		COMM_WORLD.Barrier();
		//Gaunama info iš rezultato
		COMM_WORLD.Send(&stop,1,BOOL,1,0);
		int dydis;
		COMM_WORLD.Recv(&dydis, 1, INT, 1, 0);
		char objektas[dydis];
		COMM_WORLD.Recv(objektas, dydis, CHAR, 1, 1);
		//Spausdina
		ofstream rezultatas_failas(isvesties_vieta);
		if (rezultatas_failas.is_open())
		{
			rezultatas_failas << objektas;
			rezultatas_failas.close();
		}
		else
		{
			cout << "!!!---Nesukure rezultato failo---!!!";
		}
		break;
	}
	//Rezultatu gija
	case 1:
	{
		const bool didejantis = true;
		int procesu_kiekis = COMM_WORLD.Get_size() - 3;
		int kiekis = 0;
		bool baigta = false;
		Rezultatas rez(informacijosDydis, didejantis);
		cout << "Gija " << gijos_nr << ": Rezultatas pasiruoses" << endl;
		//Pradeda darba
		while (true)
		{
			if (baigta)
			{
				break;
			}
			Status kieno_zinute;
			if (procesu_kiekis == 0)
			{
				COMM_WORLD.Barrier();
				COMM_WORLD.Probe(0, 0, kieno_zinute);
			}
			else
			{
				COMM_WORLD.Probe(ANY_SOURCE, ANY_TAG, kieno_zinute);
			}
			switch (kieno_zinute.Get_source())
			{
			//Pagrindinei gijai atsakymas
			case 0:
			{
				int info_dydis;
				string galutinis = rez.Gauti_Informacija();
				info_dydis = static_cast<int>(galutinis.size());
				const char* informacija_chars = galutinis.c_str();
				COMM_WORLD.Send(&info_dydis, 1, INT, 0, 0);
				COMM_WORLD.Send(informacija_chars, info_dydis, CHAR, 0, 1);
				baigta = true;
				break;
			}
			//Darbinems Gijoms atsakymas
			default:
			{
				int dydis;
				COMM_WORLD.Recv(&dydis, 1, INT, kieno_zinute.Get_source(), 0);
				if (dydis == 0)
				{
					procesu_kiekis--;
					break;
				}
				Zinute(gijos_nr, "Informacijos dydis yra " + to_string(dydis));
				char objektas[dydis];
				COMM_WORLD.Recv(objektas, dydis, CHAR, kieno_zinute.Get_source(), 1);
				Zinute(gijos_nr, "Eilute yra " + string(objektas));
				InformacijaEilute informacija = InformacijaEilute::Gauti_Is_XML(objektas);
				kiekis++;
				rez.Ideti_Ir_Rusiuoti(informacija);
			}
			}
		}
		break;
	}
	case 2:
	{
		int procesu_kiekis = COMM_WORLD.Get_size() - 3;
		bool pilnas = false;
		bool tuscias = true;
		bool pasibaige = false;
		DuomenuMasyvas duomenys(informacijosDydis);
		cout << "Gija " << gijos_nr << ": Duomenu masyvas paruostas" << endl;
		//Pradeda darba
		while (true)
		{
			int dydis;
			Status kieno_zinute;
			if (procesu_kiekis == 0)
			{
				break;
			}
			if (tuscias && !pasibaige)
			{
				COMM_WORLD.Probe(0, 0, kieno_zinute);
			}
			else if (pilnas)
			{
				COMM_WORLD.Probe(ANY_SOURCE, 3, kieno_zinute);
			}
			else
			{
				COMM_WORLD.Probe(ANY_SOURCE, ANY_TAG, kieno_zinute);
			}
			switch (kieno_zinute.Get_source())
			{
			case 0:
			{
				if (tuscias)
				{
					tuscias = false;
				}
				COMM_WORLD.Recv(&dydis, 1, INT, 0, 0);
				Zinute(gijos_nr, "Informacijos dydis yra " + to_string(dydis));
				if (dydis == 0)
				{
					pasibaige = true;
					break;
				}
				char objektas[dydis];
				COMM_WORLD.Recv(objektas, dydis, CHAR, 0, 1);
				Zinute(gijos_nr, "Eilute yra " + string(objektas));
				InformacijaEilute informacija = InformacijaEilute::Gauti_Is_XML(objektas);
				if (!duomenys.Ideti_Informacija(informacija))
				{
					pilnas = true;
					Zinute(gijos_nr, "Duomenu masyvas pilnas");
					break;
				}
				//-------------------------------------------
				Zinute(gijos_nr, "Siunciu, jog gavau " + to_string(kieno_zinute.Get_source()) + " Gijai");
				COMM_WORLD.Send(&pilnas, 1, BOOL, 0, 2);
				//-------------------------------------------
				break;
			}
			default:
			{
				if (pilnas)
				{
					pilnas = false;
					//-------------------------------------------
					Zinute(gijos_nr, "Siunciu, jog gavau " + to_string(kieno_zinute.Get_source()) + " Gijai");
					COMM_WORLD.Send(&pilnas, 1, BOOL, 0, 2);
					//-------------------------------------------
				}
				int info_dydis;
				bool gavau;
				if (pasibaige && tuscias)
				{
					procesu_kiekis--;
					info_dydis = 0;
					COMM_WORLD.Recv(&gavau, 1, BOOL, kieno_zinute.Get_source(), 3);
					COMM_WORLD.Send(&info_dydis, 1, INT, kieno_zinute.Get_source(), 0);
					break;
				}
				InformacijaEilute temp = duomenys.Pasalinti_Informacija();
				if (temp.Verte_Hash() == "")
				{
					tuscias = true;
					break;
				}
				COMM_WORLD.Recv(&gavau, 1, BOOL, kieno_zinute.Get_source(), 3);
				string pasalintas = temp.Paversti_XML();
				info_dydis = static_cast<int>(pasalintas.size());
				const char* informacija_chars = pasalintas.c_str();
				COMM_WORLD.Send(&info_dydis, 1, INT, kieno_zinute.Get_source(), 0);
				COMM_WORLD.Send(informacija_chars, info_dydis, CHAR, kieno_zinute.Get_source(), 1);
			}
			}
		}
		break;
	}
	default:
	{
		Zinute(gijos_nr, "Pasiruoses darbui");
		bool siusti = true;
		int dydis;
		while (true)
		{
			COMM_WORLD.Send(&siusti, 1, BOOL, 2, 3);
			Zinute(gijos_nr, "Nusiunciau");
			COMM_WORLD.Recv(&dydis, 1, INT, 2, 0);
			Zinute(gijos_nr, "Gavau");
			Zinute(gijos_nr, to_string(dydis));
			if (dydis == 0)
			{
				COMM_WORLD.Send(&dydis, 1, INT, 1, 0);
				break;
			}
			char objektas[dydis];
			COMM_WORLD.Recv(objektas, dydis, CHAR, 2, 1);
			InformacijaEilute informacija = InformacijaEilute::Gauti_Is_XML(objektas);
			//Atrenka
			if (Ar_Tinka(0, informacija))
			{
				string siunciamas = informacija.Paversti_XML();
				dydis = static_cast<int>(siunciamas.size());
				const char* informacija_chars = siunciamas.c_str();
				COMM_WORLD.Send(&dydis, 1, INT, 1, 0);
				COMM_WORLD.Send(informacija_chars, dydis, CHAR, 1, 1);
			}
		}
	}
	}
	if(gijos_nr != 0 && gijos_nr != 1)
	{
		Zinute(gijos_nr, "Prie barjero");
		COMM_WORLD.Barrier();
	}
	Zinute(gijos_nr, "Baigiau darba");
	Finalize();
	return 0;
}

void Zinute(int nr, string zinute)
{
	cout << "Gija " + to_string(nr) + ": " + zinute << endl;
}

bool Ar_Tinka(int rusiavimas, InformacijaEilute informacija)
{
	switch (rusiavimas)
	{
	case 0:
	{
		if (isalpha(informacija.Verte_Hash()[0]))
		{
			return true;
		}
		return false;
	}
	case 1:
	{
		if (isalnum(informacija.Verte_Hash()[0]))
		{
			return true;
		}
		return false;
	}
	default:
	{
		return false;
	}
	}
}

