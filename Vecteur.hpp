#ifndef VECTEUR_HPP_
#define VECTEUR_HPP_

#include <vector>
#include <iostream>
#include <cmath>
#include <initializer_list>

class Vecteur {
public:
//constructeurs:			
  Vecteur(Vecteur const& copie);
  Vecteur (std::size_t taille = 3, double x = 0.); //constructeur par défaut
  Vecteur (const std::initializer_list <double>& liste);
  Vecteur(double x, double y, double z);
  Vecteur(double x, double y, double z,double a,double b,double c);
  
//opérateurs internes:
  Vecteur operator+(Vecteur const& autre) const;
  const Vecteur operator-(Vecteur const& autre) const; //soustraction

  const Vecteur operator-()const; //oppose
  const Vecteur operator*(double x) const; //multiplication par un double
  const double operator*(Vecteur const& autre) const; //multiplication scalaire
  const Vecteur operator^(Vecteur const& autre) const; // produit vectoriel
  const Vecteur operator+=(Vecteur const& autre) const;
  
  const bool operator==(Vecteur const& autre) const;
    
  double const& operator[](size_t index) const;
  double& operator[](size_t index);


  
//méthodes
  Vecteur concatener(Vecteur const& vect1) const;
  void augmente(double);
  double norme2_vect() const;
  double norme_vect() const;
  std::ostream& affiche(std::ostream&) const;
  size_t getsize() const{return position.size();}
  std::vector<double> get_position()const{return position;};


private:
std::vector<double> position;
};

//opérateurs externes:
std::ostream& operator<<(std::ostream& sortie, Vecteur const& vect );

#endif
