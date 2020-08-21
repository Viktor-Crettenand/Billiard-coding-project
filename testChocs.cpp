#include <iostream>
#include "Vecteur.hpp"
#include "IntegrateurEuler.hpp"
#include "Boule.hpp"
#include "Support_text.hpp"


using namespace std;


int main()
{

//-----------Test sans vitesse angulaire---------

IntegrateurEuler collision;
//Support_text supp;
// Support_text* p_supp(&supp); //cette partie ne marche pas alors il faut utiliser NULL pour construire des Boules

//Support_text* supp = new Support_text();



Vecteur a(0.,0.,1.,0.,0.,0.);
Vecteur b(1.,0.,2.,0.,0.,0.);


Boule boule1 (NULL, 0.02625,0.127,0.99,0.2,a,b);

Vecteur c(0.08,0.,1.16,0.,0.,0.);
Vecteur d(0.,0.,0.,0.,0.,0.);


Boule boule2 (NULL, 0.02625, 0.127, 0.99, 0.2, c,d);
cout<<"boule1: "<<endl<<boule1<<endl<<"boule2: "<<endl<<boule2<<endl;

cout << "Choc possible au temps : " << boule1.t_collision(&boule2, 0.01, 0.05, collision) << endl;
/*
boule1.collision(&boule2);


//------------Test avec vitesse angulaire-----------------------



Vecteur E(0.,0.,1.,0.,0.,0.);
Vecteur F(1.,0.,2.,0.,0.,0.);

Boule boule3 (NULL, 0.02625,0.127,0.99,0.2,E,F);

Vecteur G(0.08,0.,1.16,0.,0.,0.);
Vecteur H(0.,0.,0.,0.,5.,0.);

Boule* boule4 = new Boule(NULL, 0.02625, 0.127, 0.99, 0.2, G,H);
cout<<"boule3: "<<endl<<boule3<<endl<<"boule4: "<<endl<<*boule4<<endl;

cout << "Choc possible au temps : " << boule3.t_collision(boule4, 0.01, 0.05, collision) << endl;

boule3.collision(boule4);
*/

}
