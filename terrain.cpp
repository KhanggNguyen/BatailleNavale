#include "terrain.h"
#include <cstdlib>
#include "setup.h"

//Accesseur en lecture
int Terrain::getLargeur(){return mLargeur;}
int Terrain::getLongueur(){return mLongueur;}
int Terrain::getForme(int i, int j) {return mForme[j][i];}

//Accesseur en écriture
void Terrain::setLargeur(int i){mLargeur=i;}
void Terrain::setLongueur(int i){mLongueur=i;}
void Terrain::setForme(int i, int j, int u){mForme[j][i]=u;}

//Fonction de contrôle
void Terrain::parDessus(Bateau b, Window& terrainJ1, int x, int y) //Affiche par dessus le terrain
{                                                                 //le bateau entrain d'être placé
  int v = 0;
  for (int i = x; i < x + 5; i++) {
    int u = 0;
    for (int j = y; j < y + 5; j++) {
      if (b.getForme(u, v) != 0)
	terrainJ1.print(i, j, ' ', BBLUE);
      u++;
    }
    v++;
  }
}

void Terrain::chevaucheBordure(int &x,int &y, Bateau &b){
  bool estVide=true;
  int U[5][5];
  while (x > 5)
    {

      for (int j = 0; j < 5; j++)
	{
	  if (b.getForme(j, 4) != 0) //Vérifie que la 5éme lignes du bateau est vide.
	    estVide = false;
	}

      if (estVide)
	{

	  for (int i = 0; i < 5; i++) 
	    for (int j = 0; j < 5; j++) {
	      U[j][i] = b.getForme(j, i);
	      b.setForme(j, i, 0);
	    }
	  for (int i = 1; i < 5; i++) 
	    for (int j = 0; j < 5; j++)  //Decale de 1 rang vers le bas le bateau.
	      b.setForme(j, i, U[j][i - 1]); 
	
	}

      x--;
    }
  
  estVide = true;
  
  while (x < 0)
    {

      for (int j = 0; j < 5; j++) 
	if (b.getForme(j, 0) != 0) 
	  estVide = false; //Vérifie que la ligne gauche de l'Objet bateau est vide.

      if (estVide) {
	for (int i = 0; i < 5; i++) 
	  for (int j = 0; j < 5; j++)
	    {
	      U[j][i] = b.getForme(j, i);
	      b.setForme(j, i, 0);
	    }
	for (int i = 0; i < 4; i++) 
	  for (int j = 0; j < 5; j++) // Decale de 1 rang vers le haut le bateau
	    b.setForme(j, i, U[j][i + 1]);
      }
      x++;
    }

  estVide = true;

  while (y < 0)
    {

      for (int j = 0; j < 5; j++) 
	if (b.getForme(0, j) != 0) 
	  estVide = false; //Vérifie que la colonne gauche de l'Objet bateau est vide.
      if (estVide) {
	for (int i = 0; i < 5; i++) 
	  for (int j = 0; j < 5; j++)
	    {
	      U[j][i] = b.getForme(j, i);
	      b.setForme(j, i, 0);
	    }
	for (int i = 0; i < 5; i++) 
	  for (int j = 0; j < 4; j++) // Decale de 1 rang vers la gauche le bateau
	    b.setForme(j, i, U[j + 1][i]);
      }
      y++;
    }
  
  estVide = true;
  
  while (y > 5)
    {
      for (int j = 0; j < 5; j++)
	if (b.getForme(4, j) != 0)
	  estVide = false;  //Vérifie que la colonne droite de l'Objet bateau est vide.
      if (estVide)
	{
	  for (int i = 0; i < 5; i++) 
	    for (int j = 0; j < 5; j++)
	      {
		U[j][i] = b.getForme(j, i);
		b.setForme(j, i, 0);
	      }
      
	  for (int i = 0; i < 5; i++) 
	    for (int j = 1; j < 5; j++) // Decale de 1 rang vers la droite le bateau
	      b.setForme(j, i, U[j - 1][i]);
	}
      y--;
    }
}
bool Terrain::chevaucheNavire(int x,int y, Bateau b) //Vérifie que la bateau ne se trouve pas
{                                                         //Sur un autre.
  int u=0;
  int v=0;
  int **copie;
   copie = new int*[mLargeur];
  for (int j = 0; j <mLargeur; j++)
    copie[j] = new int[mLongueur];
  bool erreur=false;
  for (int i = 0; i < mLargeur; i++)
    for (int j = 0; j < mLongueur; j++)
      copie[i][j] = mForme[i][j];


  for (int i = x; i < x + 5; i++) {
    u = 0;
    for (int j = y; j < y + 5; j++) {
      if (b.getForme(u, v) != 0)
	copie[j][i] = b.getForme(u, v);
      if (copie[j][i] != mForme[j][i] && mForme[j][i] != 0)
	{
	  erreur = true; //Compare le nouveau terrain avec l'ancien terrain pour vérifier que le
	}               //Navire est bien placé sur des cases vierges.

      u++;
    }
    v++;
  }
  return erreur;
}

//Fonction Ordinateur

void Terrain::afficheTerrainCache(Window& Joueur1)
  {
    Joueur1.clear();
  Joueur1.setCouleurBordure(BBLUE);
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      switch (mForme[i][j]) {
      case 0:
	Joueur1.print(j, i, ' ', BCYAN);
	break;
      case 1:
	Joueur1.print(j, i, ' ', BRED);
	break;
      case 2:
	Joueur1.print(j, i, ' ', BMAGENTA);
	break;
      case 3:
	Joueur1.print(j, i, ' ', BGREEN);
	break;
      case 4:
	Joueur1.print(j, i, ' ', BBLUE);
	break;
      case 5:
	Joueur1.print(j, i, ' ', BYELLOW);
	break;
      case 6:
	Joueur1.print(j,i,' ', BBLACK);
	break;
      case 7:
	Joueur1.print(j,i,' ',BWHITE);
	break;
      default:
	Joueur1.print(j,i,' ',BCYAN);
	break;
      }
}


void Terrain::placerNavireIA(Bateau& b) //Place le navire de maniére Aléatoire.
{

  int x = 0;
  int y = 0;
  int u=0;
  int v=0;
  int tourner = 0;
  tourner = rand() % (4);
  
  while(tourner>0){
    b.retourneBateau90();
    tourner--;
  }
    	  
  bool erreur;
  
  while (!b.getEstPlace())
    {
      x = -5;
      y = -5;
      x = rand() % (15) + x;
      y = rand() % (15) + y;

      chevaucheBordure(x,y,b);
      erreur = chevaucheNavire(x,y,b);
      if (erreur)
	{
	  b.setEstPlace(false);
	}
      else
	{
	  v=0;
	  b.setEstPlace(true);
	  for (int i = x; i < x + 5; i++)
	    {
	      u=0;
	      for (int j = y; j < y + 5; j++)
		{
		  if (b.getForme(u, v) != 0)
		    mForme[j][i] = b.getForme(u,v);

		  u++;
		}
	      v++;
	    }
	}
    }
}

void Terrain::phasePlacementIA() //Prépare les Navires à placer Aléatoirement
{
  Bateau Un(1);
  Bateau Deux(2);
  Bateau Trois(3);
  Bateau Quatre(4);
  Bateau Cinq(5);
  placerNavireIA(Quatre);
  placerNavireIA(Trois);
  placerNavireIA(Deux);
  placerNavireIA(Un);
  placerNavireIA(Cinq);
}

//Fonction Joueur

void Terrain::phasePlacement(Window& FenErreur) //Demande au joueur de choisir les navires.
{

  int ch;
  int choix = 1;

  bool sortir;
  bool place = false;
  bool droite = false;
  
  Bateau Un(1);
  Bateau Deux(2);
  Bateau Trois(3);
  Bateau Quatre(4);
  Bateau Cinq(5);
  Bateau bateauChoisit = Un;

  Selection select;
  
  Window ecranSelection(5, 25, 25, 15, ' ');
  Window terrainJ1(10, 10, 10, 10, ' ');
  Window bateauSelect(5, 5, 54, 15, ' ');

  
  terrainJ1.setCouleurBordure(BWHITE);
  bateauSelect.setCouleurBordure(BWHITE);
  ecranSelection.setCouleurBordure(BWHITE);
  
  afficheTerrain(terrainJ1);
  select.initialisation(ecranSelection);
  FenErreur.clear();
  FenErreur.print(1, 1, "Selectionnez votre Navire");

  while ((ch = getch()) != 'q' && !place) {

    switch (ch) { //Determination du bateau à placer
      
    case KEY_RIGHT:
      select.initialisation(ecranSelection);
      if (choix == 5) {
	choix = 1;
      }
      else {
	droite = false;
	choix++;
      }
      break;
    case KEY_LEFT:
      select.initialisation(ecranSelection);
      if (choix == 1)
	choix = 5;
      else {
	choix--;
      }
      droite = true;
      break;

    case 10: // Entrée dans le phase de placement
      int x = 0;
      int y = 0;
      sortir = true;
      FenErreur.clear();
      FenErreur.print(1, 1, "Appuyez sur Entree pour valider le placement");
      parDessus(bateauChoisit, terrainJ1, x, y);
      while (sortir) {
	switch (ch=getch()) { //Determiner l'emplacement du bateau
	case ' ':
	  bateauChoisit.retourneBateau90();
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);
	  break;
	case KEY_SLEFT:
	  bateauChoisit.retourneBateau90();
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);
	  break;
	case KEY_RIGHT:
	  terrainJ1.print(x, y, ' ', BCYAN);
	  x++;
	  chevaucheBordure(x,y,bateauChoisit);
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);

	  break;
	case KEY_LEFT:
	  terrainJ1.print(x, y, ' ', BCYAN);
	  x--;
	  chevaucheBordure(x,y,bateauChoisit);
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);
	  break;
	case KEY_UP:
	  terrainJ1.print(x, y, ' ', BCYAN);
	  y--;
	  chevaucheBordure(x,y,bateauChoisit);
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);

	  break;
	case KEY_DOWN:
	  terrainJ1.print(x, y, ' ', BCYAN);
	  y++;
	  chevaucheBordure(x,y,bateauChoisit);
	  afficheTerrain(terrainJ1);
	  parDessus(bateauChoisit, terrainJ1, x, y);
    
	  break;
	case 27:
	  FenErreur.clear();
	  FenErreur.print(1, 1, "Sélectionnez votre Navire");
	  sortir=false;
	  afficheTerrain(terrainJ1);
	  break;
	  
	case 10: // Valider l'Emplacement du bateau
	  sortir = false;
	  placerNavire(bateauChoisit, terrainJ1, x, y, FenErreur);
	  afficheTerrain(terrainJ1);
	  switch (choix) { 
	  case 1:
	    if (bateauChoisit.getEstPlace())
	      Un.setEstPlace(true);
	    break;
	  case 2:
	    if (bateauChoisit.getEstPlace())
	      Deux.setEstPlace(true);
	    break;
	  case 3:
	    if (bateauChoisit.getEstPlace())
	      Trois.setEstPlace(true);
	    break;
	  case 4:
	    if (bateauChoisit.getEstPlace())
	      Quatre.setEstPlace(true);
	    break;
	  case 5:
	    if (bateauChoisit.getEstPlace())
	      Cinq.setEstPlace(true);
	    break;
	  }

	  break;
	}
      }
      break;
    }

    switch (choix) // Montrer le bateau sélectionné dans la fenêtre.
      {
      case 1:
	if (Un.getEstPlace() == false) {
	  select.affiche(bateauSelect, Un,ecranSelection);
	  droite = false;
	  bateauChoisit = Un;
	}
	else if (Un.getEstPlace() == true && droite == true) {
	  choix = 5;
	  droite = true;
	  select.initialisation(ecranSelection);
	}
	else {
	  choix++;
	  droite=false;
	  select.initialisation(ecranSelection);
	}

	break;
      case 2:
	if (Deux.getEstPlace() == false) {
	  select.affiche(bateauSelect, Deux,ecranSelection);
	  droite = false;
	  bateauChoisit = Deux;
	}
	else if (Deux.getEstPlace() == true && droite == false){
	  choix++;
	  select.initialisation(ecranSelection);
	}
	else {
	  choix--;
	  droite = true;
	}
	break;
      case 3:
	if (Trois.getEstPlace() == false) {
	  select.affiche(bateauSelect, Trois,ecranSelection);
	  droite = false;
	  bateauChoisit = Trois;
	}
	else if (Trois.getEstPlace() == true && droite == false){
	  choix++;
	  select.initialisation(ecranSelection);
	}
	else {
	  choix--;
	  droite = true;
	  select.initialisation(ecranSelection);
	}
	break;
      case 4:
	if (Quatre.getEstPlace() == false) {
	  select.affiche(bateauSelect, Quatre,ecranSelection);
	  droite = false;
	  bateauChoisit = Quatre;
	}
	else if (Quatre.getEstPlace() == true && droite == false){
	  choix++;
	  select.initialisation(ecranSelection);
	}
	else {
	  choix--;
	  droite = true;
	  select.initialisation(ecranSelection);
	}
	break;
      case 5:
	if (Cinq.getEstPlace() == false) {
	  select.affiche(bateauSelect, Cinq,ecranSelection);
	  droite = false;
	  bateauChoisit = Cinq;
	}
	else if (Cinq.getEstPlace() == true && droite == false){
	  choix = 1;
	  select.initialisation(ecranSelection);
	}
	else {
	  choix--;
	  droite = true;
	  select.initialisation(ecranSelection);
	}
	break;
      }
    if (Un.getEstPlace() && Deux.getEstPlace() && Trois.getEstPlace() && Quatre.getEstPlace() && Cinq.getEstPlace())
      place = true;
  }


}

void Terrain::placerNavire(Bateau& b, Window& Joueur, int x, int y, Window& FenErreur)
{
  int **copie;
   copie = new int*[mLargeur];
  for (int j = 0; j <mLargeur; j++)
    copie[j] = new int[mLongueur];
  
  int u = 0;
  int v = 0;
  bool erreur = false;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
      copie[i][j] = mForme[i][j];
    }
  for (int i = x; i < x + 5; i++) {
    u = 0;

    for (int j = y; j < y + 5; j++) {
      if (b.getForme(u, v) != 0)
	copie[j][i] = b.getForme(u, v);
      if (copie[j][i] != mForme[j][i] && mForme[j][i] != 0) {

	erreur = true;
      }

      u++;
    }
    v++;
  }
  if (erreur) {
    b.setEstPlace(false);
    FenErreur.clear();
    FenErreur.print(1, 1, "Placement impossible (Chevauchement)");
  }
  else {
    b.setEstPlace(true);
    for (int i = 0; i < 10; i++)
      for (int j = 0; j < 10; j++) 
	mForme[i][j] = copie[i][j];
      
    FenErreur.clear();
    FenErreur.print(1, 1,"Navire place");
  }
}

//Fonction d'Affichage

void Terrain::afficheTerrain(Window& Joueur1)
{
  Joueur1.clear();

  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      switch (mForme[i][j]) {
      case 0:
	Joueur1.print(j, i, ' ', BCYAN);
	break;
      case 1:
	Joueur1.print(j, i, ' ', BRED);
	break;
      case 2:
	Joueur1.print(j, i, ' ', BMAGENTA);
	break;
      case 3:
	Joueur1.print(j, i, ' ', BGREEN);
	break;
      case 4:
	Joueur1.print(j, i, ' ', BBLUE);
	break;
      case 5:
	Joueur1.print(j, i, ' ', BYELLOW);
	break;
      case 6:
	Joueur1.print(j,i,' ', BBLACK);
	break;
      case 7:
	Joueur1.print(j,i,' ',BWHITE);
	break;
      default:
	Joueur1.print(j,i,' ',BCYAN);
	break;
      }
}



//Constructeur par défaut
Terrain::Terrain()
{
  mLargeur = 10;
  mLongueur = 10;
  mForme = new int*[mLargeur];
  for (int j = 0; j <mLargeur; j++)
    mForme[j] = new int[mLongueur];

  for (int j = 0; j < mLargeur; j++)
    for (int i = 0; i <mLongueur; i++)
      mForme[i][j]=0;

}

//Destructeur
Terrain::~Terrain()
{

}
