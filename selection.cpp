#include "selection.h"

//Accesseur en Lecture
int Selection::getColonnes(){return mColonnes;}
int Selection::getLignes(){return mLignes;}
int Selection::getSurface(int i,int j){return mSurface[i][j];}

//Accesseur en Ecriture
void Selection::setColonnes(int i){mColonnes=i;}
void Selection::setLignes(int i){mLignes=i;}
void Selection::setSurface(int i,int j, int x){mSurface[i][j]=x;}

//Fonction d'Initialisation
void Selection::initialisation(Window& selections){ // INITIALISE LA FENETRE DE SELECTION
  std::ifstream fichier("BATEAU.txt", std::ios::in);
  int deb = 0;
  int fin = 5;
  char c, u;
  // REGROUPE LA FORME DES NAVIRES LES UN A LA SUITE DE AUTRES DANS UN TABLEAU.
  while (deb < 25){
    fichier >> c;
    for (int i = 0; i < 5; i++){
      while (deb < fin){
	fichier >> u;
	mSurface[i][deb] = u - '0';
	deb++;
      }
      deb -= 5;
    }
    fin += 5;
    deb += 5;
  }
  fichier.close();
  // AFFICHE LES DIFFERENTS NAVIRES.
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 5; j++){
      switch (mSurface[j][i]){
      case 0:
	selections.print(i, j, ' ', BCYAN);
	break;
      case 1:
	selections.print(i, j, ' ', BRED);
	break;
      case 2:
	selections.print(i, j, ' ', BMAGENTA);
	break;
      case 3:
	selections.print(i, j, ' ', BGREEN);
	break;
      case 4:
	selections.print(i, j, ' ', BBLUE);
	break;
      case 5:
	selections.print(i, j, ' ', BYELLOW);
	break;
      }
    }
  }
}

//Fonction d'affichage

void Selection::afficheSelect(Window& FenSelect, int nombre){
  for (int i = 0; i < 25; i++) 
    for (int j = 0; j < 5; j++)
      if(mSurface[j][i]==nombre)
	FenSelect.print(i, j, ' ', BBLACK);

}

void Selection::affiche(Window& bateauSelect, Bateau B, Window& FenSelect){ // AFFICHE LE BATEAU CHOISIT.

  for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
        {
	  if (B.getForme(i,j) == 0)
	    bateauSelect.print(j, i, ' ', BCYAN);
	  else
	    bateauSelect.print(j, i, ' ', BGREEN);
        }
    }
  afficheSelect(FenSelect,B.getNumero());
}

//Constructeur par défaut
Selection::Selection(){
  mLignes = 5;
  mColonnes = 25;
}

//Destructeur
Selection::~Selection(){
}
