#include <iostream>
#include <time.h>
#include <string>
#include "setup.h"
#include "window.h"
#include "jouer.h"


using namespace std;

void myprogram()
{
  srand(time(NULL));

  Jouer partie;
  Window FenErreur(5,45,15, 0, ' ');
  FenErreur.setCouleurBordure(BWHITE);
  Window setup(10, 15, 62, 8,' ');
  setup.setCouleurBordure(BRED);
  Setup param;

  while (param.getChoix() != "Quit") {
    param.traiterOption(setup, FenErreur);
    if(param.getEtatDuJeu()==true)
      partie.choixPartie(param,FenErreur);

  }

}


int main()
{
  startProgramX();
  myprogram();
  stopProgramX();
  return 0;
}
