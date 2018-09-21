#ifndef __ENTITY__H__
#define __ENTITY__H__
/**
 * @file entity.h
 * @brief      Entité Entity
 * @author     Chiappelloni Nicolas
 * @version    1.0
 * @date       03/03/2018
 *
 * Entité Entity permet la création d'une entité complète (nom,prénom,etc),
 * l'entité possède les fonctions C.R.U.D et est pensée
 * de façon 'générique'
 */

  /*******************************************************************************************\
<| ////////////////////////////////////////--INCLUDE--//////////////////////////////////////// |>
  \*******************************************************************************************/
#include "own.h"
#include "date.h"

  /*******************************************************************************************\
<| //////////////////////////////////////--CONSTANTE--//////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @def BUFFER_SIZE
 * défini la taille des chaînes de caractère par défaut
 */
#define BUFFER_SIZE 50

  /*******************************************************************************************\
<| //////////////////////////////////--Structure|Entité--///////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @struct Entity
 * @brief  Entité Entité
 *
 * L'entité Entity est une structure représentant une entité vivante ou
 * toute chose pouvant avoir un nom,prénom,age(DateTime) et sexe
 */
typedef struct Entity
{
 	char sexe ; /*!< Sexe de l'Entity, 1 = femme , homme sinon */
 	char name[BUFFER_SIZE]; /*!< Nom de l'Entity*/
 	char forename[BUFFER_SIZE]; /*!< Prénom de l'Entity*/

 	DateTime birthday; /*!< Date de naissance de l'entity*/
}Entity;

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

/**
 * @fn         char isEntityEgal(const Entity *entity, const Entity *other)
 * @brief      Fonction boolean
 *
 * @param      entity  Adresse mémoire d'une structure Entity
 * @param      other   Adresse mémoire d'une structure Entity
 *
 * @return     1 si les deux entity sont égales , 0 sinon
 *
 * Fonction qui teste si deux entités sont égales à l’exception de leur id !
 */
char isEntityEgal(const Entity *entity, const Entity *other);

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

 /**
  * @fn         void initEntity(Entity *entity)
  * @brief      Procédure d'initialisation
  *
  * @param      entity  Adresse mémoire d'une structure Entity
  *
  * Procédure qui initialise à 0 toutes les données de l'entité
  */
void initEntity(Entity *entity);

 /**
  * @fn         void makeEntity(Entity *entity)
  * @brief      Procédure Création
  *
  * @param      entity Adresse mémoire d'une structure Entity
  *
  * Lance une procédure interactive de création d'une entité.
  */
void makeEntity(Entity *entity);

/**
 * @fn         void cpyEntity(Entity *entity,const Entity *src)
 * @brief      Procédure outils
 *
 * @param      entity  Adresse mémoire d'une structure Entity
 * @param      src     Adresse mémoire d'une structure Entity
 *
 * Procédure qui copie une entité A dans une entité B sauf l'id.
 */
void cpyEntity(Entity *entity,const Entity *src);

 /**
  * @fn         void editEntity (Entity *entity)
  * @brief      Procédure d'edition
  *
  * @param      entity  Adresse mémoire d'une structure Entity
  *
  * Menu interactif Permettant la modification d'une entité
  */
void editEntity(Entity *entity);

 /**
  * @fn         void printEntity (const Entity *entity )
  * @brief      Procédure d'affichage
  *
  * @param      entity  Adresse mémoire d'une structure Entity
  *
  * Procédure d'affichage structuré d'une entité
  */
void printEntity(const Entity *entity);

 /**
  * @fn         void writeEntity(FILE *file,const Entity *entity,const char separator)
  * @brief      Procédure de sauvegarde
  *
  * @param      file        Fichier de sauvegarde
  * @param      separator   Caractère de séparation entre attributs
  * @param      entity->    Adresse mémoire d'une structure Entity
  *
  * Procédure qui permet de persister une entité, cela implique une nouvelle entité ou un MAJ d'une
  * entité existante
  */
void writeEntity(FILE *file,const Entity *entity,const char separator);

 /**
  * @fn         void loadEntity(FILE *file,Entity *entity,const char separator)
  * @brief      Procédure de chargement
  *
  * @param      file       Fichier de sauvegarde
  * @param      separator  Caractère de séparation entre attributs
  * @param      entity     Adresse mémoire d'une structure Entity
  *
  * Procédure qui permet de charger une entité sauvegarder dans une fichier.
  * Le chargement se fait par étape, chaque valeur est lue jusqu'au caractère
  * de séparation et affectée à la variable qui lui est destinée.
  */
void loadEntity(FILE *file,Entity *entity,const char separator);

#endif
