#ifndef __LINE__H__
#define __LINE__H__
/**
 * @file line.h
 * @brief      Entité Line
 * @author     Chiappelloni Nicolas
 * @version    2.0
 * @date       07/04/2018
 * Entité Line qui permet la création d'une ligne de commande
 * l'entité possède les fonctions C.R.U.D,est dynamique et sert de pivot
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
 * défini la taille des chaines de charactère par defaut
 */
#define BUFFER_SIZE 50

#ifdef LINUX
    /**
     * @def LINES_FILE
     * défini le nom du fichier où se trouve les Line persistantes
     */
    #define LINES_FILE "FILES/lines.data"
#else
    #define LINES_FILE "FILES\\lines.data"
#endif

/**
 * @def SEPARATOR
 * Caractère séparateur entre les valeurs d'une entité à persister
 */
#define SEPARATOR '|'

/**
 * @def ENDLINE
 * Caractère de fin de ligne de fichier
 */
#define ENDLINE ';'

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @struct Line
 * @brief  Entité ligne de commande
 * 
 * L'entité Line est l'entité pivot entre un produit et un ordre de commande
 */
typedef struct Line
{
	int id; /*!< id de la Line*/
	int isDelete; /*!< flag de suppression*/

	int product; /*!< id du Product*/
	int quantity; /*!< quantité du product*/
	struct Line *next; /*!< Ptr vers une entité Line suivante*/
	struct Line *previous; /*!< Ptr vers une entité Line précédente*/
}Line;

/**
 * @struct ArrayLine
 * @brief  Structure de contrôle
 * 
 * Structure permettant le contrôle d'une liste chaîné de Line
 */
typedef struct ArrayLine
{
	int size; /*!< Taille de l'array*/
	Line *head; /*!< Premier élément de l'array*/
	Line *middle; /*!< Élément du milieu*/
	Line *tail; /*!< dernier élément de l'array*/
}ArrayLine;



  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         Line *new_line(const int id,const int product)
 * @brief      Procédure de Création
 *
 * @param      id       Id de l'entité Line
 * @param      product  Id d'une entité Product
 *
 * @return     entité Line , NULL sinon
 * 
 * Crée une entité Line , demande à l'utilisateur la quantité et retourne l'entité.
 * exit(1) si l'allocation de mémoire échoue.
 */
Line *new_line(const int id,const int product);

/**
 * @fn         Line *getLineById(const ArrayLine *array,const int id)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayLine
 * @param      id     Id à chercher
 *
 * @return     Retourne un pointeur vers une Line contenue dans l'array si trouvé si trouvé , NULL sinon
 * 
 * Fonction qui parcoure une structure de contrôle(ArrayLine) de lignes de commande et renvoie un pointeur sur la première
 * ligne de commande possédant le même id que passé en paramètre
 */
Line *getLineById(const ArrayLine *array,const int id);

/**
 * @fn         ArrayLine *new_array_line()
 * @brief      Procédure de Création
 *
 * @return     retourne une Structure ArrayLine
 * 
 * Fonction qui crée et initialise une structure de contrôle(ArrayLine) et la retourne.
 * exit(1) si l'allocation de mémoire échoue
 */
ArrayLine *new_array_line();

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         void initLine(Line *line)
 * @brief      Procédure d'initialisation
 *
 * @param      line  Adresse mémoire d'une entité Line
 * 
 * Procédure qui initialise à 0 toutes les données, d'une ligne de commande
 */
void initLine(Line *line);

/**
 * @fn         void editLine (Line *line)
 * @brief      Procédure Edition
 *
 * @param      line  Adresse mémoire d'une entité Line
 * 
 * Menu interactif permettant la modification|suppression d'une ligne de commande.
 */
void editLine(Line *line);

/**
 * @fn         void loadLine(Line *line,const int id);
 * @brief      Procédure de chargement
 * 
 * @param      line  Entité Line où charger les données
 * @param      id    Id de l'Entité à charger
 * 
 * Procédure qui permet de charger une ligne de commande sauvegarder dans une fichier,
 * LINES_FILE(define).
 * le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affecté à la variable qui lui est destiné .
 * Toute modification de structure de fichier LINES_FILE(define) doit être
 * répercuté dans le load
 * Structure: id isDelete product quantity
 */
void loadLine(Line *line,const int id);

 /**
  * @fn         void writeLine(const Line *line)
  * @brief      Procédure de sauvegarde
  * 
  * @param      *line  Entité Line à persister
  *
  * Procédure qui permet persister une ligne de commande.
  * Structure: id isdel product quantity
  */
void writeLine(const Line *line);

/**
 * @fn         void *addLineToArray(ArrayLine *array,Line *line)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayLine
 * @param      line   Entité Line
 * 
 * Procédure qui prend charge l'ajout d'une ligne de commande dans une structure de contrôle (ArrayLine).
 * (avec tous les liens nécessaires)
 */
void addLineToArray(ArrayLine *array,Line *line);

/**
 * @fn         void removeLineToArray(ArrayLine *array,Line *line)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayLine
 * @param      line   Entité Line
 * 
 * Procédure qui enlève une ligne de commande d'une structure de contrôle(ArrayLine)
 * (avec tous les liens nécessaires)
 */
void removeLineToArray(ArrayLine *array,Line *line);

/**
 * @fn         void destructArrayLine(ArrayLine *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayLine
 * 
 * Procédure qui libère la mémoire de toutes les lignes de commande
 * contenues dans la structure de contrôle(ArrayLine), la libération commence par la fin
 * et fini par libéré la structure de contrôle(ArrayLine).
 */
void destructArrayLine(ArrayLine *array);

/**
 * @fn         void loadLines(ArrayLine *array)
 * @brief      Procédure de chargements
 *
 * @param      array  Structure ArrayLine
 * 
 * Procédure qui commence par déterminer le nombre de lignes de commande dans le PRODUCTS_FILE(define), 
 * elle affecte ce nombre à la taille de la structure de contrôle(ArrayLine),ensuite elle boucle autant de fois que
 * nécessaire pour allouer , initialiser , charger et attacher à la structure de contrôle(ArrayLine) les lignes de commande dans le fichier. 
 */
void loadLines(ArrayLine *array);

#endif
