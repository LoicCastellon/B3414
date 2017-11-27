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
//
//
//------------------------------------------------------------------------ 

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
	void Affiche()const;
    // Mode d'emploi :
    //
    // Contrat :
    //

	bool Add(Trajet* t);
	// Mode d'emploi :
	//
	// Contrat :
	//

	bool IsBefore(Trajet& t)const;
	// Mode d'emploi :
	//
	// Contrat :
	//

	const char* GetDepart()const;
	// Mode d'emploi :
	//
	// Contrat :
	//

	const char* GetArrivee()const;
	// Mode d'emploi :
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
