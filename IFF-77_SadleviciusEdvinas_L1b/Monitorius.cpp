#include "Monitorius.h"



Monitorius::Monitorius(const int dydis, InformacijaDokumento* dok, Rezultatas* rez, const int gijuKiekis)
{
	tuscias = true;
	baigta = false;
	pilnas = false;
	dokumentas = dok;
	rezultatas = rez;
	informacija = new InformacijaEilute[dydis / 2];
}

int Monitorius::RastiTusciaIndeksa()
{
	if (sizeof(informacija) / sizeof(InformacijaEilute) == 0)
	{
		return 0;
	}
	for (unsigned int i = 0; i < sizeof(informacija) / sizeof(InformacijaEilute); i++)
	{
		if (informacija[i].Verte_Zodis().size() == 0)
		{
			return i;
		}
	}
	return -1;
}

bool Monitorius::Pagrindine_Deda_Informacija()
{
	uzraktas_gauti.uzrakinti();
	if (pilnas)
	{
		cout << "Pagrindine gija: Pilnas masyvas" << endl;;
	}
	else if (int indeksas = RastiTusciaIndeksa() < 0)
	{
		cout << "Pagrindine gija: Nera vietos masyve" << endl;
		pilnas = true;
	}
	else
	{
		cout << "Pagrindine gija: idedu informacija" << endl;
		InformacijaEilute nauja_info = dokumentas->Gauti_Verte();
		if (nauja_info.Verte_Hash().size() == 0)
		{
			cout << "Pagrindine gija: Pasibaige, nes gautas tuscias konstruktorius" << endl;
			baigta = true;
		}
		else
		{
			if (tuscias)
			{
				tuscias = false;
			}
			naudojama.push_back(indeksas);
			informacija[indeksas] = nauja_info;
		}
	}
	uzraktas_gauti.atrakinti();
	if (baigta)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Monitorius::Deti_Informacija(InformacijaEilute naujaEilute, int id)
{
	uzraktas_deti.uzrakinti();
	cout << "Gija " << id << ": Vykdau Deti_Informacija()" << endl;
	rezultatas->Ideti_Ir_Rusiuoti(&naujaEilute);
	uzraktas_deti.atrakinti();
	return true;
}

bool Monitorius::Gauti_Informacija(InformacijaEilute* info, int id)
{
	if (baigta && tuscias)
	{
		*info = InformacijaEilute();
		return false;
	}
	if (tuscias)
	{
		return true;
	}
	uzraktas_gauti.uzrakinti();
	if (pilnas)
	{
		pilnas = false;
	}
	if (naudojama.size() == 0)
	{
		tuscias = true;
		cout << "Gija " << id << ": Vykdau Gauti_Informacija(), bet tuscias masyvas" << endl;
		uzraktas_gauti.atrakinti();
		return true;
	}
	else
	{
		cout << "Gija " << id << ": Vykdau Gauti_Informacija()" << endl;;
		int indeksas = naudojama.back();
		naudojama.pop_back();
		*info = informacija[indeksas];
		informacija[indeksas] = InformacijaEilute();
		uzraktas_gauti.atrakinti();
		return false;
	}
}

Monitorius::~Monitorius()
{
	delete[] informacija;
}
