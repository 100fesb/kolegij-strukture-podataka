#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

typedef struct Studenti* PozicijaS;		//pokazivac na sljedeceg studenta

struct Studenti{

	//ovdje ide ID za ime studenta
	int ID_Ime;
	//ovdje ide ID za predmete studenta(neki mogu biti prazni ako ih student nije upisao te nije bitno da je po redu upisano)
	int ID_PredmetS1;
	int ID_PredmetS2;
	int ID_PredmetS3;
	int ID_PredmetS4;
	int ID_PredmetS5;
	int ID_PredmetS6;
	int ID_PredmetS7;
	int ID_PredmetS8;
	int ID_PredmetS9;
	int ID_PredmetS10;
	//ovdje ide ID za ocjene studenta(neki mogu biti prazni ako student nije jos dobia tu ocjenu te nije bitno da je po redu upisano)
	int ID_Predmet_Ocjena1;
	int ID_Predmet_Ocjena2;
	int ID_Predmet_Ocjena3;
	int ID_Predmet_Ocjena4;
	int ID_Predmet_Ocjena5;
	int ID_Predmet_Ocjena6;
	int ID_Predmet_Ocjena7;
	int ID_Predmet_Ocjena8;
	int ID_Predmet_Ocjena9;
	int ID_Predmet_Ocjena10;
	//pokazuje na sljedeceg studenta i ovakvih ima 15 odnosno 16 ukljucujuci i head
	PozicijaS Next;
};

//int Izbornik()
//{
//	//ovjde cemo unijeti listu potrebnik izbora za nase potrebe
//	printf("\n\n\t\t\t");
//	printf("1-");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//	printf("");
//
//	return 0;
//
//}