/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+- */
/* Abdel Said                                     modifie le 30 octobre 2001 */
/* ========================================================================= */
/*                                   File.h                                  */
/* ========================================================================= */
/*                                                                           */
/* Fichier d'interface du modèle de classe File.                             */
/*                                                                           */
/* ========================================================================= */

#ifndef FILE_H
#define FILE_H

#include <iostream.h>
#include <exception>

/*
* Emmagasine les pointeurs aux objets qu'elle "contient", pas les Objet eux
* memes.
* Se dilate ou se contracte selon les besoins, donc pas d'exception FilePleine. 
*/
// ============================================================================
template< typename Objet >
class File
// ============================================================================
{
	/*
	* Valeurs implicites de la capacite et de l'increment de la File pour
	* le constructeur implicite. ATTENTION: Il s'agit du nombre d'objets que
	* la file peut contenir et non de la dimension du tableau qui sert a
	* la realiser.
	*/
	public: static const unsigned int capaciteImplicite;
	public: static const unsigned int incrementImplicite;
	/*
	* tableau reserve dynamiquement pour contenir des pointeurs aux objets
	* stockes dans la File.
	*/
	private: Objet **objets;
	/*
	* Indice du plus ancien objet present dans la file, initialise a 0 
	*/
	private: unsigned int premier;
	/*
	* Indice de la prochaine cellule libre dans la file, juste apres le
	* dernier objet entre.
	*/
	private: unsigned int dernier;
	/*
	* Nombre maximal d'objets dans la file. Attention, la taille
	* du tableau est en fait 1 de plus que la capacite percue par
	* l'utilisateur
	*/
	private: unsigned int capacite;
	/*
	* Ajoute ou retranche a la capacite selon les besoins
	*/
	private: unsigned int increment;
	/*
	* Exception renvoyee par un objet File lorsqu'une operation d'extraction
	* ou de consultation est tentee sur une file ne contenant aucune donnee.
	*/
	// ==========================================================================
	public: class FileVide : public exception
	// ==========================================================================
	{
		// ------------------------------------------------------------------------
		public: const char * message( ) const
		// ------------------------------------------------------------------------
		{
			return "La file est vide.";
		}
	};

	/*
	* Construit une file.
	*/
	// --------------------------------------------------------------------------
	public: File( void );
	// --------------------------------------------------------------------------

	/*
	* Construit une file.
	*/
	// --------------------------------------------------------------------------
	public: File( unsigned int capacite, unsigned int increment );
	// --------------------------------------------------------------------------

	/*
	* Construit une file.
	*/
	// --------------------------------------------------------------------------
	private: void initialiser( void );
	// --------------------------------------------------------------------------

	/*
	*/
	// --------------------------------------------------------------------------
	private: void consommer( void );
	// --------------------------------------------------------------------------

	/*
	*/
	// --------------------------------------------------------------------------
	private: void restituer( void );
	// --------------------------------------------------------------------------

	// --------------------------------------------------------------------------
	public: ~File( );
	// --------------------------------------------------------------------------

	/*
	* Incremente l'indice au sens d'un tableau circulaire,
	*/
	// --------------------------------------------------------------------------
	private: unsigned int incrementer( unsigned int indice ) const;
	// --------------------------------------------------------------------------

	/*
	* Ajoute un Objet dans la file.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > & entrer( Objet &objet );
	// --------------------------------------------------------------------------

	/*
	* Surcharge de l'operateur << pour l'operation entrer.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > &operator << ( Objet &objet );
	// --------------------------------------------------------------------------

	/*
	* Retire le plus ancien Objet encore dans la file.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > &sortir( Objet &recupere ) throw( FileVide );
	// --------------------------------------------------------------------------
	/*
	* Retire le plus ancien Objet encore dans la file.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > &sortir( Objet * &recupere ) throw( FileVide );
	// --------------------------------------------------------------------------

	/*
	* Surcharge de l'operateur >> pour l'operation sortir.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > &operator >> ( Objet &recupere ) throw( FileVide );
	// --------------------------------------------------------------------------

	/*
	* Surcharge de l'operateur >> pour l'operation sortir.
	*/
	// --------------------------------------------------------------------------
	public: File< Objet > &operator >> ( Objet * &recupere ) throw( FileVide );
	// --------------------------------------------------------------------------

	/*
	* Renvoie
	*        true si la file ne contient aucun Objet
	*        false autrement.
	*/
	// --------------------------------------------------------------------------
	public: bool estVide( void ) const;
	// --------------------------------------------------------------------------

	/*
	* Renvoie
	*        true si la File est pleine
	*        false autrement.
	*/
	// --------------------------------------------------------------------------
	private: bool estPleine( void ) const;
	// --------------------------------------------------------------------------

	/*
	* Renvoie le nombre de Objet presents dans la file
	*/
	// --------------------------------------------------------------------------
	public: unsigned fournirNombreDObjets( void ) const;
	// --------------------------------------------------------------------------

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
	// --------------------------------------------------------------------------
	ostream & insererEnFlux( ostream & sortie ) const;
	// --------------------------------------------------------------------------


	/*
	* Pour autoriser le main() correcteur de verifier les membres prives de
	* la file.
	*/
	// --------------------------------------------------------------------------
	friend int main( int argc, char *argv[ ]);
	// --------------------------------------------------------------------------
};

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
// ----------------------------------------------------------------------------
template< typename Objet >
ostream & operator << ( ostream & sortie, const File< Objet > & file );
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
template< typename Objet >
const unsigned int File< Objet >::capaciteImplicite = 4;
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
template< typename Objet >
const unsigned int File< Objet >::incrementImplicite = 2;
// ----------------------------------------------------------------------------

#endif
