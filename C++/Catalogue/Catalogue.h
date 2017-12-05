//ElementTrajetSimple à remplacer par ElementTrajet
/*************************************************************************
                                  Catalogue
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( Catalogue_H )
#define Catalogue_H

//--------------------------------------------------- Interfaces utilisées
#include "Liste.h"

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// Cette classe permet de gérer plusieurs trajets
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void Affiche() const;
    // Mode d'emploi : affiche les trajets du contexte appelant
    //
    // Contrat : aucun
    //
    
	void Add(const Trajet* t) const;
    // Mode d'emploi : ajoute un trajet possible
    //
    // Contrat : aucun
    //
    
	unsigned int RechercheParcours(const char* depart, const char* arrivee) const;
    // Mode d'emploi : recherche de trajets qui vont de depart à arrivee et renvoie le nombre de solution
    //
    // Contrat : aucun
    //
    
	void RechercheParcoursAvancee(const char* depart, const char* arrivee) const;
    // Mode d'emploi : recherche de compositions de trajets qui vont de depart à arrivee et renvoie le nombre de solution
    //
    // Contrat : aucun
    //

//-------------------------------------------- Constructeurs - destructeur

    Catalogue ( );
    // Mode d'emploi : aucun
    //
    // Contrat : aucun
    //

    virtual ~Catalogue ( );
    // Mode d'emploi : aucun
    //
    // Contrat : aucun
    //

//---------------------------------------------------------------- PROTEGE

protected:
//----------------------------------------------------- Attributs protégés
	Liste* liste;


//------------------------------------------------------------------ PRIVE

private:
//------------------------------------------------------- Methodes privées
	void rechercheRecursive (const char* depart, const char* arrivee, unsigned int* tab,const unsigned int lengthTab,const unsigned int position) const;
    // Mode d'emploi : sous methode de RechercheParcoursAvancee qui recherche de compositions de trajets qui vont de depart à arrivee et renvoie le nombre de solution
    //
    // Contrat : aucun
    //

};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // Catalogue_H

