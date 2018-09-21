#ifndef __CUSTOMER__H__
#define __CUSTOMER__H__

/**
 * @file customer.h
 * @brief      Entité Customer
 * @author     Chiappelloni Nicolas
 * @version    2.0
 * @date       08/04/2018
 *
 * Entité Customer qui permet la création d'un client l'entité,
 * possède les fonctions C.R.U.D et dynamique
 */
  /*******************************************************************************************\
<| ////////////////////////////////////////--INCLUDE--//////////////////////////////////////// |>
  \*******************************************************************************************/
#include "own.h"
#include "entity.h"
#include "address.h"
  /*******************************************************************************************\
<| //////////////////////////////////////--CONSTANTE--//////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @def BUFFER_SIZE
 *
 * défini la taille des chaînes de caractère par défaut
 */
#define BUFFER_SIZE 50

#ifdef LINUX
    /**
     * @def CUSTOMERS_FILE
     *
     * défini le nom/emplacement du fichier où se trouve les Customers persistants
     */
    #define CUSTOMERS_FILE "FILES/customer.data"
#else
    #define CUSTOMERS_FILE "FILES\\customer.data"
#endif

/**
 * @def SEPARATOR
 *
 * Caractère séparateur entre les valeurs d'une entité à persister
 */
#define SEPARATOR '|'
/**
 * @def ENDLINE
 *
 * Caractère de fin de ligne dans un fichier
 */
#define ENDLINE ';'

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @struct Customer
 * @brief  Entité Customer
 *
 * L'entité Client est une entité qui joue le rôle de client,
 * elle comporte une Entity et une Address
 */
typedef struct Customer
{
	int id; /*!< id du Customer*/
	char isDelete ; /*!< Flag de suppression*/

	Entity entity; /*!< Entity du Customer*/
	Address address; /*!< Address du Customer*/
	struct Customer *next; /*!< Ptr vers une entité Customer suivante*/
	struct Customer *previous; /*!< Ptr vers une entité Customer précédente*/
}Customer;

/**
 * @struct ArrayCustomer
 * @brief  Structure de contrôle
 *
 * Structure permettant le contrôle d'une liste chaîné de Customer.
 */
typedef struct ArrayCustomer
{
	int size; /*!< Nombre d'entité traité*/
	Customer *head; /*!< Première élément de liste*/
	Customer *middle;/*!< Élément du milieu*/
	Customer *tail;/*!< Dernier élément de la liste*/
}ArrayCustomer;

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn          Customer *new_customer(const int id)
 * @brief       Fonction de Création
 *
 * @param       id  id de l'entité Customer
 *
 * @return      Entité Customer , NULL sinon
 *
 * Crée une entité client, demande les infos à l'utilisateur et retourne l'entité ,
 * retourne NULL si annulé.
 * exit(1) si l'allocation de mémoire échoue.
 */
Customer *new_customer(const int id);

/**
 * @fn         Customer *getNextCustomer(const Customer *this)
 * @brief      Fonction de recherche
 *
 * @param      this  Entité Customer
 *
 * @return     ptr élément suivant non NULL, this sinon
 *
 * Fonction qui tente de retourner un client suivant qui est non NULL et non supprimé.
 * la fonction renverra toujours un client non NULL et non supprimé quitte à ce
 * renvoyer elle-même.
 *
 * ALGO :
 * if this->next == NULL ? then
 *    this != deleted ? then
 *      return this
 *    else
 *      return getPreviousCustomer(this)
 * endif
 * if this->next == deleted ? then
 *    getNextCustomer(this->next)
 * endif
 * return this->next
 */
Customer *getNextCustomer(const Customer *this);

/**
 * @fn         Customer *getPreviousCustomer(const Customer *this)
 * @brief      Fonction de recherche
 *
 * @param      this  Entité Customer
 *
 * @return     ptr élément précédent non NULL , this sinon
 *
 * fonction qui tente de retourner un client précédent qui est non NULL et non supprimé.
 * la fonction renverra toujours un client non NULL et non supprimé quitte à ce
 * renvoyer elle-même.
 *
 * ALGO :
 * if this->previous == NULL ? then
 *    this != deleted ? then
 *      return this
 *    else
 *      return getNextCustomer(this)
 * endif
 * if this->previous == deleted ? then
 *    getPreviousCustomer(this->previous)
 * endif
 * return this->previous
 */
Customer *getPreviousCustomer(const Customer *this);

/**
 * @fn         Customer getFirstCustomer(const Customer *head)
 * @brief      Fonction de recherche
 *
 * @param      head  Structure Customer
 *
 * @return     le premier élément disponible ,NULL sinon
 *
 * fonction qui retourne le premier élément disponible (non null et non supprimé).
 *
 * ALGO :
 * if head != NULL ? then
 *  if head != deleted ? then
 *    return head
 *  else
 *    return getNextCustomer(head)
 *  endif
 * else
 *  return NULL
 * endif
 */
Customer *getFirstCustomer(const Customer *head);

/**
 * @fn         Customer getLastCustomer(const Customer *tail)
 * @brief      Fonction de recherche
 *
 * @param          tail  Structure Customer
 *
 * @return     le dernier élément disponible ,NULL sinon
 *
 * fonction qui retourne le dernier élément disponible (non null et non supprimé).
 * ALGO :
 * if tail != NULL ? then
 *  if tail != deleted ? then
 *    return tail
 *  else
 *    return getPreviousCustomer(tail)
 *  endif
 * else
 *  return NULL
 * endif
 */
Customer *getLastCustomer(const Customer *tail);

/**
 * @fn         Customer *getCustomerById(ArrayCustomer *array,const int id)
 * @brief      Fonction de recherche
 *
 * @param      array  structure ArrayCustomer
 * @param      id     id à chercher
 *
 * @return     retourne un pointeur vers une entité Customer contenue dans l'array si trouvé, NULL sinon
 *
 * Fonction qui parcoure une structure de contrôle(ArrayCustomer) de client et renvoie un pointeur sur celui
 * qui possède la même id que fournie en paramètre
 */
Customer *getCustomerById(const ArrayCustomer *array,const int id);

/**
 * @fn         Customer *browseCustomers(ArrayCustomer *array)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayCustomer
 *
 * @return    Customer si séléctionné, NULL sinon
 *
 * Menu qui permet de parcourir de "gauche à droite , début et fin" les clients contenue dans
 * une structure de contrôle ArrayCustomer.
 * Sur chaque entité parcourue il est possible de la sélectionner pour la retourner
 */
Customer *browseCustomers(ArrayCustomer *array);

/**
 * @fn         Customer *getACustomerByAlphaSort(ArrayCustomer *array)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayCustomer
 *
 * @return     Customer si sélectionné,NULL sinon
 *
 * Menu qui commence par trier tous les clients par ordre alphabétique(nom),
 * ensuite divise le total des clients en en sous-parties de 8 clients et permet
 * un parcoure de ceux-ci plus aisé.
 */
Customer *getACustomerByAlphaSort(ArrayCustomer *array);

/**
 * @fn         Customer *getCustomerByNameAndForename(const ArrayCustomer *array)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayCustomer
 *
 * @return     Customer si trouvé , NULL sinon
 *
 * Menu qui demande à l'utilisateur le nom et le prénom
 * d'un client et le retourne s'il est trouvé.
 */
Customer *getCustomerByNameAndForename(const ArrayCustomer *array);

/**
 * @fn         Customer *selectCustomerForOrder(ArrayCustomer *array)
 * @brief      Fonction Menu
 *
 * @param      array  Structure ArrayCustomer
 *
 * @return     Customer si trouvé ou crée , NULL sinon
 *
 * Menu qui permet de sélectionner un client pour crée une commande
 * avec différent choix de recherche ou encore la création de celui-ci.
 */
Customer *selectCustomerForOrder(ArrayCustomer *array);

/**
 * @fn         ArrayCustomer *new_array_customer()
 * @brief      Procédure de Création (dynamique)
 *
 * @return     retourne un nouveau ArrayCustomer
 *
 * Fonction qui crée et initialise un ArrayCustomer et le retourne.
 * exit(1) si l'allocation de mémoire échoue
 */
ArrayCustomer *new_array_customer();


  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         void initCustomer(Customer *this)
 * @brief      Procédure d'initialisation
 *
 * @param      this  Adresse mémoire d'une entité Customer
 *
 * Procédure qui initialise à 0 toutes les données d'un client.
 */
void initCustomer(Customer *this);

/**
 * @fn         void editCustomer(Customer *this)
 * @brief      Procédure outils
 *
 * @param      this  Adresse mémoire d'une entité Customer
 *
 * Menu interactif Permettant la modification d'un client
 */
void editCustomer(Customer *this);

/**
 * @fn         void loadCustomer(Customer *this,const int  id)
 * @brief      Procédure de chargement
 *
 * @param      id    Id de la structure à charger
 * @param      this  Adresse mémoire d'une structure Customer
 *
 * Procédure qui permet de charger un client sauvegardé dans une fichier; CUSTOMERS_FILE(define).
 * le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affecté à la variable qui lui est destiné .
 * ! toute modification de structure de fichier CUSTOMERS_FILE(define) doit être
 * répercuté dans le load
 * Structure : id isdel {entity} {address}
 */
void loadCustomer(Customer *this,const int  id);

/**
 * @fn         void writeCustomer(const Customer *this)
 * @brief      Procédure de sauvegarde
 *
 * @param      this  Adresse mémoire d'une entité Customer
 *
 * Procédure qui permet de persister un client.
 * Structure : id isdel {entity} {address}
 */
void writeCustomer(const Customer *this);

/**
 * @fn         void cpyCustomer(Customer *this,const Customer *src)
 * @brief      Procédure outils
 *
 * @param      src        Adresse mémoire d'une entité Customer
 * @param      this  Adresse mémoire d'une entité Customer
 *
 * Procédure qui copie les données d'un client A dans un client B sauf l'id.
 */
void cpyCustomer(Customer *this,const Customer *src);

/**
 * @fn         void printCustomer(const Customer *this)
 * @brief      Procédure d'affichage
 *
 * @param      this->  Adresse mémoire d'une entité Customer
 *
 * Procédure d'affichage structuré d'un client s'il n'est pas effacé.
 * Affiche Entity puis Address.
 */
void printCustomer(const Customer *this);

/**
 * @fn         void customerMenu(ArrayCustomer *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayCustomer
 *
 * Menu dédié à la création , modification , l'affichage de l'ensemble des clients
 * contenue dans la structure de contrôle(ArrayCustomer)
 */
void customerMenu(ArrayCustomer *array);

/**
 * @fn         void sortArrayCustomerByName(ArrayCustomer *array)
 * @brief      Procédure de tri
 *
 * @param      array  Structure ArrayCustomer
 *
 * Procédure qui trie une structure de contrôle (ArrayCustomer) de client par leur Nom
 * (tri de pointeur)
 */
void sortArrayCustomerByName(ArrayCustomer *array);

/**
 * @fn         void sortArrayCustomerById(ArrayCustomer *array)
 * @brief      Procédure de tri
 *
 * @param      array  Structure ArrayCustomer
 *
 * Procédure qui tri une structure de contrôle (ArrayCustomer) de client par leur ID
 * (tri de pointeur)
 */
void sortArrayCustomerById(ArrayCustomer *array);

/**
 * \fn void addCustomerToArray(ArrayCustomer *array,Customer *customer)
 * \brief Procédure outils
 *
 * \param array Structure ArrayCustomer
 * \param customer Entité Customer
 *
 * Procédure qui ajoute un client dans un ArrayCustomer
 */
void addCustomerToArray(ArrayCustomer *array,Customer *customer);

/**
 * @fn         void removeCustomerToArray(ArrayCustomer *array,Customer *customer)
 * @brief      Procédure outils
 *
 * @param      array     Structure ArrayCustomer
 * @param      customer  Entité Customer
 *
 * Procédure qui enlève un client d'une structure de contrôle(ArrayCustomer)
 * (avec tous les liens nécessaires)
 */
void removeCustomerToArray(ArrayCustomer *array,Customer *customer);

/**
 * @fn         void destructArrayCustomer(ArrayCustomer *array)
 * @brief      Procédure outils
 *
 * @param      array  Structure ArrayCustomer
 *
 * Procédure qui libère la mémoire de tous les clients
 * contenue dans la structure de contrôle(ArrayCustomer), la libération commence par la fin
 * et fini par libéré la structure de contrôle(ArrayCustomer).
 */
void destructArrayCustomer(ArrayCustomer *array);

/**
 * @fn         void loadCustomers(ArrayCustomer *array)
 * @brief      Procédure de chargements
 *
 * @param      array  tableau de Customer
 *
 * Procédure qui commence par déterminer le nombre de client dans le PRODUCTS_FILE(define),
 * elle affecte ce nombre à la taille de la structure de contrôle(ArrayCustomer),ensuite elle boucle autant de fois que
 * nécessaire pour allouer , initialiser , charger et attacher à la structure de contrôle(ArrayCustomer) les clients dans le fichier.
 */
void loadCustomers(ArrayCustomer *array);

/**
 * @fn         void printCustomers(const ArrayCustomer *array)
 * @brief      Procédure d'affichage
 *
 * @param      array  Structure ArrayCustomer
 *
 * Procédure d'affichage de tous les clients contenue dans la
 * structure de contrôle(ArrayCustomer).
 */
void printCustomers(const ArrayCustomer *array);

/**
 * @fn         void printCustomerTitle()
 * @brief      Procédure d'affichage
 *
 * Affiche un menu titre "Menu Client"
 */
void printCustomerTitle();

#endif
