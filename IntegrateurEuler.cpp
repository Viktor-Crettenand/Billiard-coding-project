#include "IntegrateurEuler.hpp"

class Vecteur;
void IntegrateurEuler :: integre(Boule* const boule1, double pas_de_temps)
{
	Vecteur tmp1(boule1->getomegaP() + (boule1->evolution())*pas_de_temps);
	Vecteur tmp2(boule1->getomega() + (tmp1*pas_de_temps));
	
	boule1->setomegaP(tmp1);
	boule1->setomega(tmp2);
}

