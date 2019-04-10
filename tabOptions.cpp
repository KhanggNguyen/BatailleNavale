#include <iostream>
#include <exception>
#include "tabOptions.h"
#include <string>
#include <sstream>

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

TabOptions::TabOptions(): opts(), nb_opts(0) {}

void TabOptions::clearOption(){
	unsigned int i = 0;
	while(i < nb_opts){
		opts[i].setId(0);
		i++;
	}
	nb_opts = 0;
}


void TabOptions::addOption(const Option &o) {
  if (nb_opts == NMAX_OPTS) {
   cerr << "Erreur: Impossible d'ajouter une nouvelle option." << endl
	<< "        Nombre maximum d'option atteint"<< " (" << NMAX_OPTS << ")."
	<< endl;
   terminate();   
  }
    
  bool found = (getOptionIndex(o.getName()) !=  -1) || (getOptionIndex(o.getShortcut()) !=  -1);
  
  if (found) {
    cerr << "Avertissement: L'identifiant " << o.getId() << " est déjà utilisé."
	 << endl;
  } else {
    opts[nb_opts] = o;
    nb_opts++;    
  }
}


void TabOptions::print() const {
  cout << "Options :" << endl;
  for (size_t i = 0; i < nb_opts; i++) {
    opts[i].print();
  }
}

int TabOptions::getOptionIndex(const string &opt) const {
  bool found = false;
  size_t i = 0;
  while (!found && (i < nb_opts)) {
    found = ((opts[i].getName() == opt) || (opts[i].getShortcut() == opt));
    i++;
  }
  return found ? i - 1 : -1;
}
// opt doit etre une option valide
int TabOptions::getOptionId(const std::string &opt) const {
  int i = getOptionIndex(opt);
  return (i>=0 ? opts[i].getId():-1);
}
// opt doit etre une option valide
bool TabOptions::optionHasArgument(const std::string &opt) const {
  size_t i = getOptionIndex(opt);
  return (opts[i].getType() != Option::AUCUN);
}
// opt doit etre une option valide
Option::Type TabOptions::optionArgumentType(const std::string &opt) const {
  size_t i = getOptionIndex(opt);
  return opts[i].getType();
}

int TabOptions::getNbOptions()const{
	return nb_opts;
}

std::string TabOptions::getNameOptions( int i){
	return opts[i].getName();
}

std::string TabOptions::getShortcut(int i){
	return opts[i].getShortcut();
}

std::string TabOptions::getDescription(int i){
	return opts[i].getDescription();
}

void TabOptions::menuPrincipale(){
	this->addOption(Option(NEWGAME_ID, "New", "n",
		        "Démarre une nouvelle partie",
		        Option::AUCUN));
	this->addOption(Option(HELP_ID, "Help", "h",
                        "Affiche l'aide du programme", Option::AUCUN));
  	this->addOption(Option(VERSION_ID, "Version", "v",
		        "Affiche la version du programme", Option::AUCUN));

  	this->addOption(Option(CONFIG_ID, "Configurer", "c",
		        "Charge la configuration initiale du jeu "
		        "à partir du fichier passé en paramètre",
		        Option::AUCUN));
	this->addOption(Option(LOAD_ID, "Charger", "ch", "Charger une partie", Option::AUCUN));

	this->addOption(Option(QUIT_ID, "Quit", "q",
		        "Quitter le jeu",
		        Option::AUCUN));
}

void TabOptions::menuGaming(){
	this->addOption(Option(0, "Resume", "r", "Pause/Reprendre le jeu", Option::AUCUN));
	this->addOption(Option(1, "Sauvergarder", "s", "Enregistrer le jeu", Option::AUCUN));
	this->addOption(Option(2, "Menu", "m", "Revenir dans le menu principal", Option::AUCUN));
	this->addOption(Option(3, "Quit", "q", "Quitter le jeu", Option::AUCUN));
}


void TabOptions::menuTerrain(){
	this->addOption(Option(DEUX_TERRAIN_ID, "2 terrains", "2", "2 terrains", Option::AUCUN));
	this->addOption(Option(TROIS_TERRAIN_ID, "3 terrains", "3", "3 terrains", Option::AUCUN));
	this->addOption(Option(QUATRE_TERRAIN_ID, "4 terrains", "4", "4 terrains", Option::AUCUN));
	this->addOption(Option(RETOURNE_ID, "Retourne", "r", "Retourne à la menu précedent", Option::AUCUN));
}

void TabOptions::menuJoueur(int terrain){

	std::string listString[4];
	listString[0] = "1 joueur";
	listString[1] = "2 joueurs";
	listString[2] = "3 joueurs";
	listString[3] = "4 joueurs";
	for(int i=0; i<terrain; i++){

		this->addOption(Option((i+1), listString[i], patch::to_string(i+1), listString[i], Option::AUCUN));
	}
	this->addOption(Option(RETOURNE_ID, "Retourne", "r", "Retourne à la menu précedent", Option::AUCUN)); 
	// this->addOption(Option(UN_JOUEUR_ID, "1 joueur", "1", "1 joueur", Option::AUCUN));
	// this->addOption(Option(DEUX_JOUEUR_ID, "2 joueurs", "2", "2 joueurs", Option::AUCUN));
	// this->addOption(Option(TROIS_JOUEUR_ID, "3 joueurs", "3", "3 joueurs", Option::AUCUN));
	// this->addOption(Option(QUATRE_JOUEUR_ID, "4 joueurs", "4", "4 joueurs", Option::AUCUN));
}

void TabOptions::printListOptions(Window &w, int i){
	w.clear();
		        
	for(int indice = 0; indice < this->getNbOptions(); indice++){
		if( indice == i){
			w.print(1,indice, this->getNameOptions(indice), WBLUE);
		}
		w.print(1,indice, this->getNameOptions(indice));
	}
}


