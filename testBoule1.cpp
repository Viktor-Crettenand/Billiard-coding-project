#include <iostream>
#include "Support_text.hpp"
#include "Boule.hpp"

using namespace std;

int main(){
	Vecteur vect1(6,0.);
	Vecteur vect2(6,0.);
	Vecteur vect3(6,0.);
	Vecteur vect4(6,0.);
	Vecteur vect5(1.2,3.4,5.,2.,3.,4.);
	
	
	Boule boule1(NULL/*&support*//*référence sur un SupportADessin*/, 2./*rayon*/,4./*masse*/,1./*restitution*/, 1./*coeff_frt*/,vect1/*omega*/,vect2/*omegaP*/);
	Boule boule2(NULL/*&support*//*référence sur un SupportADessin*/, 1./*rayon*/,3./*masse*/,1.4/*restitution*/, 1.3/*coeff_frt*/,vect5/*omega*/,vect5/*omegaP*/);
	
	cout<<boule1<<endl;
	
	boule1.ajoute_force(vect5);
	cout<<boule1<<endl;	
	boule1.set_frt_glis(4.);
	cout<<boule1<<endl;
	boule2.distance(&boule1);
	
	
return 0;
}
