#ifndef BATEAU_H_INCLUDED
#define BATEAU_H_INCLUDED

#include <fstream>
#include <iostream>
#include "window.h"

class Bateau 
{
 private:
  int **mForme;
  int mColonnes;
  int mLignes;
  bool mEstPlace;
  int mNumero;

 public:

  //Accesseur en lecture
  int getForme(int,int);
  bool getEstPlace();
  int getColonnes();
  int getLignes();
  int getNumero();
    
  //Accesseur en écriture
  void setEstPlace(bool);
  void setForme(int,int,int);
  void setColonnes(int);
  void setLignes(int);
  void setNumero(int);

  //Fonction pour tourner un bateau
  void retourneBateau90();
  void retourneBateauMoins90();

  //Fonction Operator
  void operator=(Bateau);
    
  //Constructeur de la classe
  Bateau(int i);
  Bateau();

  //destructeur
  ~Bateau();

};

#endif
