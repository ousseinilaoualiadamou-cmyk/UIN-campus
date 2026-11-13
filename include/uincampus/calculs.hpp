#pragma once

#include "uincampus/regles.hpp"

#include <vector>

namespace uin {

/// Indicateurs statistiques d'une série de notes.
struct Statistiques {
  double minimum{};
  double maximum{};
  double moyenne{};
  int nbValidees{};
};

/// Somme des valeurs.
[[nodiscard]] double somme(const std::vector<double> &valeurs);

/// Moyenne arithmétique.
/// @pre notes n'est pas vide
[[nodiscard]] double moyenne(const std::vector<double> &notes);

/// Moyenne pondérée par les coefficients.
/// @pre notes n'est pas vide, notes et coefficients ont la même taille,
///      la somme des coefficients est strictement positive
[[nodiscard]] double moyenne(const std::vector<double> &notes,
                             const std::vector<double> &coefficients);

/// Nombre de notes supérieures ou égales au seuil.
[[nodiscard]] int compterValidees(const std::vector<double> &notes,
                                  double seuil = seuilValidation);

/// Minimum, maximum, moyenne et nombre de notes validées.
/// @pre notes n'est pas vide
[[nodiscard]] Statistiques
calculerStatistiques(const std::vector<double> &notes);

/// Arrondi au nombre de décimales demandé.
[[nodiscard]] double arrondir(double valeur, int decimales = 2);
/// Sens du tri.
enum class Ordre { Croissant, Decroissant };

/// Trie les notes dans l'ordre demandé.
void trier(std::vector<double> &notes, Ordre ordre);
/// Ajoute un bonus à chaque note, en bornant le résultat entre 0 et 20.
void appliquerBonus(std::vector<double> &notes, double bonus);
} // namespace uin