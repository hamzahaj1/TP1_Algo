/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.h
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.h
 * \brief Ce fichier contient une définition de la classe Regle
 * \author IFT-2008
 * \version 0.1
 * \date fév. 2023
 *
 */

#ifndef _REGLE_H
#define _REGLE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <list>

namespace tp1
{

typedef std::string TypeFait;	//Le type du fait : une chaîne de caractères

class Regle{

	public:

	   Regle();	//Constructeur de la classe Regle.

	   Regle(const Regle&);	//Constructeur de copie.

	   ~Regle();	//Destructeur

	    Regle& operator = (const Regle & r); // surcharge de l’opérateur =

		bool operator == (const Regle & r) const;	// Surcharge de l'opérateur == (pour comparer deux règles).

		bool operator != (const Regle & r) const;	// Surcharge de l'opérateur != (pour comparer deux règles).

		//surcharge de <<
		//Ne pas toucher à cette fonction
		friend std::ostream& operator << (std::ostream & os, const Regle & r)
		{
			os << "Premisses: " << std::endl; 
			for (auto itr = r.premisses.begin(); itr != r.premisses.end(); ++itr)
				os << *itr << std::endl;
			os << "Conclusions: " << std::endl; 
			for (auto itr = r.conclusions.begin(); itr != r.conclusions.end(); ++itr)
				os << *itr << std::endl;

			return os;
		}


		//Accesseurs
		std::list<TypeFait> & GetPremisses () {return premisses;};
		std::list<TypeFait> & GetConclusions () {return conclusions;};
	private:

		std::list<TypeFait> premisses;	// L’ensemble des prémisses d’une règle (utilise la liste STL)
		std::list<TypeFait> conclusions;	// L’ensemble des conclusions d’une règle (utilise la liste STL)
};

}

#endif
