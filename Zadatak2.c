/*
Zadatak 2.
Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

Zadatak 3.
Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#define N_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>

typedef struct Cvor* Pozicija;

struct Cvor {
	char Ime[N_LENGTH];
	char Prezime[N_LENGTH];
	int God_rod;
	Pozicija Next;
};

int unosPocetak(Pozicija);
int ispis(Pozicija);
int unosKraj(Pozicija);
Pozicija traziPrez(Pozicija);
int brisiPrez(Pozicija, Pozicija);

int main()
{
	struct Cvor Head = { 0, NULL };
	struct Cvor* test = NULL;

	int broj_el = 0;
	

	printf("Koliko osoba na pocetak liste? ");
	scanf(" %d", &broj_el);

	for (int i = 0; i < broj_el; i++)
	{
		unosPocetak(&Head);
		ispis(Head.Next);
	}

	
	printf("\nKoliko osoba na kraj liste? ");
	scanf(" %d", &broj_el);

	for (int i = 0; i < broj_el; i++)
	{
		unosKraj(&Head);
		ispis(Head.Next);
	}

	
	test = traziPrez(&Head);
	printf("To je osoba %s %s rodjena %d.", test->Ime, test->Prezime, test->God_rod);

	/*printf("Vasa trazena osoba:\n");
	printf("\t%s\t%s\t%d", test->Ime, test->Prezime, test->God_rod);*/

	printf("\nKoju osobu zelite obrisati?");
	test = traziPrez(&Head);
	brisiPrez(test, &Head);

	ispis(Head.Next);


	return 0;
}

int unosPocetak(Pozicija P)
{
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));

	printf("\nUnesite ime, prezime, godinu rodjenja:\n");
	scanf(" %s", temp->Ime);
	scanf(" %s", temp->Prezime);
	scanf(" %d", &temp->God_rod);



	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}

int ispis(Pozicija P)
{
	printf("\nVasa lista:");

	while (P != NULL) {
		printf("\n\t");
		printf("%s\t ", P->Ime);
		printf("%s\t ", P->Prezime);
		printf("%d ", P->God_rod);


		P = P->Next;
	}

	return 0;
}



int unosKraj(Pozicija P)
{
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));

	printf("\nUnesite ime, prezime, godinu rodjenja:\n");
	scanf(" %s", temp->Ime);
	scanf(" %s", temp->Prezime);
	scanf(" %d", &temp->God_rod);

	while (P->Next != NULL) {
		P = P->Next;
	}

	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}

Pozicija traziPrez(Pozicija P)
{
	char trazeno_prez[N_LENGTH] = { NULL };

	printf("\nKoga trazimo - po prezimenu: ");
	scanf(" %s", trazeno_prez);

	while (P != NULL) {

		if (!(strcmp(P->Prezime, trazeno_prez)))
			return P;

		P = P->Next;
	}

	if (P == NULL) {
		printf("\nNije nadjena osoba.");
		return NULL;
	}
	
}


int brisiPrez(Pozicija brisiMe, Pozicija P) 
{
	while (P != NULL) {

		if (!(strcmp(P->Next->Prezime, brisiMe->Prezime))) {
			P->Next = P->Next->Next;
			printf("Brisemo osobu %s %s rodjena %d.", brisiMe->Ime, brisiMe->Prezime, brisiMe->God_rod);
			free(brisiMe);
		}

		if (brisiMe == NULL) return 0;
		P = P->Next;
	}
	if (P == NULL) {
		printf("\nNije izbrisana osoba.");
		return NULL;
	}
}
