#ifndef SYSTEME_HPP_
#define SYSTEME_HPP_

#include <iostream>
#include <vector>
#include <initializer_list>

#include "Vecteur.hpp"
#include "IntegrateurEuler.hpp"
#include "SupportADessin.hpp"
#include "Objet.hpp"
#include "Boule.hpp"
#include "Dessinable.hpp"


class Systeme : public Dessinable
{
	public:
		Systeme(SupportADessin* support_, std::initializer_list<Boule*> const& boules_, std::initializer_list<Objet*> const& system_)
		:Dessinable(support_), boules(boules_), system(system_)
		{}
		void evolue(double t, double temps_max, IntegrateurEuler collision); //Gestion et évolution du jeu de billard
		void affiche() const;
		void dessine() {support->dessine(this);}


	private:
		std::vector<Boule*> boules;
		std::vector<Objet*> system;

};

#endif
