#include "customer.h"


  /*******************************************************************************************\
<| ////////////////////////////////////////--STATICS--//////////////////////////////////////// |>
  \*******************************************************************************************/

// Permet de savoir si au moin un Customer n'est pas supprimer (use to browseCustomers)
static char atleastOne(const ArrayCustomer *array)
{
	Customer *c=array->head;
	for(c=array->head;c!=NULL;c=c->next)
		if(!c->isDelete)
			return 1;
	return 0;
}

static void arrayArrangement(ArrayCustomer *array,Customer *customer)
{
	if(array->head==NULL)
	{
		array->head=customer;
		array->middle=customer;
	}
	else
	{
		array->tail->next=customer;
		customer->previous=array->tail;
		if(customer->id%2!=0)
			array->middle=array->middle->next;
	}
	array->tail=customer;
}

//Permet l'échange de 2 pointeurs , attention c'est chevelu !
static void swap(ArrayCustomer *array,Customer *a,Customer *b)
{
	Customer *p=a->previous;
	Customer *n=a->next;
	if(p==NULL)
		array->head=b;
	if(b->next==NULL)
		array->tail=a;
	a->next=b->next;
	if(b->previous->id==a->id)//sont-ils cote à cote ?
	{
		a->next=b->next;
		if(b->next!=NULL)
			b->next->previous=a;
		if(a->previous!=NULL)
			a->previous->next=b;
		a->previous=b;
		b->previous=p;
		b->next=a;
		a->previous=b;
	}
	else
	{
		a->previous=b->previous;
		if(b->next!=NULL)
			b->next->previous=a;
		b->previous->next=a;
		b->previous=p;
		b->next=n;
		if(p!=NULL)
			p->next=b;
		n->previous=b;
	}
}

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

Customer *new_customer(const int id)
{
	Customer *customer=(Customer *)alloc(sizeof(Customer));
	initCustomer(customer);
	customer->id=id;
	do
	{
		printCustomerTitle();
		makeEntity(&customer->entity);
		printCustomerTitle();
		printEntity(&customer->entity);
	}while(!isValid("Valider l'identite ?"));

	do
	{
		printCustomerTitle();
		makeAddress(&customer->address);
		printCustomerTitle();
		printAddress(&customer->address);
	}while(!isValid("Valider l'adresse ?"));
	return customer;
}

Customer *getNextCustomer(const Customer *customer)
{
	if(customer->next==NULL)
		if(customer->isDelete==0)
			return (Customer *)customer;
		else
			return getPreviousCustomer(customer);

	if(customer->next->isDelete==1)
		return getNextCustomer(customer->next);
	else
		return (Customer *)customer->next;
}

Customer *getPreviousCustomer(const Customer *customer)
{
	if(customer->previous==NULL)
		if(customer->isDelete==0)
			return (Customer *)customer;
		else
			return getNextCustomer(customer);
	if(customer->previous->isDelete==1)
		return getPreviousCustomer(customer->previous);
	else
		return (Customer *)customer->previous;
}

Customer *getFirstCustomer(const Customer *head)
{
	if(head!=NULL)
		if(head->isDelete==1)
			return getNextCustomer(head);
		else
			return (Customer *)head;
	return NULL;
}

Customer *getLastCustomer(const Customer *tail)
{
	if(tail!=NULL)
		if(tail->isDelete==1)
			return getPreviousCustomer(tail);
		else
			return (Customer *)tail;
	return NULL;
}

Customer *getCustomerById(const ArrayCustomer *array,const int id)
{
	Customer *customer=array->head;
	for(;customer!=NULL;customer=customer->next)
		if(customer->id==id)
			return customer;
	return NULL;
}

Customer *browseCustomers(ArrayCustomer *array)
{
	Customer *selected=NULL;
	if(atleastOne(array))
		selected=getFirstCustomer(array->head);

	while(selected!=NULL)
	{
		printCustomerTitle();
		printEntity(&selected->entity);
		printAddress(&selected->address);

		visualHSeparator('-',57);
		printf("	1)Precedent 2)Selectionner 3)Suivant 9)Retour\n");
		printf("                4)Debut        6)Fin\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				selected=getPreviousCustomer(selected);
				break;
			case 2:
				return selected;
			case 3:
				selected=getNextCustomer(selected);
				break;
			case 4:
                selected=getFirstCustomer(array->head);
                break;
            case 6:
                selected=getLastCustomer(array->tail);
                break;
            case 9:
				selected=NULL;
				break;
			default:
				printCustomerTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
	return NULL;
}

Customer *getACustomerByAlphaSort(ArrayCustomer *array)
{
	const unsigned int size=8;
	unsigned int i=0;
	unsigned int choice=0;
	Customer *customer=NULL;
	Customer *tab[size];

	initVoidTab((void **)tab,size);
	sortArrayCustomerByName(array);
	customer=array->head;

	for(i=0;i<size && customer!=NULL;++i)
	{
		if(!customer->isDelete)
			tab[i]=customer;
		else
			i--;
		customer=customer->next;
	}
	customer=NULL;

	while(tab[0]!=NULL && customer==NULL)
	{
		printCustomerTitle();
		for(i=0;i<size;++i)
			if(tab[i]!=NULL)
				printf("		%d) %s %s\n",i+1,tab[i]->entity.name,tab[i]->entity.forename );
		printf("		9) Retour\n");
		printf("		0) Suivant\n");
		printf("> ");
		switch(choice=readInt())
		{
			case 0:
				for(i=0;i<size && tab[i]!=NULL;i++)
					customer=tab[i];
				initVoidTab((void **)tab,size);
				customer=customer->next;
				for(i=0;i<size && customer!=NULL;++i)
				{
					if(!customer->isDelete)
						tab[i]=customer;
					else
						i--;
					customer=customer->next;
				}
				customer=NULL;
				break;
			case 9:
			 	return NULL;
			 	break;
			default:
			 	if(choice<=size && tab[choice-1]!=NULL)
			 		customer=tab[choice-1];
		}
	}
	sortArrayCustomerById(array);
	return customer;
}

Customer *getCustomerByNameAndForename(const ArrayCustomer *array)
{
	char name[BUFFER_SIZE];
	char forename[BUFFER_SIZE];
	Customer *customer=array->head;

	printCustomerTitle();
	printf("*		--Recherche Client--\n");
	setStringParam(name, "Nom",BUFFER_SIZE,3);
	setStringParam(forename,"Prenom",BUFFER_SIZE,3);

	while(customer!=NULL)
		if(!customer->isDelete && !strcmp(customer->entity.name,name) && !strcmp(customer->entity.forename,forename))
			return customer;
		else
			customer=customer->next;
	return NULL;
}

Customer *selectCustomerForOrder(ArrayCustomer *array)
{
	unsigned char run=1;
	Customer *selected=NULL;

	while(run && selected==NULL)
	{
		printCustomerTitle();
		printf("		1) Deja client\n");
		printf("		2) Ajouter un client\n");
		printf("		9) Retour\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				printCustomerTitle();
				printf("		1) Recherche par Nom & Prenom\n");
				printf("		2) Tout afficher par ordre alphabetique\n");
				printf("		9) Retour\n");
				printf("> ");
				switch(readInt())
				{
					case 1:
						selected=getCustomerByNameAndForename(array);
						printCustomerTitle();
						if(selected==NULL)
							printf("		**Client non trouve**\n");
						else
							printCustomer(selected);
						getchar();
						break;
					case 2:
						selected=getACustomerByAlphaSort(array);
						break;
					default:
						printf("**Pas de client selectionne**\n");
						getchar();
						break;
				}
				break;
			case 2:
				selected=new_customer(array->size);
				printCustomerTitle();
				printCustomer(selected);
				if(isValid("Confirmer l'ajout du client ?"))
				{
					addCustomerToArray(array,selected);
					writeCustomer(selected);
				}
				else
				{
					free(selected);
					selected=NULL;
				}
				
				break;
			case 9:
				run=0;
				break;
			default:
				printCustomerTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
	return selected;
}

ArrayCustomer *new_array_customer()
{
	ArrayCustomer *array=(ArrayCustomer *)alloc(sizeof(ArrayCustomer));
	array->size=0;
	array->head=NULL;
	array->tail=NULL;
	array->middle=NULL;
	return array;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

void initCustomer(Customer *customer)
{
	customer->isDelete=0;
	initEntity(&customer->entity);
	initAddress(&customer->address);
	customer->next=NULL;
	customer->previous=NULL;
}

void editCustomer(Customer *customer)
{
	unsigned char run=1;
	Entity cpyEntity=customer->entity;
	Address cpyAddress=customer->address;

	while(run)
	{
		printCustomerTitle();
		printCustomer(customer);
		visualHSeparator('-',57);
		printf("		1) Modifier l'identite\n");
		printf("		2) Modifier l'adresse\n");
		printf("		3) Supprimer\n");
		printf("		9) Retour\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				printCustomerTitle();
				editEntity(&customer->entity);
				break;
			case 2:
				printCustomerTitle();
				editAddress(&customer->address);
				break;
			case 3:
				if(!isValid("Etes-vous sur de vouloir supprimer le client ?"))
					break;
				customer->isDelete=1;
			case 9:
				run=0;
				break;
			default:
				printCustomerTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}

	printCustomerTitle();
	printEntity(&customer->entity);
	printAddress(&customer->address);
	visualHSeparator('-',57);

	if(customer->isDelete ||!isEntityEgal(&customer->entity,&cpyEntity) || !isAddressEgal(&customer->address,&cpyAddress))
	{
		if(isValid("Confirmer les changements ?"))
		{
			writeCustomer(customer);
			printf("**Donnees persistees**\n> ");
		}
		else
		{
			loadCustomer(customer,customer->id);
			printf("**Donnees non persistees**\n> ");
		}
	}
	else
		printf("**Aucune modification n'a eu lieu**\n> ");
	getchar();
}

void loadCustomer(Customer *customer,const int  id)
{
	int cursor;
	FILE *file=openFile(CUSTOMERS_FILE,"r");

	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,id))!=-1)
	{
		fseek(file,cursor,SEEK_SET);
		readNextIntValue(file,SEPARATOR,&customer->id);
	 	readNextIntValue(file,SEPARATOR,(int *)&customer->isDelete);

		loadEntity(file,&customer->entity,SEPARATOR);
		loadAddress(file,&customer->address,SEPARATOR);
	}
	else
	{
		free(customer);
		customer=NULL;
	}
	fclose(file);
}

void writeCustomer(const Customer *customer)
{
	int cursor;
	FILE *file=openFile(CUSTOMERS_FILE,"r+");

	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,customer->id))!=-1)
	{
		rewind(file);
		writeCpy(file,"A.customers.tpm",cursor);
		nextLine(file,ENDLINE);
		writeCpy(file,"B.customers.tpm",-1);

		fclose(file);
		file=openFile(CUSTOMERS_FILE,"w+");
		loadCpy(file,"A.customers.tpm");
	}
	fprintf(file, "%d%c%d%c",customer->id,SEPARATOR,customer->isDelete,SEPARATOR );
	writeEntity(file,&customer->entity,SEPARATOR);
	writeAddress(file,&customer->address,SEPARATOR);
	fprintf(file, "%c",ENDLINE );
	if(cursor!=-1)
		loadCpy(file,"B.customers.tpm");
	fclose(file);
}

void cpyCustomer(Customer *customer,const Customer *src)
{
	cpyEntity(&customer->entity,&src->entity);
	cpyAddress(&customer->address,&src->address);
}


void printCustomer(const Customer *customer)
{
	if(!customer->isDelete)
	{
		printEntity(&customer->entity);
		printAddress(&customer->address);
	}
}

void customerMenu(ArrayCustomer *array)
{
	char run=1;
	Customer *selected=NULL;

	while(run)
	{
		printCustomerTitle();
		printf("		1) Ajouter un client\n");
		printf("		2) Modifier un client\n");
		printf("		3) Afficher les clients\n");
		printf("		9) Retour\n");
		printf("> ");
		switch(readInt())
		{
			case 1:
				selected=new_customer(array->size);
				printCustomerTitle();
				printCustomer(selected);

				if(isValid("Confirmer l'ajout du client ?"))
				{
				    writeCustomer(selected);
				    addCustomerToArray(array,selected);
					printf("**Informations persistees**\n");
				}
				else
				{
					printf("**Informations non persistees**\n");
					free(selected);
				}
				printf("> ");
				getchar();
				selected=NULL;
				break;
			case 2:
				selected=browseCustomers(array);
				if(selected!=NULL)
					editCustomer(selected);
				selected=NULL;
				break;
			case 3:
				printCustomers(array);
				break;
			case 9:
				run=0;
				break;
			default:
				printCustomerTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
}

void sortArrayCustomerByName(ArrayCustomer *array)
{
	int i,j;
	Customer *a=array->head;
	Customer *b=NULL;
	Customer *tpm=NULL;

	for(i=0;i<array->size-1 && a!=NULL;++i)
	{
		b=a->next;
		for(j=i;j<array->size && b!=NULL;++j)
		{
			if(isBiggerThan(a->entity.name,b->entity.name))
			{
				swap(array,a,b);
				tpm=a;
				a=b;
				b=tpm;
			}
			b=b->next;
		}
		a=a->next;
	}
}

void sortArrayCustomerById(ArrayCustomer *array)
{
	int i,j;
	Customer *a=array->head;
	Customer *b=NULL;
	Customer *tpm=NULL;
	for(i=0;i<array->size-1 && a!=NULL;++i)
	{
		b=a->next;
		for(j=i;j<array->size && b!=NULL;++j)
		{
			if(a->id>b->id)
			{
				swap(array,a,b);
				tpm=a;
				a=b;
				b=tpm;
			}
			b=b->next;
		}
		a=a->next;
	}
}

void addCustomerToArray(ArrayCustomer *array,Customer *customer)
{
	array->size++;
	arrayArrangement(array,customer);
}

void removeCustomerToArray(ArrayCustomer *array,Customer *customer)
{
	if(array->head==array->tail)
	{
		array->head=NULL;
		array->tail=NULL;
	}
	else if(customer==array->head)
	{
		array->head=customer->next;
		array->head->previous=NULL;
	}
	else if(customer==array->tail)
	{
		array->tail=customer->previous;
		array->tail->next=NULL;
	}
	else
	{
		customer->previous->next=customer->next;
		customer->next->previous=customer->previous;
	}
	array->size--;
}

void destructArrayCustomer(ArrayCustomer *array)
{
	Customer *customer=array->tail;
	while(customer!=array->head)
	{
		customer=customer->previous;
		free(customer->next);
	}
	free(customer);
	free(array);
}

void loadCustomers(ArrayCustomer *array)
{
	int i;
	Customer *c=NULL;
	FILE *file=openFile(CUSTOMERS_FILE,"r");
	array->size=howManySeparatorContainFile(file,ENDLINE);
	fclose(file);
	for(i=0;i<array->size;++i)
	{
		c=(Customer *)alloc(sizeof(Customer));
		initCustomer(c);
		loadCustomer(c,i);

		if(c!=NULL)
			arrayArrangement(array,c);
	}
}

void printCustomers(const ArrayCustomer *array)
{
	Customer *customer=array->head;
	for(customer=array->head;customer!=NULL;customer=customer->next)
		if(!customer->isDelete)
		{
			printCustomerTitle();
			printCustomer(customer);
			printf("> ");
			getchar();
		}
}

void printCustomerTitle()
{
	CLEAR()
	visualHSeparator('#',57);
	printf("#  __  __                     _____ _ _            _    #\n");
	printf("# |  \\/  |                   / ____| (_)          | |   #\n");
	printf("# | \\  / | ___ _ __  _   _  | |    | |_  ___ _ __ | |_  #\n");
	printf("# | |\\/| |/ _ \\ '_ \\| | | | | |    | | |/ _ \\ '_ \\| __| #\n");
	printf("# | |  | |  __/ | | | |_| | | |____| | |  __/ | | | |_  #\n");
	printf("# |_|  |_|\\___|_| |_|\\__,_|  \\_____|_|_|\\___|_| |_|\\__| #\n");
	printf("#                                                       #\n");
	visualHSeparator('#',57);
}
