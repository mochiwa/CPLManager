#ifndef __PRODUCT__H__
#define __PRODUCT__H__
/**
 * @file product.h
 * @brief      Entité Product
 * @author     Chiappelloni Nicolas
 * @version    2.0
 * @date       07/04/2018
 *
 * Entité Product permet la création d'un produit ou service,
 * l'entité possède les fonctions C.R.U.D et est dynamique
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
/**
 * @def PRICE_MIN
 *  défini le prix minimum d'un Product
 */
#define PRICE_MIN 1
/**
 * @def PRICE_MAX
 * défini le prix maximum d'un product
 */
#define PRICE_MAX 10000

#ifdef LINUX
    /**
     * @def PRODUCTS_FILE
     * défini le nom du fichier où se trouve les Products persistants
     */
    #define PRODUCTS_FILE "FILES/products.data"
#else
    #define PRODUCTS_FILE "FILES\\products.data"
#endif

/**
 * @def SEPARATOR
 * caractère séparateur entre les valeurs d'une entité à persisté (fichier)
 */
#define SEPARATOR '|'

/**
 * @def ENDLINE
 * caractère de fin de ligne (fichier)
 */
#define ENDLINE ';'

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @enum  Category
 * @brief énumération Category
 * Category est une énumération donnant un type spécial à un produit
 */
typedef enum Category 
{
  electro=1,
  cuisine=2,
  service=3
} Category;

/**
 * @struct Product
 * @brief  Entité Produit
 * 
 * L'entité Product est un produit ou service qu'un client peut acheter.
 */
typedef struct Product
{
	int id; /*!< Id du Product */
	char isDelete ; /*!< Flag de suppression*/

	Category category; /*!< Enumération Category  */
	float price; /*!< Prix du Product*/
	char name[BUFFER_SIZE]; /*!< Nom du Product */
	struct Product *next; /*!< Ptr vers une entité Product suivante */
	struct Product *previous; /*!< Ptr vers une entité Product précédente */
}Product;


/**
 * @struct ArrayProduct
 * @brief  Structure de contrôle
 * 
 * Structure permettant le contrôle d'une liste chainée de Product
 */
typedef struct ArrayProduct
{
	int size; /*!< Nombre d'entité traité*/
	Product *head;/*!< premier élément*/
	Product *middle;/*!< élément du milieu*/
	Product *tail;/*!< dernier élément*/
}ArrayProduct;

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         Product *new_product(const int id)
 * @brief      Fonction de Création (Dynamique)
 *
 * @param      id    id de la structure Product
 *
 * @return     Entité Product
 * 
 * Crée un produit, demande les infos à l'utilisateur et retourne le produit crée.
 * exit(1) si l'allocation de mémoire échoue.
 */
Product *new_product(const int id);

/**
 * @fn         Product *getProductById(const ArrayProduct *array,const int id)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayProduct
 * @param      id     ID à rechercher
 *
 * @return     Retourne un pointeur vers une entité Product contenue dans l'array si trouvé, NULL sinon
 *    
 * Fonction qui parcoure une structure de contrôle(ArrayProduct) de produit et renvoie un pointeur sur celui
 * qui possède la même id que fournie en paramètre
 */
Product *getProductById(const ArrayProduct *array,const int id);

/**
 * @fn         Product *getPreviousProduct(const Product *product)
 * @brief      Fonction de recherche
 *
 * @param      product  Entité Product
 *
 * @return     Un pointeur vers l'élément précédent si non NULL , product sinon
 * 
 * Fonction qui tente de retourner un produit précédent qui est non NULL et non supprimé.
 * La fonction renverra toujours un produit non NULL et non supprimé quitte à se
 * renvoyer elle-même.
 *  
 * ALGO : 
 * if product->previous == NULL ? then
 *    product != deleted ? then
 *      return product
 *    else
 *      return getNextProduct(product)
 * endif
 * if product->previous == deleted ? then 
 *    getPreviousProduct(product->previous)
 * endif
 * return product->previous
 */
Product *getPreviousProduct(const Product *product);

/**
 * @fn         Product *getNextProduct(const Product *product)
 * @brief      Fonction de recherche
 *
 * @param      product  Entité Product
 *
 * @return     Un pointeur vers l'élément suivant si non NULL , product sinon
 * 
 * Fonction qui tente de retourner un produit suivant qui est non NULL et non supprimé.
 * La fonction renverra toujours un produit non NULL et non supprimé quitte à se
 * renvoyer elle-même.
 * 
 * ALGO : 
 * if product->next == NULL ? then
 *    product != deleted ? then
 *      return product
 *    else
 *      return getPreviousProduct(product)
 * endif
 * if product->next == deleted ? then 
 *    getNextProduct(product->next)
 * endif
 * return product->next
 */
Product *getNextProduct(const Product *product);


/**
 * @fn         Product *getFirstProduct(const ArrayProduct *array)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure ArrayProduct
 *
 * @return     Le premier élément non supprimé ,NULL sinon
 *
 * Fonction qui retourne le premier produit disponible (non null et non supprimé).
 * 
 * ALGO : 
 * if head != NULL ? then
 *  if head != deleted ? then
 *    return head
 *  else
 *    return getNextProduct(head)
 *  endif
 * else
 *  return NULL
 * endif
 */
Product *getFirstProduct(const ArrayProduct *array);

/**
 * @fn         Product *getLastProduct(const ArrayProduct *array)
 * @brief      Fonction de recherche
 *
 * @param      array  Structure Product (depuis le)
 *
 * @return     Le dernier élément dispo ,NULL sinon
 * 
 * Fonction qui retourne le dernier élément disponible (non null et non supprimé).
 * 
 * ALGO : 
 * if tail != NULL ? then
 *  if tail != deleted ? then
 *    return tail
 *  else
 *    return getPreviousProduct(tail)
 *  endif
 * else
 *  return NULL
 * endif
 */
Product *getLastProduct(const ArrayProduct *array);
/////////////////////////////////////////////////////////////////

 /**
  * @fn         Product *browseProducts(const ArrayProduct *array)
  * @brief      Fonction de recherche
  *
  * @param      array  structure ArrayProduct
  *
  * @return     Product si selectionné, NULL sinon
  * 
  * Menu qui permet de parcourir de "gauche à droite , début et fin" les produits contenues dans
  * une structure de contrôle ArrayProduct.
  * Chaque produit peut être sélectionné afin d'être retourné.
  *
  */
Product *browseProducts(const ArrayProduct *array);

/**
 * @fn         ArrayProduct *new_array_product()
 * @brief      Fonction de Création (Dynamique)
 *
 * @return     structure ArrayProduct
 * 
 * Fonction qui crée et initialise une structure de contrôle(ArrayProduct) pour les produits et la retourne.
 * exit(1) si l'allocation de mémoire échoue.
 */
ArrayProduct *new_array_product();

/**
 * @fn         boolean isEgalProduct(const Product *product,const Product *other)
 * @brief      Fonction boolean
 *
 * @param      other Entité Product
 * @param      product  Entité Product
 *
 * @return     1 si les deux Product sont égaux , 0 sinon
 * 
 * Fonction qui teste si deux produits sont égaux excepté leur id.
 */
int isEgalProduct(const Product *product,const Product *other);

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         void initProduct (Product *product)
 * @brief      Procédure d'initialisation
 *
 * @param      product  Adresse mémoire d'une entité Product
 * 
 * Fonction qui initialise à 0 toutes les données d'un produit.
 */
void initProduct(Product *product);

/**
 * @fn         void editProduct (Product *product)
 * @brief      Procédure Édition
 *
 * @param      product  Adresse mémoire d'une entité Product
 * 
 * Menu interactif permettant la modification d'un produit.
 */
void editProduct(Product *product);

/**
 * @fn         void loadProduct(Product *product,const int  id)
 * @brief      Procédure de chargement
 *
 * @param      product  Adresse mémoire entité Product où charger les données
 * @param      id    Id de l' entité à charger
 * 
 * Fonction qui permet de charger un produit sauvegardé dans un fichier; PRODUCTS_FILE(define).
 * le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
 * de séparation et affecté à la variable qui lui est destiné .
 * ! toute modification de structure de fichier PRODUCTS_FILE(define) doit être
 * répercuté dans le load
 * 
 * Structure: id isDel category price name
 */
void loadProduct(Product *product,const int  id);

 /**
  * @fn         void writeProduct(const Product *product)
  * @brief      Procédure de sauvegarde
  *
  * @param      product  Adresse mémoire entité Product à persister
  * 
  * Fonction qui permet de persister un produit dans un fichier
  * 
  * Structure: id isDel category price name
  */
void writeProduct(const Product *product);

/**
 * @fn         void printProduct(const Product *product)
 * @brief      Procédure d'affichage
 *
 * @param      product  Adresse mémoire entité Product à afficher
 * 
 * Fonction d'affichage structuré d'un produit
 */
void printProduct(const Product *product);

 /**
  * @fn         void productMenu(ArrayProduct *array)
  * @brief      Procédure outils
  *
  * @param      array  structure ArrayProduct
  * 
  * Menu dédié aux produits pour leur création , modification , affichage.
  */
void productMenu(ArrayProduct *array);

/**
 * @fn         void addProductToArray(ArrayProduct *array,Product *product)
 * @brief      Procédure outils
 *
 * @param      array    Structure ArrayProduct
 * @param      product  Structure Product
 * 
 * Procédure qui prend en charge l'ajout d'un produit dans un ArrayProduct
 * (avec tous les liens nécessaires)
 */
void addProductToArray(ArrayProduct *array,Product *product);

/**
 * @fn         void removeProductToArray(ArrayProduct *array,Product *product)
 * @brief      Procédure outils
 *
 * @param      array    Structure ArrayProduct
 * @param      product  Entité Product
 * 
 * Procédure qui enlève un produit d'une structure de contrôle(ArrayProduct)
 * (avec tous les liens nécessaires)
 */
void removeProductToArray(ArrayProduct *array,Product *product);

/**
 * @fn         void destructArrayProduct(ArrayProduct *array)
 * @brief      Procédure de Suppression
 *
 * @param      array  Structure ArrayProduct
 * 
 * Procédure qui libère la mémoire de tous les produits contenus dans une structure de contrôle(ArrayProduct),
 * la libération commence par la fin et fini par libérer la structure de contrôle(ArrayProduct).
 */
void destructArrayProduct(ArrayProduct *array);

/**
 * @fn         void loadProducts(ArrayProduct *array)
 * @brief      Procédure de chargements
 *
 * @param      array  structure ArrayProduct
 * 
 * Procédure qui commence par déterminer le nombre de produits dans le PRODUCTS_FILE(define), 
 * elle affecte ce nombre à la taille de la structure de contrôle(ArrayProduct),ensuite elle boucle autant de fois que
 * nécessaire pour allouer , initialiser , charger et attacher à la structure de contrôle(ArrayProduct) les produits dans le fichier. 
 */
void loadProducts(ArrayProduct *array);

/**
 * @fn         void printProducts(const ArrayProduct *array)
 *
 * @brief      Procédure d'affichage
 *
 * @param[in]  array   structure ArrayProduct
 * 
 * Procédure qui affiche tous les produits contenus dans la structure de contrôle(ArrayProduct), attend un getchar() pour passer au suivant.
 */
 void printProducts(const ArrayProduct *array);

/**
 * @fn         void printProductTitle()
 * @brief      Procédure d'affichage
 * 
 * Procédure qui affiche à l'écran un menu titre.
 */
void printProductTitle();
#endif
