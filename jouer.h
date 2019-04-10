#ifndef JOUER_H_INCLUDED
#define JOUER_H_INCLUDED


#include "setup.h"
#include "joueur.h"

class Jouer{
 public:
  void choixPartie(Setup&,Window&);
  void partie2Joueur(Joueur,Joueur,Window&,Setup& );
  void partie3Joueur(Joueur,Joueur,Joueur ,Window&,Setup& );
  void partie4Joueur(Joueur,Joueur,Joueur,Joueur,Window&,Setup& );
  bool valideCible(Joueur, Window&);  int choixAttaque(Setup,int);
};

#endif
