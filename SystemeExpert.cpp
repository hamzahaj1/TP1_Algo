/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author IFT-2008 & Hamza Hajjam
 * \version 0.1
 * \date fév. 2023
 *
 */

#include "SystemeExpert.h"

namespace tp1 {

    namespace utilitaire {
        void nettoyer(std::string &str) {
            str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
        }
    }

    // Compléter les méthodes demandées et corriger éventuellement la valeur de retour !
    // Ajouter aussi les balises Doxygen et commenter bien vos méthodes.
    //constructeur
    SystemeExpert::SystemeExpert() {
    }

    //destructeur
    SystemeExpert::~SystemeExpert() {
    }

    //constructeur de copie
    SystemeExpert::SystemeExpert(const SystemeExpert &se) {
        this->baseFaits = se.baseFaits;
        this->baseRegles = se.baseRegles;
    }

    // surcharge de l'opérateur =
    SystemeExpert &SystemeExpert::operator=(const SystemeExpert &se) {
        if (this != &se) {
            this->baseFaits = se.baseFaits;
            this->baseRegles = se.baseRegles;
        }

        return *this;
    }

    // Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert
    void SystemeExpert::ajouterRegleSE(const Regle &tr) {
        for (const auto &regle: baseRegles) {
            if (regle == tr) {
                return;
            }
        }
        baseRegles.push_back(tr);
    }

    // Permet d'ajouter le fait tf (déjà créé et initialisé) au système expert
    void SystemeExpert::ajouterFaitSE(const TypeFait &tf) {
        for (const auto &fait: baseFaits) {
            if (fait == tf) {
                return;
            }
        }
        baseFaits.emplace_back(tf);
    }

    /*	La méthode fournie chargerSE permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
        Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction "chargerSE"
    */
    void SystemeExpert::chargerSE(std::ifstream &EntreeFichier) {
        Regle regle;        // Règle qui sera ajoutée au Système Expert.
        TypeFait faitLu;    // fait qui sera ajoutée soit à 'regle' soit à la base de faits.
        int section = 1;    // section 1: Premisses d'une règle.
        // section 2: Conclusions d'une règle.
        // section 3: Faits de base.

        // Vérifier si le fichier est ouvert en lecture
        if (!EntreeFichier.is_open()) throw std::logic_error("chargerSE: le fichier n'est pas ouvert");


        while (!EntreeFichier.eof()) // Jusqu'à ce qu'on ai atteint la fin du fichier
        {
            getline(EntreeFichier, faitLu);
            if (faitLu[0] == '!')    // Dans le format du fichier, le caractère '!'
            {                        // indique un changement de section
                if (faitLu[1] == '>')    // "!>" indique que la prochaine section
                    section = 2;        // contient des conclusions.
                else {
                    // La dernière section contenait des conclusions donc on
                    // vient de finaliser une règle.  On l'ajoute maintenant au Système Expert
                    ajouterRegleSE(Regle(regle));
                    //Vider la règle en supprimant ses prémisses et ses conclusions
                    regle.GetPremisses().clear();
                    regle.GetConclusions().clear();

                    section = (faitLu[1] == '%') ? 1 : 3;
                    // "!%" indique que la prochaine section contient
                    //	des premisses.
                    // "!!" indique que la prochaine section contient
                    //	des faits.
                }

                getline(EntreeFichier, faitLu);
            }
            utilitaire::nettoyer(faitLu);
            switch (section) {
                case 1:  // Ajout d'une premisse à une règle
                    regle.GetPremisses().push_back(faitLu);
                    break;

                case 2:    // Ajout d'une conclusion à une règle
                    regle.GetConclusions().push_back(faitLu);
                    break;

                case 3:    // Ajout d'un fait à la base de faits
                    ajouterFaitSE(faitLu);
                    break;
            }
        }
    }

    /*	La méthode chainageAvant permet de saturer la base de faits du système expert se en retrouvant
        les faits qui peuvent être déduits de la base de faits du système expert en question
        et en se basant sur les règles de celui-ci. Cette fonction retourne donc l’ensemble de règles qui ont
        permis à déduire de nouveaux faits.
        Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
        Attention: er est passé par référece, donc elle est accessible par la méthode appelante (le main dans notre cas: voir case 6).
    */
    // Cette méthode boucle sur les regles, et par la suite sur les premisses
    // des regles et compare ces premisses aux faits,
    // si la comparaison marche la regle est ajouté au vecteur er

    // \param[in] std::vector<Regle> &er
    // \param[out] std::vector<Regle> &er
    void SystemeExpert::chainageAvant(std::vector<Regle> &er) {
        if (!er.empty()) {
            throw std::invalid_argument("Le vecteur n'ai pas vide");
        }

        for (auto regle: baseRegles) {
            bool trouve;
            auto it = regle.GetPremisses().begin();

            do {
                trouve = false;

                for (const auto &fait: baseFaits) {
                    if (*it == fait) {
                        trouve = true;
                        break;
                    }
                }
                it++;

            } while (trouve && it != regle.GetPremisses().end());

            if (trouve) {
                er.push_back(regle);
                for (const auto &conclusion: regle.GetConclusions()) {
                    baseFaits.push_back(conclusion);
                }
            }
        }
    }

    /*	La méthode chainageArriere est une fonction récursive qui permet de démontrer
        la véracité du fait hypothese en se basant sur les faits et les règles du système expert.
        Si celui-ci est démontré, la valeur VRAI est retournée dans demontre, FAUX sinon.
        Les règles qui ont permis de déduire de nouveaux faits sont retournées dans l’ensemble de règles.
        Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
    */
    // Cette méthode commence par vérifier si l'hypothèse n'est pas vide, par la suite
    // elle vérifie si l'hypothèse fait partie des faits, ensuite
    // on trouve la regle qui contient en conclusion l'hypothèse et on boucle sur ses premisses,
    // ensuite on boucle sur la base de fait et si un match est trouvé on break dans la boucle
    // pour ensuite passer dans le if statement, pour entrer dans le if on doit être rendu à la fin
    // des premisses, quand on rentre dans le vrai du if on ajoute la regle à la liste et la conclusion aux faits,
    // si on n'arrive pas à entrer dans le vrai du if on appelle la méthode sur elle-même et on utilise la premisses comme hypothèse
    // \param[in] hypothese, demontre
    // \exception si l'hypothese est vide
    // \return le vecteur de regle
    std::vector<Regle> SystemeExpert::chainageArriere(const TypeFait &hypothese, bool &demontre) {
        if (hypothese.empty()) {
            throw std::invalid_argument("La chaîne hypothese est vide");
        }

        std::vector<Regle> regles;

        for (const auto &fait: baseFaits) {
            if (fait == hypothese) {
                return regles;
            }
        }

        Regle regle = trouverPremisses(hypothese);

        auto premisse = regle.GetPremisses().begin();

        while (premisse != regle.GetPremisses().end()) {
            demontre = false;

            for (const auto &fait: baseFaits) {
                if (fait == *premisse) {
                    demontre = true;
                    break;
                }
            }

            if (demontre && premisse == --regle.GetPremisses().end()) {
                regles.push_back(regle);

                for (const auto &conclusion: regle.GetConclusions()) {
                    baseFaits.push_back(conclusion);
                }
            } else {
                demontre = false;

                for (const auto &regleAjout: chainageArriere(*premisse, demontre)) {
                    regles.push_back(regleAjout);
                }
            }
            ++premisse;
        }
        return regles;
    }

    // \Méthode qui retourne une règle par rapport à l'hypothèse passé en paramètre
    // si aucune règle n'est trouvé envoie une règle vide
    // \param[in] const TypeFait &hypothese
    // \return Regle regle
    Regle SystemeExpert::trouverPremisses(const TypeFait &hypothese) {
        Regle regleVide;
        for (auto regle: baseRegles) {
            for (const auto &conclusion: regle.GetConclusions()) {
                if (conclusion == hypothese) {
                    return regle;
                }
            }
        }

        return regleVide;
    }

}
