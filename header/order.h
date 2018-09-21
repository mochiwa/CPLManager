#ifndef __ORDER__H__
#define __ORDER__H__
/**
 * @file order.h
 * @brief      Entité Order
 * @author     Chiappelloni Nicolas
 * @version    2.0
 * @date       07/04/2018
 * 
 * Entité Order qui permet la création d'une commande complète,
 * l'entité possède les fonctions C.R.U.D , est dynamique et sert de pivot
 */
  /*******************************************************************************************\
<| ////////////////////////////////////////--INCLUDE--//////////////////////////////////////// |>
  \*******************************************************************************************/
#include "own.h"
#include "date.h"
  /*******************************************************************************************\
<| //////////////////////////////////////--CONSTANTE--//////////////////////////////////////// |>
  \*******************************************************************************************/
#ifdef LINUX
    /**
     * @def ORDERS_FILE
     * défini le nom|emplacement du fichier où se trouve les Order persistants
     */
    #define ORDERS_FILE "FILES/orders.data"
#else
    #define ORDERS_FILE "FILES\\orders.data"
#endif

/**
 * @def SEPARATOR
 * Caractère séparateur entre les valeurs d'une entité à persister(fichier)
 */
#define SEPARATOR '|'
/**
 * @def ENDLINE
 * Caractère de fin de ligne (fichier)
 */
#define ENDLINE ';'

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @struct Order
 * @brief  Entité Ordre de Commande
 * 
 * L'entité Order est l'entité pivot entre un client ,une commande et les lignes de commande
 */
typedef struct Order
{
	int id; /*!< id de l Order*/
	int isDelete; /*!< flag de suppression */

	int customer; /*!< id du Customer*/
	DateTime date; /*!< date de l Order*/
	ArrayInteger *lines; /*!< arrayInteger d'ids de Line*/
	struct Order *next; /*!< Ptr vers une entité Order suivante */
	struct Order *previous; /*!< Ptr vers une entité Order précédente */
}Order;

/**
 * @struct ArrayOrder
 * @brief  Structure de contrôle
 * 
 * Structure permettant le contrôle d'une liste chainée d'Order
 */
typedef struct ArrayOrder
{
	int size; /*!< taille de l'array*/
	Order *head;/*!< premier élément*/
	Order *middle;/*!< élément du milieu*/
	Order *tail;/*!< dernier élément*/
}ArrayOrder;

  /*******************************************************************************************\
<| ///////////////////////////////////////--FONCTION--//////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         Order *new_order(const int id,const int customer)
 * @brief      Fonction de Création (Dynamique)
 *
 * @param      id        id de l'entité Order
 * @param      customer  id de l'entité Customer à associer à l'Order
 *
 * @return     Entité Order
 *  
 * Crée une entité ordre de commande,l'initialise et la retourne.
 * exit(1) si l'allocation de mémoire échoue.
 */
Order *new_order(const int id,const int customer);

/**
 * @fn         Order *getOrderById(const ArrayOrder *array,const int id)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayOrder
 * @param      id     ID à rechercher
 *
 * @return     retourne un pointeur vers une structure Order contenue dans l'array si trouvé , NULL sinon
 *             
 * Fonction qui parcoure une structure de controle ArrayOrder et renvoie un pointeur sur le premier ordre de commande
 * ayant la même id que passé en paramètre. 
 */
Order *getOrderById(const ArrayOrder *array,const int id);

/**
 * @fn         ArrayOrder *new_array_order()
 * @brief      Fonction de Création
 *
 * @return     retourne une structure ArrayOrder
 * 
 * Fonction qui crée et initialise une structure de contrôle(ArrayOrder) pour les ordres de commande et la retourne.
 * exit(1) si l'allocation de mémoire échoue.
 */
ArrayOrder *new_array_order();

/**
 * @fn         boolean isOrderHasLines(const Order *order)
 * @brief      Fonction boolean
 * 
 * @param[in]  order   Entité Order
 *
 * @return     Retourne 1 si l'order contient au moins une Line, FALSE sinon
 * 
 * Fonction qui véréfie si un ordre de commande contient au moins une ligne de commande
 * Si order->lines->size (ArrayInteger) est > 0 alors il existe au moins une ligne de commande. 
 */
int isOrderHasLines(const Order *order);

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         void initOrder (Order *order)
 * @brief      Procédure d'initialisation
 * 
 * @param      order  Adresse mémoire d'une entité Order
 * 
 * fonction qui initialise à 0 toutes les données d'un ordre de commande
 */
void initOrder(Order *order);

/**
 * @fn         void addLineToOrder(Order *order,const int line)
 * @brief      Procédure outils
 *
 * @param      order  Order
 * @param      line  id de la Line
 * 
 * Lie une ligne de commande à un ordre de commande
 */
void addLineToOrder(Order *order,const int line);

/**
 * @fn         void destructOrder(Order *order)
 * @brief      Procédure outils
 *
 * @param      order  Entité Order
 * 
 * Procédure qui libère la mémoire d'un ordre de commande ( implique la libération du ArrayInteger)
 */
void destructOrder(Order *order);

/**
 * @fn         void loadOrder(Order *order,const int id);
 * @brief      Procédure de chargement
 *
 * @param      id    Id de la l'entité à charger
 * @param      order  Entité Order où charger les données
 * 
 * Fonction qui permet de charger un ordre de commande sauvegardé dans un fichier; ORDERS_FILE(define).
 * Le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affecté à la variable qui lui est destinée .
 * ! toute modification de structure de fichier ORDERS_FILE(define) doit être
 * répercuté dans le load.
 *
 * Structure: id isDelete Customer {Lines-} date ;
 */
void loadOrder(Order *order,const int id);

/**
 * @fn         void writeOrder (const Order *order)
 * @brief      Procédure Edition
 *
 * @param      order  Adresse mémoire d'un Order
 * 
 * Procédure qui permet de persister un ordre de commande.
 * Structure: id isDelete Customer {Lines-} date ;
 */
void writeOrder(const Order *order);

/**
 * @fn         void *addOrderToArray(ArrayOrder *array,Order *order)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayOrder
 * @param      order  Entité Order
 * 
 * Procédure qui ajoute un ordre de commande à un ArrayOrder 
 * (avec tous les liens nécessaire)
 */
void addOrderToArray(ArrayOrder *array,Order *order);

/**
 * @fn         void removeOrderToArray(ArrayOrder *array,Order *order)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayOrder
 * @param      order  Entité Order
 * 
 * Procédure qui enlève un ordre de commande d'une structure de contrôle(ArrayOrder)
 * (avec tous les liens nécessaires)
 */
void removeOrderToArray(ArrayOrder *array,Order *order);

/**
 * @fn         destructArrayOrder(ArrayOrder *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayOrder
 * 
 * Procédure qui libère la mémoire de tous les ordres de commande
 * contenue dans la structure de contrôle(ArrayOrder), la libération commence par la fin
 * et fini par libérer la structure de contrôle(ArrayOrder)
 */
void destructArrayOrder(ArrayOrder *array);

/**
 * @fn         void loadOrders(ArrayOrder *array)
 * @brief      Procédure de chargements
 *
 * @param      array  structure ArrayOrder
 * 
 * Fonction qui commence par déterminer le nombre d'ordre de commande dans le PRODUCTS_FILE(define), 
 * elle affecte ce nombre à la taille de la structure de contrôle(ArrayOrder),ensuite elle boucle autant de fois que
 * nécessaire pour allouer , initialiser , charger et attacher à la structure de contrôle(ArrayOrder) les ordres de commande dans le fichier. 
 */
void loadOrders(ArrayOrder *array);




#endif


