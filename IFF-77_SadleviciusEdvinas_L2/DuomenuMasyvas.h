#pragma once
#include "InformacijaDokumento.h"
#include "Rezultatas.h"
#include "InformacijaEilute.h"
#include <vector>
class DuomenuMasyvas
{
private:
	InformacijaEilute* informacija;
	bool pilnas;
	bool tuscias;
	int RastiTusciaIndeksa();
	int RastiNetusciaIndeksa();
	int dydis;
public:
	void Atspausdinti();
	DuomenuMasyvas(const int);
	bool Ideti_Informacija(InformacijaEilute);
	InformacijaEilute Pasalinti_Informacija();
	~DuomenuMasyvas();
};

