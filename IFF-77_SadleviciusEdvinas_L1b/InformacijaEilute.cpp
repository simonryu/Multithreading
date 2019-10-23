#include "InformacijaEilute.h"
#include <stdio.h>
#pragma warning(disable : 4996)
InformacijaEilute::InformacijaEilute()
{
	zodis = "";
	zSkaicius = 0;
	rSkaicius = 0;
	hash = "";
}

InformacijaEilute::InformacijaEilute(string zod, int z, double r)
{
	zodis = zod;
	zSkaicius = z;
	rSkaicius = r;
	hash = SukurtiHash();
}

string InformacijaEilute::SukurtiHash()
{
	setlocale(LC_ALL, "en_US.utf8");
	char double_i_teksta[20];
	sprintf(double_i_teksta, "%.16g", rSkaicius);
	string naujasGautas = zodis + to_string(zSkaicius) + double_i_teksta;
	string hashNew;
	picosha2::hash256_hex_string(naujasGautas, hashNew);
	return hashNew;
}
InformacijaEilute::~InformacijaEilute()
{
}

int InformacijaEilute::Palyginti(InformacijaEilute* kitas)
{

	if (kitas == NULL || kitas->Verte_Hash()[0] < this->Verte_Hash()[0])
	{
		return -1;
	}
	if (this->Verte_Hash()[0] < kitas->Verte_Hash()[0])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

string InformacijaEilute::Verte_Hash()
{
	return hash;
}
int InformacijaEilute::Verte_zSkaicius()
{
	return zSkaicius;
};
double InformacijaEilute::Verte_rSkaicius()
{
	return rSkaicius;
};
string InformacijaEilute::Verte_Zodis()
{
	return zodis;
};
