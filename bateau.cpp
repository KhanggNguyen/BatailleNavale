#include "bateau.h"

//Accesseur en lecture

int Bateau::getForme(int i, int j){return mForme[i][j];}
bool Bateau::getEstPlace(){return mEstPlace;}
int Bateau::getColonnes(){return mColonnes;}
int Bateau::getLignes(){return mLignes;}
int Bateau::getNumero(){return mNumero;}

//Accesseur en écriture

void Bateau::setEstPlace(bool i){mEstPlace=i;}
void Bateau::setForme(int i,int j,int n){mForme[i][j]=n;}
void Bateau::setColonnes(int i){mColonnes=i;}
void Bateau::setLignes(int i){mLignes=i;}
void Bateau::setNumero(int i){mNumero=i;}

//Surcharge Operateur
void Bateau::operator=(Bateau a){
  mColonnes = 5;
  mLignes = 5;
  mNumero=a.getNumero();
  mEstPlace=a.getEstPlace();
  
  mForme=new int*[mLignes];
  for(int j=0;j<mLignes;j++)
    mForme[j]=new int[mColonnes];
  
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      mForme[i][j]=a.getForme(i,j);
}
//Retourner le bateau
void Bateau::retourneBateau90(){
  int T[5][5];
  for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
      T[i][j]=mForme[mColonnes-1-j][i];

  for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
      mForme[i][j]=T[i][j];

}

void Bateau::retourneBateauMoins90(){
  int T[5][5];
  for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
      T[mColonnes-1-j][i]=mForme[i][j];

  for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
      mForme[i][j]=T[i][j];

}

//Constructeur
Bateau::Bateau(int i)
{

  mColonnes = 5;
  mLignes = 5;
  mNumero=i;
  mForme=new int*[mLignes];
  for(int j=0;j<mLignes;j++)
    mForme[j]=new int[mColonnes];
  mEstPlace = false;
  std::ifstream fichier("BATEAU.txt", std::ios::in);
  char Numero = 0;
  while (Numero - '0' != i)
    {
      fichier >> Numero;
    }
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      fichier >> mForme[i][j];
}

//Constructeur par défaut
Bateau::Bateau(){
  mColonnes = 5;
  mLignes = 5;
  mEstPlace=false;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      mForme[i][j]=0;
}

//Destructeur
Bateau::~Bateau()
{

}
