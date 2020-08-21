#include <iostream>
#include "Vecteur.hpp"
#include "IntegrateurEuler.hpp"
#include "Boule.hpp"


using namespace std;


int main()
{
	//test de l'intégrateur sur l'exemple donné dans la documentation du projet
	IntegrateurEuler integrateur;
	cout<<"Situation de départ :"<<endl<<
	"0.127 # masse"<<endl<<
	"0.02625 # rayon"<<endl<<
	"1676.21 # masse volumique"<<endl<<
	"0 0 1 # position"<<endl<<
	"0 0 0 # angles"<<endl<<
	"1 0 2 # vitesse "<<endl<<
	"0 0 0 # vitesse angulaire"<<endl<<
	"0 0 -1.24587 # force "<<endl<<endl;
	Vecteur a(0.,0.,1.,0.,0.,0.);
	Vecteur b(1.,0.,2.,0.,0.,0.);
	
	Boule boule1 (NULL, 0.02625,0.127,1,1,a,b);
	Boule* boo (&boule1);
	double pas_de_temps (0.01);
	for(int i(1);i<11;++i)
	{
	integrateur.integre(boo, pas_de_temps);
	cout<<"Au temps "<<i*pas_de_temps<<": "<<boule1<<endl;
	}

	//les valeurs obtenue correspondent au résultats donnés dans la documentation
}
