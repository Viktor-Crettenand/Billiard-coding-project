#ifndef Objet_HPP
#define Objet_HPP

#include "Dessinable.hpp"
#include "Vecteur.hpp"


class Boule;
class IntegrateurEuler;

class Objet : public Dessinable {
	public: 
		Objet(SupportADessin* support_): Dessinable(support_) {}
		virtual ~Objet(){}
		//méthodes:
		virtual Vecteur distance(const Boule* const objet) const = 0; //Plus courte distance entre un objet et une boule
		virtual double t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision)=0; //Temps de la prochaine collision
		virtual void collision(Boule* const) = 0; //Gestion des collisions
		virtual void dessine()=0; //Utilisée pour faire apparaître les objets par le SupportADessin
};

#endif //Objet_HPP
