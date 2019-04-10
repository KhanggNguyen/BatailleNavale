#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include "window.h"
#include "bateau.h"  
#include "selection.h" 

class Setup;

class Terrain
{
 private:
  int mLargeur;
  int mLongueur;
  int **mForme;


 public:
  
  //Accesseur en lecture
  int getLargeur();
  int getLongueur();
  int getForme(int,int) ;
  
  //Accesseur en écriture
  void setLargeur(int);
  void setLongueur(int);
  void setForme(int,int,int);
  
  //Fonction concernant l'Ordinateur
  void phasePlacementIA();
  void placerNavireIA(Bateau&);
  
  //Fonction pour le Joueur
  void placerNavire(Bateau&, Window&, int, int,Window&);
  void phasePlacement(Window&);

  //Fonction de contrôle
  void chevaucheBordure(int&,int&,Bateau&) ;
  bool chevaucheNavire(int,int, Bateau);
  void parDessus(Bateau , Window &, int,int);

  //Fonction d'affichage
  void afficheTerrain(Window& );
  void afficheTerrainCache(Window& );


  //Constructeur par défaut
  Terrain();
  //Destructeur
  ~Terrain();
};

#endif
