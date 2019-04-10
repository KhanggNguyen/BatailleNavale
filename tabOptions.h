#ifndef __TABOPTIONS_H__
#define __TABOPTIONS_H__

#include <string>
#include "option.h"
#include "window.h"

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
#define UN_JOUEUR_ID 13
#define DEUX_JOUEUR_ID 14
#define TROIS_JOUEUR_ID 15
#define QUATRE_JOUEUR_ID 16
#define RETOURNE_ID 17




#define NMAX_OPTS 100
class TabOptions {
 private:
  Option opts[NMAX_OPTS];
  size_t nb_opts;
  int getOptionIndex(const std::string &opt) const;
 public:
  TabOptions();
  //~TabOptions();
  void addOption(const Option &o);
  void clearOption();
  void print() const;
  int getOptionId(const std::string &opt) const;
  bool optionHasArgument(const std::string &opt) const;
  Option::Type optionArgumentType(const std::string &opt) const;
  int getNbOptions()const;
  std::string getNameOptions(int);
  std::string getDescription(int);
	std::string getShortcut(int);
  void printListOptions(Window&, int);
	void menuPrincipale();
	void menuGaming();
	void menuTerrain();
  void menuJoueur(int);
};

#endif
