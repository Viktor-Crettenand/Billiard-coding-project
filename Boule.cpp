#include "Boule.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979932384
#endif //M_PI

using namespace std;


//classe Boule:
//constructeurs:
Boule::Boule(
	SupportADessin* support_,
	double rayon_,
	double masse_, 
	double restitution_,
	double coeff_frt_,
	Vecteur omega_=Vecteur(6,0.),
	Vecteur omegaP_=Vecteur(6,0.)) 
	:Objet(support_), force(),force_moment()
{
	rayon=rayon_;
	volume_boule=(4.0/3.0 * M_PI*pow(rayon, 3)); 
	masse=masse_;
	restitution=restitution_;
	coeff_frt=coeff_frt_;
	frt_roul=0.;
	frt_glis=0.;
	omega=omega_;
	omegaP=omegaP_;
	force[2] = poids();
	
}	

//méthodes:

Vecteur Boule::evolution() const
{
	return ((force_moment *(1/(2*masse*rayon*rayon/5))).concatener(force*(1/ masse))); // acc. = F/m ; acc. ang. = Mom_force/I
}

Vecteur Boule::distance(const Boule* const autre) const
{
	//Calcul la distance entrouvant les deux points les plus proche l'un de l'autre des deux boules
	Vecteur res1; 
	Vecteur res2;
	res1 = get_vect(omega,true) + ((autre->get_vect(omega,true)-get_vect(omega,true))*(1/(autre->get_vect(omega,true)-get_vect(omega,true)).norme_vect()))*rayon;
	res2 = autre->get_vect(omega,true) +((get_vect(omega,true)-autre->get_vect(omega,true))*(1/(get_vect(omega,true)-autre->get_vect(omega,true)).norme_vect()))*autre->rayon;
    return res2-res1;
}

double Boule:: t_collision(Boule* const autre, double t, double temps_max, IntegrateurEuler collision)
{
	for(double i(0) ; i<1 ; i+=t){
//------------------les deux boules sont mobiles------------------

	//Positions initiales
	Vecteur x1(autre->getomega());
	Vecteur x2(getomega());
	
	//Les boules évoluent d'un pas de temps si elles sont mobiles
	if(not (omegaP == Vecteur(6)))
	{
		collision.integre(this, t);
	} 
	if(not (autre->omegaP == Vecteur(6))){	
		collision.integre(autre, t); 
	}  
	                                                                                                                                                                                                                
	//Positions après un pas de temps                                                                                                                                                                                                                                           
	Vecteur x1_(autre->getomega());
	Vecteur x2_(getomega());   

	 
	//Calcul coefficient second degré
	Vecteur a (x2 - x1);
	Vecteur b(x2_ - x1_ -a);
	double A(b.norme2_vect());
	double B(b*a*2);
	double C(a.norme2_vect()-(rayon+autre->rayon)*(rayon+autre->rayon));

	//Résolution équation second degré
	try{
		double delta = B*B -4*A*C;
		double res1;
		double res2;
		
	
	if(delta < 0) { 
		throw int(4);
	}
		
	if (delta == 0)
	{
		res1 = -B/(2*A);
		if(res1>=0 and res1<1)
		{
			return res1*temps_max;
		}
	}else{
		res1 = (-B+sqrt(delta))/(2*A);
		res2 = (-B-sqrt(delta))/(2*A);
		if(res2<1 and res1>res2 and res2>=0){ 
			return res2*temps_max;
		}
		if(res1<1 and res2>res1 and res1>=0)
		{
			return res1*temps_max;
		}
	}
	}

	catch(int)
	{
		cout << "Delta négatif, racine complexes!!!"<< endl;
	}
	
//---------------------------Deux figures de cas où une des boules est à l'arrêt----------------------
	double temps;
	Vecteur normal; 
	normal = (autre->get_vect(omega,true)-get_vect(omega,true))*(1/(autre->get_vect(omega,true)-get_vect(omega,true)).norme_vect());
	
	//[1] L'autre boule est à l'arrêt
	if(not(omegaP == Vecteur(6)) and autre->omegaP == Vecteur(6)) // Test si l'instance courante est à l'arrêt
	{
		Vecteur D_ini;
		D_ini = distance(autre);
		collision.integre(this, t); 
		Vecteur D_fin;
		D_fin = distance(autre);
		if(D_fin.norme_vect() < rayon or D_ini*D_fin < 0.)
		{
			temps=(autre->rayon - (normal*D_ini))/((normal*D_fin)-(normal*D_ini));
			return temps*temps_max;
	
		}
	}
	 
	//[2]l'instance courante est à l'arrêt
	Vecteur D_ini;
	D_ini = distance(autre);
	collision.integre(autre, t);
	Vecteur D_fin;
	D_fin = distance(autre);
	if(D_fin.norme_vect()<rayon or D_ini*D_fin<0){
		temps=(autre->rayon - (normal*D_ini))/((normal*D_fin)-(normal*D_ini));
		return temps*temps_max;
	}	
}
return -1.0; //Cela montre que nous ne sommes pas dans une situation cohérent de choc, car il ne peut pas y avoir de temps négatif. 
}
	

void Boule :: collision(Boule* const choc)
{
	if((omega-choc->omega).norme_vect()<=(rayon+choc->rayon)){//condition de choc
		
		//Calcul des coefficients
		double restitution_(restitution*choc->restitution);
		double coeff_frt_(coeff_frt*choc->coeff_frt);
		double lambda;
		lambda = (1+restitution_)*choc->masse/(masse*choc->masse);
		
		//Normale, vitesses cartésiennes et de contact nécessaires à la gestion des chocs
		Vecteur normal ;
		normal = (choc->get_vect(omega,true)-get_vect(omega,true))*(1/(choc->get_vect(omega,true)-get_vect(omega,true)).norme_vect());
		double vit_cart;
		vit_cart = (get_vect(omegaP,true)-choc->get_vect(omegaP,true))*normal;
		Vecteur vit_contact;
		vit_contact = choc->get_vect(omegaP,true)-get_vect(omegaP,true) + normal*vit_cart + (normal^(get_vect(omegaP,false)*rayon + choc->get_vect(omegaP,false)*choc->rayon));
		
		
		//Différences de vitesses à calculées
		Vecteur deltaV_cart;
		Vecteur deltaV_ang;
		
		if((vit_cart*(7*coeff_frt_*(1+restitution_)))>vit_contact.norme_vect()){
			deltaV_cart = normal*(lambda*vit_cart) - vit_contact*(2*masse/(7*(masse+choc->masse)));
			deltaV_ang = (normal^vit_contact)*((5*masse)/(7*rayon*(masse+choc->masse)));
		}
		else{
			deltaV_cart = (normal - (vit_contact*((1/(vit_contact).norme_vect()*coeff_frt_)))*lambda*vit_cart);
			deltaV_ang = ((normal^(vit_contact*(1/(vit_contact).norme_vect())))*5*coeff_frt_*lambda*vit_cart*(1/(2*choc->rayon)));
		}
		
		//On affecte les changements calculés aux boules
		setomegaP(getomegaP() + deltaV_ang.concatener(deltaV_cart));
		choc->setomegaP(choc->get_vect(omegaP,true) + (deltaV_ang*((masse*rayon)/(choc->masse*choc->rayon))).concatener(deltaV_cart*(masse/choc->masse)));
	
}
}

void Boule :: dessine(){ support->dessine(this);} //permet d'afficher Boule grace à son SupportADessin

ostream& Boule :: affiche(ostream& sortie) const
{
	sortie << "rayon: "<<rayon<<" masse: "<<masse<<endl<<"Force: "<< force<<endl<<"restitution: "
	<<restitution<<" coeff_frt: "<<coeff_frt<<endl<<" omega: "<< omega<<endl<<" omega´: "<<omegaP<<endl;
	return sortie;
}

//Getters et setters

void Boule:: setomega(Vecteur const& set)
{
	size_t taille_set(set.getsize());
	size_t taille_vect(omega.getsize());

	try{
	if(taille_set != taille_vect){
		throw size_t(taille_vect);
	}
	} catch(size_t taille){
		cerr << "Le vecteur entré en paramètre n'a pas la bonne taille ! " << endl
			 << "Merci d'introduire un vecteur de taille " 
			 << taille << endl;
	}
	for(size_t i(0); i<taille_vect;++i)
		omega[i]=set[i];
}


void Boule :: setomegaP(Vecteur const& set)
{
	size_t taille_set(set.getsize());
	size_t taille_vect(omegaP.getsize()); 
	try{
	  if(taille_set != taille_vect)
	  throw size_t(taille_vect);
	}
	catch(size_t taille){
		cerr << "Le vecteur entré en paramètre n'a pas la bonne taille ! " << endl
			 << "Merci d'introduire un vecteur de taille " 
			 << taille << endl;
	}
	for(size_t i(0); i<taille_vect; ++i)
		omegaP[i]=set[i];
}

void Boule :: set_comp_omega(double j, size_t i)
{
	omega[i] = j;
}

Vecteur Boule::get_vect(Vecteur vect, bool cartesienne_ou_angulaire) const{ 
	Vecteur res;
	size_t a;
	if(cartesienne_ou_angulaire)
	a=0;
	else
	a=3;
	for(size_t i(a);i<=a+3;++i){
		res[i]=vect[i];
	}
	return res;
}


//méthodes privées:

double Boule:: poids() const
{
    return -masse*gravite; 
}


//opérateurs externes:

ostream& operator<<(ostream& sortie,const Boule&  boule)
{
	return boule.affiche(sortie);
}
