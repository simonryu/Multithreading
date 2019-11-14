#include "Besisukantis_Uzraktas.h"


Besisukantis_Uzraktas::Besisukantis_Uzraktas()
{
}


Besisukantis_Uzraktas::~Besisukantis_Uzraktas()
{
}
void Besisukantis_Uzraktas::atrakinti()
{
	uzraktas.clear();
}
void Besisukantis_Uzraktas::uzrakinti()
{
	while (uzraktas.test_and_set());
}
