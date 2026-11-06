#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/version.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::cout << "UIN|Campus - Calcul de la moyenne d'un etudiant\n\n";

  const std::string nom = uin::lireTexte("Nom de l'etudiant : ");
  const int nbNotes = uin::lireEntier("Nombre de notes (1 a 30) : ", 1, 30);

  std::vector<double> notes;
  for (int i = 0; i < nbNotes; ++i) {
    notes.push_back(uin::lireNote("Note " + std::to_string(i + 1) + " : "));
  }

  double somme(0.0);
  for (double n : notes) {
    somme += n;
  }

  const double moyenne = somme / static_cast<double>(notes.size());
  const uin::Mention mention = uin::mentionPour(moyenne);

  std::cout << std::left << std::setw(20) << "Decision" << std::right
            << std::setw(20)
            << (moyenne >= uin::seuilValidation ? "Valide" : "Non valide")
            << "\n";
  std::cout << std::left << std::setw(20) << "Nombre de notes" << std::right
            << std::setw(20) << notes.size() << "\n";
  std::cout << std::left << std::setw(20) << "Moyenne" << std::right
            << std::setw(20) << std::fixed << std::setprecision(2) << moyenne
            << "\n";
  std::cout << std::left << std::setw(20) << "Mention" << std::right
            << std::setw(20) << uin::libelle(mention) << "\n";
  std::cout << std::left << std::setw(20) << "Decision" << std::right
            << std::setw(20)
            << (moyenne >= uin::seuilValidation ? "Valide" : "Non valide")
            << "\n";
  std::cout << std::string(40, '-') << "\n";

  return 0;
}