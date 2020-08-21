#ifndef INTEGRATEUR_HPP
#define INTEGRATEUR_HPP

#include "Boule.hpp"

class Boule;

class Integrateur {
	public:
		virtual void integre(Boule* const boule1, double pas_de_temps) = 0; 
		virtual ~Integrateur(){}
};

 
#endif //INTEGRATEUR_HPP
