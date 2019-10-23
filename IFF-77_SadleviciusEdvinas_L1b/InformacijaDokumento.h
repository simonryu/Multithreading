#pragma once
#include <iostream>
#include <vector>
#include "InformacijaEilute.h"
#include "pugixml.hpp"
using namespace std;

class InformacijaDokumento
{
private:
	pugi::xml_document dok;
	vector<InformacijaEilute> informacija;
	vector<InformacijaEilute> paimta_informacija;
	bool Saugoti_Informacija();
	int likutis;
	char* klaida;
public:
	InformacijaDokumento();
	InformacijaDokumento(const char* failas);
	~InformacijaDokumento();
};
