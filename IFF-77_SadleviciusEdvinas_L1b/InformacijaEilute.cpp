#include "InformacijaEilute.h"
#include <stdio.h>
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
	string naujasGautas = zodis + to_string(zSkaicius) + Pasalinti_nereikalingus_0(to_string(rSkaicius));
	string hashNew;
	picosha2::hash256_hex_string(naujasGautas, hashNew);
	return Pakeisti_Teksta_Didziosios_Bruksniai(hashNew);
}

string InformacijaEilute::Pakeisti_Teksta_Didziosios_Bruksniai(string hash)
{
	string naujas = "";
	for (unsigned int i = 0; i < hash.size(); i++)
	{
		if (i != 0 && i % 2 == 0)
		{
			naujas += '-';
		}
		if (isalpha(hash[i]))
		{
			naujas += (char)toupper(hash[i]);
		}
		else
		{
			naujas += hash[i];
		}
	}
	return naujas;
}
InformacijaEilute::~InformacijaEilute()
{
}

int InformacijaEilute::Palyginti(InformacijaEilute* kitas)
{

	if (kitas->Verte_Hash().size() == 0 || kitas->Verte_Hash()[0] < this->Verte_Hash()[0])
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

string InformacijaEilute::Pasalinti_nereikalingus_0(string zodis)
{
	string naujas;
	string trumpalaikis = "";
	for (unsigned int i = 0; i < zodis.size(); i++)
	{
		if (zodis[i] == (0 + '0'))
		{
			trumpalaikis += zodis[i];
		}
		else
		{
			naujas += trumpalaikis + zodis[i];
			trumpalaikis = "";
		}
	}
	return naujas;
};
