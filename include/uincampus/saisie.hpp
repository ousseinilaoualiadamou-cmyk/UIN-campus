#pragma once
#include <string>
#include <string_view>
#include <vector>
namespace uin {
/// Lit une ligne de texte (espaces compris).
std::string lireTexte(std::string_view invite);
/// Lit un entier compris entre min et max ; redemande tant que la saisie est
/// invalide.
int lireEntier(std::string_view invite, int min, int max);
/// Lit une note valide ; accepte la virgule décimale.
double lireNote(std::string_view invite);
} // namespace uin
namespace carnet {

[[nodiscard]] int afficherMenu();
void ajouter(std::vector<double> &notes);
void afficherNotes(const std::vector<double> &notes);
void modifier(std::vector<double> &notes);
void supprimer(std::vector<double> &notes);
void trierNotes(std::vector<double> &notes);
void afficherStatistiques(const std::vector<double> &notes);
void appliquerBonusNotes(std::vector<double> &notes);
} // namespace carnet