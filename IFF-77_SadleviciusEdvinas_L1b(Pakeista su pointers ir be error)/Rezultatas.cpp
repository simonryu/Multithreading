#include "Rezultatas.h"


Rezultatas::Rezultatas(int dydis, bool didejantis)
{
	rezultatai = new InformacijaEilute[dydis];
	Rezultatas::dydis = 0;
	Rezultatas::didejantis = didejantis;
}


Rezultatas::~Rezultatas()
{
	delete[] rezultatai;
}

bool Rezultatas::Ideti_Ir_Rusiuoti(InformacijaEilute* info)
{
	return Perdeti_Elementa(info, 0);
}

bool Rezultatas::Perdeti_Elementa(InformacijaEilute* info, int kelintas)
{
	if (dydis == kelintas)
	{
		rezultatai[kelintas] = InformacijaEilute(*info);
		dydis++;
		return true;
	}
	if (didejantis)
	{
		switch(info->Palyginti(&rezultatai[kelintas]))
		{
			case 1:
			{
				InformacijaEilute temp = rezultatai[kelintas];
				rezultatai[kelintas] = InformacijaEilute(*info);
				return Perdeti_Elementa(&temp, ++kelintas);
			}
			default:
				return Perdeti_Elementa(info, ++kelintas);
		}

	}
	else
	{
		switch(info->Palyginti(&rezultatai[kelintas]))
		{
			case -1:
			{
				InformacijaEilute temp = rezultatai[kelintas];
				rezultatai[kelintas] = InformacijaEilute(*info);
				return Perdeti_Elementa(&temp, ++kelintas);
			}
			default:
				return Perdeti_Elementa(info, ++kelintas);
		}
	}
}

int Rezultatas::Verte_Dydis()
{
	return dydis;
}

void Rezultatas::Spausdinti_Rezultata(const char* keliasIkiRez)
{
	ofstream rezultatas_failas(keliasIkiRez);
	if (rezultatas_failas.is_open())
	{
		char pagrLin[200];
		sprintf(pagrLin,"|%-20s|%-20s|%-20s|%-100s|\n", "Pavadinimas", "Parduota", "Kaina", "HASH");
		const char* linija = "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		rezultatas_failas << pagrLin << linija;
		for(int i = 0;i < dydis;i++)
		{ 
			char rez[400];
			sprintf(rez, "|%-20s|%-20d|%-20.16g|%-100s|\n", rezultatai[i].Verte_Zodis().c_str(), rezultatai[i].Verte_zSkaicius(), rezultatai[i].Verte_rSkaicius(), rezultatai[i].Verte_Hash().c_str());
			rezultatas_failas << rez << linija;
		}
		rezultatas_failas << "Viso: " << dydis;
		rezultatas_failas.close();
		cout << "Uzdare" << endl;
	}
	else
	{
		cout << "Nesukure rezultato failo";
	}
}