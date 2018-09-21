#ifndef __OWN__H__
#define __OWN__H__
/**
 * @file own.h
 * @brief      Bibliothèque Personnelle
 * @author     Chiappelloni Nicolas
 * @version    0.2
 * @date       06/05/2018
 *
 * Bibliothèque Personnelle
 */

/*****************\
	  INCLUDE
\*****************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*****************\
	 CONSTANTE
\*****************/
/**
 * @def LINUX
 * Variable de compilation pour rendre compatible certaines fonctions entre
 * Linux et Windows
 */

#define LINUX 1
#ifdef LINUX
	/**
	 * @def CLEAR()
	 * Nettoie la console
	 */
	#define CLEAR() system("clear");
#else
	#define CLEAR() system("cls");
#endif


/*****************\
	 STRUCTURE
\*****************/
/**
 * @typedef boolean
 *
 * Enumération de type boolean
 */
//typedef enum {FALSE,TRUE}boolean;

/**
 * @struct Integer
 * @brief  Entité Integer
 *
 * Structure contenant un int servant à un ArrayInteger
 */
typedef struct Integer
{
	int value;
	struct Integer *next;
	struct Integer *previous;
}Integer;

/**
 * @struct ArrayInteger
 * @brief  Structure de contrôle
 *
 * Structure permettant le contrôle d'une liste doublement chaînée d'Integer
 */
typedef struct ArrayInteger
{
	int size;
	Integer *head;
	Integer *middle;
	Integer *tail;
}ArrayInteger;
/*****************\
	 FONCTION
\*****************/

/**
 * @fn         int read(char *buffer,size_t size )
 * @brief      Lecture clavier sécurisée
 *
 * @param      buffer  adresse du buffer
 * @param      size    taille du buffer (sizeof)
 *
 * @return     0 si aucune erreur , 1 sinon
 *
 * Lecture sécurisée du clavier de n-1 caractères (\0)
 */
int read(char *buffer,const size_t size);

/**
 * @fn         int readInt ()
 * @brief      Lecture sécurisée d'un Integer au clavier
 *
 * @return     la chaîne convertie si aucune erreur , 0 sinon
 *
 * Lecture sécurisée d'un type Integer , utilise la fonction read() et convertie le résultat.
 */
int readInt();

/**
 * @fn         float readFloat ()
 * @brief      Lecture sécurisée d'un Float au clavier
 *
 * @return     la chaîne convertie si aucune erreur , 0 sinon
 *
 * Lecture sécurisée d'un type Float , utilise la fonction read() et convertie le résultat.
 */
float readFloat();


/**
 * @fn         int isValid (const char *string)
 * @brief      fonction question binaire
 *
 * @param      string  phrase à afficher
 *
 * @return     1 si l'utilisateur choisi 'y' , 0 sinon
 *
 * fonction de validation binaire , affiche une phrase et attend la
 * réponse de l'user(y|n)
 */
int isValid(const char *string);

/**
 * @fn         int power (int x, int y)
 * @brief      fonction retournant un nombre X puissance Y
 *
 * @param      x     Nombre
 * @param      y     puissance
 *
 * @return     X puissance Y
 *
 * Fonction récursive qui retourne un nombre X à la puissance Y
 */
int power(int x,int y);

/**
 * @fn         int isEnoughtLong (const char *string,const unsigned  int min)
 * @brief      fonction qui vérifie la longueur d'une chaîne par rapport à une
 *             taille minimum
 *
 * @param      string  la chaîne de caractère
 * @param      min     le minimum que doit faire la chaîne
 *
 * @return     1 si le string > minimum, 0 sinon
 */
int isEnoughtLong(const char *string,const unsigned  int min);

/**
 * @fn         int isAlphaRegex (const char *string,const size_t size)
 * @brief      vérifie si une chaîne est alpha-Non-Numérique
 *
 * @param      string  la chaîne de caractère
 * @param      size    la taille de la chaîne
 *
 * @return     0 si un caractère est différent de A-Za-z, 1 sinon
 *
 * verifie si une chaîne est alpha-Non-Numérique.
 */
int isAlphaRegex(const char *string,const size_t size);

/**
 * @fn         FILE* openFile(const char *name,const char *mode)
 * @brief      ouvre et retourne un fichier
 *
 * @param      name  nom du fichier
 * @param      mode  type d'ouverture
 *
 * @return     retourne un fichier ouvert
 *
 * Fonction qui tente d'ouvrir un fichier comme spécifié en paramètre,
 * si cela n'est pas possible (read mode and file not exist) alors la fonction
 * créé le fichier le ferme et effectue une récursion
 */
FILE *openFile(const char *name,const char *mode);

/**
 * @fn         int isFileContainInt(FILE *file,const unsigned int count,const char separator,const char endline,const int sequence)
 * @brief      recherche un integer dans un fichier
 *
 * @param      file       nom du fichier
 * @param      count      après combien de séparator chercher
 * @param      separator  le séparateur entre chaque valeur
 * @param      endline    charactère de fin de ligne
 * @param      sequence   la sequence de chiffre à chercher
 *
 * @return     retourne la position du cursor si la séquence est trouvé , -1
 *             sinon
 *
 * Fonction qui va rechercher dans un fichier un integer , le fichier
 * se doit d'être structuré de façon a avoir 1 donnée un séparateur ex:
 * valeur1|valeur2|valeur3|....
 */
int isFileContainInt(FILE *file,const unsigned int count,const char separator,const char endline,const int sequence);

/**
 * @fn         int int isFileContainSequence(FILE *file,const unsigned int count,const char separator,const char endline, const char *sequence)
 * @brief      recherche une séquence de char dans un fichier
 *
 * @param      file       nom du fichier
 * @param      count      après combien de séparator chercher
 * @param      separator  le séparateur entre chaque valeur
 * @param      endline    caractère de fin de ligne
 * @param      sequence   la séquence de caractère à chercher
 *
 * @return     retourne la position du cursor si la séquence est trouvé , -1
 *             sinon
 *
 * Fonction qui va rechercher dans un fichier un integer , le fichier
 * se doit d'être structuré de façon a avoir 1 donnée un séparateur ex:
 * valeur1_valeur2_valeur3_....
 */
int isFileContainSequence(FILE *file,const unsigned int count,const char separator,const char endline, const char *sequence);

/**
 * @fn         int howManySeparatorContainFile(FILE *file,const char separator)
 * @brief      fonction de recherche
 *
 * @param      file       fichier où rechercher
 * @param      separator  le caractère à rechercher
 *
 * @return     le nombre d'occurrence trouvé
 *
 * Fonction qui recherche dans un fichier le nombre de fois ou un caractère
 * spécifique à été trouvé
 */
int howManySeparatorContainFile(FILE *file,const char separator);
/**
 * @fn         int isBiggerThan(char *a,char *b)
 * @brief      fonction boolean
 *
 * @param      a     première chaîne de caractère
 * @param      b     deuxième chaîne de caractère
 *
 * @return     1 si le caractère a[0] > b[0] , 0 sinon
 *
 * Fonction qui compare deux chaîne de caractère dans le but d'un tri,
 * les 2 chaînes doivent se terminer par \0 !
 */
int isBiggerThan(char *a,char *b);

/**
 * @fn         void* alloc (size_t size)
 * @brief      allocation dynamique sécurisé
 *
 * @param      size  taille en octect à allouer
 *
 * @return     *void retourne un pointeur ou exit
 *
 * Fonction retournant un pointeur de type void,a caster donc !
 *	Si la fonction ne peut allouer alors le programme quitte
 */
void *alloc(const size_t size);

/**
 * @fn         Integer *new_Integer(const int value)
 * @brief      Procédure Création
 *
 * @param      value  valeur de l'Integer
 *
 * @return     Structure Integer , NULL sinon
 *
 * crée une structure Integer et la retourne
 * exit(1) si l'allocation de mémoire échoue
 */
Integer *new_Integer(const int value);

/**
 * @fn         ArrayInteger *new_array_integer()
 * @brief      Procédure Création
 *
 * @return     retourne un nouveau ArrayInteger
 *
 * Fonction qui crée et initialise un ArrayInteger et le retourne.
 * exit(1) si l'allocation de mémoire échoue
 */
ArrayInteger *new_array_integer();

/**
 * @fn         Integer *addIntegerToArray(ArrayInteger *array,const int value)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayInteger
 * @param      value  Valeur à ajouter
 *
 * @return     Integer crée (new_integer()), sinon NULL
 *
 * Procédure qui prend en charge la création d'un Integer et l'ajoute
 * (avec tous les liens nécessaires) dans un ArrayInteger,
 * si la création c'est bien déroulé l'Integer est retourné, NULL sinon
 */
Integer *addIntegerToArray(ArrayInteger *array,const int value);
/*****************\
	 PROCEDURE
\*****************/
/**
 * @fn         void clearBuffer()
 * @brief      Nettoie le Buffer
 *
 * Nettoie le buffer si des données sont en attente
 */
void clearBuffer();

/**
 * @fn         void stringLower(char *string ,size_t size)
 *
 * @brief      place un text en minuscule
 *
 * @param      string  chaîne de caractère
 * @param      size    taille de la chaîne
 *
 * Procédure permettant le passage d'un tableau de char
 *	en minuscule.
 */
void stringLower(char *string,const size_t size);

/**
 * @fn         void stringUpper(char *string,size_t size)
 *
 * @brief      place un text en majuscule
 *
 * @param      string  la chaîne
 * @param      size    taille de la chaîne
 *
 * Procédure permettant le passage d'un tableau de char
 * en majuscule.
 */
void stringUpper(char *string,const size_t size);

/**
 * @fn         void initString (char *string,size_t size)
 * @brief      initialise un string
 *
 * @param      string  la chaîne
 * @param      size    taille de la chaîne
 *
 * Procédure initialisant un string où le dernier caractère
 * est le fin de chaîne '\0'.
 */
void initString(char *string,const size_t size);

/**
 * @fn         void initVoidTab (void *tab,const size_t size)
 * @brief      initialise un tableau
 *
 * @param      tab  le tableau
 * @param      size    taille de la chaîne
 *
 * Procédure initialisant un tableau de tout type à NULL
 */
void initVoidTab(void *tab[],const size_t size);

/**
 * @fn         void setShortParam(short *param,const char *field,const int min,const int max)
 * @brief      applique une valeur à un int de façon sécurisé
 *
 * @param      param  adresses d'un integer
 * @param      field  phrase à afficher à l'utilisateur
 * @param      min    taille minimum
 * @param      max    taille maximum
 *
 * Procédure qui assigne à un Short une valeur entre 2 intervalles,
 * la fonction affiche un message d'aide à l'utilisateur
 */
void setShortParam(short *param,const char *field,const int min,const int max);
/**
 * @fn         void setIntegerParam(int *param,const char *field,const int min,const int max)
 * @brief      applique une valeur à un int de façon sécurisé
 *
 * @param      param  adresses d'un integer
 * @param      field  phrase à afficher à l'utilisateur
 * @param      min    taille minimum
 * @param      max    taille maximum
 *
 * Procédure qui assigne à un integer une valeur entre 2 intervalles,
 *	la fonction affiche un message d'aide à l'utilisateur
 */
void setIntegerParam(int *param,const char *field,const int min,const int max);

/**
 * @fn         void setFloatParam(float *param,const char *field,const float min,const float max)
 * @brief      applique une valeur à un float de façon sécurisé
 *
 * @param      param  l'adresse d'un float
 * @param      field  phrase à afficher à l'utilisateur
 * @param      min    taille minimum
 * @param      max    taille maximum
 *
 * Procédure qui assigne à un float une valeur entre 2 intervalles,
 *	la fonction affiche un message d'aide à l'utilisateur
 */
void setFloatParam(float *param,const char *field,const float min,const float max);

/**
 * @fn         void setStringParam(char *string,const char *field,const size_t size,const size_t min)
 * @brief      applique une valeur à un char[] de façon sécurisé
 *
 * @param      string  adresses d'un char[]
 * @param      field   phrase à afficher à l'utilisateur
 * @param      size    taille du char[]
 * @param      min     taille minimum
 *
 * Procédure qui assigne à un char[] une valeur entre 2 intervalles de longueur,
 *	la fonction affiche un message d'aide à l'utilisateur
 */
void setStringParam(char *string,const char *field,const size_t size,const size_t min);

/**
 * @fn         void exitFail(char *str)
 * @brief      gestion d'une sortie suite à une fail
 *
 * @param      str   texte a afficher
 *
 * Procédure qui gère les sorties suite à une erreur, permet d’envoyer
 *  un message puis exit(1);
 */
void exitFail(char *str);

/**
 * @fn         void nextLine(FILE *file,char endline )
 * @brief      lit une ligne
 *
 * @param      file     fichier
 * @param      endline  caractère de fin de ligne
 *
 * Procédure lit tous les caractère jusqu'à arriver au caractère de fin de ligne
 */
void nextLine(FILE *file,char endline);

/**
 * @fn         void readNextCharValue(FILE *file,char separator,char *out,size_t size)
 * @brief      lit une str[] dans un fichier
 *
 * @param      file       fichier
 * @param      separator  séparateur entre 2 valeurs
 * @param      out        variable qui contiens la valeur lu
 * @param      size       taille max de la chaîne contenue dans le fichier
 *
 * Procédure lit tous les caractère jusqu'à arriver au caractère de séparation et place
 * les données lues dans le out
 */
void readNextCharValue(FILE *file,char separator,char *out,size_t size);

/**
 * @fn         void readNextShortValue(FILE *file,char separator,short *out)
 * @brief      lit  un Short dans un fichier
 *
 * @param      file       fichier
 * @param      separator  séparateur entre 2 valeurs
 * @param      out        variable qui contient la valeur lu
 *
 * Procédure lit tous les caractère jusqu'à arriver au caractère de séparation et place
 * les données lues dans le out (converstion en int grance a strtol)
 */
void readNextShortValue(FILE *file,char separator,short *out);
/**
 * @fn         void readNextIntValue(FILE *file,char separator,int *out)
 * @brief      lit un Entier dans un fichier
 *
 * @param      file       fichier
 * @param      separator  separateur entre 2 valeurs
 * @param      out        variable qui contien la valeur lu
 *
 * Procédure lit tous les caractère jusqu'à arriver au caractère de séparation et place
 * les données lues dans le out (conversion en int grâce à strtol)
 */
void readNextIntValue(FILE *file,char separator,int *out);

/**
 * @fn         void readNextFloatValue(FILE *file,char separator,float *out)
 * @brief      lit un Float dans un fichier
 *
 * @param      file       fichier
 * @param      separator  séparateur entre 2 valeurs
 * @param      out        variable qui contient la valeur lu
 *
 * Procédure lit tous les caractère jusqu'à arriver au caractère de séparation et place
 *  les données lues dans le out (conversion en float grâce a strtof)
 */
void readNextFloatValue(FILE *file,char separator,float *out);


/**
 * @fn         void writeCpy(FILE *file,const char *nameTpm,const int cursorPos)
 * @brief      Création d'un fichier de copie temporaire
 *
 * @param      file       fichier
 * @param      nameTpm    nom du fichier temporaire
 * @param      cursorPos  position max du cursor, -1 si EOF visé
 *
 * première procédure de modification par copy, la fonction
 * tente de créer un fichier FILE_CPY(define) si et seulement si le fichier
 * n'existe pas au préalable alors la procédure commence , lit tous les caractères du fichier passé en paramètre
 * et les place dans le fichier FILE_CPY(define) nouvellement crée.
 */
void writeCpy(FILE *file,const char *nameTpm,const int cursorPos);

/**
 * @fn         void loadCpy(FILE *file,const char *nameTpm)
 * @brief      chargement du fichier de copy temporaire
 *
 * @param      file     fichier
 * @param      nameTpm  nom du fichier temporaire
 *
 * deuxieme et dernière étape de la procédure de modification par copy,
 * Si et seulement si le fichier FILE_CPY(define) existe alors lit tout les caractères
 * contenue dans le FILE_CPY et les place dans le fichier placé en paramètre.
 * le fichier FILE_CPY(define) est supprimé à la fin de la copie
 */
void loadCpy(FILE *file,const char *nameTpm);

/**
 * @fn         void SYS_LOG(char *str,char *file,int line)
 * @brief      gestion d'un log file
 *
 * @param      str   message à noter
 * @param      file  fichier actuel
 * @param      line  ligne d'appel
 *
 * Procédure qui permet la gestion d'un fichier log simple,
 * ajout en écriture l'heure,la date un message le fichier et la ligne
 */
void SYS_LOG(char *str,char *file,int line);

/**
 * @fn         void visualHSeparator(const char c,const int count)
 * @brief      gestion d'un log file
 *
 * @param      c      message à noter
 * @param      count  fichier actuel
 *
 * Procédure crée un séparateur visuel pour la console
 */
void visualHSeparator(const char c,const int count);

/**
 * @fn         void destroyArrayInteger(ArrayInteger *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayInteger
 *
 * Procédure qui libère la mémoire de tous les Integer
 * contenue dans le ArrayInteger, la libération commence par la fin
 * et fini par libéré l'arrayInteger
 */
void destructArrayInteger(ArrayInteger *array);

/**
 * @fn         void destroyArrayInteger(ArrayInteger *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayInteger
 *
 * Procédure qui permet persister un Integer.
 * Structure: %d-..
 */
void writeInteger(FILE *file,const Integer *integer);
/**
 * @fn         void writeArrayInteger(FILE *file,const ArrayInteger *array,char separator)
 * @brief      Procédure outils
 *
 * @param      file   fichier où sont persisté les données
 * @param      array  Structure ArrayInteger
 * @param      separator  Caractère de séparation entre les valeurs
 *
 * Procédure qui permet persister l'intégralité d'un arrayInteger.
 * Structure: size separator ...writeInteger()... separator
 */
void writeArrayInteger(FILE *file,const ArrayInteger *array,char separator);
/**
 * @fn         void loadArrayInteger(FILE *file,ArrayInteger *array,char separator)
 * @brief      Procédure outils
 *
 * @param      file       fichier où sont persisté les données
 * @param      array      Structure ArrayInteger
 * @param      separator  Caractère de séparation entre les valeurs
 *
 * Procédure qui commence par déterminer le nombre d'Integer dans le fichier,
 * elle affecte ce nombre à la taille de la structure de contrôle(ArrayInteger),ensuite elle boucle autant de fois que
 * nécessaire pour allouer , initialiser , charger et attacher à la structure de contrôle(ArrayInteger) les Integers dans le fichier.
 */
void loadArrayInteger(FILE *file,ArrayInteger *array,char separator);
/**
 * @fn         void removeIntegerToArray(ArrayInteger *array,Integer *integer)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayInteger
 * param       integer Integer à retirer
 *
 * Procédure qui enlève un Integer d'une structure de contrôle(ArrayInteger)
 * (avec tous les liens nécessaires)
 */
void removeIntegerToArray(ArrayInteger *array,Integer *integer);


#endif
