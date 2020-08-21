CXX = g++
CC  = $(CXX)

CXXFLAGS = -std=c++11  # C++11

# Partie commentée : choisissez les options que vous voulez avoir
#                    en décommentant la/les lignes correspondantes
#
CXXFLAGS += -pedantic -Wall       # pour les purs et durs
CXXFLAGS += -g                    # pour debugger
CXXFLAGS += -pg                 # pour profiler
LDFLAGS  += -pg                 # pour profiler
CXXFLAGS += -O2                 # pour optimiser la vitesse

all: testVecteur testBoule1 testIntegrateur testChocs testSysteme tmp


tmp: Tapis.o Paroi.o Systeme.o

Vecteur.o: Vecteur.cpp Vecteur.hpp

IntegrateurEuler.o: IntegrateurEuler.cpp IntegrateurEuler.hpp Integrateur.hpp

Boule.o: Boule.cpp Boule.hpp Objet.hpp Dessinable.hpp Support_text.hpp SupportADessin.hpp

Paroi.o : Paroi.cpp Paroi.hpp Objet.hpp Dessinable.hpp Support_text.hpp SupportADessin.hpp

Tapis.o : Tapis.cpp Tapis.hpp Objet.hpp Dessinable.hpp Support_text.hpp SupportADessin.hpp Objet.hpp Paroi.hpp Vecteur.hpp

Systeme.o : Systeme.cpp Systeme.hpp Vecteur.hpp Dessinable.hpp Boule.hpp SupportADessin.hpp IntegrateurEuler.hpp Objet.hpp

testChocs.o: testChocs.cpp Boule.hpp Vecteur.hpp IntegrateurEuler.hpp Support_text.hpp

testSysteme.o: testSysteme.cpp Systeme.hpp Vecteur.hpp Boule.hpp IntegrateurEuler.hpp

IntegrateurEuler.o: IntegrateurEuler.hpp IntegrateurEuler.cpp Boule.hpp

Support_text.o: SupportADessin.hpp Support_text.hpp Support_text.cpp Paroi.hpp Tapis.hpp Systeme.hpp

testVecteur: testVecteur.o Vecteur.o

testBoule1: testBoule1.o Boule.o Vecteur.o IntegrateurEuler.o Systeme.o

testIntegrateur: testIntegrateur.o Vecteur.o Boule.o IntegrateurEuler.o

testChocs: testChocs.o Systeme.o Vecteur.o Boule.o Paroi.o Tapis.o IntegrateurEuler.o Support_text.o 

testSysteme: testSysteme.o Systeme.o Paroi.o Tapis.o Boule.o Vecteur.o IntegrateurEuler.o Support_text.o

clean:
	rm *.o
