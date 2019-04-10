#ifndef __SETUP_H__
#define __SETUP_H__

#include "window.h"
#include "tabOptions.h"
#include <fstream>
#include <string> 
#include <iostream>
#include "joueur.h"

#define HELP_ID     1
#define VERSION_ID  2
#define NEWGAME_ID	3
#define RESUME_ID 	4
#define CONFIG_ID		5
#define SAVE_ID			6
#define QUIT_ID			7
#define LOAD_ID		8
#define UN_TERRAIN_ID 9
#define DEUX_TERRAIN_ID 10
#define TROIS_TERRAIN_ID 11
#define QUATRE_TERRAIN_ID 12

class Setup {
	private:
		bool etat_jeu;
		int nb_joueur;
		int nb_terrain;
		std::string nom_joueur;
		std::string choix;


		//Menu Principale
		TabOptions menuP;

		//menu choix de terrain durant le jeu
		TabOptions menuT;

		//menu choix de joueur 
		TabOptions menuJ;

		//menu en jeu
		TabOptions menuG;
	public:
		Setup();

		//accesseur en lecture
		bool getEtatDuJeu() const;
		int getNombreJoueur() const;
		int getNombreTerrain() const;
		std::string getNomJoueur() const;
		std::string getChoix() const;

		//accesseur en écriture
		void setEtatDuJeu(bool etat);
		void setNombreJoueur(int i);
		void setNombreTerrain(int i);
		void setNomJoueur(std::string s);
		void setChoix(std::string s);

		void traiterOption(Window&, Window&);
		void sauvegarder(Joueur&);
		int Charger(int,Joueur&);
};

#endif
