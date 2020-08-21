#include "Paroi.hpp"


Paroi :: Paroi(SupportADessin* support_, double coef, double rest, Vecteur n, Vecteur o, Vecteur L, Vecteur l)
:Tapis(support_, coef, rest, n, o),longueur(L), largeur(l)
{	
	unit_longueur = longueur*(1/longueur.norme_vect()); //Vecteur unitaire
	unit_largeur = largeur*(1/largeur.norme_vect()); //Idem
}


Vecteur Paroi :: distance(const Boule* const autre) const
{	
	Vecteur plus_proche(6);
	plus_proche = Tapis::distance(autre) + autre->getRayon(); //Au départ, vecteur plus_proche calculé comme dans Tapis
	
	//Calcul des coordonnées du point le plus proche
	Vecteur lon;
	lon = (plus_proche - origine)*unit_longueur;
	Vecteur lar;
	lar = (plus_proche - origine)*unit_largeur;
	
	//Affectation du calcul de coordonnées
	if(lon.norme_vect()>longueur.norme_vect()){
		plus_proche = plus_proche - (lon - longueur)*unit_longueur;
	}
	if(lon.norme_vect() < 0){
		plus_proche = plus_proche - lon*unit_longueur;
	}
		
	if(lar.norme_vect()>largeur.norme_vect()){
		plus_proche = plus_proche - (lar - largeur)*unit_largeur;
	}
	if(lar.norme_vect() < 0){
		plus_proche = plus_proche - lar*unit_largeur;
	}

	return plus_proche - autre->getomega();
}

double Paroi :: t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision)
{
	//Même déroulement que tapis, sans la condition de plaquage au sol. 
	return Tapis :: t_col_tapisETparoi(autre, t, temps_max, collision);
}


void Paroi :: collision(Boule* const choc)
{
		Tapis::collision(choc); //Même déroulement que pour tapis
}


void Paroi :: affiche() const
{
  std::cout<<"Paroi: "<<std::endl<<"normale: "<<normale<<std::endl<<"originie: "<<origine<<std::endl<<"coef_frt: "<<coef_frt<<std::endl<<
  "rest_ener: "<<rest_ener<<std::endl<<"longueur: "<<longueur <<std::endl<<"unit_longueur: "<<unit_longueur<<std::endl<<"largeur: "<<largeur<<std::endl
  <<"unit_largeur: "<< unit_largeur <<std::endl;
	
}
