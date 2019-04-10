#include "jouer.h"
#include "window.h"
#include <string>
#include <stdlib.h>

void Jouer::choixPartie(Setup& param, Window& FenErreur){

  FenErreur.clear();
  FenErreur.print(1, 1, "PLACEMENT", BWHITE);
  if (param.getNombreTerrain() == 2)
    {
      Joueur J1(1);
      Joueur J2(2);
      if (param.getNombreJoueur() >= 1)
	J1.setIA(false);
      if (param.getNombreJoueur() >= 2)
	J1.setIA(false);
      J1.placerTerrain(FenErreur);
      J2.placerTerrain(FenErreur);
      
      partie2Joueur(J1, J2, FenErreur, param);
    }
  else if (param.getNombreTerrain() == 3)
    {
      Joueur J1(1);
      Joueur J2(2);
      Joueur J3(3);
      if (param.getNombreJoueur() >= 1)
	J1.setIA(false);
      if (param.getNombreJoueur() >= 2)
	J2.setIA(false);
      if (param.getNombreJoueur() >= 3)
	J3.setIA(false);

      J1.placerTerrain(FenErreur);
      J2.placerTerrain(FenErreur);
      J3.placerTerrain(FenErreur);
      partie3Joueur(J1, J2, J3, FenErreur, param);
    }
  else if (param.getNombreTerrain() == 4)
    {
      Joueur J1(1);
      Joueur J2(2);
      Joueur J3(3);
      Joueur J4(4);
      if (param.getNombreJoueur() >= 1)
	J1.setIA(false);
      if (param.getNombreJoueur() >= 2)
	J2.setIA(false);
      if (param.getNombreJoueur() >= 3)
	J3.setIA(false);
      if (param.getNombreJoueur() >= 4)
	J4.setIA(false);

      J1.placerTerrain(FenErreur);
      J2.placerTerrain(FenErreur);
      J3.placerTerrain(FenErreur);
      J4.placerTerrain(FenErreur);
      partie4Joueur(J4,J3,J1,J2, FenErreur, param);
    }
}

int Jouer::choixAttaque(Setup param, int numero){
  int ch;
  int terrainChoisit=1;
  bool quitte = false;
  Window fenChoix(2, 5, 0, 0, ' ');
  std::string T;
   
  if(terrainChoisit==numero)
    terrainChoisit++;


  T=std::to_string(terrainChoisit);

  fenChoix.print(1, 1,T);
  while (!quitte)
    {
    
      switch (ch=getch())
        {
	case KEY_RIGHT:
	  terrainChoisit++;

	  if( terrainChoisit==numero)
	    terrainChoisit++;
	      
	  if(terrainChoisit>param.getNombreTerrain()){
	    terrainChoisit=1;
	    if (terrainChoisit==numero)
	      terrainChoisit++;
	  }
   
	  T=std::to_string(terrainChoisit);
	  fenChoix.clear();
	  fenChoix.print(1, 1, T);
	  break;
	case KEY_LEFT:
	  terrainChoisit--;
	  if( terrainChoisit==numero)
	    terrainChoisit--;
	      
	  if(terrainChoisit<1){
	    terrainChoisit=param.getNombreTerrain();
	    if (terrainChoisit==numero)
	      terrainChoisit--;
	  }
		      
	
  
	  T=std::to_string(terrainChoisit);
	  fenChoix.clear();
	  fenChoix.print(1, 1, T);
	  break;
	case 10:
	  quitte = true;
	  break;
        }
    }
  return terrainChoisit;
}


int generer_bornes(int min, int max){
    srand(time(NULL));
    return rand()%(max-min+1) + min;
}


void phaseDeplacement(Joueur J, Window& Terrain){
  int x = 0;
  int y = 0;
  int ch;
  bool sortir = true;
  while (sortir) {
    switch(ch=getch()){
    case KEY_RIGHT:
      if(x < J.getLargTerrain()-1){
	if(J.getTerrain(x+1,y) <= 5){
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  x++;
	  Terrain.print(x,y, ' ',BRED);
	}
	else{
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  int tmp = x;
	  if(x < J.getLargTerrain()-1){
	    x = x+2;
	    if(J.getTerrain(x,y) > 5){
	      while(J.getTerrain(x,y) > 5){
		x++;
	      }
	      if(x < J.getLargTerrain()){
		Terrain.print(x,y, ' ',BRED);
	      }
	      else{ Terrain.print(tmp,y, ' ',BRED);
		x = tmp;
	      }
	    }
	    else Terrain.print(x,y, ' ',BRED);
	  }
	  else Terrain.print(x,y, ' ',BRED);
	}
      }
      else Terrain.print(x,y, ' ',BRED);
      break;
    case KEY_LEFT:
      if(x > 0){
	if(J.getTerrain(x-1,y) <= 5){
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  x--;
	  Terrain.print(x,y, ' ',BRED);
	}
	else{
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  int tmp = x;
	  if(x > 0){
	    if(x == 1){
	      Terrain.print(x,y, ' ',BRED);
	    }
	    else {
	    x = x-2;
	    if(J.getTerrain(x,y) > 5){
	      while(J.getTerrain(x,y) > 5){
		x--;
	      }
	      if(x >= 0){
		Terrain.print(x,y, ' ',BRED);
	      }
	      else{
		Terrain.print(tmp,y, ' ',BRED);
		x = tmp;
	      }
	    }
	    else Terrain.print(x,y, ' ',BRED);
	  }
	  }
	  else Terrain.print(x,y, ' ',BRED);
	}
      }
      else Terrain.print(x,y, ' ',BRED);
      break;
    case KEY_UP:
      if(y > 0){
	if(J.getTerrain(x,y-1) <= 5){
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  y--;
	  Terrain.print(x,y, ' ',BRED);
	}
	else{
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  int tmp = y;
	  if(y > 0){
	    if(y == 1){
	      Terrain.print(x,y, ' ',BRED);
	    }
	    else {
	    y = y-2;
	    if(J.getTerrain(x,y) > 5){
	      while((J.getTerrain(x,y) > 5) && (y > 0)){
		y--;
	      }
	      if(y > 0){
		Terrain.print(x,y, ' ',BRED);
	      }

	      else{
		Terrain.print(x,tmp, ' ',BRED);
		y = tmp;
	      }
	    }
	    else Terrain.print(x,y, ' ',BRED);
	  }
	  }
	  else Terrain.print(x,y, ' ',BRED);
	}
      }
      else Terrain.print(x,y, ' ',BRED);
      break;
    case KEY_DOWN:
       if(y < J.getLongTerrain()-1){
	if(J.getTerrain(x,y+1) <= 5){
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  y++;
	  Terrain.print(x,y, ' ',BRED);
	}
	else{
	  J.afficheTerrainCache(Terrain);
	  Terrain.print(x, y, ' ', BCYAN);
	  int tmp = y;
	  if(y <= J.getLongTerrain()-1){
	    if(y == J.getLongTerrain()-2){
	      Terrain.print(x,y, ' ',BRED);
	    }
	    else{
	      y = y+2;
	      if(J.getTerrain(x,y) > 5){
		while((J.getTerrain(x,y) > 5) && (y < J.getLongTerrain()-1 )){
		   y++;
		}
		if(y < J.getLongTerrain()-1){
		  Terrain.print(x,y, ' ',BRED);
		}
		else{
		  Terrain.print(x,tmp, ' ',BRED);
		  y = tmp;
		}
	      }
	      else Terrain.print(x,y, ' ',BRED);
	    }
	  }
	  else Terrain.print(x,y, ' ',BRED);
	}
       }
      else Terrain.print(x,y, ' ',BRED);
      break;
    case 10: // J Attaque
      if(J.getTerrain(x,y) != 0){
	if((J.getTerrain(x,y) == 7) ||(J.getTerrain(x,y) == 6)){
	  J.afficheTerrainCache(Terrain);
	}
	else{
	  J.setTerrain(x,y,7);
	  sortir=false;
	  J.afficheTerrainCache(Terrain);
	}
      }
      else{
	J.setTerrain(x,y,6);
	sortir=false;
	J.afficheTerrainCache(Terrain);
      }
      break;
    case 27:
      sortir=false;
      J.afficheTerrainCache(Terrain);
      break;
    }
  }
}

void iaJoue(Joueur J, Window& Terrain){
  
  bool sortir = true;
  while(sortir){
  int x = generer_bornes(1, J.getLargTerrain()-1);
  int y = generer_bornes(1, J.getLongTerrain()-1);
  
  if(J.getTerrain(x,y) != 0){
    if((J.getTerrain(x,y) == 7) || (J.getTerrain(x,y) == 6)){
    }
    else{
      J.setTerrain(x,y,7);
      sortir=false;
      J.afficheTerrainCache(Terrain);
    }
  }
  else{
    J.setTerrain(x,y,6);
    sortir=false;
    J.afficheTerrainCache(Terrain);
  }
  }
}

void Jouer::partie2Joueur(Joueur J1,Joueur J2, Window& FenErreur, Setup& param)
{ // terrain1 et terrain 2 sont des tableaux 10*10 et peuvent être utilisé a partir d'ici (pas
  // avant).
  FenErreur.clear();
  FenErreur.print(1, 1, "Partie", BWHITE);
  Window TerrainJ1(10, 10, 0, 10, ' ');
  Window TerrainJ2(10, 10, 13, 10, ' ');
  Window setup(10, 15, 62, 8,' ');
  J1.afficheTerrainCache(TerrainJ1);
  J2.afficheTerrainCache(TerrainJ2);
  int ch;
  int ajouer;
  int jRestant = param.getNombreTerrain();
  ajouer = generer_bornes(1,2);
  
  param.traiterOption(setup, FenErreur);
  while (param.getChoix() != "Quit" && jRestant != 1)
    {
      ch = getch();
      switch (ch)
        {
	case 27:
	  param.setChoix("Pause");
	  param.traiterOption(setup, FenErreur);
	  if (param.getChoix()=="Sauvergarder"){
	    param.sauvegarder(J1);
	    param.sauvegarder(J2);
	    param.setChoix("Resume");
	  }
	  break;
	case 10:
	  switch (ajouer)
	    {
	    case 1: // J1 attaque
	      if(J1.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
		int score = J1.getScore();
		J1.setScore(score +1);
		if(J1.getIA() == false){
		  J2.afficheTerrainCache(TerrainJ2);
		  TerrainJ2.print(0,0, ' ',BRED);
		  phaseDeplacement(J2,TerrainJ2);
		}
		else {
		  J2.afficheTerrainCache(TerrainJ2);
		  iaJoue(J2,TerrainJ2);
		}
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
		ajouer = 2;
	      }
	      else {
		param.setChoix("Pause");
		param.traiterOption(setup, FenErreur);
	      }
	      break;
	    case 2: //J2 attaque
	      if(J2.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
		int score = J2.getScore();
		J2.setScore(score +1);
		if(J2.getIA() == false){
		  J1.afficheTerrainCache(TerrainJ1);
		  TerrainJ1.print(0,0, ' ',BRED);
		  phaseDeplacement(J1,TerrainJ1);
		}
		else {
		  J1.afficheTerrainCache(TerrainJ1);
		  iaJoue(J1,TerrainJ1);
		}
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
		ajouer = 1;
	      }
	      else {
		param.setChoix("Pause");
		param.traiterOption(setup, FenErreur);
	      }
	      break;
	    }
	  break;
	}
    }
  
}




void Jouer::partie3Joueur(Joueur J1, Joueur J2, Joueur J3, Window& FenErreur, Setup& param)
{ // terrain1 et terrain 2 sont des tableaux 10*10 et peuvent être utilisé a partir d'ici (pas
  // avant).
  FenErreur.clear();
  FenErreur.print(1, 1, "Partie", BWHITE);
  Window TerrainJ1(10, 10, 0, 10, ' ');
  Window TerrainJ2(10, 10, 13, 10, ' ');
  Window TerrainJ3(10, 10, 26, 10, ' ');
  Window setup(10, 15, 62, 8,' ');
  J1.afficheTerrainCache(TerrainJ1);
  J2.afficheTerrainCache(TerrainJ2);
  J3.afficheTerrainCache(TerrainJ3);
  int ch;
  int ajouer;
  int jRestant = param.getNombreTerrain();
  int terrainChoisit;
  //bool valide;
  ajouer = generer_bornes(1,3);
  
  param.traiterOption(setup, FenErreur);
  while (param.getChoix() != "Quit" && jRestant != 1)
    {
      ch = getch();
      switch (ch)
        {
	case 27:
	  param.setChoix("Pause");
	  param.traiterOption(setup, FenErreur);
	  if (param.getChoix()=="Sauvergarder"){
	    param.sauvegarder(J1);
	    param.sauvegarder(J2);
	    param.sauvegarder(J3);
	    param.setChoix("Resume");
	  }
	  break;
	case 10:
	  switch (ajouer)
	    {
	    case 1: // J1 attaque
	      if(J1.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
		int score = J1.getScore();
		J1.setScore(score +1);
		if(J1.getIA() == false){
		  if((J3.estMort() == false) && (J2.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J1.getNumero());
		  }
		  else {
		    if (J3.estMort() == true) terrainChoisit = 2;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 3){   //SI J1 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    TerrainJ3.print(0,0, ' ',BRED);
		    phaseDeplacement(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 2){  // Si J1 attaque J3
		    J2.afficheTerrainCache(TerrainJ2);
		    TerrainJ2.print(0,0, ' ',BRED);
		    phaseDeplacement(J2,TerrainJ2);
		  }
		}
		else {
		  if((J3.estMort() == false) && (J2.estMort() == false)){
		    terrainChoisit = generer_bornes(1,2);
		  }
		  else {
		    if (J3.estMort() == true) terrainChoisit = 2;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    iaJoue(J2,TerrainJ2);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
	      ajouer = 2;
	      break;
	    case 2: //J2 attaque
	      
	      if(J2.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
		int score = J2.getScore();
		J2.setScore(score +1);
		if(J2.getIA() == false){
		  if((J1.estMort() == false) && (J3.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J2.getNumero());
		  }
		  else {
		    if (J1.estMort() == true) terrainChoisit = 3;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 1){   //SI J2 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    TerrainJ1.print(0,0, ' ',BRED);
		    phaseDeplacement(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 3){  // Si J2 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    TerrainJ3.print(0,0, ' ',BRED);
		    phaseDeplacement(J3,TerrainJ3);
		  }
		}
		else {
		  if((J1.estMort() == false) && (J3.estMort() == false)){
		    terrainChoisit = generer_bornes(1,2);
		  }
		  else {
		    if (J1.estMort() == true) terrainChoisit = 2;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 1){   //SI J2 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    iaJoue(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J2 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 3", BWHITE);
	      ajouer = 3;
	      break;
	    case 3: //J3 attaque
	      
	     if(J3.estMort() == false){
	       FenErreur.clear();
	       FenErreur.print(1, 1, "Au tour de Joueur 3", BWHITE);
	       int score = J3.getScore();
	       J3.setScore(score+1);
		if(J3.getIA() == false){
		  if((J1.estMort() == false) && (J2.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J3.getNumero());
		  }
		  else {
		    if (J1.estMort() == true) terrainChoisit = 2;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    TerrainJ1.print(0,0, ' ',BRED);
		    phaseDeplacement(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    TerrainJ2.print(0,0, ' ',BRED);
		    phaseDeplacement(J2,TerrainJ2);
		  }
		}
		else {
		  if((J1.estMort() == false) && (J2.estMort() == false)){
		    terrainChoisit = generer_bornes(1,2);
		  }
		  else {
		    if (J1.estMort() == true) terrainChoisit = 2;
		    else terrainChoisit = 1;
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    iaJoue(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    iaJoue(J2,TerrainJ2);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
	      ajouer = 1;
	      break;
	    }
	  break;
        }
    }
}



void Jouer::partie4Joueur(Joueur J4,Joueur J3,Joueur J1,Joueur J2, Window& FenErreur, Setup& param)
{ // terrain1 et terrain 2 sont des tableaux 10*10 et peuvent être utilisé a partir d'ici (pas
  // avant).
 
  FenErreur.clear();
  FenErreur.print(1, 1, "Partie", BWHITE);
  Window TerrainJ1(10, 10, 0, 10, ' ');
  Window TerrainJ2(10, 10, 13, 10, ' ');
  Window TerrainJ3(10, 10, 26, 10, ' ');
  Window TerrainJ4(10, 10, 39, 10, ' ');
  Window setup(10, 15, 62, 8,' ');
  J1.afficheTerrainCache(TerrainJ1);
  J2.afficheTerrainCache(TerrainJ2);
  J3.afficheTerrainCache(TerrainJ3);
  J4.afficheTerrainCache(TerrainJ4);
  int ch;
  int ajouer;
  int jRestant = param.getNombreTerrain();
  int terrainChoisit;
  //bool valide;
  ajouer = generer_bornes(1,4);
  
  param.traiterOption(setup, FenErreur);
  while (param.getChoix() != "Quit" && jRestant != 1)
    {
      ch = getch();
      switch (ch)
        {
	case 27:
	  param.setChoix("Pause");
	  param.traiterOption(setup, FenErreur);
	  if (param.getChoix()=="Sauvergarder"){
	    param.sauvegarder(J1);
	    param.sauvegarder(J2);
	    param.sauvegarder(J3);
	    param.sauvegarder(J4);
	    param.setChoix("Resume");
	  }
	  break;
	case 10:
	  switch (ajouer)
	    {
	    case 1: // J1 attaque
	      if(J1.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
		int score = J1.getScore();
		J1.setScore(score +1);
		if(J1.getIA() == false){
		  if((J3.estMort() == false) && (J2.estMort() == false) &&
		     (J4.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J1.getNumero());
		  }
		  if(terrainChoisit == 3){   //SI J1 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    TerrainJ3.print(0,0, ' ',BRED);
		    phaseDeplacement(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 2){  // Si J1 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    TerrainJ2.print(0,0, ' ',BRED);
		    phaseDeplacement(J2,TerrainJ2);
		  }
		   else if (terrainChoisit == 4){  // Si J1 attaque J4
		    J4.afficheTerrainCache(TerrainJ4);
		    TerrainJ4.print(0,0, ' ',BRED);
		    phaseDeplacement(J4,TerrainJ4);
		  }
		}
		else {
		  if((J3.estMort() == false) && (J2.estMort() == false) &&
		     (J4.estMort() == false)){
		    terrainChoisit = generer_bornes(2,4);
		  }
		  if(terrainChoisit == 3){   //SI J3 attaque J1
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    iaJoue(J2,TerrainJ2);
		  }
		  else if (terrainChoisit == 4){  // Si J3 attaque J2
		    J4.afficheTerrainCache(TerrainJ4);
		    iaJoue(J4,TerrainJ4);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
	      ajouer = 2;
	      break;
	    case 2: //J2 attaque
	      
	      if(J2.estMort() == false){
		FenErreur.clear();
		FenErreur.print(1, 1, "Au tour de Joueur 2", BWHITE);
		int score = J2.getScore();
		J2.setScore(score +1);
		if(J2.getIA() == false){
		  if((J1.estMort() == false) && (J3.estMort() == false) &&
		     (J4.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J2.getNumero());
		  }
		  if(terrainChoisit == 1){   //SI J2 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    TerrainJ1.print(0,0, ' ',BRED);
		    phaseDeplacement(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 3){  // Si J2 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    TerrainJ3.print(0,0, ' ',BRED);
		    phaseDeplacement(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 4){  // Si J2 attaque J3
		    J4.afficheTerrainCache(TerrainJ4);
		    TerrainJ4.print(0,0, ' ',BRED);
		    phaseDeplacement(J4,TerrainJ4);
		  }
		}
		else {
		  if((J1.estMort() == false) && (J3.estMort() == false)&&
		     (J4.estMort() == false)){
		    terrainChoisit = generer_bornes(1,4);
		  }
		  if(terrainChoisit == 1){   //SI J2 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    iaJoue(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J2 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 3){  // Si J2 attaque J3
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		  else if (terrainChoisit == 4){  // Si J2 attaque J3
		    J4.afficheTerrainCache(TerrainJ4);
		    iaJoue(J4,TerrainJ4);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 3", BWHITE);
	      ajouer = 3;
	      break;
	    case 3: //J3 attaque
	      
	     if(J3.estMort() == false){
	       FenErreur.clear();
	       FenErreur.print(1, 1, "Au tour de Joueur 3", BWHITE);
	       int score = J3.getScore();
	       J3.setScore(score+1);
		if(J3.getIA() == false){
		  if((J1.estMort() == false) && (J2.estMort() == false)&&
		     (J4.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J3.getNumero());
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    TerrainJ1.print(0,0, ' ',BRED);
		    phaseDeplacement(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    TerrainJ2.print(0,0, ' ',BRED);
		    phaseDeplacement(J2,TerrainJ2);
		  }
		  else if (terrainChoisit == 4){  // Si J3 attaque J2
		    J4.afficheTerrainCache(TerrainJ4);
		    TerrainJ4.print(0,0, ' ',BRED);
		    phaseDeplacement(J4,TerrainJ4);
		  }
		}
		else {
		  if((J1.estMort() == false) && (J2.estMort() == false)&&
		     (J4.estMort() == false)){
		    terrainChoisit = generer_bornes(1,4);
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    iaJoue(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    iaJoue(J2,TerrainJ2);
		  }
		  
		  else if (terrainChoisit == 3){  // Si J3 attaque J2
		    J4.afficheTerrainCache(TerrainJ4);
		    iaJoue(J4,TerrainJ4);
		  }
		  
		  else if (terrainChoisit == 4){  // Si J3 attaque J2
		    J4.afficheTerrainCache(TerrainJ4);
		    iaJoue(J4,TerrainJ4);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 4", BWHITE);
	      ajouer = 4;
	      break;
	      case 4: //J3 attaque
	      
	     if(J4.estMort() == false){
	       FenErreur.clear();
	       FenErreur.print(1, 1, "Au tour de Joueur 4", BWHITE);
	       int score = J4.getScore();
	       J4.setScore(score+1);
		if(J4.getIA() == false){
		  if((J1.estMort() == false) && (J2.estMort() == false)&&
		     (J3.estMort() == false)){
		    terrainChoisit = choixAttaque(param, J4.getNumero());
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    TerrainJ1.print(0,0, ' ',BRED);
		    phaseDeplacement(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    TerrainJ2.print(0,0, ' ',BRED);
		    phaseDeplacement(J2,TerrainJ2);
		  }
		  else if (terrainChoisit == 3){  // Si J3 attaque J2
		    J3.afficheTerrainCache(TerrainJ3);
		    TerrainJ3.print(0,0, ' ',BRED);
		    phaseDeplacement(J3,TerrainJ3);
		  }
		}
		else {
		  if((J1.estMort() == false) && (J2.estMort() == false)&&
		     (J4.estMort() == false)){
		    terrainChoisit = generer_bornes(1,4);
		  }
		  if(terrainChoisit == 1){   //SI J3 attaque J1
		    J1.afficheTerrainCache(TerrainJ1);
		    iaJoue(J1,TerrainJ1);
		  }
		  else if (terrainChoisit == 2){  // Si J3 attaque J2
		    J2.afficheTerrainCache(TerrainJ2);
		    iaJoue(J2,TerrainJ2);
		  }
		  
		  else if (terrainChoisit == 3){  // Si J3 attaque J2
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		  
		  else if (terrainChoisit == 4){  // Si J3 attaque J2
		    J3.afficheTerrainCache(TerrainJ3);
		    iaJoue(J3,TerrainJ3);
		  }
		}
	      }
	      FenErreur.clear();
	      FenErreur.print(1, 1, "Au tour de Joueur 1", BWHITE);
	      ajouer = 1;
	      break;
	    }
	  break;
        }
    }
}
