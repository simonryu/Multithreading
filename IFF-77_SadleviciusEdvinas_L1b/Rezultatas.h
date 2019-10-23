#pragma once
#include "InformacijaEilute.h"
class Rezultatas
{
private:
	InformacijaEilute* rezultatai;
	bool didejantis;
	int dydis;
public:
	int Verte_Dydis();
	void Spausdinti_Rezultata();
	bool Ideti_Ir_Rusiuoti(InformacijaEilute*);
	bool Perdeti_Elementa(InformacijaEilute*,int);
	Rezultatas();
	Rezultatas(int,bool);
	~Rezultatas();
};

