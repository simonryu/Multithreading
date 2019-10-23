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
#pragma warning(disable : 4996)
using namespace std;

int Gauti_Giju_Kieki(int);
void Hello(char*);

int main()
{
	const int informacijosDydis = 25;
	const int rusiavimas = 0;
	const bool didejantis = true;
	const char* ivesties_vieta = "IvestiesFailai/IFF77_SadleviciusE_L1_dat_1.xml";
	const char* isviesties_vieta = "IsvestiesFailai/IFF77_SadleviciusE_L1_rez_1.txt";
	int giju_skaicius = Gauti_Giju_Kieki(informacijosDydis);
	InformacijaDokumento dokumentas(ivesties_vieta);
	Rezultatas rez(informacijosDydis, didejantis);
	rez.Ideti_Ir_Rusiuoti(&InformacijaEilute("mew",5,12.5));
	rez.Ideti_Ir_Rusiuoti(&InformacijaEilute("hello", 8, 999.77156));
	rez.Spausdinti_Rezultata();
	/*auto c = 99;
	auto * lock = new omp_lock_t;
	omp_init_lock(lock);
	#pragma omp parallel num_threads(2) private(c)
	{
		c = omp_get_thread_num();
		omp_set_lock(lock);
		printf_s("Hello\n");
		omp_unset_lock(lock);
	}
	printf_s("Baigta\n");
	omp_destroy_lock(lock);*/

	/*OutputInformation output = new OutputInformation(informationSize, ascend);
	NewMonitor monitor = new NewMonitor(informationSize, document, output);
	List<Thread> threads = new List<Thread>();
	OutputInformation output = new OutputInformation(informationSize, ascend);
	NewMonitor monitor = new NewMonitor(informationSize, document, output);

	//Sukuriamos naujos gijos
	for (int i = 0; i < thread_number; i++)
	{
		threads.Add(new Thread(() = >
		{
			CustomThread naujas = new CustomThread(monitor, sort);
			while (naujas.Start());
		}));
	}
	//Paleidžiamos gijos darbui
	foreach(Thread thread in threads)
	{
		thread.Start();
	}
	//Pagrindine gija pradeda pildyti masyvą
	while (monitor.MainIsAddingInformation());

	//Pagrindine gija laukia, kol pabaigs visos jos sukurtos naujos gijos
	foreach(Thread thread in threads)
	{
		thread.Join();
	}
	output.PrintInformation(pathOfOutput);
	Console.WriteLine("Pagrindine gija: Baigiau darba ir sulaukiau visu vaiku");*/
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
		printf(klaida);
		return Gauti_Giju_Kieki(kiekis);
	}
}

void Hello(char* vardas)
{
	printf(vardas);
}

