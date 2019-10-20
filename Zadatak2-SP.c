/*
Zadatak 2.
Definirati strukturu osoba (ime, prezime, godina ro�enja) i napisati program koji:
a) dinami�ki dodaje novi element na po�etak liste,
b) ispisuje listu,
c) dinami�ki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) bri�e odre�eni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

Zadatak 3.
Prethodnom zadatku dodati funkcije:
a) dinami�ki dodaje novi element iza odre�enog elementa,
b) dinami�ki dodaje novi element ispred odre�enog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) �ita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS		//da ne moramo koristiti windows funckije
#define N_LENGTH 1024		//pisemo ovo u [] da nam je lakse povecati ako nam zatreba

#include <stdio.h>		//standardna biblioteka(printf,scanf,...)
#include <stdlib.h>		//biblioteka za (NULL,malloc,...)

typedef struct Cvor* Pozicija;		//deklaracija pokazivaca na strukturu cvor a ime pokazivaca je Pozicija

struct Cvor {		//deklaracija strukture
	char Ime[N_LENGTH];		//niz karaktera maksimalne duljine N_LENGTH
	char Prezime[N_LENGTH];		//niz karaktera maksimalne duljine N_LENGTH
	int God_rod;		//deklaracija int God_rod
	Pozicija Next;		?//deklaracija pokazivaca na funckiju imena Next
};

int unosPocetak(Pozicija);		//protorip funckije koja prima pokazivac na strukturu
int ispis(Pozicija);		//protorip funckije koja prima pokazivac na strukturu
int unosKraj(Pozicija);		//protorip funckije koja prima pokazivac na strukturu
Pozicija traziPrez(Pozicija);		//protorip funckije koja prima pokazivac na strukturu
int brisiPrez(Pozicija, Pozicija);		//protorip funckije koja prima pokazivac na strukturu i to prvo one koju brisemo a druga je &Head

int main()		//main koja ne prima nista
{
	struct Cvor Head = {0,NULL};		//Head je ime prve stukture u listi,0 je jer nema osoba u Head-u a NULL je jer su joj clanovi prazni
	struct Cvor* test = NULL;		//pokazivac na strukturu Cvor inicijaliziran na NULL

	int broj_el = 0;		//broj_el deklariran i inicijaliziran na 0
	

	printf("Koliko osoba na pocetak liste? ");		//printf pita koliko osoba na pocetak liste zelimo unijeti
	scanf(" %d", &broj_el);		//unosimo taj broj osoba i on se sprema na adresu &broj_el

	for (int i = 0; i < broj_el; i++)		//for se izvrti onoliko puta koliko smo htjeli unijeti osoba
	{
		unosPocetak(&Head);		//pozivamo funckiju za unos na pocetak i saljemo joj adresu od Head
		ispis(Head.Next);		//pozivamo funckiju za ispis i saljemo joj pokazivac iz Head-a
	}

	
	printf("\nKoliko osoba na kraj liste? ");		//printf pita koliko zelimo osoba na kraj liste
	scanf(" %d", &broj_el);		//prepisujemo na istu adresu koju smo koristili za broj osoba na pocetak

	for (int i = 0; i < broj_el; i++)		//for se izvrti onoliko puta koliko smo htjeli unijeti osoba
	{
		unosKraj(&Head);		//pozivamo funckiju za unos na kraj i saljemo joj adresu Head
		ispis(Head.Next);		//pozivamo funkciju za ispis i saljemo joj pokazivac iz Head-a
	}

	
	test = traziPrez(&Head);		//pozivamo funckiju traziPrez i ona vraca pokazivac na onu strukturu u kojoj se nalazi prezime koje smo trazili
	printf("To je osoba %s %s rodjena %d.", test->Ime, test->Prezime, test->God_rod);		//pomocu printf ispisujemo tu osobu te pazi koristimo -> jer ispisujemo pomocu pokazivaca na funckije

	printf("\nKoju osobu zelite obrisati?");		//pitamo koliko osoba zelimo obrisati
	test = traziPrez(&Head);		//pomocu iste funckije traziPrez trazimo po prezimenu osobu koju zelimo izbrisati te vracamo pokazivac na tu strukturu a saljemo adresu Head-a
	brisiPrez(test, &Head);		//pozivamo funckiju koja brise tu strukturu i povezuje onu prije nje sa onom nakon nje

	ispis(Head.Next);		//pozivamo funckiju za ispis i saljemo joj pokazivac iz Head-a dalje jer u Head-u nema osoba to je samo prvi element liste


	return 0;		//ako je sve proslo dobro program vraca nulu i to znaci alles gut
}

int unosPocetak(Pozicija P)		//funkcija unosPocetak prima pokazivac na Head
{
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));		//dinamicka alokacija memorije za tu strukturu

	printf("\nUnesite ime, prezime, godinu rodjenja:\n");		//govorimo korisniku sto cemo traziti od njega
	scanf(" %s", temp->Ime);		//unosimo ime
	scanf(" %s", temp->Prezime);		//unosimo prezime
	scanf(" %d", &temp->God_rod);		//unosimo godinu rodenja



	temp->Next = P->Next;		//stavljamo na Next u temp NULL koja je bila na Next u Head-u
	P->Next = temp;		//onda pokazivac iz Head-a Next stavimo da pokazuje na temp

	return 0;		//ako je sve proslo ok funckija vraca 0
}

int ispis(Pozicija P)		//funckija za ispis prima pokazivac na prvi clan liste izuzev Head-a
{
	printf("\nVasa lista:");		//ispisemo objasnjenje onog sto ispisujemo

	while (P != NULL) {		//dok god pokazivac ne pokazuje na NULL tj dok nismo dosli do zadnjeg clana izvrsava se petlja
		printf("\n\t");		//printf da lipse izgleda
		printf("%s\t ", P->Ime);		//ispis imena preko pokazivaca na strukturu
		printf("%s\t ", P->Prezime);		//ispis prezimena preko pokazivaca na strukturu
		printf("%d ", P->God_rod);		//ispis godine rodenja preko pokazivaca na strukturu


		P = P->Next;		//prebacujemo se na sljedeci clan u listi
	}

	return 0;		//ako je sve proslo ok funckija vraca 0
}



int unosKraj(Pozicija P)		//funckija prima pokazivac na Head
{
	Pozicija temp = (Pozicija)malloc(sizeof(struct Cvor));		//dinamicka alokacija memorije za tu strukturu

	printf("\nUnesite ime, prezime, godinu rodjenja:\n");		//govorimo korisniku sto cemo traziti od njega
	scanf(" %s", temp->Ime);		//unosimo ime
	scanf(" %s", temp->Prezime);		//unosimo prezime
	scanf(" %d", &temp->God_rod);		//unosimo godinu rodenja

	while (P->Next != NULL) {		//funckija se izvrsava dok god nije dosla do zadnjeg clana
		P = P->Next;		//prebacuje pokazivac na sljedeci
	}

	temp->Next = P->Next;		//stavljamo na Next u temp NULL koja je bila na Next u Head-u
	P->Next = temp;		//onda pokazivac iz Head-a Next stavimo da pokazuje na temp

	return 0;		//ako je sve ok funckija vrati 0
}

Pozicija traziPrez(Pozicija P)		//funckija trazi osobu po prezimenu i vraca pokazivac na tu strukturu a prima adresu Head-a
{
	char trazeno_prez[N_LENGTH] = { NULL };		//deklariramo i inicijaliramo niz karaktera za to prezime

	printf("\nKoga trazimo - po prezimenu: ");		//printf nas trazi da unesemo to prezime
	scanf(" %s", trazeno_prez);		//unosimo to prezime i spremamo pod trazeno_prez

	while (P != NULL) {		//petlja se izrsava dok god nismo dosli do kraja liste ali je prekine kada naide na prezime

		if (!(strcmp(P->Prezime, trazeno_prez)))		//strcmp vraca nulu ako su dva stringa ista zato smo stavili !
			return P;		//ako su isti vraca pokazivac na tu strukturu gdje je to prezime
	
		P = P->Next;		//setamo pomocu pokazivaca na sljedeci clan u listi
	}

	if (P == NULL) {		//ako je pokazivac nakon cijele liste i dalje NULL znaci da nismo nasli tu osobu tj da je nema u listi
		printf("\nNije nadjena osoba.");		//pomocu printf saljemo poruku korisniku
		return NULL;		//vracamo NULL sa return sto opet znaci da se program dobro izvrsio te je to isto kao i return 0
	}
	
}


int brisiPrez(Pozicija brisiMe, Pozicija P) 		//funckija brise element liste te prima pokazivac na element koji brisemo i na Head
{
	while (P != NULL) {		//dok pokazivac nije nula se izvrsava

		if (!(strcmp(P->Next->Prezime, brisiMe->Prezime))) {		//ako su isti stringovi(prezime iz sljedece stukture na koju pokazuje p i briseMe prezime) if se izvrsi
			P->Next = P->Next->Next;		//pokazivac na strukturu proseta jos jednu dalje ako ovo ne stavimo lista vise nije lista
			printf("Brisemo osobu %s %s rodjena %d.", brisiMe->Ime, brisiMe->Prezime, brisiMe->God_rod);		//isprintamo koju osobu brisemo
			free(brisiMe);		//funckija koja brise memoriju na kojoj je ta struktura
		}

		if (brisiMe == NULL) return 0;		//ako je brisi me NULL znaci da smo izbrisali pa je pokazivac na nju NULL
		P = P->Next;		//prebacimo P na sljedecu strukturu
	}
	if (P == NULL) {		//ako je pokazivac na P NULL znaci da nismo izbrisali
		printf("\nNije izbrisana osoba.");		//poruka obavijesti
		return NULL;		//vraca NULL kao i sto se vrati 0
	}
}

