#pragma once
#include "Monitorius.h"
class Gija
{
private:
	int id;
	InformacijaEilute* informacija;
	Monitorius* monitorius;
	int rusiavimas;
public:
	bool Reikalingas();
	bool Pradeti();
	static int gijuSkaicius;
	Gija(Monitorius*, const int);
	int Gauti_Id();
	Monitorius* GautiMonitoriu();
	~Gija();
};

