#include <iostream>
#include "Systeme.hpp"
#include "Vecteur.hpp"
#include "IntegrateurEuler.hpp"
#include "Boule.hpp"
#include "Support_text.hpp"

using namespace std;

int main(){
	Vecteur vect1(1.,1.,1.,0.,0.,0.);
	Vecteur vect2(1.,1.1,5.,0.,0.,0.);
	Vecteur vect3(0.,1.1,1.2,8.,0.,0.);
	Vecteur vect4(6,0.);
	
	IntegrateurEuler integrateur;
	
	Support_text* supp = new Support_text();
	
	Boule* boule1= new Boule(supp/*référence sur un SupportADessin*/, 2./*rayon*/,4./*masse*/,1./*restitution*/, 1./*coeff_frt*/,vect1/*omega*/,vect4/*omegaP*/);
	Boule* boule2= new Boule(supp/*référence sur un SupportADessin*/, 2./*rayon*/,4./*masse*/,1./*restitution*/, 1./*coeff_frt*/,vect2/*omega*/,vect4/*omegaP*/);
	Boule* boule3= new Boule(supp/*référence sur un SupportADessin*/, 2./*rayon*/,4./*masse*/,1./*restitution*/, 1./*coeff_frt*/,vect3/*omega*/,vect4/*omegaP*/);
	
	
	Systeme sys(supp,{boule1,boule2,boule3} /*std::initializer_list<Boule*> const& boules_*/, {}/*initializer_list<Objet*> const& system_*/);
	
	//sys.dessine();
	
	double pas_de_temps(0.01);
	sys.evolue(0.01,0.1,integrateur);
	sys.dessine();

	
	cout<<endl<<"à comparer avec: "<<endl; //nous comparons les résultats à ceux obtenu avec les intégrateurs pour nous assurer que les chocs on bien eu lieu
	
	
	for(int i(1);i<11;++i)
	{
	integrateur.integre(boule1, pas_de_temps);
	integrateur.integre(boule1, pas_de_temps);
	integrateur.integre(boule1, pas_de_temps);
	cout<<"Au temps "<<i*pas_de_temps<<": "<<boule1<<endl;
	}
	
	
return 0;
}

