#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <omp.h>
#include <stdio.h>
#include <string>
#include "Rezultatas.h"
#include "InformacijaDokumento.h"
#include "pugixml.hpp"
#include "Monitorius.h"
#include "Gija.h"
using namespace std;
int Gija::gijuSkaicius = 0;
int Gauti_Giju_Kieki(int);

int main()
{
	const int informacijosDydis = 25;
	const int rusiavimas = 0;
	const bool didejantis = true;
	const char* ivesties_vieta = "IvestiesFailai/IFF77_SadleviciusE_L1_dat_1.xml";
	const char* isviesties_vieta = "IsvestiesFailai/IFF77_SadleviciusE_L1_rez_1.txt";
	int giju_skaicius = Gauti_Giju_Kieki(informacijosDydis) + 1;
	InformacijaDokumento dokumentas(ivesties_vieta);
	Rezultatas rez(informacijosDydis, didejantis);
	Monitorius monitorius(informacijosDydis, &dokumentas, &rez, giju_skaicius);
	#pragma omp parallel num_threads(giju_skaicius)
	{
		if (omp_get_thread_num() == 0)
		{
			while (monitorius.Pagrindine_Deda_Informacija());
		}
		else
		{
			Gija naujas(&monitorius, rusiavimas);
			while(naujas.Pradeti());
		}
	}

	rez.Spausdinti_Rezultata(isviesties_vieta);
	printf("Pagrindine gija: Baigiau darba ir sulaukiau visu vaiku");
	return 0;
}

int Gauti_Giju_Kieki(int kiekis)
{
	int naujasKiekis = kiekis / 4;
	printf("Pasirinkite giju kieki(2 <= gijuKiekis <= %d)\n", naujasKiekis);
	try
	{
		int giju_skaicius;
		cin >> giju_skaicius;
		system("CLS");
		if (giju_skaicius >= 2 && giju_skaicius <= naujasKiekis)
		{
			return giju_skaicius;
		}
		else
		{
			throw "Klaida: parinktas per mazas arba per didelis giju kiekis\n";
		}
	}
	catch (const char* klaida)
	{
		printf("%s", klaida);
		return Gauti_Giju_Kieki(kiekis);
	}
}

