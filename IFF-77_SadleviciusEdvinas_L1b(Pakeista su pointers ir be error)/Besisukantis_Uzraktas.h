#pragma once
#include <atomic>
class Besisukantis_Uzraktas
{
private:
std::atomic_flag uzraktas = ATOMIC_FLAG_INIT;
public:
	Besisukantis_Uzraktas();
	void uzrakinti();
	void atrakinti();
	~Besisukantis_Uzraktas();
};
