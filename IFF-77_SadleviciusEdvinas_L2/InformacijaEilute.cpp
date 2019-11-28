#include "InformacijaEilute.h"
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
InformacijaEilute::InformacijaEilute(const InformacijaEilute& nuoroda)
{
	zodis = nuoroda.zodis;
	zSkaicius = nuoroda.zSkaicius;
	rSkaicius = nuoroda.rSkaicius;
	hash = nuoroda.hash;
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
	bool galima = false;
	bool ivykdytas = false;
	string trumpalaikis = "";
	for (unsigned int i = 0; i < zodis.size(); i++)
	{
		if (zodis[i] == '.')
		{
			galima = true;
			continue;
		}
		if (galima && zodis[i] == (0 + '0'))
		{
			trumpalaikis += zodis[i];
		}
		else
		{
			if (galima && !ivykdytas)
			{
				ivykdytas = true;
				trumpalaikis += ".";
			}
			naujas += trumpalaikis + zodis[i];
			trumpalaikis = "";
		}
	}
	return naujas;
};

string InformacijaEilute::Paversti_XML()
{
	//<Projektas pavadinimas="AkademijaTriukams" parduota="87" kaina="90040.14"/>
	string xml = "<Projektas pavadinimas=\"" + zodis + "\" parduota=\"" + to_string(zSkaicius) + "\" kaina=\"" + Pasalinti_nereikalingus_0(to_string(rSkaicius)) + "\"/>";
	return xml;
}
InformacijaEilute InformacijaEilute::Gauti_Is_XML(string info)
{
	xml_document dok;
	dok.load_string(info.c_str());
	xml_node visaInfo = dok.first_child();
	double r = stod(visaInfo.attribute("kaina").value());
	int z = atoi(visaInfo.attribute("parduota").value());
	string pav = visaInfo.attribute("pavadinimas").value();
	return InformacijaEilute(pav,z,r);
}
