#ifndef __MENU__H__
#define __MENU__H__
/**
 * @file menu.h
 * @brief      Header des menus
 * @author     Chiappelloni Nicolas
 * @version    1.0
 * @date       14/02/2018
 * 
 * Fichier regroupant tous les menus disponible permerttant l'utilisation
 * des divers entités
 */

/*****************\
	  INCLUDE
\*****************/
#include "own.h"
#include "date.h"
#include "customer.h"
#include "product.h"
#include "line.h"
#include "order.h"
/*****************\
	 CONSTANTE
\*****************/
/**
 * @def BUFFER_SIZE
 * defini la taille des chaines de charactère par defaut
 */
#define BUFFER_SIZE 50

/*****************\
	 STRUCTURE
\*****************/

/*****************\
	 FONCTION
\*****************/

/*****************\
	 PROCEDURE
\*****************/

/**
 * @fn         void mainMenu()
 *
 * @brief      Menu principal
 * 
 * Premier menu lancé dans l'application, c'est dans ce menu qu'est déclaré les divers
 * données, et leur chargement.
 * Le menu permet de se déplacer vers divers menu; client, produit, commande.
 * La principal utilisation du menu est la création d'une commande
 */
void mainMenu();

/**
 * @fn         void addToCart(Order *order,Line *line,ArrayLine *lines)
 * @brief      Procédure outils
 *
 * @param      order  -> Structure Order
 * @param      line   ->  Structure Line
 * @param      lines  -> Structure ArrayLine
 * 
 * Procédure qui tente d'ajouter un produit au panier, 
 * une ligne de commande(Line) est ajoutable à un Order si et seulement si elle n'est pas deja présent
 * si la ligne de commande est déja présent on teste de lui ajouter la quantité voulu si ça ne depasse pas une limite(stock)
 
 */
void addToCart(Order *order,Line *line,ArrayLine *lines);

/**
 * @fn         void ValidCart(const Order *order,const ArrayLine *lines)
 * @brief      Procédure outils
 *
 * @param      order  -> l'Order courant
 * @param      lines  -> liste de Line
 * 
 * Parcour les lignes de commandes d'un ordre de commande et les persiste ensuite 
 * persiste l'ordre
 */
void ValidCart(const Order *order,const ArrayLine *lines);
/**
 * @fn         void editCart(Order *order,ArrayLine *lines,const ArrayProduct *products)
 * @brief      Menu dedier au commande d'un client
 *
 * @param      order     -> l'Order
 * @param      lines     -> liste de Line
 * @param      products  -> liste de Product
 * 
 * Menu dedier a la modification d'une commande en cours
 */
void editCart(Order *order,ArrayLine *lines,const ArrayProduct *products);

/**
 * @fn         void cartMenu(Order *order,ArrayLine *lines,const ArrayProduct *products)
 * @brief      Menu dedier au commande d'un client
 *
 * @param      order     -> Structure Order
 * @param      lines     -> Structure ArrayLine
 * @param      products  -> Structure ArrayProduct
 * 
 * Menu dedier a la creation , modif , etc d'une commande d'un client précis , menu lancer depuis
 * le mainMenu()
 */
void cartMenu(Order *order,ArrayLine *lines,const ArrayProduct *products);

/**
 * @fn         void printOrderLine(const Line *line,const Product *product )
 * @brief      Fonction d'affichage
 *
 * @param      line     -> Line à afficher
 * @param      product  -> Product à afficher
 * 
 * Fonction qui affiche une ligne de commande à l'écran
 */
void printOrderLine(const Line *line,const Product *product);

/**
 * @fn         void printOrderLines(Order *order,ArrayLine *lines,ArrayProduct *products);
 *
 * @brief      Fonction d'affichage
 *
 * @param      order     -> Structure Order
 * @param      lines     -> Structure ArrayLine
 * @param      products  -> Structure ArrayProduct
 * 
 * Fonction qui parcour toutes les lignes d'un ordre de commande
 * et le envoie à la fonction d'affichage printOrderLine()
 */
void printOrderLines(Order *order,ArrayLine *lines,ArrayProduct *products);

/**
 * @fn         void printBill(Order *order,ArrayLine *lines,const ArrayProduct *products)
 *
 * @brief      Fonction d'affichage
 *
 * @param      order     -> Structure Order
 * @param      lines     -> Structure ArrayLine
 * @param      products  -> Structure ArrayProduct
 * 
 * Affiche la facture du client
 */
void printBill(Order *order,ArrayLine *lines,const ArrayProduct *products);

/**
 * @fn         void printAllOrder(Order *orders,Line *lines,Product *products,Customer *customers)
 *
 * @brief      Fonction d'affichage
 *
 * @param      orders     -> liste d'Order
 * @param      lines      -> liste de Line
 * @param      products   -> liste de Product
 * @param      customers  -> liste de Customer
 * 
 * Affiche toutes les factures clients en 2 étapes
 *	1)Affiche {date Nom Prenom} et demande la selection d'un
 *	2)Affiche le detail de la commande selectionnée  
 */
void printAllOrder(ArrayOrder *orders,ArrayLine *lines,ArrayProduct *products,ArrayCustomer *customers);

/**
 * @brief      Removes a cartesian.
 *
 * @param      order  The order
 * @param      lines  The lines
 * 
 * Supprime un panier
 */
void removeCart(Order *order,ArrayLine *lines);
#endif
