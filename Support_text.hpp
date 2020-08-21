#ifndef SUPPORTADESSINBOULE_HPP_
#define SUPPORTADESSINBOULE_HPP_

#include "SupportADessin.hpp"

class Boule;
class Paroi;
class Tapis;

class Support_text: public SupportADessin
{
public:

//Support_text est une façon d'afficher les différents Objet. Nous pourrions en implémenter d'autres, par exemple une façon graphique d'afficher les objets
  void dessine(const Boule* const boule);
  void dessine(const Tapis* const tapis);
  void dessine(const Systeme* const systeme);
  void dessine(const Paroi* const paroi);

};
#endif
