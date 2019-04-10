#ifndef SELECTION_H_INCLUDED
#define SELECTION_H_INCLUDED

#include <fstream>
#include "window.h"
#include "bateau.h"

class Selection
{

 private:
  int mColonnes;
  int mLignes;
  int mSurface[5][25];

 public:
    
  //Accesseur en Lecure
  int getColonnes();
  int getLignes();
  int getSurface(int,int);
    
  //Accesseur en écriture
  void setColonnes(int);
  void setLignes(int);
  void setSurface(int,int,int);

  //Methode d'initialisation et d'affichage
  void initialisation(Window&);
  void affiche(Window&, Bateau, Window&);

  void afficheSelect(Window&, int);

  //Constructeur et Desctructeur par défaut
  Selection();
  ~Selection();
};

#endif
