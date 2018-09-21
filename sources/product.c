#include "product.h"

  /*******************************************************************************************\
<| ////////////////////////////////////////--STATICS--//////////////////////////////////////// |>
  \*******************************************************************************************/

//search if atleast one structure on arrayProduct is present and not NULL
static int atleastOne(const ArrayProduct *array)
{
	Product *p=NULL;
	for(p=array->head;p!=NULL;p=p->next)
		if(!p->isDelete)
			return 1;
	return 0;
}

static void setCategory(Product *product)
{
	product->category=0;
	while(!product->category)
	{
		printProductTitle();
		printf("*Categorie du produit :\n");
		printf("  1)Electro\n");
		printf("  2)Cuisine\n");
		printf("  3)Service\n");
		printf("  > ");
		switch(readInt())
		{
			case 1:
				product->category=electro;
				break;
			case 2:
				product->category=cuisine;
				break;
			case 3:
				product->category=service;
				break;
			default:
				printf("!----BAD REQUEST----!\n");
				printf("> ");
				getchar();
				break;
		}
	}
}

static void setPrice(Product *product)
{
	if(product->category==service)
		setFloatParam(&product->price,"Prix",-PRICE_MAX,PRICE_MAX);
	else
		setFloatParam(&product->price,"Prix",PRICE_MIN,PRICE_MAX);
}

static void arrayArrangement(ArrayProduct *array,Product *product)
{
	if(array->head==NULL)
	{
		array->head=product;
		array->middle=product;
	}
	else
	{
		array->tail->next=product;
		product->previous=array->tail;
		if(product->id%2!=0)
			array->middle=array->middle->next;
	}
	array->tail=product;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

Product *new_product(const int id)
{
	Product *product=(Product *) alloc(sizeof(Product));
	initProduct(product);
	product->id=id;

	setStringParam(product->name,"Nom du produit",BUFFER_SIZE,3);
	setCategory(product);
	setPrice(product);
	return product;
}

Product *getProductById(const ArrayProduct *array,const int id)
{
	Product *p=NULL;
	if(id < 0 || id >= array->size)
		return NULL;
	if(id < array->middle->id)
		p=array->head;
	else
		p=array->middle;
	for(;p!=NULL;p=p->next)
		if(p->id==id)
			return p;
	return NULL;
}

Product *getNextProduct(const Product *product)
{
	if(product->next==NULL)
		if(product->isDelete==0)
			return (Product *)product;
		else
			return getPreviousProduct(product);
	if(product->next->isDelete==1)
		return getNextProduct(product->next);
	else
		return (Product *)product->next;
}

Product *getPreviousProduct(const Product *product)
{
	if(product->previous==NULL)
		if(product->isDelete==0)
			return (Product *)product;
		else
			return getNextProduct(product);
	if(product->previous->isDelete==1)
		return getPreviousProduct(product->previous);
	else
		return (Product *)product->previous;
}

Product *getFirstProduct(const ArrayProduct *array)
{
	if(array->head!=NULL)
		if(array->head->isDelete==1)
			return getNextProduct(array->head);
		else
			return (Product *)array->head;
	return NULL;
}

Product *getLastProduct(const ArrayProduct *array)
{
	if(array->tail!=NULL)
		if(array->tail->isDelete==1)
			return getPreviousProduct(array->tail);
		else
			return (Product *)array->tail;
	return NULL;
}

Product *browseProducts(const ArrayProduct *array)
{
    Product *selected=NULL;

    if(atleastOne(array))
		selected=getFirstProduct(array);

	while(selected!=NULL)
    {
		printProductTitle();
		printProduct(selected);
		visualHSeparator('-',57);
		printf("	1)Precedent 2)Selectionner 3)Suivant 9)Retour\n");
		printf("                4)Debut        6)Fin\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				selected=getPreviousProduct(selected);
				break;
			case 2:
				return (Product *)selected;
				break;
			case 3:
				selected=getNextProduct(selected);
				break;
            case 4:
                selected=getFirstProduct(array);
                break;
            case 6:
                selected=getLastProduct(array);
                break;
			case 9:
				selected=NULL;
				break;
			default:
				break;
        }
    }
    return NULL;
}

ArrayProduct *new_array_product()
{
	ArrayProduct *array=(ArrayProduct *) alloc(sizeof(ArrayProduct));
	array->size=0;
	array->head=NULL;
	array->middle=NULL;
	array->tail=NULL;
	return array;
}

int isEgalProduct(const Product *product,const Product *other)
{
	if(product->isDelete==other->isDelete)
		if(product->category==other->category)
			if(product->price==other->price)
				if(!strcmp(product->name,other->name))
					return 1;
	return 0;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

void initProduct(Product *product)
{
	product->id=-1;
	product->isDelete=0;
	product->price=0;
	product->category=0;
	initString(product->name,BUFFER_SIZE);
	product->next=NULL;
	product->previous=NULL;
}

void editProduct(Product *product)
{
	int run=1;
	Product cpy=*product;
	while(run)
	{
		printProductTitle();
		printProduct(product);
		visualHSeparator('-',67);
		printf("		1) Modifier le nom \n");
		printf("		2) Modifier la categorie\n");
		printf("		3) Modifier le prix \n");
		printf("		4) Tout modifier \n");
		printf("		5) Supprimer \n");
		printf("		9) Retour \n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				setStringParam(product->name,"Nom",BUFFER_SIZE,3);
				break;
			case 2:
				setCategory(product);
				break;
			case 3:
				setPrice(product);
				break;
			case 4:
				setStringParam(product->name,"Nom",BUFFER_SIZE,3);
				setCategory(product);
				setPrice(product);
				break;
			case 5:
				if(!isValid("Confirmer la suppression ?"))
					break;
				product->isDelete=1;
			case 9:
				run=0;
				break;
			default:
				printf("!----BAD REQUEST----!\n");
				printf("> ");
				getchar();
				break;
		}
	}

	printProductTitle();
	printProduct(product);
	visualHSeparator('-',67);

	if(!isEgalProduct(product,&cpy))
	{
		if(isValid("Confirmer les changements ?"))
		{
			writeProduct(product);
			printf("**Donnees persistes** \n");
		}
		else
		{
			loadProduct(product,product->id);
			printf("**Donnees non persistes**\n");
		}
	}
	else
		printf("**Aucune modification n'a eu lieu**\n");
	getchar();
}

void loadProduct(Product *product,const int  id)
{
	int cursor;
	FILE *file=openFile(PRODUCTS_FILE,"r");

	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,id))!=-1)
	{
		fseek(file,cursor,SEEK_SET);
		readNextIntValue(file,SEPARATOR,&product->id);
		readNextIntValue(file,SEPARATOR,(int *)&product->isDelete);

		readNextIntValue(file,SEPARATOR,(int *)&product->category);
		readNextFloatValue(file,SEPARATOR,&product->price);

		readNextCharValue(file,SEPARATOR,product->name,BUFFER_SIZE);
	}
	fclose(file);
}

void writeProduct(const Product *product)
{
	FILE *file=openFile(PRODUCTS_FILE,"r+");
	int cursor;
	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,product->id))!=-1)
	{
		rewind(file);
		writeCpy(file,"A.product.tpm",cursor);
		nextLine(file,ENDLINE);
		writeCpy(file,"B.product.tpm",-1);

		fclose(file);
		file=openFile(PRODUCTS_FILE,"w");
		loadCpy(file,"A.product.tpm");
	}
	fprintf(file, "%d%c%d%c",product->id,SEPARATOR,product->isDelete,SEPARATOR );
	fprintf(file, "%d%c%.2f%c%s%c",product->category,SEPARATOR,product->price,SEPARATOR,product->name,SEPARATOR );
	fprintf(file, "%c",ENDLINE );
	if(cursor!=-1)
		loadCpy(file,"B.product.tpm");
	fclose(file);
}

void printProduct(const Product *product)
{
	if(!product->isDelete)
	{
		printf("* -Nom: %s \n",product->name);
		printf("* -Categorie: ");
		switch(product->category)
		{
			case electro:
				printf("Electro");
				break;
			case cuisine:
				printf("Cuisine");
				break;
			case service:
				printf("Service");
				break;
			default:
				printf("%d",product->category );
				break;
		}
		printf("\n* -Prix: %.2f$\n",product->price);
	}
}

void productMenu(ArrayProduct *array)
{
    int run=1;
    Product *selected=NULL;
	while(run)
	{
		printProductTitle();
		printf("		1) Ajouter un produit\n");
		printf("		2) Modifier un produits\n");
		printf("		3) Tout afficher\n");
		printf(" 		9) Retour\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				printProductTitle();
				selected=new_product(array->size);
				printProductTitle();
				printProduct(selected);
				if(isValid("Valider le produit ?"))
				{
					addProductToArray(array,selected);
					writeProduct(selected);
					printf("**Donnees persistes**\n");
				}
				else
				{
					free(selected);
					printf("**Donnees non persistes**\n");
				}
				getchar();
				break;
			case 2:
			    if((selected=browseProducts(array))!=NULL)
                    editProduct(selected);
				break;
			case 3:
				printProducts(array);
				break;
			case 9:
				run=0;
				break;
			default:
				printProductTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
}

void addProductToArray(ArrayProduct *array,Product *product)
{
	array->size++;
	arrayArrangement(array,product);
}

void removeProductToArray(ArrayProduct *array,Product *product)
{
	if(array->head==array->tail)
	{
		array->head=NULL;
		array->tail=NULL;
	}
	else if(product==array->head)
	{
		array->head=product->next;
		array->head->previous=NULL;
	}
	else if(product==array->tail)
	{
		array->tail=product->previous;
		array->tail->next=NULL;
	}
	else
	{
		product->previous->next=product->next;
		product->next->previous=product->previous;
	}
	array->size--;
}

void destructArrayProduct(ArrayProduct *array)
{
	Product *product=array->tail;
	while(product!=array->head)
	{
		product=product->previous;
		free(product->next);
	}
	free(product);
	free(array);
}

void loadProducts(ArrayProduct *array)
{
	int i;
	Product *product=NULL;
	FILE *file=openFile(PRODUCTS_FILE,"r");
	array->size=howManySeparatorContainFile(file,ENDLINE);
	fclose(file);

	for(i=0;i<array->size;++i)
	{
		product=(Product *)alloc(sizeof(Product));
		initProduct(product);
		loadProduct(product,i);
		arrayArrangement(array,product);
	}
}

void printProducts(const ArrayProduct *array)
{
	Product *product=NULL;
	for(product=array->head; product!=NULL ;product=product->next)
		if(!product->isDelete)
		{
			printProductTitle();
			printProduct(product);
			printf("> ");
			getchar();
		}
}


void printProductTitle()
{
    CLEAR()
	visualHSeparator('#',67);
	printf("#                                                                 #\n");
	printf("#  __  __                  _____               _       _ _        #\n");
	printf("# |  \\/  |                |  __ \\             | |     (_) |       #\n");
	printf("# | \\  / | ___ _ __  _   _| |__) | __ ___   __| |_   _ _| |_ ___  #\n");
	printf("# | |\\/| |/ _ \\ '_ \\| | | |  ___/ '__/ _ \\ / _` | | | | | __/ __| #\n");
	printf("# | |  | |  __/ | | | |_| | |   | | | (_) | (_| | |_| | | |_\\__ \\ #\n");
	printf("# |_|  |_|\\___|_| |_|\\__,_|_|   |_|  \\___/ \\__,_|\\__,_|_|\\__|___/ #\n");
	printf("#                                                                 #\n");
	visualHSeparator('#',67);
}
