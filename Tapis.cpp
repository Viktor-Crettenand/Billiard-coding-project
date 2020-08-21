#include "Tapis.hpp"

Tapis :: Tapis(SupportADessin* support_, double coef, double rest, Vecteur n, Vecteur o)
	:Objet(support_), coef_frt(coef), rest_ener(rest), normale(n), origine(o)
	{}

Vecteur Tapis :: distance(const Boule* const autre) const
{
	Vecteur plus_proche(6);
	plus_proche = autre->getomega() + normale*((origine-autre->getomega())*normale);
	return plus_proche - autre->getRayon();
} 

void Tapis :: reaction(Boule& boule) 
{
  if((boule.get_comp_omegaP(2)<0.01) & (distance(&boule).norme_vect() < 0.001)){ // la boule est sur le sol. 
		boule.set_frt_roul(coef_frt*boule.getCoeff_frt());// on initialise ses frottement de roulement et de glissement
		boule.set_frt_glis(coef_frt*boule.getCoeff_frt());
		double poids;
		poids = boule.get_masse()*gravite; //force de réaction verticale
		Vecteur a(0, 0, poids);
		boule.ajoute_force(a);
		boule.set_comp_omega(boule.getRayon(),2);
	}else{ //la boule ne touche pas la table, donc on met ses coefficient de frottement à 0.
		boule.set_frt_roul(0);
		boule.set_frt_glis(0);
	}
}

double Tapis :: t_col_tapisETparoi(Boule* const autre, double t, double temps_max, IntegrateurEuler collision)
{
	Vecteur dist_in;
	dist_in = distance(autre); 
	Vecteur dist_fin;
	collision.integre(autre, t);
	dist_fin = distance(autre);
	
	//Conditions de choc
	double tau(0); //nombre de pas de temps pour la collision
	if((dist_fin.norme_vect()<autre->getRayon()) or dist_in*dist_fin>0){
		tau = (autre->getRayon() - normale*dist_in)/(normale*dist_fin - normale*dist_in);
	}
		
	return tau*temps_max;
}
double Tapis :: t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision)
{
	//Pour une énergie cinétique faible, la boule est plaquée au sol.
	if((autre->getomegaP()*autre->getomegaP()*autre->get_masse()*0.5)+(autre->getomegaP()*autre->getomegaP()*2*autre->get_masse()*autre->getRayon()*autre->getRayon()*(1/5)*0.5)){
		autre->set_comp_omega(0, 2);
	}

	return t_col_tapisETparoi(autre, t, temps_max, collision);
}

void Tapis :: collision(Boule* const choc)
{
	if(distance(choc).norme_vect()<=choc->getRayon()){ //Condition de choc

		//Calcul des coefficients 
		double restitution_(rest_ener*choc->getRestitution());
		double coeff_frt_(coef_frt*choc->getCoeff_frt()) ;
		double lambda;
		lambda = 0;

		//Vitesses cartésienne et de contact de la boule avec le tapis
		double vit_cart; 
		vit_cart = choc->get_vect(choc->getomegaP(),true)*normale;
		Vecteur vit_contact;
		vit_contact = choc->get_vect(choc->getomegaP(),true) + normale*vit_cart + (normale^choc->get_vect(choc->getomegaP(),false)*choc->getRayon());

		//Différences de vitesses calculées
		Vecteur deltaV_cart;
		Vecteur deltaV_ang; 

		if((vit_cart*(7*coeff_frt_*(1+restitution_)))>vit_contact.norme_vect()){
			deltaV_cart = normale*(lambda*vit_cart) - vit_contact*(2/7);
			deltaV_ang = (normale^vit_contact)*(5/(7*choc->getRayon()));
		}
		else{
			deltaV_cart = (normale - (vit_contact*((1/(vit_contact).norme_vect()*coeff_frt_)))*lambda*vit_cart);
			deltaV_ang = ((normale^(vit_contact*(1/(vit_contact).norme_vect())))*5*coeff_frt_*lambda*vit_cart*(1/(2*choc->getRayon())));
		}

		//Affectation des résultat à la boule
		choc->setomegaP(choc->get_vect(choc->getomegaP(),true) + (deltaV_ang).concatener(deltaV_cart));
	}
}

void Tapis :: affiche() const{
	std::cout<<"Tapis: "<<std::endl<<"normale: "<<normale<<std::endl<<"originie: "<<origine<<std::endl<<"coeff_frt: "<<coef_frt<<std::endl<<
	"rest_ener: "<<rest_ener<<std::endl;
}
