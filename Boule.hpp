#ifndef BOULE_HPP_
#define BOULE_HPP_

#include <cmath>
#include <iostream>

#include "IntegrateurEuler.hpp"
#include "Objet.hpp"


//constantes:
const double gravite (9.81);


class Boule: public Objet{
public:
//constructeur:
	Boule(
	SupportADessin* support_,
	double rayon_,
	double masse_,
	double restitution_,
	double coeff_frt_,
	Vecteur omega_,
	Vecteur omegaP
	);

  
//méthodes:
	
	Vecteur evolution() const; //Calcul l'équation d'évolution des boules selon F=ma et M=I*alpha
	Vecteur distance(const Boule* const autre) const; //retourne le vecteur séparant deux boules
	double t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision); //Temps prochaine collision
	void collision(Boule* const); //Gestion des collisions entre boules
	void dessine();
	std::ostream& affiche(std::ostream& sortie) const; //permet d'afficher Boule
	
	//Getter et setter
    void ajoute_force(Vecteur const& df){force+=df;} //ajoute un Vecteur force à la force de Boule
	void ajoute_force_moment(Vecteur const& mf){force_moment+=mf;} //ajoute un Vecteur moment de force à Boule 
	void set_frt_roul(double frt_roul_){frt_roul=frt_roul_;} //modificateur pour le frotement de roulement
	void set_frt_glis(double frt_glis_){frt_glis=frt_glis_;} //modificateur pour le frotement de glissement
	void setomega(Vecteur const& set);
	void setomegaP(Vecteur const& set);
	void set_comp_omega(double j, size_t i);
	Vecteur get_vect(Vecteur vect, bool cartesienne_ou_angulaire) const; //getter à usage multiple true=>partie cartésienne false=>partie angulaire d'un vecteur de Boule
	
	double getRayon() const {return rayon;} //getter pour le Rayon
	double get_masse() const {return masse;}
	double get_frt_roul(){return frt_roul;} //getter pour le frotement de roulement
	double get_frt_glis(){return frt_glis;} //getter pour le frotement de glissement
	double getCoeff_frt() const {return coeff_frt;}
	double getRestitution() const {return restitution;}
	Vecteur getomega() const {return omega;}
	Vecteur getomegaP() const {return omegaP;}
	double get_comp_omegaP(size_t i){return omegaP[i];}	//Permet d'agir sur une composante
  

private:
    //attributs:
	double rayon;
	double masse;
	Vecteur force;
	Vecteur force_moment;
	double restitution;
	double coeff_frt;
	double frt_roul;
	double frt_glis;
	double volume_boule;
	Vecteur omega;
	Vecteur omegaP;
  
    //méthodes privées:
	double poids() const; //retourne la force d'attraction
	const double masse_volumique (){return (masse/volume_boule);}; //calcule la masse volumique
};

//opérateurs externes:
std::ostream& operator<<(std::ostream& sortie, const Boule& boule);		//surcharge de l'opérateur << pour afficher des Boule

#endif
