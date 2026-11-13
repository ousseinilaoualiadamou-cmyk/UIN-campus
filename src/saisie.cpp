#include "uincampus/saisie.hpp"
#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"
#include <format>
#include <iostream>
#include <print>
#include <sstream>
namespace uin {
namespace {
struct EntierLu {
  bool valide{false};
  int valeur{0};
};
struct ReelLu {
  bool valide{false};
  double valeur{0.0};
};
std::string lireLigne(std::string_view invite) {
  std::cout << invite;
  std::string ligne;
  std::getline(std::cin, ligne);
  return ligne;
}
[[nodiscard]] EntierLu versEntier(const std::string &texte) {
  std::istringstream flux{texte};
  int valeur{};
  char reste{};
  const bool valide = (flux >> valeur) && !(flux >> reste);
  return {valide, valeur};
}
[[nodiscard]] ReelLu versReel(std::string texte) {
  for (char &c : texte) {
    if (c == ',') {
      c = '.';
    }
  }
  std::istringstream flux{texte};
  double valeur{};
  char reste{};
  const bool valide = (flux >> valeur) && !(flux >> reste);
  return {valide, valeur};
}
} // namespace
std::string lireTexte(std::string_view invite) { return lireLigne(invite); }
int lireEntier(std::string_view invite, int min, int max) {
  while (std::cin) {
    const auto [valide, valeur] = versEntier(lireLigne(invite));
    if (!valide) {
      std::cout << "Saisie invalide : entrez un nombre entier.\n";
    } else if (valeur < min || valeur > max) {
      std::cout << "La valeur doit être comprise entre " << min << " et " << max
                << ".\n";
    } else {
      return valeur;
    }
  }
  return min;
}
double lireNote(std::string_view invite) {
  while (std::cin) {
    const auto [valide, note] = versReel(lireLigne(invite));
    if (!valide) {
      std::cout << "Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
    } else if (!estNoteValide(note)) {
      std::cout << "La note doit être comprise entre " << noteMin << " et "
                << noteMax << ".\n";
    } else {
      return note;
    }
  }
  return noteMin;
}
} // namespace uin
namespace carnet {

int afficherMenu() {
  std::cout << "\n=== Carnet de notes ===\n";
  std::cout << "1. Ajouter une note\n";
  std::cout << "2. Afficher les notes\n";
  std::cout << "3. Modifier une note\n";
  std::cout << "4. Supprimer une note\n";
  std::cout << "5. Trier les notes (croissant / décroissant)\n";
  std::cout << "6. Statistiques\n";
  std::cout << "7. Appliquer un bonus\n";
  std::cout << "0. Quitter\n";
  return uin::lireEntier("Votre choix : ", 0, 7);
}
void ajouter(std::vector<double> &notes) {
  notes.push_back(uin::lireNote("Note à ajouter : "));
}

void afficherNotes(const std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note.");
    return;
  }
  for (std::size_t i{0}; i < notes.size(); ++i) {
    std::println("{:>3}. {:6.2f}", i + 1, notes[i]);
  }
}

void modifier(std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note à modifier.");
    return;
  }
  afficherNotes(notes);
  const int rang = uin::lireEntier("Numéro de la note : ", 1,
                                   static_cast<int>(notes.size()));
  notes[static_cast<std::size_t>(rang - 1)] =
      uin::lireNote("Nouvelle valeur : ");
}
void supprimer(std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note à supprimer.");
    return;
  }
  afficherNotes(notes);
  const int rang = uin::lireEntier("Numéro de la note à supprimer : ", 1,
                                   static_cast<int>(notes.size()));
  notes.erase(notes.begin() + (rang - 1));
}
void trierNotes(std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note à trier.");
    return;
  }
  const int sens = uin::lireEntier("1. Croissant  2. Décroissant : ", 1, 2);
  uin::trier(notes,
             sens == 1 ? uin::Ordre::Croissant : uin::Ordre::Decroissant);
  afficherNotes(notes);
}
void afficherStatistiques(const std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note.");
    return;
  }
  const uin::Statistiques stats = uin::calculerStatistiques(notes);
  std::println("Minimum : {:.2f}", stats.minimum);
  std::println("Maximum : {:.2f}", stats.maximum);
  std::println("Moyenne : {:.2f}", stats.moyenne);
  std::println("UE validées : {} / {}", stats.nbValidees, notes.size());
}
void appliquerBonusNotes(std::vector<double> &notes) {
  if (notes.empty()) {
    std::println("Aucune note.");
    return;
  }
  const double bonus = uin::lireNote("Bonus à appliquer : ");
  uin::appliquerBonus(notes, bonus);
  afficherNotes(notes);
}
} // namespace carnet