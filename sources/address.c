#include "address.h"

  /*******************************************************************************************\
<| ////////////////////////////////////////--STATIC--//////////////////////////////////////// |>
  \*******************************************************************************************/

/* Selection automatique de la ville*/
static void setCity(Address *address)
{
	char run=1;
	char city[BUFFER_SIZE]={0};
	FILE *file=openFile("cities.data","r");

	setIntegerParam(&address->postalCode,"Code postal",CP_MIN,CP_MAX);
	while(run==1)
	{
	    printf("%d",address->postalCode);
		if(isFileContainInt(file,0,'&',';',address->postalCode)!=-1)
		{
			readNextCharValue(file,'&',city,BUFFER_SIZE);
			printf("* Ville : %s\n",city );
			if(isValid("* Valider la ville ?"))
				run=0;
			else
				initString(city,BUFFER_SIZE);
		}
		else
		{
			do{
				setStringParam(city,"Ville",BUFFER_SIZE,3);
			}while(!isAlphaRegex(city,BUFFER_SIZE));
			run=0;
		}
	}
	strcpy(address->city,city);
	fclose(file);
}

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

char isAddressEgal(const Address *address,const Address *other)
{
	if(address->number==other->number)
		if(address->bte==other->bte)
			if(address->postalCode==other->postalCode)
				if(!strcmp(address->street,other->street))
					if(!strcmp(address->city,other->city))
						if(!strcmp(address->country,other->country))
							return 1;
	return 0;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

void initAddress(Address *this)
{
	this->number=0;
	this->postalCode=0;
	this->bte=0;

	initString(this->street,BUFFER_SIZE);
	initString(this->city,BUFFER_SIZE);
	initString(this->country,BUFFER_SIZE);
}

void makeAddress(Address *this)
{
	setStringParam(this->street,"Rue",BUFFER_SIZE,3);
	setIntegerParam(&this->number,"Numero",NUM_MIN,NUM_MAX);
	if(isValid("* Appartement ?"))
		setIntegerParam(&this->bte,"Boite",BTE_MIN,BTE_MAX);
	setCity(this);
	do
	{
		setStringParam(this->country,"Pays (belgique)",BUFFER_SIZE,0);
		if(this->country[0]==0)
			strcpy(this->country,"belgique");
	}while(strlen(this->country)<3);
	if(this->country[0]==0)
		strcpy(this->country,"belgique");
}

void cpyAddress(Address *this,const Address *src)
{
	this->number=src->number;
	this->bte=src->bte;
	this->postalCode=src->postalCode;

	strcpy(this->street,src->street);
	strcpy(this->city,src->city);
	strcpy(this->country,src->country);
}

void editAddress(Address *this)
{
	printf("		1) Modifier le Numero| Boite \n");
	printf("		2) Modifier la Rue \n");
	printf("		3) Modifier la Code postal| Ville \n");
	printf("		4) Modifier le Pays \n");
	printf("		5) Tout modifier \n");
	printf("		9) Retour\n");
	printf("> ");
	switch(readInt())
	{
		case 1:
			setIntegerParam(&this->number,"Numero",NUM_MIN,NUM_MAX);
			if(isValid("* Appartement ?"))
				setIntegerParam(&this->bte,"Boite",BTE_MIN,BTE_MAX);
			else
				this->bte=0;
			break;
		case 2:
			setStringParam(this->street,"Rue",BUFFER_SIZE,3);
			break;
		case 3:
			setCity(this);
			break;
		case 4:
			do
			{
				setStringParam(this->country,"Pays (belgique)",BUFFER_SIZE,0);
				if(this->country[0]==0)
					strcpy(this->country,"belgique");
			}while(strlen(this->country)<3);
			break;
		case 5:
			makeAddress(this);
			break;
		case 9:
			break;
		default:
			break;
	}
}

void printAddress(const Address *this)
{
	printf("* -Rue : %s N %d \n",this->street,this->number);
	if(this->bte>0)
		printf("* -Bte : %d\n",this->bte );
	else
		printf("* -Bte : /\n");
	printf("* -Ville : %d %s \n",this->postalCode,this->city );
	printf("* -Pays : %s\n",this->country );
}

void writeAddress(FILE *file,const Address *this,const char separator )
{
	fprintf(file, "%d%c%d%c%d%c",this->number,separator,this->bte,separator,this->postalCode,separator );
	fprintf(file, "%s%c%s%c%s%c",this->street,separator,this->city,separator,this->country,separator );
}

void loadAddress(FILE *file,Address *this,const char separator )
{
	readNextIntValue(file,separator,&this->number);
	readNextIntValue(file,separator,&this->bte);
	readNextIntValue(file,separator,&this->postalCode);

	readNextCharValue(file,separator,this->street,BUFFER_SIZE);
	readNextCharValue(file,separator,this->city,BUFFER_SIZE);
	readNextCharValue(file,separator,this->country,BUFFER_SIZE);
}
