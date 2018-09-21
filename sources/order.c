#include "order.h"

  /*******************************************************************************************\
<| ////////////////////////////////////////--STATICS--//////////////////////////////////////// |>
  \*******************************************************************************************/

static void arrayArrangement(ArrayOrder *array,Order *order)
{
	if(array->head==NULL)
	{
		array->head=order;
		array->middle=order;
	}
	else
	{
		array->tail->next=order;
		order->previous=array->tail;
		if(order->id%2!=0)
			array->middle=array->middle->next;
	}
	array->tail=order;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

Order *new_order(const int id,const int customer)
{
	Order *order=(Order *)alloc(sizeof(Order));
	order->lines=new_array_integer();
	initOrder(order);
	order->id=id;
	order->customer=customer;
	setDateTimeToToday(&order->date);
	return order;
}

Order *getOrderById(const ArrayOrder *array,const int id)
{
	Order *order=array->head;
	for(;order!=NULL;order=order->next)
		if(order->id==id)
			return (Order *) order;
	return NULL;
}

ArrayOrder *new_array_order()
{
	ArrayOrder *array=(ArrayOrder *)alloc(sizeof(ArrayOrder));
	array->size=0;
	array->head=NULL;
	array->middle=NULL;
	array->tail=NULL;
	return array;
}

int isOrderHasLines(const Order *order)
{
	if(order->lines->size>0)
		return 1;
	return 0;
}
  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

void initOrder(Order *order)
{
	order->id=-1;
	order->isDelete=0;
	order->customer=-1;
	initDateTime(&order->date);
	order->next=NULL;
	order->previous=NULL;
}

void addLineToOrder(Order *order,const int line)
{
	addIntegerToArray(order->lines,line);
}

void destructOrder(Order *order)
{
	destructArrayInteger(order->lines);
	free(order);
	order=NULL;
}

void loadOrder(Order *order,const int id)
{
	int cursor;
	FILE *file=openFile(ORDERS_FILE,"r");
	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,id))!=-1)
	{
		fseek(file,cursor,SEEK_SET);
		readNextIntValue(file,SEPARATOR,&order->id);
		readNextIntValue(file,SEPARATOR,&order->isDelete);
		readNextIntValue(file,SEPARATOR,&order->customer);
		loadArrayInteger(file,order->lines,SEPARATOR);
		loadDateTime(file,&order->date,SEPARATOR);
	}
	fclose(file);
}


void writeOrder(const Order *order)
{
 	int cursor;
 	FILE *file=openFile(ORDERS_FILE,"r+");

 	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,order->id))!=-1)
 	{
 		rewind(file);
 		writeCpy(file,"A.orders.tpm",cursor);
 		nextLine(file,ENDLINE);
 		writeCpy(file,"B.orders.tpm",-1);

 		fclose(file);
 		file=fopen(ORDERS_FILE,"w");
 		loadCpy(file,"A.orders.tpm");
 	}

 	fprintf(file, "%d%c%d%c",order->id,SEPARATOR,order->isDelete,SEPARATOR);
	fprintf(file, "%d%c",order->customer,SEPARATOR);

	writeArrayInteger(file,order->lines,SEPARATOR);

	writeDateTime(file,&order->date,SEPARATOR);
 	fprintf(file, "%c",ENDLINE );

 	if(cursor!=-1)
 		loadCpy(file,"B.orders.tpm");
 	fclose(file);
}

void addOrderToArray(ArrayOrder *array,Order *order)
{
	array->size++;
	arrayArrangement(array,order);
}

void removeOrderToArray(ArrayOrder *array,Order *order)
{
	if(array->head==array->tail)
	{
		array->head=NULL;
		array->tail=NULL;
	}
	else if(order==array->head)
	{
		array->head=order->next;
		array->head->previous=NULL;
	}
	else if(order==array->tail)
	{
		array->tail=order->previous;
		array->tail->next=NULL;
	}
	else
	{
		order->previous->next=order->next;
		order->next->previous=order->previous;
	}
	array->size--;
}

void destructArrayOrder(ArrayOrder *array)
{
	Order *order=array->tail;

	while(order!=array->head)
	{
		order=order->previous;
		destructOrder(order->next);
	}
	if(order!=NULL)
		destructOrder(order);
	free(array);
}

void loadOrders(ArrayOrder *array)
{
	int i;
	Order *order=NULL;
	FILE *file=openFile(ORDERS_FILE,"r");
	array->size=howManySeparatorContainFile(file,ENDLINE);
	fclose(file);
	for(i=0;i<array->size;++i)
	{
		order=new_order(0,0);
		loadOrder(order,i);
		arrayArrangement(array,order);
	}
}

