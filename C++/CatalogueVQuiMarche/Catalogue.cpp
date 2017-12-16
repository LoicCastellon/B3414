/*************************************************************************
                                  Catalogue
                             -------------------
    début                : 18/11/2017
    copyright            : (C) 2017 par Loïc CASTELLON & Florian MUTIN
    e-mail               : loic.castellon@insa-lyon.fr
			   			   florian.mutin@insa-lyon.fr
*************************************************************************/
//----- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) -----

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//----------------------------------------------------------------- PUBLIC

void Catalogue::SetFichierSauvegarde(string fichier)
// Algorithme : aucun
{
	fichierSauvegarde = fichier;
} //----- Fin de SetFichierSauvegarde

void Catalogue::Save() const
// Algorithme : aucun
{
	if(fichierSauvegarde.empty())
	{
		cerr << "Le fichier de sauvegarde n'est pas renseigné" << endl;
		return;
	}
	
	fstream fs;
	fs.open(fichierSauvegarde, fstream::out | fstream::app);
	if(fs.is_open())
	{
		fs << "Bonjour"<<endl;
		ElementListe* cur = liste->first;
		while(cur != nullptr)
		{
			cur->trajet->Save(fs);
			cur=cur->suivant;
		}
		fs.close();
	}
	else
	{
		cerr << "Erreur lors de l'ouverture du fichier de sauvegarde";
		cerr << endl;
	}
} //----- Fin de Save

void Catalogue::GetSauvegarde() const
// Algorithme : aucun
{
	if(fichierSauvegarde.empty())
	{
		cerr << "Le fichier de sauvegarde n'est pas renseigné" << endl;
		return;
	}
	ifstream fichier(fichierSauvegarde, ios::in);
	if(fichier)
	{
		string ligne;
		while(getline(fichier, ligne))
		{
			if(!ligne.compare("TS"))
			{
				getline(fichier, ligne);
				char* depart = new char[NB_MAX_CHAR];
				strcpy(depart,ligne.c_str());

				getline(fichier, ligne);
				char* arrivee = new char[NB_MAX_CHAR];
				strcpy(arrivee,ligne.c_str());

				getline(fichier, ligne);
				char* moyenTransport = new char[NB_MAX_CHAR];
				strcpy(moyenTransport,ligne.c_str());

				Trajet * t = new TrajetSimple(
										depart,arrivee,moyenTransport);
				if(!Add(t))
				{
					cout<<"Ce trajet est déjà présent dans le catalogue.";
					delete t;
					cout<<endl;
				}

			}


			else if(!ligne.compare("TCD"))
			{
				//trajet 1
				getline(fichier, ligne);

				getline(fichier, ligne);

				getline(fichier, ligne);

				getline(fichier, ligne);
				char* depart1 = new char[NB_MAX_CHAR];
				strcpy(depart1,ligne.c_str());

				getline(fichier, ligne);
				char* arrivee1 = new char[NB_MAX_CHAR];
				strcpy(arrivee1,ligne.c_str());

				getline(fichier, ligne);
				char* moyenTransport1 = new char[NB_MAX_CHAR];
				strcpy(moyenTransport1,ligne.c_str());

				Trajet * t1 = new TrajetSimple(
										depart1,arrivee1,moyenTransport1);

				//trajet 2
				getline(fichier, ligne);

				getline(fichier, ligne);
				char* depart2 = new char[NB_MAX_CHAR];
				strcpy(depart2,ligne.c_str());

				getline(fichier, ligne);
				char* arrivee2 = new char[NB_MAX_CHAR];
				strcpy(arrivee2,ligne.c_str());

				getline(fichier, ligne);
				char* moyenTransport2 = new char[NB_MAX_CHAR];
				strcpy(moyenTransport2,ligne.c_str());

				Trajet * t2 = new TrajetSimple(
										depart2,arrivee2,moyenTransport2);

				// création du TrajetCompose
				TrajetCompose * tc = new TrajetCompose(t1,t2);


				getline(fichier, ligne);

				while(ligne.compare("TCF"))
				{
					getline(fichier, ligne);
					char* depart = new char[NB_MAX_CHAR];
					strcpy(depart,ligne.c_str());

					getline(fichier, ligne);
					char* arrivee = new char[NB_MAX_CHAR];
					strcpy(arrivee,ligne.c_str());

					getline(fichier, ligne);
					char* moyenTransport = new char[NB_MAX_CHAR];
					strcpy(moyenTransport,ligne.c_str());

					Trajet * t = new TrajetSimple(
											depart,arrivee,moyenTransport);
					tc->Add(t);

					getline(fichier, ligne);
				}
				if(!Add(tc))
				{
					cout<<"Ce trajet est déjà présent dans le catalogue.";
					delete tc;
					cout<<endl;
				}
			}


		}
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier : "+fichierSauvegarde << endl;
} //----- Fin de GetSauvegarde

void Catalogue::GetSauvegardeTypeTrajet(bool type) const
// Algorithme : aucun
{
	if(fichierSauvegarde.empty())
	{
		cerr << "Le fichier de sauvegarde n'est pas renseigné" << endl;
		return;
	}
	ifstream fichier(fichierSauvegarde, ios::in);
	if(fichier)
	{
		string ligne;
		while(getline(fichier, ligne))
		{
			if(!ligne.compare("TS"))
			{
				if(type)
				{
					getline(fichier, ligne);
					char* depart = new char[NB_MAX_CHAR];
					strcpy(depart,ligne.c_str());

					getline(fichier, ligne);
					char* arrivee = new char[NB_MAX_CHAR];
					strcpy(arrivee,ligne.c_str());

					getline(fichier, ligne);
					char* moyenTransport = new char[NB_MAX_CHAR];
					strcpy(moyenTransport,ligne.c_str());

					Trajet * t = new TrajetSimple(
											depart,arrivee,moyenTransport);
					if(!Add(t))
					{
						cout<<"Ce trajet est déjà présent dans le catalogue.";
						delete t;
						cout<<endl;
					}
				}
				else
				{
					getline(fichier, ligne);
					getline(fichier, ligne);
					getline(fichier, ligne);
				}

			}


			else if(!ligne.compare("TCD"))
			{
				if(!type)
				{
					//trajet 1
					getline(fichier, ligne);

					getline(fichier, ligne);

					getline(fichier, ligne);

					getline(fichier, ligne);
					char* depart1 = new char[NB_MAX_CHAR];
					strcpy(depart1,ligne.c_str());

					getline(fichier, ligne);
					char* arrivee1 = new char[NB_MAX_CHAR];
					strcpy(arrivee1,ligne.c_str());

					getline(fichier, ligne);
					char* moyenTransport1 = new char[NB_MAX_CHAR];
					strcpy(moyenTransport1,ligne.c_str());

					Trajet * t1 = new TrajetSimple(
											depart1,arrivee1,moyenTransport1);

					//trajet 2
					getline(fichier, ligne);

					getline(fichier, ligne);
					char* depart2 = new char[NB_MAX_CHAR];
					strcpy(depart2,ligne.c_str());

					getline(fichier, ligne);
					char* arrivee2 = new char[NB_MAX_CHAR];
					strcpy(arrivee2,ligne.c_str());

					getline(fichier, ligne);
					char* moyenTransport2 = new char[NB_MAX_CHAR];
					strcpy(moyenTransport2,ligne.c_str());

					Trajet * t2 = new TrajetSimple(
											depart2,arrivee2,moyenTransport2);

					// création du TrajetCompose
					TrajetCompose * tc = new TrajetCompose(t1,t2);


					getline(fichier, ligne);

					while(ligne.compare("TCF"))
					{
						getline(fichier, ligne);
						char* depart = new char[NB_MAX_CHAR];
						strcpy(depart,ligne.c_str());

						getline(fichier, ligne);
						char* arrivee = new char[NB_MAX_CHAR];
						strcpy(arrivee,ligne.c_str());

						getline(fichier, ligne);
						char* moyenTransport = new char[NB_MAX_CHAR];
						strcpy(moyenTransport,ligne.c_str());

						Trajet * t = new TrajetSimple(
												depart,arrivee,moyenTransport);
						tc->Add(t);

						getline(fichier, ligne);
					}
					if(!Add(tc))
					{
						cout<<"Ce trajet est déjà présent dans le catalogue.";
						delete tc;
						cout<<endl;
					}
				}
				else
				{
					do
					{
						getline(fichier, ligne);
					}
					while(ligne.compare("TCF"));
				}
			}


		}
		fichier.close();
	}
	else
		cerr << "Impossible d'ouvrir le fichier : "+fichierSauvegarde << endl;
} //----- Fin de GetSauvegardeTypeTrajet


void Catalogue::Affiche () const
// Algorithme : aucun
{
	cout<<"Catalogue de trajets"<<endl<<"{"<<endl;
	if(liste == nullptr)
	{
		cout << "Erreur : TrajetCompose vide"<<endl;
		return;
	}
	liste->Affiche("    ");
	cout<<"}"<<endl;
} //----- Fin de Affiche

bool Catalogue::Add (const Trajet* t) const
// Algorithme : aucun
{
	ElementListe* cur = liste->first;
	while(cur != nullptr)
	{
		if(cur->trajet->Equals(*t))
		{
			return false;
		}
		cur=cur->suivant;
	}
	liste->Add(t);
	return true;
} //----- Fin de Add

unsigned int Catalogue::RechercheParcours(const char* depart,
												const char* arrivee) const
// Algorithme : aucun
{
	unsigned int cpt = 0;
	cout<<"resultat :"<<endl;
	cout<<"{"<<endl;

	ElementListe* cur = liste->first;
	//parcours des trajets
	while(cur != nullptr)
	{
		//test sur le départ du trajet en cours
		bool ok = true;
		const char* departCur = cur->trajet->GetDepart();
		if(strlen(departCur) != strlen(depart))
			ok = false ;
		else
		{
			for(unsigned int i=0 ; i<strlen(departCur) ; i++)
			{
				if(departCur[i] != depart[i])
					ok = false;
			}
		}

		//test sur l'arrivée du trajet en cours
		const char* arriveeCur = cur->trajet->GetArrivee();
		if(ok && strlen(arriveeCur) != strlen(arrivee))
			ok = false ;
		else
		{
			for(unsigned int i=0 ; i<strlen(arriveeCur) ; i++)
			{
				if(arriveeCur[i] != arrivee[i])
					ok = false;
			}
		}

		//conclusion
		if(ok)
		{
			cpt++;
			cur->trajet->Affiche();
			cout<<endl;
		}
		cur = cur->suivant;
	}
	cout<<"{"<<endl;
	return cpt;
} //----- Fin de RechercheParcours

void Catalogue::RechercheParcoursAvancee(const char* depart,
												const char* arrivee) const
// Algorithme : aucun
{
	// initialisation
	unsigned int nbTrajet = 0;
	ElementListe* cur = liste->first;
	while(cur != nullptr)
	{
		++nbTrajet;
		cur=cur->suivant;
	}
	unsigned int * tab = new unsigned int[nbTrajet];
	for(unsigned int i = 0 ; i < nbTrajet ; i++)
	{
		tab[i] = 0;
	}

	//récursivité et affichage
	cout<<"resultat :"<<endl;
	cout<<"{"<<endl;
	rechercheRecursive(depart,arrivee,tab,nbTrajet,1);
	cout<<"{"<<endl;

	delete[] tab;
} //----- Fin de RechercheParcoursAvancee

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ()
// Algorithme : aucun
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
	liste = new Liste();
	fichierSauvegarde = "";
	
#ifdef TEST
	fichierSauvegarde = "testFlo.txt";
#endif
} //----- Fin de Catalogue

Catalogue::~Catalogue ( )
// Algorithme : aucun
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
	delete liste;
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE
//------------------------------------------------------- Methodes privées
void Catalogue::rechercheRecursive(const char* depart,
								const char* arrivee, unsigned int* tab,
								const unsigned int lengthTab,
								const unsigned int position) const
// Algorithme : parcours en profondeur du catalogue de trajet
{
	//test fin de récursivité
	bool compFin=true;
	if(strlen(arrivee) != strlen(depart))
		compFin = false ;
	else
	{
		for(unsigned int i=0 ; i<strlen(arrivee) ; i++)
		{
			if(depart[i] != arrivee[i])
				compFin = false;
		}
	}
	if(compFin)
	{
		//affichage d'une solution
		cout<<endl<<"*"<<endl;
		for(unsigned int p = 1 ; p<position ; p++)
		{
			unsigned int numTrajet = 0;
			ElementListe* cur = liste->first;
			while(tab[numTrajet]!=p)
			{
				cur=cur->suivant;
				++numTrajet;
			}
			cur->trajet->Affiche();
			cout<<endl;
		}
		cout<<endl;
		return;
	}

	//recursivité
	unsigned int numTrajet = 0;
	ElementListe* cur = liste->first;
	//parcours des trajets
	while(cur != nullptr)
	{
		//test sur le depart du trajet en cours
		bool compDepart = true;
		const char* departCur = cur->trajet->GetDepart();
		if(strlen(departCur) != strlen(depart))
			compDepart = false ;
		else
		{
			for(unsigned int i=0 ; i<strlen(departCur) ; i++)
			{
				if(departCur[i] != depart[i])
					compDepart = false;
			}
		}

		//appel récursif si le depart convient et que le trajet n'est pas
		//utilisé
		if(compDepart && tab[numTrajet]==0)
		{
			tab[numTrajet]=position;
			rechercheRecursive(cur->trajet->GetArrivee(), arrivee, tab,
												lengthTab, position+1);
			tab[numTrajet]=0;
		}
		//on passe au trajet suivant
		++numTrajet;
		cur = cur->suivant;
	}
} //----- Fin de rechercheRecursive