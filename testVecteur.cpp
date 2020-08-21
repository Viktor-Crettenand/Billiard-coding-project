#include "Vecteur.hpp"
#include <iostream>

using namespace std;

int main()
{

Vecteur vect1(1.,2.,3.);
Vecteur vect2(vect1);
Vecteur vect3;
Vecteur vect4({2.1,5.4,6.,3.,5.0});
Vecteur vect11(0.,0.,0.,0.,0.,0.);


cout<<vect1<<endl<<vect2<<endl<<vect3<<endl<<vect4<<endl<<vect11<<endl;



vect1.augmente(1.0);
cout<<vect1<<endl;
vect1.augmente(2.0);
cout<<vect1<<endl; 
vect1.augmente(-0.1); 
cout<<vect1<<endl;
vect2.augmente(2.6);
cout<<vect2<<endl; 
vect2.augmente(3.5);
cout<<vect2<<endl; 
vect2.augmente( 4.1); 
cout<<vect2<<endl;
vect3 = vect1;
cout<<vect3<<endl;
cout<<vect1<<endl;



//Test du constructeur
Vecteur vect0({0.0, 0.0, 0.0}); 
Vecteur vect5({1.2, 3.5});

cout<<vect0<<endl<<vect5<<endl;


//Test surcharge des opérateurs:

Vecteur vect6(3,1);
Vecteur vect7(1,2,3);

cout<<vect6<<"	"<<vect7<<endl;

cout<<"vect6+vect7: "<<vect6+vect7<<endl
	<<"-vect6: "<< -vect6<<endl
	<<"vect6^vect7"<<(vect6^vect7)<<endl;

return 0;
}






