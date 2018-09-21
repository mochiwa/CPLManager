#include "date.h"

//////////////////////////////--FONTIONS--/////////////////////////////////////////////

char *getMonthToString(const  int month)
{
	switch(month)
	{
		case 1:
			return "Janvier";
		case 2:
			return "Fevrier";
		case 3:
			return "Mars";
		case 4:
			return "Avril";
		case 5:
			return "Mais";
		case 6:
			return "Juin";
		case 7:
			return "Juillet";
		case 8:
			return "Aout";
		case 9:
			return "Septembre";
		case 10:
			return "Octobre";
		case 11:
			return "Novembre";
		case 12:
			return "Decembre";
		default:
			return "NULL";
	}
}

char isBissextile(const DateTime *dateTime)
{
	if(dateTime->years%4==0 && dateTime->years%100!=0)
		return 1;
	else if(dateTime->years%400==0)
		return 1;
	else
		return 0;
}

//////////////////////////////--PROCEDURES--/////////////////////////////////////////////

void initDateTime(DateTime *dateTime)
{
	dateTime->hour=0;
	dateTime->minute=0;
	dateTime->second=0;

	dateTime->day=0;
	dateTime->month=0;
	dateTime->years=0;
}
void makeDateTime(DateTime *dateTime)
{
	setIntegerParam(&dateTime->day,"Jour",1,31);
	setIntegerParam(&dateTime->month,"Mois",1,12);
	setIntegerParam(&dateTime->years,"Annee",1900,2019);
}

void makeTime(DateTime *dateTime)
{
	setIntegerParam(&dateTime->hour,"Heure",0,23);
	setIntegerParam(&dateTime->minute,"Minute",0,59);
	setIntegerParam(&dateTime->second,"Seconde",0,59);
}

void cpyDateTime(DateTime *dateTime,const DateTime *host)
{
	dateTime->hour=host->hour;
	dateTime->minute=host->minute;
	dateTime->second=host->second;

	dateTime->day=host->day;
	dateTime->month=host->month;
	dateTime->years=host->years;
}

void editDateTime(DateTime *dateTime)
{
	int run=1;
	while(run)
	{
		printf("1)Modifier le jour\n");
		printf("2)Modifier le mois\n");
		printf("3)Modifier l'annee\n");
		printf("4)Modifier l'heure\n");
		printf("5)Mettre a la date d'aujourd'hui\n");
		printf("6)Tout modifier\n");
		printf("9)Retour\n");
		printf("> ");
		switch(readInt(1))
		{
			case 1:
				setIntegerParam(&dateTime->day,"Jour",1,31);
				break;
			case 2:
				setIntegerParam(&dateTime->month,"Mois",1,12);
				break;
			case 3:
				setIntegerParam(&dateTime->years,"Annee",1900,2019);
				break;
			case 4:
				makeTime(dateTime);
				break;
			case 5:
				setDateTimeToToday(dateTime);
				break;
			case 6:
				makeDateTime(dateTime);
				break;
			case 9:
				run=0;
				break;
			default:
				printf("!----BAD REQUEST----!\n");
		}
	}
}

void setDateTimeToToday(DateTime *dateTime)
{
	time_t tms;
	struct tm *timer;
	tms=time(NULL);
	timer=gmtime(&tms);
	dateTime->day=(short)timer->tm_mday;
	dateTime->month=(short)timer->tm_mon+1;
	dateTime->years=(short)timer->tm_year+1900;
	setDateTimeToSystem(dateTime);
}
void  setDateTimeToSystem(DateTime *dateTime)
{
	time_t tms;
	struct tm *timer;
	tms=time(NULL);
	timer=gmtime(&tms);
	dateTime->hour=(short)timer->tm_hour;
	dateTime->minute=(short)timer->tm_min;
	dateTime->second=(short)timer->tm_sec;
}
void printDateTime(const DateTime *dateTime)
{
	if(dateTime->day<10)
		printf("0");
	printf("%d/",dateTime->day );
	if(dateTime->month<10)
		printf("0");
	printf("%d/%d ",dateTime->month,dateTime->years );

	if(dateTime->hour<10)
		printf("0");
	printf("%d:",dateTime->hour );
	if(dateTime->minute<10)
		printf("0");
	printf("%d:",dateTime->minute );
	if(dateTime->second<10)
		printf("0");
	printf("%d",dateTime->second );
}
void printDateTimeShort(const DateTime *dateTime)
{
	if(dateTime->day<10)
		printf("0");
	printf("%d/",dateTime->day );
	if(dateTime->month<10)
		printf("0");
	printf("%d/%d ",dateTime->month,dateTime->years );
}

void printDateTimeToString(const DateTime *dateTime)
{
	printf("%d %s %d ",dateTime->day,getMonthToString(dateTime->month),dateTime->years );
}

void writeDateTime(FILE *file,const DateTime *dateTime,const char separator)
{
	fprintf(file, "%d%c%d%c%d%c",dateTime->day,separator,dateTime->month,separator,dateTime->years,separator );
	fprintf(file, "%d%c%d%c%d%c",dateTime->hour,separator,dateTime->minute,separator,dateTime->second,separator );
}

void loadDateTime(FILE *file,DateTime *dateTime,const char separator)
{
	readNextIntValue(file,separator,&dateTime->day);
	readNextIntValue(file,separator,&dateTime->month);
	readNextIntValue(file,separator,&dateTime->years);

	readNextIntValue(file,separator,&dateTime->hour);
	readNextIntValue(file,separator,&dateTime->minute);
	readNextIntValue(file,separator,&dateTime->second);
}
