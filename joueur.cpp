#include "joueur.h"

//Accesseur en Lecture
bool Joueur::getIA(){return mIA;}
bool Joueur::getVictoire(){return mVictoire;}
int Joueur::getNumero(){return mNumero;}
char Joueur::getPseudo(){return mPseudo;}
int Joueur::getScore(){return mScore;}
bool Joueur::getEtatBateau(int i){return mEtatBateau[i];}

//Accesseur en Ecriture
void Joueur::setIA(bool t){mIA=t;}
void Joueur::setScore(int i){mScore=i;}
void Joueur::setNumero(int i){mNumero=i;}
void Joueur::setVictoire(bool b){mVictoire=b;}
void Joueur::setPseudo(char a){mPseudo=a;}
void Joueur::setEtatBateau(int i, bool Viv){mEtatBateau[i]=Viv;}  

void Joueur::bateauEstVivant(){
  for(int w=0;w<5;w++){
    mEtatBateau[w]=true;
    if(mEtatBateau[w])
      for(int i=0;i<getLongTerrain();i++)
	for(int j=0;j<getLargTerrain();j++)
	  if(getTerrain(i,j)==w+1)
	    mEtatBateau[w]=false;
    
  }
    
}

bool Joueur::estMort(){
  bool mort = true;
  for(int i=0;i<getLongTerrain();i++){
    for(int j=0;j<getLargTerrain();j++){
      if(getTerrain(i,j) != 0){
	if(getTerrain(i,j) < 6){
	  mort = false;
	}
      }
      
    }
  }
  return mort;
}

//Methode lié a terrain
void Joueur::placerTerrain(Window& fenMessage){
  if (mIA==true)
    mTerrain.phasePlacementIA();
  else
    mTerrain.phasePlacement(fenMessage);
}

void Joueur::afficheTerrain(Window& fenTerrain){
  mTerrain.afficheTerrain(fenTerrain);
}

void Joueur::afficheTerrainCache(Window &fenTerrain){
  mTerrain.afficheTerrainCache(fenTerrain);
}
//Accesseur en Lecture lié à terrain
int Joueur::getTerrain(int i,int j){return mTerrain.getForme(i,j);}
int Joueur::getLongTerrain(){return mTerrain.getLongueur();}
int Joueur::getLargTerrain(){return mTerrain.getLargeur();}

//Accesseur en écriture lié à terrain
void Joueur::setTerrain(int i,int j,int x){mTerrain.setForme(i,j,x);}


//Constructeur

Joueur::Joueur(int i){
  mScore=0;
  mNumero=i;
  mIA=true;
  mVictoire=true;
}

//Destructeur

Joueur::~Joueur(){}
