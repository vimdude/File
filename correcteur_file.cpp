/* -+----1----+----2----+----3----+----4----+----5----+----6----+----7----+- */
/* ========================================================================= */
/*                            FileCorrecteur.cpp                             */
/* ========================================================================= */

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "File.cpp"

static void afficherErreur( char *message );

static FILE *fichCorr;

/*
* Une classe exemple d'Objet.
*/
class Lieu
{
public:
	double x;
	double y;
	Lieu( void ) : x( 0.0 ), y( 0.0 ) { }
	Lieu( double x, double y ) : x( x ), y( y ) { }
	bool operator == ( Lieu &autreLieu )
	{
		return
			   fabs( x - autreLieu.x  ) < 1.0e-4
			&& fabs( y - autreLieu.y  ) < 1.0e-4;
	}
	Lieu operator = ( Lieu original ) {
		this->x = original.x;
		this->y = original.y;
		return *this;
	}
};

ostream & operator << ( ostream &sortie, const Lieu &lieu )
{
	return sortie << "(" << lieu.x << ", " << lieu.y << ")";
}

/* ------------------------------------------------------------------------- */ 
int main( int argc, char * argv[ ]) 
/* ------------------------------------------------------------------------- */ 
{ 
	char message[ 1000 ];
	/*
	ofstream temoin;
	ofstream fichCorr;
	ofstream fichierNote;
	*/
	// FILE *fichCorr;
	FILE *fichierNote;
	double valeur;
	int continuer = 1;
	int erreur;
	unsigned int numeroDuTest = 0;

	double noteMax = 0.0;
	double note = 0.0;

	if (( fichCorr = fopen( "correction.txt", "w" )) == 0 ) {
		fprintf( stderr, "echec de l'ouverture du fichier de correction." );
		continuer = 0;
	}

	File< int > file( 3, 2 );
	/*
	char histoire[ 1000 ];
	char *ptHistoire = histoire;
	*/

	/*
	* sortir( ) devrait generer l'exception FileVide
	*/
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		try {
			int consulte;
			file.sortir( consulte );
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Une file vient d'etre creee et est encore vide, une\n",
				numeroDuTest );
			strcat( message,
				"exception FileVide devrait etre generee a l'invocation\n" );
			strcat( message, "de sortir()\n" );
			afficherErreur( message );
		}
		catch( File< int >::FileVide fileVide ) {
		}
	}

	int truc = 5;
	file.entrer( truc );

	/*
	* La cellule premier du tableau contient-elle bien l'adresse de truc?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.objets[ file.premier ] != &truc ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) objets[ premier ] ne contient pas l'adresse de l'objet\n",
				numeroDuTest );
			strcat( message, "qu'on vient d'y entrer." );
			afficherErreur( message );
		}
	}

	/*
	* premier vaut-il 0?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.premier != 0 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Pour une nouvelle File ne contenant qu'un seul objet\n",
				numeroDuTest );
			strcat( message, "premier devrait etre nul." );
			afficherErreur( message );
		}
	}

	/*
	* dernier vaut-il 1?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.dernier != 1 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Pour une nouvelle File ne contenant qu'un seul objet\n",
				numeroDuTest );
			strcat( message, "premier devrait valoir 0." );
			afficherErreur( message );
		}
	}

	/*
	* fournirNombreDObjets vaut-il 1?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.fournirNombreDObjets( ) != 1 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Pour une nouvelle File ne contenant qu'un seul objet\n",
				numeroDuTest );
			strcat( message, "fournirNombreDObjets( ) devrait renvoyer 1." );
			afficherErreur( message );
		}
	}

	/*
	* Retirer un int qui vient d'etre ajoute devrait le restituer.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		int sorti;
		file.sortir( sorti );
		if ( sorti != 5 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Un int a ete ajoute a la file a l'aide de entrer(),\n",
				numeroDuTest );
			strcat( message, "sortir devrait le restituer." );
			afficherErreur( message );
		}
	}

	/*
	* premier et dernier valent-ils 1?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.premier != 1 || file.dernier != 1  ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) On a entre puis sorti un objet d'une nouvelle File\n",
				numeroDuTest );
			strcat( message, "premier et dernier devraient valoir 1." );
			afficherErreur( message );
		}
	}

	/*
	* sortir( ) devrait generer l'exception FileVide
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		try {
			int sorti;
			file.sortir( sorti );
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Une file precedemment videe devrait declencher une\n",
				numeroDuTest );
			strcat( message,
				"exception FileVide a l'invocation de sortir()\n" );
			afficherErreur( message );
		}
		catch( File< int >::FileVide fileVide ) {
		}
	}

	/*
	* Meme test avec l'operateur <<
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		int six = 6;
		file << six;
		cerr << "file = \n" << file;
		int sorti;
		file.sortir( sorti );
		if ( sorti != six ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Un int a ete ajoute a la file grace a operator <<( ),\n",
				numeroDuTest );
			strcat( message, "sortir devrait le restituer.\n" );
			afficherErreur( message );
		}
	}

	/*
	* Meme test avec l'operateur >>
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		int sept = 7;
		file << sept;
		cerr << "file = \n" << file;
		int retire;
		file >> retire; 
		if ( retire != 7 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Un int a ete ajoute a la file grace a operator <<( ),\n",
				numeroDuTest );
			strcat( message, "operator >>( ) devrait le restituer.\n" );
			afficherErreur( message );
		}
	}

	/*
	* On rempli la file jusqu'a pleine
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	int un = 1, deux = 2, trois = 3;
	if ( continuer ) {
		note += valeur;
		file << un << deux << trois;
		cerr << "file = \n" << file;
		if ( file.fournirNombreDObjets( ) != 3 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La longueur de la file ne correspond pas au nombre d'objets",
				numeroDuTest );
			strcat( message, "dans la file.\n" );
			afficherErreur( message );
		}
	}

	/*
	* On verifie filePleine( )
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		if ( !file.estPleine( )) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La file est Pleine, estPleine( ) devrait renvoyer true.",
				numeroDuTest );
			afficherErreur( message );
		}
	}

	/*
	* premier vaut-il 3?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.premier != 3 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Apres quelques entrees et sorties premier n'a pas\n",
				numeroDuTest );
			strcat( message, "pas la bonne valeur." );
			afficherErreur( message );
		}
	}

	/*
	* dernier vaut-il 2?.
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		cerr << "file = \n" << file;
		if ( file.dernier != 2 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Apres quelques entrees et sorties dernier n'a pas\n",
				numeroDuTest );
			strcat( message, "pas la bonne valeur." );
			afficherErreur( message );
		}
	}

	/*
	* on declenche consommer( ).
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	int huit = 8;
	if ( continuer ) {
		note += valeur;
		file.entrer( huit );
		if ( file.capacite != 5 ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) la fonction consommer() aurait du etre invoquee\n",
				numeroDuTest );
			strcat( message,
				"et faire passer la capacite a 5.\n" );
			afficherErreur( message );
		}
	}

	File< char > *fileCar;

	/*
	* On rempli la file jusqu'a pleine
	*/
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	numeroDuTest++;
	if ( continuer ) {
		note += valeur;
		fileCar = new File< char >( 3, 2 );
		char lettre_a = 'a', lettre_b = 'b', lettre_c = 'c';
		*fileCar << lettre_a << lettre_b << lettre_c;
		cerr << "fileCar = \n" << *fileCar << "\n";
		if ( !fileCar->estPleine( )) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La file est pleine avec premier == 0 la fonction estPleine( )",
				numeroDuTest );
			strcat( message, "ne fonctionne pas dans ces conditions.\n" );
			afficherErreur( message );
		}
	}

	/*
	* On retire un objet pour liberer la cellule 0, ce qui doit
	* nous permettre de loger un nouvel objet dans la cellule capacite - 1
	*/
	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		try {
			char carac;
			char lettre_q = 'q';
			*fileCar >> carac << lettre_q;
			cerr << "fileCar = \n" << *fileCar << "\n";
			if ( !fileCar->estPleine( )) {
				note -= valeur;
				continuer = 0;
				sprintf( message,
					"(%u) La file est pleine avec premier == 1 la fonction estPleine( )",
					numeroDuTest );
				strcat( message, "ne fonctionne pas dans ces conditions.\n" );
				afficherErreur( message );
			}
		}
		catch( File< char >::FileVide fileVide ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) premier == 1 et la file n'est pas vide. l'operation >>()",
				numeroDuTest );
			strcat( message,
				"n'aurait pas du provoquer l'exception FileVide.\n" );
			afficherErreur( message );
		}
	}

	File< Lieu > lieux( 3, 2 );
	Lieu a( 0.0, 0.0 ), b( 0.0, 1.0 ), c( 0.0, 2.0 );

	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		lieux << a << b << c;
		cerr << "lieux = \n" << lieux << "\n";
		if ( !lieux.estPleine( )) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La file est pleine avec premier == 0 la fonction estPleine( )",
				numeroDuTest );
			strcat( message, "ne fonctionne pas dans ces conditions.\n" );
			afficherErreur( message );
		}
	}


	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		Lieu A, B, C;
		lieux >> A >> B >> C;
		cerr << "lieux = \n" << lieux << "\n";
		if ( !( A == a ) || !( B == b ) || !( C == c )) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La file ne restitue pas les objets dans l'ordre d'entrée.",
				numeroDuTest );
			afficherErreur( message );
		}
	}

	numeroDuTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		lieux << a << b << c;
		Lieu *ptA, *ptB, *ptC;
		lieux >> ptA >> ptB >> ptC;
		cerr << "lieux = \n" << lieux << "\n";
		if ( !( ptA == &a ) || !( ptB == &b ) || !( ptC == &c )) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) La file ne restitue pas les objets dans l'ordre d'entrée.",
				numeroDuTest );
			afficherErreur( message );
		}
	}



	/*
	numeroDeTest++;
	valeur = 10.0;
	noteMax += valeur;
	note -= valeur;
	if ( continuer ) {
		note += valeur;
		if ( file != capaciteImplicite ) {
			note -= valeur;
			continuer = 0;
			sprintf( message,
				"(%u) Le vecteur vient d'etre cree par le constructeur par defaut.",
				numeroDuTest );
			sprintf( suite, 
				" sa capacite devrait etre capaciteImplicite soit %d\n",
				capaciteImplicite );
			strcat( message, suite );
			afficherErreur( message );
		}
	}
	*/

	/*
	cerr << "file = \n" << file << "\n";
	file.entrer( 3 );
	cerr << "apres entrer( 3 )\n";
	cerr << "file = \n" << file << "\n";
	int retire;
	try {
		file << 12 << 5;
		cerr << "\nfile = \n" << file << "\n";
		file >> retire;
		cerr << "\nfile = \n" << file << "\n";
		cerr << "retire = " << retire << "\n";
		file.entrer( 8 );
		file.entrer( 1 );
		cerr << "\nfile = \n" << file << "\n";
	}
	catch ( FilePleine filePleine ) {
		cerr << filePleine.message( ) << "\n\n";
	}
	*/

	/* ----------------------------- service --------------------------------- */
	note += noteMax;
	note = note/noteMax;

	erreur = 0;
	char * nomDuFichierNote = "note.txt";
	if ( argc == 2 ) nomDuFichierNote = argv[ 1 ]; 
	if (( fichierNote = fopen( nomDuFichierNote, "w" )) == 0 ) {
		fprintf( stderr, "echec de l'ouverture du fichier note." );
		fichierNote = fopen( "note.txt", "w" );
		// erreur = 1;
	}
	if ( !erreur ) {
		if ( fprintf( fichierNote, "%6.2lf", note ) == -1 ) {
			erreur = 1;
		}
	}
	if ( erreur ) {
		sprintf( message, "note obtenue: %6.2lf.\n", note );
		afficherErreur( message );
		afficherErreur(
			"Erreur systeme, enregistrement de la note impossible.\n" );
		return 1;
	}
	sprintf( message, "note = %6.2lf\n", note );
	afficherErreur( message );
	return 0;
}

/* ------------------------------------------------------------------------- */
static void afficherErreur( char *message )
/* ------------------------------------------------------------------------- */
{
	fprintf( fichCorr, message ); fflush( fichCorr );
	fprintf( stderr, message ); fflush( stderr );
}