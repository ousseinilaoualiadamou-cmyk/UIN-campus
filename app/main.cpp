#include "uincampus/saisie.hpp"

#include <cstdlib>
#include <vector>

int main() {
  std::vector<double> notes;
  int choix{};

  do {
    choix = carnet::afficherMenu();
    switch (choix) {
    case 1:
      carnet::ajouter(notes);
      break;
    case 2:
      carnet::afficherNotes(notes);
      break;
    case 3:
      carnet::modifier(notes);
      break;
    case 4:
      carnet::supprimer(notes);
      break;
    case 5:
      carnet::trierNotes(notes);
      break;
    case 6:
      carnet::afficherStatistiques(notes);
      break;
    case 7:
      carnet::appliquerBonusNotes(notes);
      break;
    default:
      break;
    }
  } while (choix != 0);

  return EXIT_SUCCESS;
}
