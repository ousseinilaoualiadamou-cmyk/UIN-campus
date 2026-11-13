#include "uincampus/calculs.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

namespace uin {

double somme(const std::vector<double> &valeurs) {
  return std::accumulate(valeurs.begin(), valeurs.end(), 0.0);
}

double moyenne(const std::vector<double> &notes) {
  assert(!notes.empty() && "moyenne() : aucune note");
  return somme(notes) / static_cast<double>(notes.size());
}

double moyenne(const std::vector<double> &notes,
               const std::vector<double> &coefficients) {
  assert(!notes.empty() && "moyenne() : aucune note");
  assert(notes.size() == coefficients.size() &&
         "moyenne() : tailles différentes");

  const double sommeCoefficients = somme(coefficients);
  assert(sommeCoefficients > 0.0 && "moyenne() : somme des coefficients nulle");

  const double sommePonderee =
      std::inner_product(notes.begin(), notes.end(), coefficients.begin(), 0.0);
  return sommePonderee / sommeCoefficients;
}

int compterValidees(const std::vector<double> &notes, double seuil) {
  return static_cast<int>(
      std::ranges::count_if(notes, [seuil](double n) { return n >= seuil; }));
}

Statistiques calculerStatistiques(const std::vector<double> &notes) {
  assert(!notes.empty() && "calculerStatistiques() : aucune note");

  const auto [mini, maxi] = std::ranges::minmax(notes);

  return Statistiques{
      .minimum = mini,
      .maximum = maxi,
      .moyenne = moyenne(notes),
      .nbValidees = compterValidees(notes, 10.0),
  };
}

double arrondir(double valeur, int decimales) {
  const double facteur = std::pow(10.0, decimales);
  return std::round(valeur * facteur) / facteur;
}

void trier(std::vector<double> &notes, Ordre ordre) {
  if (ordre == Ordre::Croissant) {
    std::ranges::sort(notes);
  } else {
    std::ranges::sort(notes, [](double a, double b) { return a > b; });
  }
}
void appliquerBonus(std::vector<double> &notes, double bonus) {
  std::ranges::for_each(
      notes, [bonus](double &n) { n = std::clamp(n + bonus, 0.0, 20.0); });
}
} // namespace uin