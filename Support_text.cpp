#include "Support_text.hpp"
#include "Paroi.hpp"
#include "Tapis.hpp"
#include "Systeme.hpp"



void Support_text :: dessine(const Boule* const boule) {std::cout<<boule<<std::endl;}
void Support_text :: dessine(const Paroi* const paroi) {paroi->affiche();}
void Support_text :: dessine(const Tapis* const tapis) {tapis->affiche();}
void Support_text :: dessine(const Systeme* const systeme) {systeme->affiche();}
