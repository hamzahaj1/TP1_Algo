/////////////////////////////////////////////////////////////////////////////
//Fichier Principal.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Principal.cpp
 * \brief Ce fichier contient un main permettant de tester le système
 * \author IFT-2008 & Hamza Hajjam
 * \version 0.1
 * \date fév. 2023
 *
 * Ce fichier contient un main permettant de tester le système
 * expert en utilisant un menu contenant des choix proposés à l'utilisateur.
 */

#include <iostream>
#include <fstream>
using namespace std;

#include "SystemeExpert.h"

int main()
{
	int nb = 1;					//Choix de l'utilisateur dans le menu initialisé à 1.
	tp1::SystemeExpert se1;		//Le système expert utilisé pour les tests de base.
	tp1::SystemeExpert se2;		//Le système expert utilisé principalement pour le chaînage avant.
    tp1::SystemeExpert se3;		//Le système expert utilisé principalement pour le chaînage arrière.
	tp1::Regle re;				//Une règle.
	tp1::TypeFait fait;			//Un fait.
    ifstream EntreeFichier1;	//Flux d'entrée
    ifstream EntreeFichier2;	//Flux d'entrée
    std::vector<tp1::Regle> er;	//Un vecteur de règles pour le retour du chaînage (avant et arrière).
    bool test = false;	// Pour tester la véracité d'une hypothèse par chaînage arrière.
    int nr = 1; //utilisé pour numeroter les règles.


	//Affichage du menu
	cout << "------------------ Menu --------------------------------" << endl;
	cout << "1 - Ajouter une regle au systeme expert." << endl;
	cout << "2 - Ajouter un fait a analyser au systeme expert." << endl;
	cout << "3 - Supprimer une regle du systeme expert." << endl;
	cout << "4 - Supprimer un fait du systeme expert." << endl;
	cout << "5 - Charger un systeme expert depuis un fichier texte." << endl;
	cout << "6 - Tirer des conclusions a partir de la base de faits." << endl;
    cout << "7 - Verifier une hypothese a partir de la base de regles." << endl;
	cout << "8 - Copier un systeme expert dans un autre" << endl;
	cout << "0 - Quitter." << endl;
	cout << "--------------------------------------------------------" << endl;

	while (nb != 0)
	{
		do
		{
			cout << endl;
			cout << "Entrer s.v.p. votre choix (0 a 8):? ";
			cin >> nb;
			if(nb <0 || nb>8)
			{
				cout << "***Option invalide!***\n";
			}
		}while(nb <0 || nb>8);

		try
		{
			switch (nb)
			{
				case 1:
					//Ajouter une regle au systeme expert.
                    if (find(re.GetPremisses().begin(), re.GetPremisses().end(), "a des poils") == re.GetPremisses().end())
					    re.GetPremisses().push_back("a des poils");
                    if (find(re.GetConclusions().begin(), re.GetConclusions().end(), "est un mammifere") == re.GetConclusions().end())
					    re.GetConclusions().push_back("est un mammifere");
					se1.ajouterRegleSE(re);
					cout << "La regle suivante a ete ajoutee:" << endl;
					cout << "Si Animal << a des poils>>, alors Animal <<est un mammifere>>" << endl;
					cout << "Nombre de premisses de cette regle: " << re.GetPremisses().size() << endl;;
					cout << "Nombre de conclusions de cette regle: " << re.GetConclusions().size() << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 2:
					//Ajouter un fait au systeme expert.
					fait = "a des poils";
					se1.ajouterFaitSE(fait);
					cout <<"Le fait suivant a ete ajoute: " << fait << endl;
					cout << "Nombre de faits dans la base de faits: " << se1.getBaseFaits().size() << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 3:
					//Supprimer une regle du systeme expert.
					se1.getBaseRegles().erase(se1.getBaseRegles().begin());
					cout << "La regle suivante a ete supprimee:" << endl;
					cout << "Si Animal <<a des poils>>, alors Animal <<est un mammifere>>" << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 4:
					//Supprimer un fait du systeme expert.
					se1.getBaseFaits().pop_front();
					cout <<"Le fait suivant a ete supprime: " << fait << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 5:
					//Charger un systeme expert depuis un fichier texte.
					EntreeFichier1.open("Animaux.txt", ios::in);
					if(EntreeFichier1.is_open())
					{
						se2.chargerSE(EntreeFichier1);
						cout << "Le systeme expert a ete charge, voici son contenu:" << endl << se2 << endl;
						cout << "Nombre de regles dans la base de regles: " << se2.getBaseRegles().size() << endl;
						cout << "Nombre de faits dans la base de faits: " << se2.getBaseFaits().size() << endl;
					}
					else
						cout << "ERREUR: Fichier introuvable!" << endl;
					EntreeFichier1.close();

					break;

				case 6:
					//Tirer des conclusions a partir de la base de faits (Saturer la base de faits par chainage avant)
					se2.chainageAvant(er);
					cout << "Le systeme expert a ete sature." << endl;
				    cout << "Voici la nouvelle base de faits: " << endl;
					for (auto itr = se2.getBaseFaits().begin(); itr!= se2.getBaseFaits().end(); ++itr)
							cout << *itr << std::endl;
                    cout << endl << "Voici la liste des regles utilisees: " << endl;
                    nr = 1;
                    for (auto itr = er.begin(); itr!= er.end(); ++itr)
                    {
                        cout << "Regle numero " << nr << ": " << std::endl;
                        cout << *itr << std::endl;
                        nr++;
                    }

					cout << "Nombre de regles utilisees: " << er.size() << endl;

					break;

				case 7:
                    //Verifier une hypothese a partir de la base de regles.

                    //Commencer par charger un systeme expert depuis un fichier texte.
                    EntreeFichier2.open("Pingouin.txt", ios::in);
                    if(EntreeFichier2.is_open())
                    {
                        se3.chargerSE(EntreeFichier2);
                        er = se3.chainageArriere("est un pingouin", test);
                        if (test)
                        {
                            cout << "L'hypothese (est un pingouin) est vraie" << endl;
                            cout << "Voici les regles utilisees:" << endl;
                            nr = 1;
                            for (auto itr = er.begin(); itr!= er.end(); ++itr)
                            {
                                cout << "Regle numero " << nr << ": " << std::endl;
                                cout << *itr << std::endl;
                                nr++;
                            }
                            cout << "Nombre de regles utilisees: " << er.size() << endl;
                        }
                        else
                            cout << "L'hypothese (est un pingouin) n'est pas vraie" << endl;
                    }
                    else
                        cout << "ERREUR: Fichier introuvable!" << endl;
                    EntreeFichier2.close();

                    break;

				case 8:
                    //Copier un systeme expert dans un autre.
                    cout << "Affichage du systeme expert avant la copie:" << endl << se1 << endl;
                    se1 = tp1::SystemeExpert(se2);
                    cout << "Affichage du systeme expert apres la copie:" << endl << se1 << endl;

                    break;
			}

		}
		catch(exception & e)
		{
			std::cerr << "ERREUR: " << e.what() << std::endl;
		}
	}

	cout << "***Merci et au revoir !***" << endl;

	return 0;
}

