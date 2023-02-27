/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author IFT-2008 & Hamza Hajjam
 * \version 0.1
 * \date fév. 2023
 *
 */

#include "Regle.h"

namespace tp1 {
    // Compléter les méthodes demandées et corriger éventuellement la valeur de retour !
    // Ajouter aussi les balises Doxygen et commenter bien vos méthodes.

    //Constructeur de la classe Regle
    Regle::Regle() {
    }

    //Constructeur de copie.
    Regle::Regle(const Regle &r) {
        this->premisses = r.premisses;
        this->conclusions = r.conclusions;
    }

    //Destructeur
    Regle::~Regle() {
    }

    // surcharge de l’opérateur =
    Regle &Regle::operator=(const Regle &r) {
        if (this != &r)
        {
            this->premisses = r.premisses;
            this->conclusions = r.conclusions;
        }

        return *this;
    }

    // surcharge de l’opérateur ==
    bool Regle::operator==(const Regle &r) const {
        bool resultPremisses = std::equal(r.premisses.begin(), r.premisses.end(), this->premisses.begin());
        bool resultConlusions = std::equal(r.conclusions.begin(), r.conclusions.end(), this->conclusions.begin());

        return resultConlusions && resultPremisses;
    }

    // surcharge de l’opérateur !=
    bool Regle::operator!=(const Regle &r) const {
        return !(r == *this);
    }

}
