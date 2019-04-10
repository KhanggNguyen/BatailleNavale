#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "terrain.h"
#include "window.h"



class Joueur{
 private:
  char mPseudo;
  int mScore;
  int mNumero;
  Terrain mTerrain;
  bool mIA;
  bool mVictoire;
  bool mEtatBateau[5];

 public:  
  
  //Accesseur en Lecture
  int getScore();
  int getNumero();
  bool getIA();
  bool getVictoire();
  char getPseudo();
  bool getEtatBateau(int);

  //Accesseur en Ecriture
  void setScore(int);
  void setNumero(int);
  void setIA(bool);
  void setVictoire(bool);
  void setPseudo(char);
  void setEtatBateau(int,bool);

  void bateauEstVivant();

  //Accesseur en écriture lié à terrain
  void setTerrain(int,int,int);

  //Accesseur en lecture lié à terrain
    int getTerrain(int,int);
    int getLongTerrain();
    int getLargTerrain();

    bool estMort();

  //Methode de la classe en rapport avec Terrain
    void placerTerrain(Window&);
  void afficheTerrain(Window&);
  void afficheTerrainCache(Window&);

  //Constructeur et Destructeur
  Joueur(int i);
  ~Joueur();
 

};
#endif
