#include <iostream>
#include <stdlib.h>
#include "setup.h"
#include "jouer.h"

using namespace std;

Setup::Setup(): etat_jeu(false), nb_joueur(0), nb_terrain(0), choix("Menu"), menuP(), menuT(), menuJ(), menuG(){
  menuP.menuPrincipale();
  menuT.menuTerrain();
  menuG.menuGaming();
}

//setup::set(bool etat, int nb_j, int nb_t, std::string ch): etat_jeu(etat), nb_joueur(nb_j), nb_t(nb_terrain), choix(ch){}


//accesseur en lecture
bool Setup::getEtatDuJeu() const { return etat_jeu;}
int Setup::getNombreJoueur() const { return nb_joueur; }
int Setup::getNombreTerrain() const { return nb_terrain; }
std::string Setup::getNomJoueur()const { return nom_joueur;}
std::string Setup::getChoix() const { return choix;}

//accesseur en écriture
void Setup::setNombreJoueur(int i) { nb_joueur = i;}
void Setup::setNombreTerrain(int i) { nb_terrain = i;}
void Setup::setNomJoueur(std::string s) { nom_joueur = s;}
void Setup::setChoix(std::string s) { choix = s;}


void Setup::sauvegarder(Joueur& J){
  ofstream fichier("sauvegarde.txt",ios::app);
  if(fichier.tellp()==0)
    fichier<<nb_terrain<<endl;
  
  fichier<<J.getNumero()<<endl;
  
  if(J.getIA())
    fichier<<"True"<<endl;
  else
    fichier<<"False"<<endl;
  
  if(J.getVictoire())
    fichier<<"Oui"<<endl;
  else
    fichier<<"Non"<<endl;

  fichier<<J.getScore()<<endl;

  for(int i=0;i<10;i++){ //Tableau
    for(int j=0;j<10;j++)
      fichier<<J.getTerrain(i,j)<<" ";
    
    fichier<<endl;
  }

  fichier.close();
      
    
}


int Setup::Charger(int Pos,Joueur& J){
  ifstream fichier("sauvegarde.txt", ios::in);
  fichier.seekg(Pos, ios::beg);
  string T;
  int x;
  if(fichier){
    if(Pos==0)
      fichier>>nb_terrain; //Nb_terrain
    
    fichier>>x; //Numero Joueur
    fichier>>T; //IA
    if(T=="True")
      J.setIA(1);
    else
      J.setIA(0);
			    
    fichier>>T; //En Vie
    if(T=="Oui")
      J.setVictoire(1);
    else
      J.setVictoire(0);
    
    fichier>>x; //score
    J.setScore(x);

    for(int i=0;i<10;i++) //Tableau
      for(int j=0;j<10;j++){
	fichier>>x;
	J.setTerrain(i,j,x);
      }

  }			
  Pos=fichier.tellg();
  fichier.close();
  return Pos;
}

void Setup::traiterOption(Window &opt, Window &mess){
  int key;
  int highlight = 0;
  if(etat_jeu == true){
    menuG.printListOptions(opt, highlight);
    mess.print(1,1, menuG.getDescription(highlight));
  }
  else{
    menuP.printListOptions(opt, highlight);
    mess.print(1, 1, menuP.getDescription(highlight));
  }

  while((key = getch()) != 27 || choix != "Resume"){
    if(choix == "Quit"){
      break;
    }


    if(choix == "Menu"){
      switch (key) {
      case KEY_UP:
	highlight --;
	if(highlight == -1){
	  highlight = 0;
	}
	menuP.printListOptions(opt, highlight);
	mess.clear();
	mess.print(1,1, menuP.getDescription(highlight));
	break;

      case KEY_DOWN:
	highlight++;
	if (highlight == (menuP.getNbOptions())) {
	  highlight = menuP.getNbOptions() - 1;
	}
	menuP.printListOptions(opt, highlight);
	mess.clear();
	mess.print(1, 1, menuP.getDescription(highlight));
	break;
      }
      if(key == 10){
	choix = menuP.getNameOptions(highlight);
      }
      if(choix == "New"){
	mess.clear();
	mess.print(1,1, "Veillez choisir le nombre de terrain");
	menuT.printListOptions(opt, highlight);
	highlight = 0;
	choix = "Terrain";
	key = 0;
      }
    }
  



    
    if (choix=="Charger"){
      Jouer Partie;
      int PosCur=0;
      Joueur J1(1);
      PosCur=Charger(PosCur,J1);
      if (nb_terrain==2){
	Joueur J2(2);
	PosCur=Charger(PosCur,J2);
	etat_jeu=true;
	choix="Resume";
        Partie.partie2Joueur(J1,J2,mess,*this);
      }
			     
      if (nb_terrain==3){
	Joueur J2(2);
	PosCur=Charger(PosCur,J2);
	Joueur J3(3);
	PosCur=Charger(PosCur,J3);
	etat_jeu=true;
	choix="Resume";
        Partie.partie3Joueur(J1,J2,J3,mess,*this);

      }
      if(nb_terrain==4){
	Joueur J2(2);
	PosCur=Charger(PosCur,J2);
	Joueur J3(3);
	PosCur=Charger(PosCur,J3);
	Joueur J4(4);
	PosCur=Charger(PosCur,J4);
	etat_jeu=true;
	choix="Resume";
        Partie.partie4Joueur(J4,J3,J1,J2,mess,*this);

      }
    }
    

  if(choix == "Terrain"){
    switch(key){
    case KEY_UP:
      highlight--;
      if(highlight == -1){
	highlight = 0;
      }
      menuT.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1, menuT.getDescription(highlight));
      break;

    case KEY_DOWN:
      highlight++;
      if(highlight == (menuT.getNbOptions())){
	highlight = menuT.getNbOptions() -1;
      }
      menuT.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1,menuT.getDescription(highlight));
      break;
    }

    if(key == 10){
      if(menuT.getNameOptions(highlight) != "Retourne"){
	nb_terrain = atoi(menuT.getShortcut(highlight).c_str());
	choix = "Joueur";
	highlight = 0;
	mess.print(1,1, "Veillez choisir le nombre de joueur");
	TabOptions menuJ_tempo;
  menuJ_tempo.menuJoueur(nb_terrain);
  menuJ = menuJ_tempo;
	menuJ.printListOptions(opt, highlight);
	key = 0;
      }else{
	choix = "Menu";
	highlight = 0;
	menuP.printListOptions(opt, highlight);
	mess.clear();
	mess.print(1, 1, menuP.getDescription(highlight));
	key = 0;
      }	
    }
  }

  if(choix == "Joueur"){
    switch(key){
    case KEY_UP:
      highlight--;
      if(highlight == -1){
	highlight = 0;
      }
      menuJ.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1, menuJ.getDescription(highlight));
      break;

    case KEY_DOWN:
      highlight++;
      if(highlight == (menuJ.getNbOptions())){
	highlight = menuJ.getNbOptions() -1;
      }
      menuJ.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1,menuJ.getDescription(highlight));
      break;
    }
    if(key == 10){
      if(menuJ.getNameOptions(highlight) != "Retourne"){
	nb_joueur = atoi(menuJ.getShortcut(highlight).c_str());
	etat_jeu = true;
	choix = "Resume";
	key = 0;
      }else{
	choix = "Terrain";
	highlight = 0;
	menuT.printListOptions(opt, highlight);
	menuJ.clearOption();
	mess.clear();
	mess.print(1,1, menuT.getDescription(highlight));
	key = 0;
      }
    }
  }

  if(choix == "Resume"){
    break;
  }

  if(choix == "Help"){
    choix = "Menu";
    mess.clear();
    mess.print(1,1, "Ceci est le tuto");
  }

  if(choix == "Version"){
    choix = "Menu";
    mess.clear();
    mess.print(1,1, "La version du jeu est 1.0. Ce jeu a été réalisé par SAFFIN, DI MARINO, MARTIAL, NGUYEN");
  }

  if(choix == "Sauvergarder"){
   ofstream fichier("sauvegarde.txt" );
   fichier.close();
    break;
  }

  if(etat_jeu == true && choix == "Pause"){
    switch(key){
    case KEY_UP:
      highlight--;
      if(highlight == -1){
	highlight = 0;
      }
      menuG.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1,menuG.getDescription(highlight));
      break;

    case KEY_DOWN:
      highlight++;
      if(highlight == (menuG.getNbOptions())){
	highlight = menuG.getNbOptions()-1;
      }
      menuG.printListOptions(opt, highlight);
      mess.clear();
      mess.print(1,1,menuG.getDescription(highlight));
      break;
    }
    if(key == 10){
      choix = menuG.getNameOptions(highlight);
      if(choix == "Menu"){ etat_jeu = false;}
      key = 0;
    }
  }
}
} 
