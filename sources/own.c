#include "own.h"
//////////////////////////////--STATICS--/////////////////////////////////////////////
static unsigned int cursorToBack(int sequence,int value)
{
	if(sequence/10 > 0)
		return cursorToBack(sequence/10,++value);
	else
		return value;
}

static void arrayArrangement(ArrayInteger *array,Integer *integer)
{
	if(array->head==NULL)
	{
		array->head=integer;
		array->middle=integer;
	}
	else
	{
		array->tail->next=integer;
		integer->previous=array->tail;
	}
	array->tail=integer;
}
//////////////////////////////--FONTIONS--/////////////////////////////////////////////

int read(char *string,const size_t lenght)
{
	char *ptr=NULL;
	if(lenght<1)
		return 1;

	if(fgets(string,lenght+1,stdin))
	{
		ptr=strchr(string,'\n');
		if(ptr!=NULL)
			*ptr='\0';
		else
			clearBuffer();
		return 0;
	}
	clearBuffer();
	return 1;
}

int readInt()
{
	char tab[9+1];
	initString(tab,9);
	read(tab,9);
	return strtol(tab,NULL,10);
}

float readFloat()
{
	char tab[30+1];
	initString(tab,30);
	read(tab,30);
	return strtof(tab,NULL);
}

int isValid(const char *string)
{
	char c[1+1];
	do{
		printf("%s (y|n)\n> ",string );
		read(c,1);
	}while(c[0]!='y' && c[0]!='n');

	if(c[0]=='y')
		return 1;
	return 0;
}

int power(int X,int Y)
{
	if(Y>0)
		return power(X*X,--Y);
	else
		return X;
}

int isEnoughtLong(const char *string,const unsigned  int minimum)
{
	if(strlen(string)>=minimum)
		return 1;
	return 0;
}

int isAlphaRegex(const char *string,const size_t size)
{
	unsigned int i;
	for(i=0; i<size && string[i]!='\0' ;++i )
		if( (string[i]<65 && string[i]!=32) || (string[i] > 90 && string[i]<97) || string[i] > 122 )
			return 0;
	return 1;
}

FILE *openFile(const char *name,const char *mode)
{
	FILE *file=fopen(name,mode);
	if(file==NULL)
	{
		file=openFile(name,"w");
		if(file==NULL)
			exitFail("Impossible d'ouvrir le fichier!");
		fclose(file);
		return openFile(name,mode);
	}
	return file;
}

int isFileContainInt(FILE *file,const unsigned int count,const char separator,const char endline,const int sequence)
{
	char c;
	char buffer[255];
	unsigned int tour=0;
	unsigned int i=0;
	initString(buffer,255);
	while((c=fgetc(file))!=EOF)
	{
		if(c==separator)
		{
			if((tour++)==count)
			{
				if(strtol(buffer,NULL,10)==sequence)
					return ftell(file)-cursorToBack(sequence,1)-1;
				else
					nextLine(file,endline);
				tour=0;
			}
			c=fgetc(file);
			initString(buffer,255);
			i=0;
		}
		if(i<255)
			buffer[i++]=c;
	}
	return -1;
}

int isFileContainSequence(FILE *file,const unsigned int count,const char separator,const char endline, const char *sequence)
{
	char c;
	int buffer=0;
	int cursor=0;
	int wordToFind=0;
	unsigned int tour=0;
	unsigned int i=0;

	for(i=0;sequence[i]!='\0';++i)
		wordToFind+=sequence[i];

	while((c=fgetc(file))!=EOF)
	{
		if(c==separator)
		{
			if((tour++)==count)
			{
				if(buffer==wordToFind)
					return ftell(file)-cursor;
				else
					nextLine(file,endline);
			}
			c=fgetc(file);
			buffer=0;
			i=0;
			cursor=0;
		}
		buffer+=c;
		cursor++;
	}
	return -1;
}

int howManySeparatorContainFile(FILE *file,const char separator)
{
	char c;
	int count=0;
	while((c=fgetc(file))!=EOF)
		if(c==separator)
			count++;
	return count;
}

int isBiggerThan(char *a,char *b)
{
	if(a[0]=='\0' || b[0]=='\0')
		return 0;
	else if(a[0] == b[0])
		return isBiggerThan(&a[1],&b[1]);
	if(a[0]>b[0])
		return 1;
	else
		return 0;
}

void *alloc(const size_t size)
{
	void *ptr=NULL;
	if((ptr=malloc(size))==NULL)
		exitFail("ALLOCATION DYNAMIQUE IMPOSSIBLE");
	return ptr;
}

Integer *new_integer(int value)
{
	Integer *integer=(Integer *)alloc(sizeof(Integer));
	integer->value=value;
	integer->next=NULL;
	integer->previous=NULL;
	return integer;
}

ArrayInteger *new_array_integer()
{
	ArrayInteger *array=(ArrayInteger *)alloc(sizeof(ArrayInteger));
	array->size=0;
	array->head=NULL;
	array->middle=NULL;
	array->tail=NULL;
	return array;
}

Integer *addIntegerToArray(ArrayInteger *array,int value)
{
	Integer *integer=new_integer(value);
	if(integer!=NULL)
	{
		array->size++;
		arrayArrangement(array,integer);
	}
	return integer;
}
//////////////////////////////--PROCEDURES--/////////////////////////////////////////////

void clearBuffer()
{
	int c=0;
	while(c!='\n' && c!=EOF)
		c=getchar();
}

void stringLower(char *str,const size_t size)
{
	unsigned int i;
	for(i=0;str[i]!='\0' && i<size;++i)
		if(str[i]<91 && str[i]>64)
			str[i]+=32;
}

void stringUpper(char *str,const size_t size)
{
	unsigned int i;
	for(i=0;str[i]!='\0' && i<size;++i)
		if(str[i]>96 && str[i]<123)
			str[i]-=32;
}

void initString(char *str,const size_t size)
{
	unsigned int i;
	for(i=0;i<size;++i)
		*(str+i)=0;
	*(str+i)='\0';
}
void initVoidTab(void *tab[],const size_t size)
{
	unsigned int i;
	for(i=0;i<size;++i)
		*(tab+i)=NULL;
}

void setShortParam(short *param,const char *field,const int min,const int max)
{
	do
	{
		printf("* %s (%d-%d): ",field,min,max );
		*param=(short)readInt();
	}while(*param<min || *param>max);
}

void setIntegerParam(int *param,const char *field,const int min,const int max)
{
	do
	{
		printf("* %s (%d-%d): ",field,min,max );
		*param=readInt();
	}while(*param<min || *param>max);
}

void setFloatParam(float *param,const char *field,const float min,const float max)
{
	do
	{
		printf("* %s (%2.f-%2.f): ",field,min,max );
		*param=readFloat();
	}while(*param<min || *param>max);
}

void setStringParam(char *string,const char *field,const size_t size,const size_t min)
{
	do
	{
		printf("* %s : ",field);
		read(string,size);
	}while(!isEnoughtLong(string,min));
	stringLower(string,size);
}

void exitFail(char *str)
{
	printf("%s\n",__FILE__ );
	printf("Line : %d \n",__LINE__ );
	printf("%s \n", str);
	exit(1);
}

void nextLine(FILE *file,char endline)
{
	char c;
	do
	{
		c=fgetc(file);
	}while(c!=endline && c!=EOF);
}

void readNextCharValue(FILE *file,char separator,char *out,size_t size)
{
	char buffer[size];
	char c;
	unsigned int i=0;
	initString(buffer,size);
	while((c=fgetc(file))!=separator && c!=EOF && i<size)
		buffer[i++]=c;
	strcpy(out,buffer);
}

void readNextShortValue(FILE *file,char separator,short *out)
{
	char buffer[6]={0};
	char c;
	unsigned int i=0;
	while((c=fgetc(file))!=separator && c!=EOF && i<6)
		buffer[i++]=c;
	*out=(short)strtol(buffer,NULL,10);
}

void readNextIntValue(FILE *file,char separator,int *out)
{
	char buffer[11]={0};
	char c;
	unsigned int i=0;
	while((c=fgetc(file))!=separator && c!=EOF && i<11)
		buffer[i++]=c;
	*out=strtol(buffer,NULL,10);
}

void readNextFloatValue(FILE *file,char separator,float *out)
{
	char buffer[30]={0};
	char c;
	unsigned int i=0;
	while((c=fgetc(file))!=separator && c!=EOF && i<30)
		buffer[i++]=c;
	*out=strtof(buffer,NULL);
}

void writeCpy(FILE *file,const char *nameTpm,const int cursorPos)
{
	char c;
	FILE *tpmFile=NULL;

	if((tpmFile=fopen(nameTpm,"w"))!=NULL)
		if(cursorPos==-1)
			while((c=fgetc(file))!=EOF)
				fputc(c,tpmFile);
		else
			while(ftell(file)<cursorPos)
				fputc(fgetc(file),tpmFile);
	else
		exitFail("CAN'T OPEN(write) FILE ");
	fclose(tpmFile);
}

void loadCpy(FILE *file,const char *nameTpm)
{
	char c;
	FILE *cpyFile=NULL;
	if((cpyFile=fopen(nameTpm,"r"))!=NULL)
		while((c=fgetc(cpyFile))!=EOF)
			fputc(c,file);
	else
		exitFail("CAN'T OPEN(read) FILE");
	fclose(cpyFile);
	remove(nameTpm);
}

void SYS_LOG(char *str,char *file,int line)
{
	FILE *logfile=openFile("log","a+");
	fprintf(logfile, "%s %d %s\n",file,line,str );
	fclose(logfile);
}

void visualHSeparator(const char c,const int count)
{
	int i;
	for(i=0;i<count;++i)
		printf("%c",c);
	printf("\n");
}



void removeIntegerToArray(ArrayInteger *array,Integer *integer)
{
	if(integer==array->head)
	{
		array->head=integer->next;
		if(array->head!=NULL)
			array->head->previous=NULL;
		else
			array->tail=NULL;
	}
	else if(integer==array->tail)
	{
		array->tail=integer->previous;
		array->tail->next=NULL;
	}
	else
	{
		integer->previous->next=integer->next;
		integer->next->previous=integer->previous;
	}
	array->size--;
}

void destructArrayInteger(ArrayInteger *array)
{
	Integer *integer=array->tail;
	while(integer!=array->head)
	{
		integer=integer->previous;
		free(integer->next);
	}

	free(integer);
	free(array);
}

void writeInteger(FILE *file,const Integer *integer)
{
	fprintf(file, "%d-",integer->value);
}

void writeArrayInteger(FILE *file,const ArrayInteger *array,char separator)
{
	Integer *tpm=array->head;
	fprintf(file, "%d%c",array->size,separator );
	while(tpm!=NULL)
	{
		writeInteger(file,tpm);
		tpm=tpm->next;
	}
	fprintf(file, "%c",separator );
}

void loadArrayInteger(FILE *file,ArrayInteger *array,char separator)
{
	int i;
	Integer *tpm=NULL;
	char tiret;
	readNextIntValue(file,separator,&array->size);
	for(i=0;i<array->size;++i)
	{
		tpm=new_integer(0);
		readNextIntValue(file,'-',&tpm->value);
		arrayArrangement(array,tpm);
		tpm=NULL;
	}
	readNextCharValue(file,separator,&tiret,1);
}
