#include "Monitorius.h"



Monitorius::Monitorius(const int dydis, InformacijaDokumento* dok, Rezultatas* rez)
{
	Monitorius::dydis = dydis/2;
	tuscias = true;
	baigta = false;
	pilnas = false;
	dokumentas = dok;
	rezultatas = rez;
	informacija = (InformacijaEilute**)malloc(sizeof(InformacijaEilute*) * dydis/2);
	for (int i = 0; i < dydis / 2; i++)
	{
		informacija[i] = NULL;
	}
}

int Monitorius::RastiTusciaIndeksa()
{
	for (int i = 0; i < dydis; i++)
	{
		if (informacija[i] == NULL)
		{
			cout << "Radau: " << i << endl;
			return i;
		}
	}
	return -1;
}

bool Monitorius::Pagrindine_Deda_Informacija()
{
	uzraktas_gauti.uzrakinti();
	int indeksas;
	if (pilnas)
	{
		cout << "Pagrindine gija: Pilnas masyvas" << endl;;
	}
	else if ((indeksas = RastiTusciaIndeksa()) < 0)
	{
		cout << "Pagrindine gija: Nera vietos masyve" << endl;
		pilnas = true;
	}
	else
	{
		cout << "Pagrindine gija: idedu informacija" << endl;
		InformacijaEilute* nauja_info = dokumentas->Gauti_Verte();
		if (nauja_info == NULL)
		{
			cout << "Pagrindine gija: Pasibaige, nes gautas tuscias konstruktorius" << endl;
			baigta = true;
		}
		else
		{
			if (tuscias)
			{
				tuscias = false;
			}
			naudojama.push_back(indeksas);
			informacija[indeksas] = nauja_info;
		}
	}
	uzraktas_gauti.atrakinti();
	if (baigta)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Monitorius::Deti_Informacija(InformacijaEilute*& naujaEilute, int id)
{
	uzraktas_deti.uzrakinti();
	cout << "Gija " << id << ": Vykdau Deti_Informacija()" << endl;
	rezultatas->Ideti_Ir_Rusiuoti(naujaEilute);
	uzraktas_deti.atrakinti();
	return true;
}

bool Monitorius::Gauti_Informacija(InformacijaEilute*& info, int id)
{
	if (baigta && tuscias)
	{
		info = NULL;
		return false;
	}
	if (tuscias)
	{
		return true;
	}
	uzraktas_gauti.uzrakinti();
	if (pilnas)
	{
		pilnas = false;
	}
	if (naudojama.size() == 0)
	{
		tuscias = true;
		cout << "Gija " << id << ": Vykdau Gauti_Informacija(), bet tuscias masyvas" << endl;
		uzraktas_gauti.atrakinti();
		return true;
	}
	else
	{
		cout << "Gija " << id << ": Vykdau Gauti_Informacija()" << endl;;
		int indeksas = naudojama.back();
		naudojama.pop_back();
		info = informacija[indeksas];
		informacija[indeksas] = NULL;
		uzraktas_gauti.atrakinti();
		return false;
	}
}

Monitorius::~Monitorius()
{
	delete[] informacija;
}
