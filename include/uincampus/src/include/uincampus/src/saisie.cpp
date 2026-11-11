#include "uincampus/saisie.hpp"
#include "uincampus/regles.hpp"

#include <iostream>
#include <sstream>

namespace uin {

namespace {

std::string lireLigne(std::string_view invite)
{
    std::cout << invite;

    std::string ligne;
    std::getline(std::cin, ligne);

    return ligne;
}

bool estEntierStrict(const std::string& texte, int& valeur)
{
    std::istringstream flux{texte};

    if (!(flux >> valeur)) {
        return false;
    }

    flux >> std::ws;

    return flux.eof();
}

bool estReelStrict(std::string texte, double& valeur)
{
    for (char& caractere : texte) {
        if (caractere == ',') {
            caractere = '.';
        }
    }

    std::istringstream flux{texte};

    if (!(flux >> valeur)) {
        return false;
    }

    flux >> std::ws;

    return flux.eof();
}

}

std::string lireTexte(std::string_view invite)
{
    return lireLigne(invite);
}

int lireEntier(std::string_view invite, int min, int max)
{
    while (true) {
        const std::string ligne = lireLigne(invite);

        int valeur{};

        if (!estEntierStrict(ligne, valeur)) {
            std::cout << "Saisie invalide : entrez un entier.\n";
        }
        else if (valeur < min || valeur > max) {
            std::cout << "La valeur doit être comprise entre "
                      << min << " et " << max << ".\n";
        }
        else {
            return valeur;
        }
    }
}

double lireNote(std::string_view invite)
{
    while (true) {
        const std::string ligne = lireLigne(invite);

        double note{};

        if (!estReelStrict(ligne, note)) {
            std::cout << "Saisie invalide.\n";
        }
        else if (!estNoteValide(note)) {
            std::cout << "La note doit être comprise entre 0 et 20.\n";
        }
        else {
            return note;
        }
    }
}

}
