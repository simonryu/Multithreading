#include "InformacijaDokumento.h"
#include <stdio.h>
InformacijaDokumento::InformacijaDokumento()
{
	likutis = 0;
}
InformacijaDokumento::InformacijaDokumento(const char* failoVieta)
{
	likutis = 0;
	if (dok.load_file((char*)failoVieta))
	{
		printf("Skaitoma is failo\n");
		if (Saugoti_Informacija())
		{
			printf("Failo skaitymas baigtas\n");
		}
		else
		{
			printf("Nepavyko skaityti failo.\nError: %s", klaida);
		}

	}
	else
	{
		printf("Nepavyko atidaryti failo.\nError: %s", klaida);
	}
}

bool InformacijaDokumento::Saugoti_Informacija()
{
	pugi::xml_node projektai = dok.child("Projektai");
	for (pugi::xml_node projektas = projektai.child("Projektas"); projektas; projektas = projektas.next_sibling("Projektas"))
	{
		double n = stod(projektas.attribute("kaina").value());
		likutis++;
		InformacijaEilute naujas(projektas.attribute("pavadinimas").value(), atoi(projektas.attribute("parduota").value()), n);
		informacija.push_back(naujas);
		cout << naujas.Verte_Hash() << endl;
	}
	return true;
}
InformacijaEilute* InformacijaDokumento::Gauti_Verte()
{
	if (likutis == 0)
	{
		return NULL;
	}
	InformacijaEilute* gauti = &informacija[likutis-- - 1];
	paimta_informacija.push_back(*gauti);
	return gauti;
}
InformacijaDokumento::~InformacijaDokumento()
{
	informacija.clear();
	paimta_informacija.clear();
}
