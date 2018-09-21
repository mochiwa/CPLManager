#include "line.h"

  /*******************************************************************************************\
<| ////////////////////////////////////////--STATICS--//////////////////////////////////////// |>
  \*******************************************************************************************/

static void arrayArrangement(ArrayLine *array,Line *line)
{
	if(array->head==NULL)
	{
		array->head=line;
		array->middle=line;
	}
	else
	{
		array->tail->next=line;
		line->previous=array->tail;
		if(line->id%2!=0)
			array->middle=array->middle->next;
	}
	array->tail=line;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--FONTIONS--///////////////////////////////////////// |>
  \*******************************************************************************************/

Line *new_line(const int id,const int product)
{
	Line *line=(Line *)alloc(sizeof(Line));
	initLine(line);
	line->id=id;
	line->product=product;
	setIntegerParam(&line->quantity,"quantite",1,10);
	return line;
}

Line *getLineById(const ArrayLine *array,const int id)
{
	Line *line=array->head;
	while(line!=NULL)
	{
		if(line->id==id)
			return (Line *)line;
		else
			line=line->next;
	}
		

	return NULL;
}

ArrayLine *new_array_line()
{
	ArrayLine *array=(ArrayLine *)alloc(sizeof(ArrayLine));

	array->size=0;
	array->head=NULL;
	array->middle=NULL;
	array->tail=NULL;

	return array;
}

  /*******************************************************************************************\
<| //////////////////////////////////////--PROCEDURES--/////////////////////////////////////// |>
  \*******************************************************************************************/

void initLine(Line *line)
{
	line->id=-1;
	line->isDelete=0;
	line->product=0;
	line->quantity=0;
	line->next=NULL;
	line->previous=NULL;
}

void editLine(Line *line)
{
	printf("		1) Modifier la quantite\n");
	printf("		2) Supprimer la ligne\n");
	printf("		9) Retour\n");
	printf("> ");
	switch(readInt())
	{
		case 1:
			setIntegerParam(&line->quantity,"quantite",1,10);
			break;
		case 2:
			if(isValid("Confirmer la suppression"))
				line->isDelete=1;
			break;
		case 9:
			break;
		default:
			printf("		!----BAD REQUEST----!\n");
			getchar();
			break;
	}
}

void loadLine(Line *line,const int id)
{
	int cursor;
	FILE *file=openFile(LINES_FILE,"r");

	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,id))!=-1)
	{
		fseek(file,cursor,SEEK_SET);
		readNextIntValue(file,SEPARATOR,&line->id);

		readNextIntValue(file,SEPARATOR,&line->isDelete);
		readNextIntValue(file,SEPARATOR,&line->product);
		readNextIntValue(file,SEPARATOR,&line->quantity);
	}
	fclose(file);
}

void writeLine(const Line *line)
{
	int cursor;
	FILE *file=openFile(LINES_FILE,"r+");

	if((cursor=isFileContainInt(file,0,SEPARATOR,ENDLINE,line->id))!=-1)
	{
		rewind(file);
		writeCpy(file,"A.Lines.tpm",cursor);
		nextLine(file,ENDLINE);
		writeCpy(file,"B.Lines.tpm",-1);
		
		fclose(file);
		file=openFile(LINES_FILE,"w");
		loadCpy(file,"A.Lines.tpm");
	}
	fprintf(file,"%d%c%d%c",line->id,SEPARATOR,line->isDelete,SEPARATOR );
	fprintf(file, "%d%c%d%c",line->product,SEPARATOR,line->quantity,SEPARATOR );
	fprintf(file, "%c",ENDLINE);
	if(cursor!=-1)
		loadCpy(file,"B.Lines.tpm");
	fclose(file);
}

void addLineToArray(ArrayLine *array,Line *line)
{
	array->size++;
	arrayArrangement(array,line);
}

void removeLineToArray(ArrayLine *array,Line *line)
{
	if(array->head==array->tail)
	{
		array->head=NULL;
		array->tail=NULL;
	}
	else if(line==array->head)
	{
		array->head=line->next;
		array->head->previous=NULL;
	}
	else if(line==array->tail)
	{
		array->tail=line->previous;
		array->tail->next=NULL;
	}
	else
	{
		line->previous->next=line->next;
		line->next->previous=line->previous;
	}
	array->size--;
}

void destructArrayLine(ArrayLine *array)
{
	Line *line=array->tail;
	while(line!=array->head)
	{
		line=line->previous;
		free(line->next);
	}
	free(line);
	free(array);
}

void loadLines(ArrayLine *array)
{
	int i;
 	Line *line=NULL;
 	FILE *file=openFile(LINES_FILE,"r");
 	array->size=howManySeparatorContainFile(file,ENDLINE);
 	fclose(file);

 	for(i=0;i<array->size;++i)
 	{
 		line=(Line *)alloc(sizeof(Line));
 		loadLine(line,i);
 		arrayArrangement(array,line);
 	}
}
