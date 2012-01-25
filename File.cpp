/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+- */
/* Abdel Said                                     modifie le 9 novembre 2001 */
/* ========================================================================= */
/*                                   File.cpp                                */
/* ========================================================================= */
/*                                                                           */
/* Fichier des fonctions membres de la classe File.                          */
/*                                                                           */
/* ========================================================================= */

#include<iostream.h>
#include "File.h"
#include <exception>
#include <iomanip.h>
 

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet >::File ( void ) 
/*------------------------------------------------------------------------- */
{
	capacite = capaciteImplicite;
	increment = incrementImplicite;
	initialiser ( ) ;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet >::~File ( ) 
/*------------------------------------------------------------------------- */
{
	delete [ ] objets;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet >::File ( unsigned int capacite, unsigned int increment ) 
/*------------------------------------------------------------------------- */
{
	this->capacite = capacite;
	this->increment = increment;
	initialiser ( ) ;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
void File< Objet >::initialiser ( void ) 
/*------------------------------------------------------------------------- */
{
	premier = 0;
	dernier = 0;
	objets = new Objet *[ capacite + 1 ];
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::entrer ( Objet &objet ) 
/*------------------------------------------------------------------------- */
{
	if ( estPleine ( )  ) consommer ( ) ;
	objets[ dernier++ ]= &objet;
	if ( dernier > capacite ) dernier = 0;
	return *this;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
unsigned int File< Objet >::incrementer ( unsigned int indice ) const
/*------------------------------------------------------------------------- */
{
	if ( indice == capacite ) return 0;
	else return  ++indice;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
void File< Objet >::consommer ( void ) 
/*------------------------------------------------------------------------- */
{
	Objet **nouveauTableau;
	nouveauTableau = new Objet *[ capacite + increment + 1 ];
	int j = premier;
	for ( int i=0; i < ( capacite + 1 ) ; i++ ) 
	{
		nouveauTableau[ i ]= objets[ j ];
		j++;
		if ( j == ( capacite + 1 )  ) j = 0; 
		if ( j == dernier ) 
		{
			dernier = ++i;
			i = capacite + 1;
			premier = 0;
		}
	}
	delete[ ]objets;
	capacite += increment;
	objets = nouveauTableau;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::operator << ( Objet &objet ) 
/*------------------------------------------------------------------------- */
{
	return entrer ( objet ) ;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::sortir ( Objet *&recupere ) throw ( FileVide ) 
/*------------------------------------------------------------------------- */
{
	if ( estVide ( )  ) throw File::FileVide ( ) ;
	recupere = objets[ premier ];
	premier = incrementer ( premier ) ;
	if (  ( capacite - fournirNombreDObjets ( )  ) == 2*increment ) 
		restituer ( ) ;
	return *this;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::sortir ( Objet &recupere ) throw ( FileVide ) 
/*------------------------------------------------------------------------- */
{
	if ( estVide ( )  ) throw File::FileVide ( ) ;
	recupere = *objets[ premier ];
	premier = incrementer( premier );
	if ( ( capacite - fournirNombreDObjets ( ) ) == 2*increment ) 
		restituer ( ) ;
	return *this;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
void File< Objet >::restituer ( void ) 
/*------------------------------------------------------------------------- */
{
	Objet ** nouveauTableau;
	capacite -= increment;
	nouveauTableau = new Objet *[ capacite + 1 ];
	int j = 0, i;
	for ( i = premier; i != dernier; i++ ) 
	{
		nouveauTableau[ j ]= objets[ i ];
		j++;
		if ( i == ( capacite + 1 )  ) i = 0;
	}
	delete objets;
	objets = nouveauTableau;
	delete nouveauTableau;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::operator >> ( Objet *&recupere ) throw ( FileVide ) 
/*------------------------------------------------------------------------- */
{
	return sortir ( recupere ) ;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
File< Objet > & File< Objet >::operator >> ( Objet &recupere ) throw ( FileVide ) 
/*------------------------------------------------------------------------- */
{
	return sortir ( recupere ) ;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
bool File< Objet >::estVide ( void ) const
/*------------------------------------------------------------------------- */
{
	if ( premier == dernier ) return true;
	else return false;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
bool File< Objet >::estPleine ( void ) const
/*------------------------------------------------------------------------- */
{
	int indice = dernier;
	indice = incrementer ( indice ) ;
	if ( indice == premier ) return true;
	return false;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
unsigned File< Objet >::fournirNombreDObjets ( void ) const
/*------------------------------------------------------------------------- */
{
	if ( dernier > premier ) 
		return dernier - premier;
	else
	{
		if ( premier > dernier ) 
		{
			if (  ( premier - 1 ) == dernier ) return  capacite;
			else return (  ( capacite + 1 ) - ( premier - dernier )  ) ;
		}
		return 0;
	}
}
/*
* Affiche a l'ecran tout le contenu de la file selon le format
* illustre par l'exemple suivant:
*
* 4                  5
* 3 premier          2
* 2                  ?
* 1          dernier ?
* 0                  7
*/

/*------------------------------------------------------------------------- */
template< typename Objet >
ostream & File< Objet >::insererEnFlux ( ostream & sortie ) const
/*------------------------------------------------------------------------- */
{
	int i;
	if( dernier == premier)
	{
		for( i = capacite ; i >= 0 ;i--)
		{
			if( i == dernier ) sortie << i << " premier"<< setw(1) <<" dernier ?"<<endl;
			else sortie << i << setw (18) << "?"<< endl;
		}
	}
	else if ( dernier > premier )
	{
		for ( i = capacite; i != dernier; i-- ) sortie << i << setw (16) << "?"<< endl;
		cout << i << setw(16) << "dernier ?"<<endl;
		for (i = dernier - 1; i != premier; i-- )cout << i << setw (16) << *objets[ i ]<<endl;
		cout << i <<" premier"<<setw(8) << *objets[i] <<endl;
		for( i = premier -1 ; i >= 0 ; i--) sortie << i << setw (16) << "?"<< endl;
	}
	else if( dernier < premier )
	{
		for ( i = capacite; i != premier; i-- ) cout << i << setw (16) << *objets[ i ]<<endl;
		cout << i <<" premier" <<setw(8) << *objets[i] <<endl;
		for (i = premier - 1; i != dernier; i-- ) sortie << i << setw (16) << "?"<< endl;
		cout << i << setw(16) << "dernier ?"<<endl;
		for(i = dernier - 1; i >= 0 ; i--) cout << i << setw (16) << *objets[ i ]<<endl;
	}
	cin.get();
	sortie << "\nappuyer sur une touche pour voir le prochain affichage" << endl << endl;
	return sortie;
}

/*------------------------------------------------------------------------- */
template< typename Objet >
ostream & operator << ( ostream & sortie, const File< Objet > & file ) 
/*------------------------------------------------------------------------- */
{
	file.insererEnFlux ( sortie ) ;
	return sortie;
}
