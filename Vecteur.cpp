#include "Vecteur.hpp"


using namespace std;

//classe Vecteur:


//constructeurs:

Vecteur :: Vecteur(Vecteur const& copie)
{
	
	size_t taille(copie.position.size());
	for(size_t i (0); i<taille; ++i){
	position.push_back(0);
	}
	for(size_t i (0); i<taille; ++i){
	position[i]=copie.position[i]; 
	}
}


Vecteur :: Vecteur(size_t taille, double x)
{
	for(size_t i (0); i<taille; ++i){
	position.push_back(x);
	}
}

Vecteur :: Vecteur(double x, double y, double z)
{
	position.push_back(x);
	position.push_back(y);
	position.push_back(z);
}

Vecteur :: Vecteur(double x, double y, double z,double a,double b,double c)
{
	position.push_back(x);
	position.push_back(y);
	position.push_back(z);
	position.push_back(a);
	position.push_back(b);
	position.push_back(c); 
}

Vecteur :: Vecteur(const initializer_list <double>& liste)
{
	for (auto a : liste) {position.push_back(a);}
	
}


//opérateurs:

//addition
Vecteur Vecteur :: operator+(Vecteur const& autre) const
{
	size_t n = position.size();
	Vecteur res(n);	
	try
		{
		  if(autre.position.size() != n){
		  throw int(n);
	      }
          for(size_t i(0); i<=n; ++i){
            res.position[i]= autre.position[i]+position[i];
		  }
        }
        
    catch(int taille)
    {
        cerr << "Le vecteur entré en paramètre n'a pas la bonne taille ! " << endl
			 << "L'addition ne peut pas avoir lieu. Merci d'introduire un vecteur de taille " 
			 << taille << endl;
    }
    return res;
}

//soustraire
const Vecteur Vecteur :: operator-(Vecteur const& autre) const
{
	Vecteur vect(0);
	try{
		if(position.size()!=autre.position.size()){
			throw int(position.size());
		}
			
		for(size_t i (0); i<position.size(); ++i){
			vect.position.push_back(position[i]-autre.position[i]);
		}
		
	}

	catch(int taille){
		cerr << "Le vecteur entré en paramètre n'a pas la même taille que l'objet ! " << endl
			 << "La soustraction ne peut pas avoir lieu. Merci d'introduire un vecteur de taille " 
			 << taille << endl;	
	}
	return vect;
}

//oppose
const Vecteur Vecteur :: operator-() const
{
	Vecteur res(position.size());	
	while (res.position.size()<position.size()){ 
      res.position.push_back(0);   
	}               	                          
	for(size_t i(0); i<=position.size(); ++i){
      res.position[i] = 0 - position[i];
	}
    return res;
}

//multiplication d'un vect par un scalaire
const Vecteur Vecteur :: operator*(double x) const
{
	Vecteur res(position.size());
	for(size_t i(0);i<=position.size();++i){
		res.position[i]=x*position[i];
	}
	return res;
}

//produit scalaire
const double Vecteur :: operator*(Vecteur const& autre) const
{
	double res(0.);
	try{
		if(position.size()!=autre.position.size()){
			throw int(position.size());
		}
		for(size_t i(0); i<=autre.position.size();++i){
			res=res+autre.position[i]*position[i];
		}
	    
	}
	
	catch(int taille){
		cerr << "Le vecteur entré en paramètre n'est pas de la même taille que l'instance ! " << endl
			 << "Le produit scalaire ne peut pas s'effectuer. Merci d'introduire un vecteur de taille " << endl
			 << taille << endl;
		 }
	return res;
}

//produit vectoriel
const Vecteur Vecteur::operator^(Vecteur const& autre) const
{
	Vecteur res(autre);
	try{
		if(autre.position.size()!= 3 or position.size() != 3){
			throw int(3);
		}
		res.position[0] = position[1]*autre.position[2] - position[2]*autre.position[1];
		res.position[1] = position[2]*autre.position[0] - position[0]*autre.position[2];
		res.position[2]= position[0]*autre.position[1] - position[1]*autre.position[0];
	}
	catch(int){
		cerr << "Le vecteur entré en paramètre et le vecteur lié à l'instance doivent avoir la taille 3. " << endl;
	}	
	return res;
}

const Vecteur Vecteur::operator+=(Vecteur const& autre) const
{
	size_t taille (position.size());
	Vecteur res(*this);
	
	try
	{
	 if(taille!=autre.position.size()){
	   throw int(taille);
     }	
	 for(size_t i(0);i<taille;++i)
	   res.position[i]+=autre.position[i];
    }
    
	catch(int taille){
	cerr << "Le vecteur entré en paramètre n'a pas la bonne taille ! " << endl
		 << "Merci d'introduire un vecteur de taille " 
		 << taille << endl;
	};
	
	return res;
}

//compare
const bool Vecteur :: operator==(Vecteur const& autre) const
{
	if (position.size()!=autre.position.size())
		return false; 
	
	bool still_okay = true;
	
	for(size_t i(0); i < position.size() && still_okay; ++i)
		still_okay = (position[i] == autre.position[i]);
		
	return still_okay;
	
}




double& Vecteur::operator[](size_t index) {
	return position[index];
}


double const& Vecteur::operator[](size_t index) const {
	return position[index];
}


//méthodes

Vecteur Vecteur::concatener(Vecteur const& vect1) const
{
	
	size_t taille(vect1.position.size()+position.size());
	Vecteur retour (taille);
	for(size_t i(0); i<vect1.position.size(); ++i)
	retour[i] = vect1[i];
	size_t taille2(vect1.position.size());
	for(size_t i(taille2);i<position.size();++i)
	retour[i]=position[i];
	return retour;
}

void Vecteur :: augmente(double valeur)
{
	position.push_back(valeur);
}

double Vecteur :: norme2_vect() const
{	
	double res(0.);
	for(size_t i(0); i<=position.size(); ++i){
		res += position[i]*position[i];
	}
	return res;
}

double Vecteur :: norme_vect() const
{
	return sqrt(norme2_vect());
}

ostream& Vecteur :: affiche(ostream& sortie) const
{
	sortie << "{";			
	const size_t dernier(position.size()-1);				
	for(size_t i(0);i<dernier;++i){
		sortie << position[i] << ",";
	}
	sortie<<position.back()<<"}";
	return sortie;
}


//opérateur externes:
ostream& operator<<(ostream& sortie, Vecteur const& vect )
{
	return vect.affiche(sortie);
}

