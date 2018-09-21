#ifndef __DATE__H__
#define __DATE__H__
/**
 * @file date.h
 * @brief      Entité DateTime
 * @author     Chiappelloni Nicolas
 * @version    1.0
 * @date       14/02/2018
 *
 * Entité DateTime qui permet la création d'une date et heure
 * l'entité possède les fonctions C.R.U.D
 */
/*****************\
	  INCLUDE
\*****************/
#include "own.h"
#include <time.h>
/*****************\
	 CONSTANTE
\*****************/
/**
 * @def BUFFER_SIZE
 * défini la taille des chaînes de caractère par défaut
 */
#define BUFFER_SIZE 50
/*****************\
	 STRUCTURE
\*****************/
/**
 * @struct DateTime
 * @brief  Entité Date
 *
 * L'entité DateTime permet la création d'une date avec le jour, le mois, l'année et l'heure minute seconde
 */
typedef struct DateTime
{
	 int hour; /*!< Heure d'une DateTime */
	 int minute; /*!< Minute d'une DateTime */
	 int second; /*!< Seconde d'une DateTime */

	 int day; /*!< Jour d'une DateTime */
	 int month; /*!< Mois d'une DateTime */
	 int years; /*!< Année d'une DateTime */
}DateTime;
/*****************\
	 FONCTION
\*****************/
/**
 * @fn         char *getMonthToString(const int month)
 *
 * @brief      Fonction outils
 *
 * @param      month  mois de 1 à 12
 *
 * @return     le mois en string (ex 11 -> novembre).
 *
 * Fonction faisant la conversion entre un mois en chiffre vers un mois en lettre 1=Janvier <-> 12=Décembre
 */
char *getMonthToString(const int month);
/**
 * @fn         char isBissextile(const DateTime *dateTime)
 * @brief      Fonction boolean
 *
 * @param      dateTime  Structure d'une DateTime.
 *
 * @return     retourne 1 Si l'année est bissextile, 0 sinon.
 *
 * Fonction retourne vrai si une année est divisible par 400 ou par 4 mais pas par 100.
 */
char isBissextile(const DateTime *dateTime);

/*****************\
	 PROCEDURE
\*****************/

/**
 * @fn         void initDateTime(DateTime *dateTime )
 * @brief      Procédure d'initialisation
 *
 * @param      dateTime  Adresse mémoire d'une DateTime
 *
 * Procédure qui initialise à 0 toutes les données d'une date
 */
void initDateTime(DateTime *dateTime);

/**
 * @fn         void makeDateTime(DateTime *dateTime)
 * @brief      Procédure de création
 *
 * @param      dateTime  Adresse mémoire d'une DateTime
 *
 * Lance une procédure interactive de création d'une date.
 */
void makeDateTime(DateTime *dateTime);

/**
 * @fn         void makeTime (DateTime *dateTime)
 * @brief      Procédure de création
 *
 * @param      dateTime  Adresse mémoire d'une DateTime
 *
 * Lance une procédure interactive de création d'une heure
 */
void makeTime(DateTime *dateTime);

/**
 * @fn         void cpyDateTime(DateTime *dateTime,const DateTime *host)
 * @brief      Procédure outils
 *
 * @param      host       Adresse mémoire d'une DateTime
 * @param      dateTime  Adresse mémoire d'une DateTime
 *
 * Procédure qui copie une Date B dans une Date A
 */
void cpyDateTime(DateTime *dateTime,const DateTime *host);

/**
 * @fn         void editDateTime(DateTime *dateTime)
 * @brief      Procédure de Modification
 *
 * @param      dateTime  Adresse mémoire d'une DateTime
 *
 * Menu interactif permettant la modification d'une date
 */
void editDateTime(DateTime *dateTime);

/**
 * @fn         void setDateTimeToToday(DateTime *dateTime)
 * @brief      Procédure de Modification
 *
 * @param      dateTime  Adresse mémoire d'une Date
 *
 * Procédure qui met la date passé en paramètre à la date système
 */
void setDateTimeToToday(DateTime *dateTime);

/**
 * @fn         void setDateTimeToSystem(DateTime *dateTime)
 * @brief      Procédure de Modification
 *
 * @param      dateTime  Adresse mémoire d'une Date
 *
 * Procédure qui met la date passé en paramètre à l'heure du système
 */
void setDateTimeToSystem(DateTime *dateTime);

/**
 * @fn         void printDateTime(const DateTime *dateTime)
 * @brief      Procédure d'affichage
 *
 * @param      dateTime  Structure DateTime
 *
 * Procédure qui affiche une date sous la forme dd/mm/yyyy + heure
 */
void printDateTime(const DateTime *dateTime);

/**
 * @fn         void printDateTimeShort(const DateTime *dateTime)
 * @brief      Procédure d'affichage
 *
 * @param      dateTime  Structure DateTime
 *
 * Procédure qui affiche une date sous la forme dd/mm/yyyy
 */
void printDateTimeShort(const DateTime *dateTime);

/**
 * @fn         void printDateTimeToString(const DateTime *dateTime)
 * @brief      Procédure d'affichage
 *
 * @param      dateTime  Structure DateTime
 *
 * Procédure qui affiche une date en lettre
 */
void printDateTimeToString(const DateTime *dateTime);

/**
 * @fn         void writeDateTime(FILE *file,const DateTime *dateTime,const char separator)
 * @brief      Procédure de sauvegarde
 *
 * @param      file       fichier où persister
 * @param      separator  caractère de séparation entre attributs
 * @param      dateTime  DateTime à persister
 *
 * Procédure qui persiste une DateTime dans un fichier
 */
void writeDateTime(FILE *file,const DateTime *dateTime,const char separator);

/**
 * @fn         void loadDateTime(FILE *file,DateTime *dateTime,const char separator);
 * @brief      Procédure de chargement
 *
 * @param      file       fichier
 * @param      separator  caractère de séparation entre attributs
 * @param      dateTime  DateTime qui contiendra les données
 *
 * Procédure qui permet de charger une DateTime sauvegarder dans une fichier.
 * le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affecté à la variable qui lui est destiner .
 * ! toute modification de structure de fichier de sauvegarde doit être
 * répercuté dans le load()
 */
void loadDateTime(FILE *file,DateTime *dateTime,const char separator);
#endif
