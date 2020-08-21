#include "Systeme.hpp"

void Systeme :: evolue(double t, double temps_max, IntegrateurEuler collision)
{
	for(size_t i(0); i<temps_max ; i+=t){
//----------Arrêt des boules à très faible énergie cinétique------------------
		for(size_t i(0) ; i<boules.size() ; ++i){
		if(((boules[i]->get_vect(boules[i]->getomegaP(),true) * boules[i]->get_masse()*0.5 + boules[i]->get_vect(boules[i]->getomegaP(),false)*2*boules[i]->get_masse()* boules[i]->getRayon()* boules[i]->getRayon()*(1/5))).norme_vect() < 0.0001){
				Vecteur nul(6) ;
				boules[i]->setomegaP(nul);
				}
				
//---------Calcul des forces --------
			//Calcul force de réaction
			//Tapis a;
			//a.reaction(boules[i]);
			//bizarrement ça ne fonctionne pas. Pourtant on a bien un constructeur par défaut pour Tapis
						
			// calcul de la force de frottement selon 2 cas. 
			Vecteur frot(3);
			Vecteur frot_m(3);
			Vecteur vit_c(3);
			Vecteur normal(0,0,boules[i]->getRayon());
			vit_c = boules[i]->get_vect(boules[i]->getomegaP(), true) + (normal^boules[i]->get_vect(boules[i]->getomegaP(), false)*boules[i]->getRayon()) ; // Vitesse de contact
		
			//Frottement de glissement
			if (vit_c.norme_vect() != 0.){
				frot = (vit_c*(1/vit_c.norme_vect())) * boules[i]->get_frt_glis()*-gravite*boules[i]->get_masse();
				frot_m = frot^(normal*boules[i]->getRayon());
			}else{ //Frottement de roulement
				frot = (boules[i]->get_vect(boules[i]->getomegaP(), true)*(1/(boules[i]->get_vect(boules[i]->getomegaP(), true)).norme_vect()))* boules[i]->get_frt_roul()*gravite*boules[i]->get_masse()*(-1);
				frot_m = boules[i]->get_vect(boules[i]->getomegaP(), false) * (1/(boules[i]->get_vect(boules[i]->getomegaP(), false)).norme_vect())*(boules[i])->get_masse()*(-gravite);
			}
			
			boules[i]->ajoute_force(frot);
			boules[i]->ajoute_force_moment(frot_m);
		}


//------------Calcul permière collision--------

		struct impact { 	// Structure d'écriture du premier choc
			double temps;	
			Boule* percuteur; 
			Objet* obstacle;
		};
		
		impact premier = {t, nullptr,nullptr};

		for(size_t i(0) ; i<system.size() ; ++i){
			for(size_t j(1) ; j<=boules.size() ; ++j){
				if (system[i] != boules[i]){ // Test pour ne pas choquer une boule avec elle-même
					if(system[i]->t_collision(boules[j], t, temps_max, collision)<premier.temps){
						premier.temps = system[i]->t_collision(boules[j],t,temps_max, collision);
						premier.obstacle = system[j];
						premier.percuteur = boules[i];
					}
				}
			}
		}
	

//-------Gestion de collision et avancée du systeme-------

		for(size_t i(0) ; i<boules.size() ; ++i){
			collision.integre(boules[i], premier.temps);
			
		}

		(*premier.obstacle).collision(premier.percuteur);

		for(size_t i(0) ; i<boules.size() ; ++i){
			collision.integre(boules[i], t-premier.temps);
		}
	}
}

void Systeme::affiche() const{
	for(auto element: system){
	element->dessine();	
	}	
}
