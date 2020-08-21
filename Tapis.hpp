#ifndef TAPIS_HPP_
#define TAPIS_HPP_

#include <iostream>

#include "IntegrateurEuler.hpp"
#include "Objet.hpp"



class Tapis : public Objet 
{
	public:
		Tapis(SupportADessin* support_ = nullptr, double coef = 0.0, double rest = 0.0, Vecteur n = Vecteur(0,0,1), Vecteur origine = Vecteur(0,0,0)); 
		void reaction(Boule&); //Calcul la force de réaction
		Vecteur distance(const Boule* const autre) const; //Plus courte distance entre une boule et un tapis
		double t_col_tapisETparoi(Boule* const autre, double t, double temps_max, IntegrateurEuler collision); //Calcul commun à Paroi et Tapis
		double t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision); //Temps de la prochaine collision
		void collision(Boule* const choc) ; //Gestion des chocs
		void dessine() {support->dessine(this);} //Affiche Tapis sur SupportADessin
		void affiche() const; //Affiche Tapis
	
	
	protected:
		double coef_frt;
		double rest_ener;
		Vecteur normale; // (0,0,1)
		Vecteur origine; // (0,0,0) par défaut
};

#endif
