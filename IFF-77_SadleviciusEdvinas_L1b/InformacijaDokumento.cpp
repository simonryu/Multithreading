#include "InformacijaDokumento.h"
#include <stdio.h>
InformacijaDokumento::InformacijaDokumento()
{
	likutis = 0;
}
InformacijaDokumento::InformacijaDokumento(const char* failoVieta)
{
	InformacijaDokumento();
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
		cout << setprecision(8) << naujas.Verte_Hash() << endl;
	}
	return true;
}
InformacijaEilute InformacijaDokumento::Gauti_Verte()
{
	if (likutis == 0)
	{
		return InformacijaEilute();
	}
	cout << &informacija[likutis-- - 1] << endl;
	InformacijaEilute gauti = *&informacija[likutis-- - 1];
	paimta_informacija.push_back(InformacijaEilute());
	//return gauti;
	return InformacijaEilute();
}
InformacijaDokumento::~InformacijaDokumento()
{
}
