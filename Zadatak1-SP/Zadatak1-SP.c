/*
Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS		//ne moramo koristiti windows funkcije

#define BUFFER_LEN 1024		//stavljamo konstantu da nam je kasnije lakse mjenjati velicinu
#define NAME_BUFFER_LENGTH 128		//stavljamo konstantu da nam je kasnije lakse mjenjati velicinu

#include <stdio.h>		//standardna biblioteka(printf,scanf,...)
#include <stdlib.h>		//standrardna biblioteka(NULL,malloc,...)
#include <string.h>		//standardna biblioteka(string,...)


typedef struct _student _STUDENT;		//deklarirali smo strukturu imena _STUDENT koja ima parametre kao _student
typedef struct _student* _pstud;		//deklarirali smo pokazivac *_pstud na strukturu _student

struct _student		//tip i naziv strukture
{		
	char ime[NAME_BUFFER_LENGTH];		//niz karaktera imena ime a maksimalne duljine NAME_BUFFER_LENGTH
	char prezime[NAME_BUFFER_LENGTH];		//niz karaktera imena prezime a maksimalne duljine NAME_BUFFER_LENGTH
	int bodovi;		//varijabla bodovi tipa int
};


int CountRecords(char*);		//prototip funkcije CountRecords(broji koliko ima clanova) koji prima pokazivac na datoteku a vraca int
int ReadRecords(int, _pstud, char*);		//prototip funckije ReadRecords(cita i racuna maksimalni broj bodova) koja prima broj osoba u datoteci,pokazivac na strukturu i pokazivac na datoteku bodova a vraca maksimalni broj bodova
int PrintRecords(int, _pstud, int);		//prototip funckije PrintRecords(ispisuje sve clanove datoteke) koja prima broj osoba,pokazivac na strukturu i maksimalni broj bodova te ispisuje na ekran

int main()		//main funckija koja ne prima nista
{

	char* fileName = NULL;		//pokazivac na datoteku i inicijaliziran na nulu
	int lineN = 0;		//broj clanova u datoteci i inicijaliziran na nulu
	_pstud popis = NULL;		//pokazivac na strukturu i inicijaliziran na nulu
	int maxPoints = 0;		//broj maksimalnih bodova i inicijaliziran na nulu

	fileName = (char*)malloc(sizeof(char)* MAX_PATH);		//dinamicka alokacija memorije za ime datoteke
	if (fileName == NULL) printf("Greska prilikom alokacije buffera za file :(((");		//ako je alocirana memorija nula znaci da se dogodila greska

	printf("Unesite ime datoteke(pazi na .txt): ");		//printf obicni da lipse izgleda
	scanf(" %s", fileName);		//upisujemo naziv datoteke

	lineN = CountRecords(fileName);		//brojimo pomocu funckije i spremamo u lineN koliko ima osoba ili redaka u datoteci

	if (lineN > 0)		//ako ima vise od nula osoba
	{
		printf("Izbrojeno %d zapisa.", lineN);		//ispisuje koliko ima osoba
		popis = (_pstud)malloc(sizeof(_STUDENT)* lineN);		//dinamicka alokacija memorije za onoliko struktura koliko redaka ima datoteka	
		if (popis == NULL) printf("Greska prilikom alokacije popisa studenata :(");		//ako je alocirana memorija nula znaci da se dogodila greska

		maxPoints = ReadRecords(lineN, popis, fileName);		//pomocu funckije trazimno maksimalni broj bodova
		printf("\nMaksimalni broj bodova: %d", maxPoints);		//printf obicni da lipse izgleda

		PrintRecords(lineN, popis, maxPoints);		//funckija za ispis datoteke
	}
	else{		//kontra uvjet od if ako je broj clanova nula
		printf("Nema zapisa u datoteci.");		//printf obicni da lipse izgleda
	}
	


	

	return 0;		//return 0 zapravo znaci da je program uspjesno izvrsen
}

int CountRecords(char* fName)		//funckija koja broji koliko ima clanova
{
	FILE* fp = NULL;		//pokazivac na datoteku smo inicijalizirali na nula
	char* buff = NULL;		//pokazivac na buff smo inicijalizirali na NULL
	int n = 0;		//inicijalizacija varijable n na nula i deklaracija naravno

	fp = fopen(fName, "r");		//naredba za otvaranje file-a i citanje iz njega da je bilo "w" onda bi bila za pisanje u njega
	if (fp == NULL) printf("Nije bilo moguce otvoriti datoteku '%s'. Provjerite tocnost unosa.", fName);		//javlja pomocu printf da nismo uspili otvoriti datoteku

	buff = (char*)malloc(sizeof(char)* BUFFER_LEN);		//dinamicka alokacija memorije za buff
	if (buff == NULL) printf("Greska prilikom alokacije buffera :((");		//ako je buff NULL znaci da nije uspjela dinamicka alokacija memorije za njega

	while (!feof(fp))		//funkcija se odvija dok nije dosla do kraja file-a
	{
		fgets(buff, BUFFER_LEN, fp);		//funckija fgets uzima red iz fp sprema ga u buff i to radi BUFFER_LEN-1(pazi na ovo) puta i onda se zavrsi i program nastavlja dalje
		n++;		//raste varijabla n za jedan svaki put kad se izvrsi fgets
	}

	fclose(fp);		//funckija zatvara datoteku
	return n;		//funckija vraca broj redaka n 
}

int ReadRecords(int n, _pstud P, char* fName)		//funckija ReadRecords koja prima broj redaka,pokazivac na strukturu i pokazivac na datoteku
{
	FILE* fp = NULL;		//deklaracija i inicijalizacija pokazivaca na file na NULL
	char* buff = NULL;		//deklaracija i inicijalizacija pokazivaca na buff na NULL
	int maxP = 0;		//deklaracija i inicijalizacija varijable za maksimalni broj bodova na 0

	fp = fopen(fName, "r");		//funckija koja otvara datoteku fname 
	if (fp == NULL) printf("Nije bilo moguce otvoriti datoteku '%s'. Provjerite tocnost unosa.", fName);		//ako je fp NULL znaci da je otvaranje datoteke bilo neuspjesno

	buff = (char*)malloc(sizeof(char)* BUFFER_LEN);		//dinamicka alokacija memorije za buff koji sluzi kao pomoc za sscanf
	if (buff == NULL) printf("Greska prilikom alokacije buffera :((");		//ako je buff NULL znaci da alokacija nije uspjela

	while (!feof(fp))		//funckija while se izvrsava dok god nismo dosli do zadnjeg retka
	{
		fgets(buff, BUFFER_LEN, fp);		//uzima jedan red pohranjuje ga u buff a pomocu BUFFER_LENGTH zna kolika mu je duljina
		sscanf(buff, "  %d %s %s", &P->bodovi, P->ime, P->prezime);		//uzima iz datoteke bodove,ime i prezime i sprema na neko vrijeme u strukturu P

		if (P->bodovi > maxP)		//ako je zadnji maksimalni broj bodova veci od prijasnjeg onda se if izvrsava
			maxP = P->bodovi;		//maxP pridodjeljujemo broj bodova koji smo ode poslali preko pokazivaca P iz strukture _student
		P++;		//raste vrijednost od P(pazi dobro na ovaj redak) 
	}

	fclose(fp);		//zatvaramo datoteku koju smo koristili
	return maxP;		//vracamo vrijednost maksimalnog broja bodova
}

int PrintRecords(int n, _pstud P, int maxPoint)		//funckija prima broj redova,pokazivac na strukturu i maksimalni broj bodova
{
	int i = 0;		//deklaracija i inicijalizacija varijable i na nula
	printf("\nNova tablica ucenika glasi:\n\n\t\t%15s %15s %4s %4s", "Ime", "Prezime", "Aps bodovi", "Relativni bodovi");		//printf vrh tablice u koju printamo clanove
	for (i = 0; i < n; i++)		//for petlja koja ce se izvrsiti onoliko puta koliko ima ljudi tj redaka
	{
		printf("\n\t\t%15s %15s %5d %8d/%d = %6.2f", P->ime, P->prezime, P->bodovi, P->bodovi, maxPoint, ((float)P->bodovi / maxPoint) * 100);		//printf printa clanove i apsolutni i relativni broj bodova
		P++;		//idemo na sljedecu strukturu u nizu,a to mozemo jer smo alocirali niz struktura
	}

	return 0;		//vraca 0 ako se funckija uspjesno izvrsila
}

