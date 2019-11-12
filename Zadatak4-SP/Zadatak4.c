/*4. Napisati program za zbrajanje i množenje polinoma.
Koeficijenti i eksponenti se čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS		//da ne moramo koristit windows funckije
#define N_LENGHT 1024		//ovako nam je kasnije lakse ako moramo povecat

#include <stdio.h>		//standardna biblioteka(printf,scanf,...)
#include <stdlib.h>		//bibliotek(malloc,NULL,...)

typedef struct Polinom* Pozicija;		//deklaracija pokazivaca Pozicija na strukturu Polinom

struct Polinom {		//deklaracija strukture
	int Koef;		//int za koeficijent
	int Eks;		//int za eksponent
	Pozicija Next;		//pokazivac Next na sljedecu strukturu
};

int CitaIzFile(char*, Pozicija);		//prototip funkcije koja cita iz datoteke koja prima ime datoteke i pokazivac na strukturu u koju zapisuje
int Suma(Pozicija, Pozicija, Pozicija);		//prototip funckije za sumu polinoma koja prima pokazivace na strukture koje zbraja i zadnji na strukturu u koju zapisuje
int Produkt(Pozicija, Pozicija, Pozicija);		//prototip funckije za produkt polinoma koja prima pokazivace na strukture koje mnozi i zadnji na strukturu u koju zapisuje
Pozicija StvoriNovu();		//prototip funckije koja stvara novi element liste i vraca pokazivac na Head
int Ispis(Pozicija);		//prototip funkcije za ispis

int main()		//main funkcija
{
	Pozicija HeadP1 = NULL, HeadP2 = NULL, HeadSuma = NULL, HeadProdukt = NULL;		//deklaracija i inicijalizacija P1,P2,Suma i Produkt
	char fileName[N_LENGHT];		//deklaracija fileName koje predstavlja ime datoteke
	HeadP1 = StvoriNovu();		//stvara novu i vraca pokazivac 
	HeadP2 = StvoriNovu();		//stvara novu i vraca pokazivac 
	HeadSuma = StvoriNovu();		//stvara novu i vraca pokazivac 
	HeadProdukt = StvoriNovu();		//stvara novu i vraca pokazivac 
	printf("Unesite ime datoteke iz koje zelite citati prvi polinom:\n");		//pita nas ime datoteke za prvi,pazi moras txt napisat
	scanf(" %s", fileName);		//unosimo ime datoteke
	CitaIzFile(fileName, HeadP1);		//cita iz file-a a prima ime file-a i pokazivac na strukturu u koju sprema
	printf("Unesite ime datoteke iz koje zelite citati drugi polinom:\n");		//pita nas ime datoteke za drugi,pazi moras txt napisat
	scanf(" %s", fileName);		//unosimo ime datoteke
	CitaIzFile(fileName, HeadP2);		//cita iz file-a a prima ime file-a i pokazivac na strukturu u koju sprema
	printf("Polinom1:\n");		//printf prvi polinom
	Ispis(HeadP1->Next);		//ispisuje prvi polinom a prima pokazivac na prvi clan 
	printf("Polinom2:\n");		//printf drugi polinom
	Ispis(HeadP2->Next);		//ispisuje drugi polinom a prima pokazivac na prvi clan
	Suma(HeadP1->Next, HeadP2->Next, HeadSuma);		//prima pokazivac na prvi clan na drugi clan i na HeadSuma i zbraja ih
	printf("Suma:\n");		//printf Suma
	Ispis(HeadSuma->Next);		//ispisuje sumu


	Produkt(HeadP1->Next, HeadP2->Next, HeadProdukt);		//prima pokazivac na prvi clan na drugi clan i na HeadProdukt i mnozi ih
	printf("Produkt:\n");		//printf Produkt
	Ispis(HeadProdukt->Next);		//ispisuje produkt

	system("Pause");
	return 0;		//vraca nulu ako je sve bilo u redu
}

int Ispis(Pozicija P)		//funkcija za ispis prima pokazivac na prvi clan onoga kojeg ispisuje
{
	while (P != NULL)		//izvrsava se petlja dok P nije NULL
	{
		printf("%d %d\r\n", P->Koef, P->Eks);		//ispisuje polinom
		P = P->Next;		//prebacuje pokazivac na sljedeci
	}
	return 0;		//vraca nulu ako je sve u redu
}

Pozicija StvoriNovu()		//funckija koja stvara novu strukturu tj novu listu te ne prima nista a vraca pokazivac na listu koju je stvorila
{
	Pozicija Nova = NULL;		//deklarira novi objekt temp i inicijalizira ga na NULL
	Nova = (Pozicija)malloc(sizeof(struct Polinom));		//dinamicka alokacija memorije za temp
	if (Nova == NULL)	printf("Greska");		//ispise Greska ako je doslo do greske prilikom alokacije memorije

	Nova->Next = NULL;		//stavlja pokazivac na Next na NULL

	return Nova;		//vraca pokazivac na listu tj na Head liste
}

int CitaIzFile(char* filename, Pozicija P)		//funckija koja cita polinom iz datoteke a prima ime datoteke i Head liste u koju sprema
{
	Pozicija temp1 = P;		//pridodijelili smo varijabli temp1 vrijednost P
	Pozicija temp2 = NULL;		//objekt deklariran i inicijaliziran na NULL
	FILE* fp = NULL;		//pokazivac na datoteku inicijaliziran na NULL
	char* buffer = NULL;		//pokazivac na buffer inicijaliziran na NULL
	buffer = (char*)malloc(N_LENGHT * sizeof(buffer));		//dinamicka alokacija za buffer
	fp = fopen(filename, "r");		//otvara file
	if (fp == NULL)	printf("Greska");		//ispisuje Greska ako je pokazivac na datoteku NULL

	while (!feof(fp))		//izvrsava se dok nije doslo do kraja funkcije
	{
		memset(buffer, 0, N_LENGHT);		//popuni string u bufferu duljine N_LENGHT i popuni sa 0 
		fgets(buffer, N_LENGHT, fp);		//uzima iz fp string duljine N_LENGHT i sprema u buffer
		if (buffer[0] != '\n' && buffer[0] != '\0')		//provjerava jeli buffer novi red ili kraj stringa
		{
			temp2 = StvoriNovu();		//stvara novu datoteku i vraca pokazivac na nju i pridodijeljuje ga temp2
			sscanf(buffer, "%d %d", &temp2->Koef, &temp2->Eks);		//iz buffera upisuje u temp2 
			P = temp1;		//ovo je potrebno zbog donjeg while-a
			while (P->Next != NULL && P->Next->Eks >= temp2->Eks)		//ova linija trazi koji po redu ima isti eksponent
				P = P->Next;		//prebacuje na sljedecu strukturu dok ne naide na isti ili veci eksponent
			if (P->Eks == temp2->Eks)		//izvrsava se ako je P eksponent isti kao i temp2 eksponent 
			{
				P->Koef = temp2->Koef;		//zbraja koeficijent iz temp2 na koeficijent P
			}
			else {		//u protivnom izvrsava
				temp2->Next = P->Next;		//pokazivac na strukturu koja je nakon P prebacujemo na mjesto iza temp2
				P->Next = temp2;		//pokazivac na temp2 pridodjeljujemo pokazivacu na sljedeci iza P
			}
		}
		else continue;		//ako uvjet od if nije ispunjen preskace funkciju i ide dalje
	}
	buffer = NULL;		//oslobada memoriju zauzetu od strane buffer-a
	fclose(fp);		//zatvara datoteku da je i drugi programi mogu koristiti
	return 0;		//vraca 0 ako je sve u redu
}

int Suma(Pozicija P1, Pozicija P2, Pozicija Suma)		//funkcija prima pokazivace na dva koja zbraja i na sumu di zapisuje
{
	Pozicija temp1 = NULL;		//temp1 deklarira i inicijalizira na NULL
	Pozicija temp2 = NULL;		//temp2 deklarira i inicijalizira na NULL
	while (P1 != NULL && P2 != NULL)		//izvrsava se dok P1 i P2 nisu nula tj. njihovi pokazivaci
	{
		temp1 = StvoriNovu();		//stvara se novi Head za temp1 tj vraca pokazivac na Head,mora pomocu stvori novu inace 
		if (P1->Eks > P2->Eks)		//ako je eksponent iz P1 veci od onoga iz P2 onda se izvrsava,jer ih slaze po redu pocevsi od najmanjeg eksponenta
		{
			temp1->Eks = P1->Eks;		//eksponent iz P1 se pridodjeljuje temp1
			temp1->Koef = P1->Koef;		//koeficijent iz P1 se pridodjeljuje temp1
			P1 = P1->Next;		//Next iz P1 se prebaci na mjesto pokazivaca na P1
		}
		else if (P1->Eks < P2->Eks)		//ako je eksponent iz P1 manji od onoga iz P2 onda se izvrsava
		{
			temp1->Eks = P2->Eks;		//eksponent iz P2 se pridodjeljuje temp1
			temp1->Koef = P2->Koef;		//koeficijent iz P2 se pridodjeljuje temp1
			P2 = P2->Next;		//Next iz P2 se inicijalizira na mjesto pokazivaca na P2
		}
		else         //ako nije slucaj ni jedan od dva prethodna slucaja znaci da su eksponenti jednaki i izvrsava se kod unutar else-a
		{
			temp1->Eks = P1->Eks;		//eksponent iz P1 se pridodjeljuje temp1
			temp1->Koef = P1->Koef + P2->Koef;		//koeficijenti iz P1 i P2 se zbrajaju i pridodjeljuju temp1 eksponentu
			P1 = P1->Next;		//Next iz P1 se inicijalizira na mjesto pokazivaca na P1
			P2 = P2->Next;		//Next iz P2 se inicijalizira na mjesto pokazivaca na P2
		}
		temp1->Next = Suma->Next;		//pokazivac na C Next se pridodjeljuje temp1 Next
		Suma->Next = temp1;		//pokazivac na temp1 se pridodjeljuje C Next
		Suma = temp1;		//Head od temp1 se pridodjeljuje pokazivacu na C
	}		//ova while petlja zbraja a ima tri if-a jer moze biti prvi veci manji ili jednak drugom koeficijentu

	return 0;		//vraca 0 ako je sve u redu
}

int Produkt(Pozicija P1, Pozicija P2, Pozicija Produkt)		//funkcija Produkt prima pokazivace na Head-ove od oba polinoma i pokazivac na Produkt
{
	Pozicija temp1 = NULL;		//deklaracija temp1 i inicijalizacija na NULL
	Pozicija temp2 = P2;		//deklaracija temp2 i inicijalizacija na P2
	Pozicija temp3 = Produkt;		//deklaracija temp3 i inicijalizacija na Produkt
	while (P1 != NULL)		//izvrsava se dok pokazivac na P1 nije NULL
	{
		P2 = temp2;		//pridodjeljuje vrijednost temp2 na P2
		while (P2 != NULL)		//izvrsava se dok pokazivac na P2 nije NULL
		{
			temp1 = StvoriNovu();		//stvara novi Head i vraca pokazivac na njega na temp1
			temp1->Eks = P1->Eks + P2->Eks;		//zbraja eksponente od P1 i P2 i pridodjeljuje tu vrijednost na temp1 eksponent
			temp1->Koef = P1->Koef * P2->Koef;		//zbraja koeficijente od P1 i P2 i pridodjeljuje tu vrijednost na temp1 koeficijent

			temp1->Next = Produkt->Next;		//pokazivac na C Next se pridodjeljuje temp1 Next
			Produkt->Next = temp1;		//pokazivac na temp1 se pridodjeljuje C Next
			Produkt = temp1;		//Head od temp1 se pridodjeljuje pokazivacu na C

			P2 = P2->Next;		//P2 Next se pridodjeljuje pokazivacu na P2
		}
		P1 = P1->Next;		//P1 Next se pridodjeljuje pokazivacu na P1
	}
	return 0;		//vraca 0 ako je sve u redu
}
