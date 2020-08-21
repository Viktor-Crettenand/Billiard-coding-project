#ifndef IntegrateurEuler_HPP
#define IntegrateurEuler_HPP

#include "Integrateur.hpp"


class IntegrateurEuler : public Integrateur
{
	public:
		void integre(Boule* const boule1, double pas_de_temps);
};

#endif //IntegrateurEuler_HPP
