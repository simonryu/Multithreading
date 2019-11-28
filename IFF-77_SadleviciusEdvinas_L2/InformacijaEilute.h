#pragma once
#include "picosha2.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "pugixml.hpp"
using namespace std;
using namespace pugi;
class InformacijaEilute
{
private:
	string zodis;
	int zSkaicius;
	double rSkaicius;
	string hash;
	string SukurtiHash();
	string Pakeisti_Teksta_Didziosios_Bruksniai(string);
	string Pasalinti_nereikalingus_0(string);
public:
	static InformacijaEilute Gauti_Is_XML(string);
	string Paversti_XML();
	InformacijaEilute();
	InformacijaEilute(const InformacijaEilute&);
	InformacijaEilute(string,int,double);
	int Palyginti(InformacijaEilute*);
	string Verte_Hash();
	int Verte_zSkaicius();
	double Verte_rSkaicius();
	string Verte_Zodis();
	~InformacijaEilute();
};

