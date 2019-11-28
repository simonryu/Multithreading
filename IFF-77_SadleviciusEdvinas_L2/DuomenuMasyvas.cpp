#include "DuomenuMasyvas.h"



DuomenuMasyvas::DuomenuMasyvas(const int dydis)
{
	DuomenuMasyvas::dydis = dydis/2;
	informacija = new InformacijaEilute[DuomenuMasyvas::dydis];
}

void DuomenuMasyvas::Atspausdinti()
{
	for (int i = 0; i < dydis; i++)
	{
		cout << "Spausdinu " << i << ": " << informacija[i].Verte_Zodis() << endl;;
	}
}

int DuomenuMasyvas::RastiTusciaIndeksa()
{
	for (int i = 0; i < dydis; i++)
	{
		if (informacija[i].Verte_Hash() == "")
		{
			return i;
		}
	}
	return -1;
}
int DuomenuMasyvas::RastiNetusciaIndeksa()
{
	for (int i = 0; i < dydis; i++)
	{
		if (informacija[i].Verte_Hash() != "")
		{
			return i;
		}
	}
	return -1;
}

bool DuomenuMasyvas::Ideti_Informacija(InformacijaEilute info)
{
		int indeksas;
		if ((indeksas = RastiTusciaIndeksa()) < 0)
		{
			return false;
		}
		else
		{
				informacija[indeksas] = info;
				if (RastiTusciaIndeksa() < 0)
				{
					return false;
				}
				return true;
		}
}

InformacijaEilute DuomenuMasyvas::Pasalinti_Informacija()
{
	int indeksas = RastiNetusciaIndeksa();
	if (indeksas < 0)
	{
		return InformacijaEilute();
	}
	InformacijaEilute temp = informacija[indeksas];
	informacija[indeksas] = InformacijaEilute();
	return temp;
}

DuomenuMasyvas::~DuomenuMasyvas()
{
	delete[] informacija;
}
