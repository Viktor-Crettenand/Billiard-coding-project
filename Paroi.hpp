#ifndef PAROI_HPP_
#define PAROI_HPP_

#include <cmath>
#include <iostream>

#include "IntegrateurEuler.hpp"
#include "Tapis.hpp"

class Objet;
class Boule;
class IntegrateurEuler;

class Paroi : public Tapis
{
	public:
		Paroi(SupportADessin* support_, double coef, double rest, Vecteur n, Vecteur origine, Vecteur L, Vecteur l);
		Vecteur distance(const Boule* const autre) const; //Distance entre une paroi et une boule
		double t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision);	//Temps de la prochaine collision
		void collision(Boule* const choc); //Gestion des collisions
		void dessine() {support->dessine(this);} // Permet d'afficher Paroi via le SupporADessin
		void affiche() const;



	private:
		Vecteur longueur; // ( , , 0)
		Vecteur unit_longueur;
		Vecteur largeur;//( , , )
		Vecteur unit_largeur; //largeur*(1/largeur.norme_vect())
		
		//Vecteur origine en bas à gauche
};

#endif
