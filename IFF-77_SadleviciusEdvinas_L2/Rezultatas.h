#pragma once
#include "InformacijaEilute.h"
class Rezultatas
{
private:
	InformacijaEilute* rezultatai;
	bool Perdeti_Elementa(InformacijaEilute, int);
	bool didejantis;
	int dydis;
public:
	void Atspausdinti();
	int Verte_Dydis();
	string Gauti_Informacija();
	bool Ideti_Ir_Rusiuoti(InformacijaEilute);
	Rezultatas(int,bool);
	~Rezultatas();
};

