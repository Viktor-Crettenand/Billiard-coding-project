#ifndef DESSINABLE_HPP_
#define DESSINABLE_HPP_

#include "SupportADessin.hpp"


class Dessinable {
	public:
		Dessinable(SupportADessin* support_):support(support_){}
		virtual ~Dessinable(){}
		virtual void dessine()=0;

	protected:
		SupportADessin* support;
};

#endif

