#include "menu.h"

//////////////////////////////--STATICS--/////////////////////////////////////////////

static void printMainTitle()
{
	CLEAR()
	visualHSeparator('#',63);
	printf("#   _____      _     _            _____          _            #\n");
	printf("#  / ____|    (_)   (_)          |  __ \\        | |           #\n");
	printf("# | |    _   _ _ ___ _ _ __   ___| |__) |_ _ ___| |     __ _  #\n");
	printf("# | |   | | | | / __| | '_ \\ / _ \\  ___/ _` / __| |    / _` | #\n");
	printf("# | |___| |_| | \\__ \\ | | | |  __/ |  | (_| \\__ \\ |___| (_| | #\n");
	printf("#  \\_____\\__,_|_|___/_|_| |_|\\___|_|   \\__,_|___/______\\__,_| #\n");
	printf("#                                                             #\n");
	visualHSeparator('#',63);
}

static void printOrderTitle()
{
	CLEAR()
	visualHSeparator('#',60);
	printf("#   _____                                          _       #\n");
	printf("#  / ____|                                        | |      #\n");
	printf("# | |     ___  _ __ ___  _ __ ___   __ _ _ __   __| | ___  #\n");
	printf("# | |    / _ \\| '_ ` _ \\| '_ ` _ \\ / _` | '_ \\ / _` |/ _ \\ #\n");
	printf("# | |___| (_) | | | | | | | | | | | (_| | | | | (_| |  __/ #\n");
	printf("#  \\_____\\___/|_| |_| |_|_| |_| |_|\\__,_|_| |_|\\__,_|\\___| #\n");
	printf("#                                                          #\n");
	visualHSeparator('#',60);
}

static void makeSpace(int n)
{
	int i;
	for(i=0;i<n;++i)
		printf(" ");
}

static void printBillHead()
{
	printf("  ");
	visualHSeparator('-',54);
	printf(" | QTY");
	printf(" |");
	makeSpace(5);
	printf("Produit");
	makeSpace(5);
	printf("|");
	makeSpace(5);
	printf("Prix");
	makeSpace(5);
	printf("|");
	makeSpace(5);
	printf("Total");
	makeSpace(5);
	printf("|\n  ");
	visualHSeparator('-',54);
}

//////////////////////////////--PROCEDURES--/////////////////////////////////////////////

void mainMenu()
{
	unsigned char run=1;

	/*********Dedié aux clients*************/
	ArrayCustomer *customers=new_array_customer();
	Customer *customer=NULL;
	loadCustomers(customers);

	/*********Dediéaux produits*************/
	ArrayProduct *products=new_array_product();
	loadProducts(products);

	/*********Dedié aux commandes*************/
	ArrayOrder *orders=new_array_order();
	Order *order=NULL;
	loadOrders(orders);

	ArrayLine *lines=new_array_line();
	loadLines(lines);

	while(run)
	{
		printMainTitle();
		printf("		1) Creer une commande\n");
		printf("		2) Afficher l'historique des commandes\n");
		printf("		3) Menu produits\n");
		printf("		4) Menu clients\n");
		printf("		9) Quitter\n");
		printf("> ");

		switch(readInt())
		{
			case 1:
				printOrderTitle();
				if((customer=selectCustomerForOrder(customers))!=NULL)
				{
					order=new_order(orders->size,customer->id);
					cartMenu(order,lines,products);
					if(order->lines->size>0)
						addOrderToArray(orders,order);
					else
						destructOrder(order);
				}
				customer=NULL;
				order=NULL;
				break;
			case 2:
				printAllOrder(orders,lines,products,customers);
				break;
			case 3:
				productMenu(products);
				break;
			case 4:
				customerMenu(customers);
				break;
			case 9:
				run=0;
				break;
			default:
				printMainTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
	destructArrayProduct(products);
	destructArrayOrder(orders);
	destructArrayLine(lines);
	destructArrayCustomer(customers);
}

void cartMenu(Order *order,ArrayLine *lines,const ArrayProduct *products)
{
	unsigned char run=1;
	Line *line=NULL;
	Product *product=NULL;

	while(run)
	{
		printOrderTitle();
		printBill(order,lines,products);
		visualHSeparator('-',60);
		printf("		1) Ajouter un produit\n");
		printf("		2) Modifier la commande\n");
		printf("		3) Valider la commande\n");
		printf("		9) Retour\n");
		printf("> ");

		switch(readInt())
		{
			case 1:
				product=browseProducts(products);
				if(product!=NULL)
				{
					line=new_line(lines->size,product->id);
					printOrderTitle();
					printBillHead();
					printOrderLine(line,product);
					if(isValid("Ajouter au panier ?"))
						addToCart(order,line,lines);
					else
						free(line);
				}
				product=NULL;
				line=NULL;
				break;
			case 2:
				if(isOrderHasLines(order))
					editCart(order,lines,products);
				break;
			case 3:
				if(isOrderHasLines(order))
				{
					if(isValid("Valider la commande ?"))
					{
						ValidCart(order,lines);
						printf("**Donnees persistes**\n");
						run=0;
					}
					else
						printf("**Donnees non persistes**\n");
				}
				else
					printf("**Aucun article dans votre panier**\n");
				printf(">");
				getchar();
				break;
			case 9:
				if(order->lines->size>0)
					removeCart(order,lines);
				run=0;
				break;
			default:
				printMainTitle();
				printf("		!----BAD REQUEST----!\n");
				getchar();
				break;
		}
	}
}

void removeCart(Order *order,ArrayLine *lines)
{
	Line *toRemove=NULL;
	Line *detached=getLineById(lines,order->lines->tail->value);

	while(detached!=NULL && detached->id>=order->lines->head->value)
	{
		removeLineToArray(lines,detached);
		toRemove=detached;
		detached=toRemove->previous;
		free(toRemove);
		order->lines->size--;
	}
}

void addToCart(Order *order,Line *line,ArrayLine *lines)
{
	Line *lineTpm=lines->head;
	Line *match=NULL;
	Integer *orderLine=order->lines->head;
	while(orderLine!=NULL && match==NULL)//Le produit est déja présent ?
	{
		lineTpm=getLineById(lines,orderLine->value);
		if(lineTpm!=NULL && lineTpm->product==line->product)
			match=lineTpm;
		orderLine=orderLine->next;
	}
	if(match!=NULL)//alors modifie la quantité
	{
		if(match->isDelete==1)
		{
			match->isDelete=0;
			match->quantity=0;
		}

		if(match->quantity+line->quantity<=10)
			match->quantity+=line->quantity;
		else
		{
			printOrderTitle();
			printf("	Pas assez de stock ! %d articles ajoutes !\n",10-match->quantity );
			getchar();
			match->quantity=10;
		}
		free(line);
	}
	else//sinon ajouter une nouvelle ligne
	{
		addIntegerToArray(order->lines,line->id);
		addLineToArray(lines,line);
	}
}

void editCart(Order *order,ArrayLine *lines,const ArrayProduct *products)
{
	int j=0;
	Line *lineTpm=getLineById(lines,order->lines->head->value);
	Integer *integer=order->lines->head;
	printOrderTitle();
	printf("		--Selectionner l'article--\n");
	while(lineTpm!=NULL)
	{
		printf("		%d) ",++j);
		printf("%d x %s = ",lineTpm->quantity,getProductById(products,lineTpm->product)->name);
		printf("%.2f$\n",getProductById(products,lineTpm->product)->price*lineTpm->quantity);
		lineTpm=lineTpm->next;
	}
	printf("		0) Retour \n");
	setIntegerParam(&j,"Article",0,j);
	printOrderTitle();
	lineTpm=getLineById(lines,order->lines->head->value);
	if(j!=0)
	{
		while(--j>0 && lineTpm!=NULL)
		{
			lineTpm=lineTpm->next;
			integer=integer->next;
		}
		editLine(lineTpm);
	}
}

void ValidCart(const Order *order,const ArrayLine *lines)
{
	Line *line=getLineById(lines,order->lines->head->value);
	for(;line!=NULL;line=line->next)
		writeLine(line);
	writeOrder(order);
}






/*******************************************************************************
									Méthodes affichage
                                           ,-.
                      ___,---.__          /'|`\          __,---,___
                   ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
                 ,'        |           ~'\     /`~           |        `.
                /      ___//              `. ,'          ,  , \___      \
               |    ,-'   `-.__   _         |        ,    __,-'   `-.    |
               |   /          /\_  `   .    |    ,      _/\          \   |
               \  |           \ \`-.___ \   |   / ___,-'/ /           |  /
                \  \           | `._   `\\  |  //'   _,' |           /  /
                 `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
                    ``       /     \    ,='/ \`=.    /     \       ''
                            |__   /|\_,--.,-.--,--._/|\   __|
                            /  `./  \\`\ |  |  | /,//' \,'  \
Zone dangereuse            /   /     ||--+--|--+-/-|     \   \
                          |   |     /'\_\_\ | /_/_/`\     |   |
                           \   \__, \_     `~'     _/ .__/   /
                            `-._,-'   `-._______,-'   `-._,-'
********************************************************************************/
void printAllOrder(ArrayOrder *orders,ArrayLine *lines,ArrayProduct *products,ArrayCustomer *customers)
{
	int i=0;
	Order *order=orders->head;
	Customer *customer=NULL;

	printOrderTitle();
	printf("		--Selectionner la commande--\n");
	while(order!=NULL)
	{
		if(!order->isDelete)
		{
			customer=getCustomerById(customers,order->customer);
			printf("		%d) ",++i );
			printDateTimeShort(&order->date);
			if(customer!=NULL)
				printf("%s %s\n",customer->entity.name,customer->entity.forename );
		}
		order=order->next;
	}
	printf("		0) Retour \n" );
	setIntegerParam(&i,"Commande",0,i);
	order=orders->head;
	if(i>0)
	{
		while(--i>0 && order!=NULL)
		{
			order=order->next;
			if(order->isDelete)
				i++;
		}

		printOrderTitle();
		customer=getCustomerById(customers,order->customer);
		if(customer->entity.sexe)
			printf("Mme");
		else
			printf("Mr");
		printf(" %s %s 				",customer->entity.name,customer->entity.forename);
		printDateTimeToString(&order->date);
		printf("\n");
		printBill(order,lines,products);
		printf("> ");
		getchar();
	}
}

void printOrderLine(const Line *line,const Product *product)
{
	if(!line->isDelete)
	{
		if(line->quantity>99)
			makeSpace(4);
		else if(line->quantity>9)
			makeSpace(5);
		else
			makeSpace(6);
		printf("%d|",line->quantity );
        if((int)(13-strlen(product->name)) > 0)
            makeSpace((13-strlen(product->name))/2);

		printf("  %s  ", product->name);
        if((int)(14-strlen(product->name)) > 0)
            makeSpace((14-strlen(product->name))/2);
		printf("|");
		if(product->price>9999)
			makeSpace(2);
		else if(product->price>999)
			makeSpace(2);
		else if(product->price>99)
			makeSpace(4);
		else if(product->price>9)
			makeSpace(4);
		else if(product->price<-9)
			makeSpace(2);
		else if(product->price<-99)
			makeSpace(1);
		else if(product->price<-999)
			makeSpace(0);
		else
			makeSpace(4);

		printf("%.2f$",product->price);

		if(product->price>9999)
			makeSpace(1);
		else if(product->price>999)
			makeSpace(2);
		else if(product->price>99)
			makeSpace(3);
		else if(product->price>9)
			makeSpace(4);
		else if(product->price>-9)
			makeSpace(4);
		else if(product->price>-99)
			makeSpace(2);
		else if(product->price>-999)
			makeSpace(1);
		else
			makeSpace(3);
		printf("|");

		printf("  %.2f$",line->quantity*product->price);
		printf("\n");
	}
}

void printBill(Order *order,ArrayLine *lines,const ArrayProduct *products)
{
	Line *line=NULL;
	Product *product=NULL;
	Integer *orderLine=order->lines->head;
	float total=0;
	printBillHead();
	while(orderLine!=NULL)
	{
		line=getLineById(lines,orderLine->value);
		product=getProductById(products,line->product);
		printOrderLine(line,product);
		total+=line->quantity*product->price;
		orderLine=orderLine->next;
	}
	printf("     ");
	visualHSeparator('-',48);
	printf("		   Total :  %.2f$\n  ",total);
	visualHSeparator('-',54);
}


