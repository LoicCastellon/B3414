/*************************************************************************
                                TrajetCompose
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilis�es
#include "Liste.h"
#include "TrajetSimple.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <TrajetCompose>
// Permet d'impl�menter les trajets compos�s
//
//------------------------------------------------------------------------ 

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
	void Affiche()const;
    // Mode d'emploi : affiche les caract�ristiques du trajet
    //
    // Contrat :
    //

	bool Add(Trajet* t);
	// Mode d'emploi : permet d'ajouter un trajet � la suite de l'actuel, renvoie true si cela est possible sinon false
	//
	// Contrat :
	//

	bool IsBefore(Trajet& t)const;
	// Mode d'emploi : retourne true si le d�part de t correspond � l'arriv�e du contexte appelant. Sinon retourne false.
	//
	// Contrat :
	//

	const char* GetDepart()const;
	// Mode d'emploi : renvoie le d�part du trajet
	//
	// Contrat :
	//

	const char* GetArrivee()const;
	// Mode d'emploi : renvoie l'arriv�e du trajet
	//
	// Contrat :
	//    

//-------------------------------------------- Constructeurs - destructeur
      TrajetCompose (Trajet* t1, Trajet* t2);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//---------------------------------------------------------------- PROTEGE

protected:
//----------------------------------------------------- Attributs prot�g�s
	Liste * liste;
};

//----------------------------------------- Types d�pendants de <TrajetCompose>

#endif // TrajetCompose_H
