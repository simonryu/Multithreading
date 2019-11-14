#pragma once
#include "InformacijaDokumento.h"
#include "Rezultatas.h"
#include "InformacijaEilute.h"
#include "Besisukantis_Uzraktas.h"
#include <vector>
class Monitorius
{
private:
	InformacijaEilute** informacija;
	InformacijaDokumento* dokumentas;
	Rezultatas* rezultatas;
	vector<int> naudojama;
	vector<bool> giju_leidimas_ideti;
	vector<bool> giju_leidimas_isimti;
	vector<int> giju_laukimas_ideti;
	vector<int> giju_laukimas_isimti;
	bool baigta;
	bool pilnas;
	bool tuscias;
	Besisukantis_Uzraktas uzraktas_deti;
	Besisukantis_Uzraktas uzraktas_gauti;
	int RastiTusciaIndeksa();
	int dydis;
public:
	Monitorius(const int, InformacijaDokumento*,Rezultatas*);
	bool Pagrindine_Deda_Informacija();
	bool Deti_Informacija(InformacijaEilute*&,int);
	bool Gauti_Informacija(InformacijaEilute*&, int);
	~Monitorius();
};

