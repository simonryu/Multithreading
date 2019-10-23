#include "InformacijaDokumento.h"
#include <stdio.h>
#pragma warning(disable : 4996)
InformacijaDokumento::InformacijaDokumento()
{
	likutis = 0;
}
InformacijaDokumento::InformacijaDokumento(const char* failoVieta)
{
	InformacijaDokumento();
	//cout << "Load result: " << rezultatas.description() << ", mesh name: " << doc.child("Projektai").child << endl;
	if (dok.load_file((char*)failoVieta))
	{
		printf("Reading from file\n");
		if (Saugoti_Informacija())
		{
			printf("File reading completed\n");
		}
		else
		{
			printf("Could not read file.\nError: %s", klaida);
		}

	}
	else
	{
		printf("Could not read file.\nError: %s", klaida);
	}
}

bool InformacijaDokumento::Saugoti_Informacija()
{
	pugi::xml_node projektai = dok.child("Projektai");
	for (pugi::xml_node projektas = projektai.child("Projektas"); projektas; projektas = projektas.next_sibling("Projektas"))
	{
		double n;
		sscanf_s(projektas.attribute("kaina").value(), "%Lg", &n);
		likutis++;
		InformacijaEilute naujas(projektas.attribute("pavadinimas").value(), atoi(projektas.attribute("parduota").value()), n);
		informacija.push_back(naujas);
	}
	return true;
}
InformacijaDokumento::~InformacijaDokumento()
{
}
