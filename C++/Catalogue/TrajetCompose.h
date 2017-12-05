/*************************************************************************
                                TrajetCompose
                             -------------------
    d�but                : 15/11/2017
    copyright            : (C) 2017 par Lo�c CASTELLON & Florian MUTIN
    e-mail               : loic.castellon@insa-lyon.fr
			   			   florian.mutin@insa-lyon.fr
*************************************************************************/

//--- Interface de la classe <TrajetCompose> (fichierTrajetCompose.h)---- 
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilis�es
#include "Liste.h"
#include "TrajetSimple.h"

//------------------------------------------------------------------------ 
// R�le de la classe <TrajetCompose>
// Cette classe impl�mente les trajets compos�s
//------------------------------------------------------------------------ 

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- M�thodes publiques
	void Affiche()const;
    // Mode d'emploi : affiche les attributs du contexte appelant
    // Contrat : aucun

	bool Add(const Trajet* t) const;
	// Mode d'emploi : si le trajet t est une suite du contexte appelant,
	//     alors il est ajout� au contexte appelant et on retourne true, 
	//     sinon on ne fait rien et retourne false
	// Contrat : t est non null

	bool IsBefore(const Trajet& t) const;
	// Mode d'emploi : retourne true si le d�part de t correspond � 
	//     l'arriv�e du contexte appelant. Sinon retourne false.
	// Contrat : aucun

	const char* GetDepart() const;
	// Mode d'emploi : retourne le d�part
	// Contrat : aucun

	const char* GetArrivee() const;
	// Mode d'emploi : retourne l'arriv�e
	// Contrat : aucun

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose (const Trajet* t1, const Trajet* t2);
    // Mode d'emploi : t1 et t2 sont resp�ctivement l'�tape 1 et 2 du
	//     trajet compos� cr��
    // Contrat : t1 et t2 sont non nulls et t2 est une suite de t1

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    // Contrat :

//---------------------------------------------------------------- PROTEGE
protected:
//----------------------------------------------------- Attributs prot�g�s
	Liste * liste;

};

#endif // TrajetCompose_H
