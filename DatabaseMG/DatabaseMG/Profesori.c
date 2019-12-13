#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<time.h>

typedef struct Profesori* PozicijaP;		//pokazivac na sljedeceg profesora

struct Profesori{
	//ovdje ide ID za ime profesora
	int ID_Ime;
	//ovdje ide ID za predmete profesora(neki mogu biti prazni ako ih profesor ne predaje te nije bitno da je po redu upisano)
	int ID_PredmetP1;
	int ID_PredmetP2;
	int ID_PredmetP3;
	int ID_PredmetP4;
	int ID_PredmetP5;
	int ID_PredmetP6;
	int ID_PredmetP7;
	int ID_PredmetP8;
	int ID_PredmetP9;
	int ID_PredmetP10;
	//ovo pokazuje na sljedeceg profesora i bit ce ih 10 odnosno 11 ukljucujuci i head
	PozicijaP Next;
};