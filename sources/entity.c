#include "entity.h"

//////////////////////////////--FONTIONS--/////////////////////////////////////////////

char isEntityEgal(const Entity *entity,const Entity *other)
{
	if(entity->sexe==other->sexe)
		if(!strcmp(entity->name,other->name))
			if(!strcmp(entity->forename,other->forename))
				return 0;
	return 1;
}

//////////////////////////////--PROCEDURES--/////////////////////////////////////////////

void initEntity(Entity *entity)
{
 	entity->sexe=0;
 	initString(entity->name,BUFFER_SIZE);
 	initString(entity->forename,BUFFER_SIZE);

 	initDateTime(&entity->birthday);
}

void makeEntity(Entity *entity)
{
	do{
		setStringParam(entity->name,"Nom",BUFFER_SIZE,3);
	}while(!isAlphaRegex(entity->name,BUFFER_SIZE));

	do{
 		setStringParam(entity->forename,"Prenom",BUFFER_SIZE,3);
 	}while(!isAlphaRegex(entity->forename,BUFFER_SIZE));

 	entity->sexe=!isValid("* Etes-vous un Homme ?");
 	printf("* --Date de naissance--\n");
 	makeDateTime(&entity->birthday);
}

void cpyEntity(Entity *entity,const Entity *src)
{
	entity->sexe=src->sexe;
	strcpy(entity->name,src->name);
	strcpy(entity->forename,src->forename);
	cpyDateTime(&entity->birthday,&src->birthday);
}

void editEntity(Entity *entity)
{
 	printf("		1) Modifier le nom\n");
 	printf("		2) Modifier le prenom\n");
 	printf("		3) Modifier le sexe\n");
 	printf("		4) Modifier la naissance\n");
 	printf("		5) Tout modifier\n");
 	printf("		9) Retour \n");
 	printf("> ");
 	switch(readInt())
 	{
 		case 1:
 			do{
 				setStringParam(entity->name,"Nom",BUFFER_SIZE,3);
 			}while(!isAlphaRegex(entity->name,BUFFER_SIZE));
	 		break;
 		case 2:
 			do{
	 			setStringParam(entity->forename,"Prenom",BUFFER_SIZE,3);
	 		}while(!isAlphaRegex(entity->forename,BUFFER_SIZE));
	 		break;
 		case 3:
	 		entity->sexe=isValid("Etes-vous une Femme ?");
	 		break;
	 	case 4:
	 		makeDateTime(&entity->birthday);
	 		break;
 		case 5:
	 		makeEntity(entity);
	 		break;
 		case 9:
	 		break;
 		default:
 			break;
 	}
}

void printEntity(const Entity *entity)
{
 	printf("* -Nom : %s\n",entity->name );
 	printf("* -Prenom : %s\n",entity->forename );
 	printf("* -Sexe : ");
 	if(entity->sexe)
 		printf("femme\n");
 	else
 		printf("homme\n");
 	printf("* -Naissance: ");
 	printDateTimeToString(&entity->birthday);
 	printf("\n");
}

void writeEntity(FILE *file,const Entity *entity,const char separator)
{
 	fprintf(file, "%d%c",entity->sexe,separator);
	fprintf(file, "%s%c%s%c",entity->name,separator,entity->forename,separator );
	writeDateTime(file,&entity->birthday,separator);
}

void loadEntity(FILE *file,Entity *entity,const char separator)
{
	readNextIntValue(file,separator,(int *)&entity->sexe);
	readNextCharValue(file,separator,entity->name,BUFFER_SIZE);
	readNextCharValue(file,separator,entity->forename,BUFFER_SIZE);
	loadDateTime(file,&entity->birthday,separator);
}
