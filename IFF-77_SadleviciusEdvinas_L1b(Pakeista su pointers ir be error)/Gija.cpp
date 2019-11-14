#include "Gija.h"



Gija::Gija(Monitorius* mon, const int ru)
{
	id = gijuSkaicius++;
	informacija = NULL;
	monitorius = mon;
	rusiavimas = ru;
}

int Gija::Gauti_Id()
{
	return id;
}


Monitorius* Gija::GautiMonitoriu()
{
	return monitorius;
}

bool Gija::Reikalingas()
{
	switch (rusiavimas)
	{
	case 0:
	{
		if (isalpha(informacija->Verte_Hash()[0]))
		{
			return true;
		}
		return false;
	}
	case 1:
	{
		if (isalnum(informacija->Verte_Hash()[0]))
		{
			return true;
		}
		return false;
	}
	default:
		return false;
	}
}
bool Gija::Pradeti()
{
	while (monitorius->Gauti_Informacija(informacija, id));
	if (informacija == NULL)
	{
		cout << "Gija " << id << ": Baigiau darba" << endl;
		return false;
	}
	else
	{
		if (Reikalingas())
		{
			monitorius->Deti_Informacija(informacija, id);
			return true;
		}
		else
		{
			return true; ;
		}
	}
}
Gija::~Gija()
{
	delete informacija;
}
