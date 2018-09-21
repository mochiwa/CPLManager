#ifndef __ADDRESS__H__
#define __ADDRESS__H__
/**
 * @file address.h
 * @brief      Entité Address
 * @author     Chiappelloni Nicolas
 * @version    2.0
 * @date       03/03/2018
 *
 * Entité Address qui décrit une adresse complète,
 * l'entité possède les fonctions C.R.U.D et est pensée
 * de façon 'générique'
 */

  /*******************************************************************************************\
<| ////////////////////////////////////////--INCLUDE--//////////////////////////////////////// |>
  \*******************************************************************************************/
#include "own.h"
  /*******************************************************************************************\
<| //////////////////////////////////////--CONSTANTE--//////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @def BUFFER_SIZE
 * défini la taille des chaînes de caractère par défaut
 */
#define BUFFER_SIZE 50
/**
 * @def NUM_MIN
 * défini le numéro minimum d'une habitation
 */
#define NUM_MIN 1
/**
 * @def NUM_MAX
 * défini le numéro maximum d'une habitation
 */
#define NUM_MAX 1000
/**
 * \def BTE_MIN
 * défini le numéro minimum d'une boite
 */
#define BTE_MIN 1
/**
 * @def BTE_MAX
 * défini le numéro maximum d'une boite
 */
#define BTE_MAX 1000
/**
 * @def CP_MIN
 * défini le numéro minimum d'un code postale
 */
#define CP_MIN 1000
/**
 * @def CP_MAX
 * défini le numéro maximum d'un code postale
 */
#define CP_MAX 9999

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @struct Address
 * @brief  Entité Adresse
 *
 * Entité Address comprenant tout ce qui est nécessaire à la création d'une adresse postale
 */
typedef struct Address
{
	int number; /*!< Numéro d'un bâtiment */
	int bte; /*!< Boite d'un bâtiment */
	int postalCode; /*!< Code postale de la ville */

	char street[BUFFER_SIZE]; /*!< Nom de la rue */
	char city[BUFFER_SIZE]; /*!< Nom de la ville */
	char country[BUFFER_SIZE]; /*!< Nom du pays */
}Address;

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         char isAddressEgal(const Address *address,const Address *other)
 * @brief      Fonction boolean
 *
 * @param      address  Adresse mémoire d'une structure Address
 * @param      other    Adresse mémoire d'une structure Address
 *
 * @return     1 si les deux Address sont égales , 0 sinon
 *
 * Fonction qui teste si deux adresses sont égales.
 */
char isAddressEgal(const Address *address,const Address *other);

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         void initAddress(Address *address)
 * @brief      Procédure d'initialisation
 *
 * @param      address  Adresse mémoire d'une structure Address
 *
 * Procédure qui initialise à 0 toutes les données d'une adresse
 */
void initAddress(Address *address);

/**
 * @fn         void makeAddress (Address *address)
 * @brief      Procédure Création
 *
 * @param      address  Adresse mémoire d'une structure Address
 *
 * Procédure interactive de création d'une adresse.
 */
void makeAddress(Address *address);

/**
 * @fn         void cpyAddress(Address *address,const Address *src)
 * @brief      Procédure outils
 *
 * @param      src      Adresse mémoire d'une structure Address
 * @param      address  Adresse mémoire d'une structure Address
 *
 * Procédure qui copie une Address A dans une Address B
 */
void cpyAddress(Address *address,const Address *src);

/**
 * @fn         void editAddress (Address *address)
 * @brief      Procédure Edition
 *
 * @param      address  Adresse mémoire d'une structure Address
 *
 * Menu interactif permettant la modification d'une adresse
 */
void editAddress(Address *address);

/**
 * @fn         void printAddress (const Address *address)
 * @brief      Procédure d'affichage
 *
 * @param      address  Adresse mémoire d'une structure Address
 *
 * Procédure d'affichage structurée d'une adresse
 */
void printAddress(const Address *address);

 /**
  * @fn         writeAddress(FILE *file,const Address *address,const char separator)
  * @brief      Procédure de sauvegarde
  *
  * @param      file       Fichier de sauvegarde
  * @param      separator  Caractère de séparation entre attributs
  * @param      address    Adresse mémoire d'une structure Address
  *
  * Procédure qui permet de persister une adresse, cela implique une nouvelle adresse ou la MAJ d'une
  * adresse existante
  */
void writeAddress(FILE *file,const Address *address,const char separator);

/**
 * @fn         void loadAddress(FILE *file,Address *address,const char separator)
 * @brief      Procédure de chargement
 *
 * @param      file        fichier de sauvegarde
 * @param      separator   caractère de séparation entre attributs
 * @param      address     Adresse mémoire d'une structure Address
 *
 * Procédure qui permet de charger une adresse sauvegardée dans une fichier.
 * Le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affectée à la variable qui lui est destinée.
 */
void loadAddress(FILE *file,Address *address,const char separator);
#endif

