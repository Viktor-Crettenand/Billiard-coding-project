#ifndef SUPPORTADESSIN_HPP_
#define SUPPORTADESSIN_HPP_

class Boule;
class Paroi;
class Tapis;
class Systeme;

class SupportADessin
{
public:

  virtual void dessine(const Boule* const boule) = 0;
  virtual void dessine(const Tapis* const tapis) = 0;
  virtual void dessine(const Systeme* const systeme) = 0;
  virtual void dessine(const Paroi* const paroi) = 0;

};

#endif

