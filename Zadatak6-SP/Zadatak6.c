/*6. Napisati program koji pomoæu vezanih listi simulira rad : a) stoga, b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100. */

#include <stdio.h>
#include <stdlib.h>

#define N_LENGHT 128

typedef struct Elementi* Pozicija;

struct Elementi
{
	int El;
	Pozicija Next;
};

Pozicija StvoriNovu();
int Ispis(Pozicija);
int Push(Pozicija);
int Pop(Pozicija);
int UnosRed(Pozicija);
int IzbrisiRed(Pozicija);

int main()
{
	Pozicija Head1 = NULL;
	Pozicija Head2 = NULL;
	Head1 = StvoriNovu();
	Head2 = StvoriNovu();

	printf("\nRed:");
	UnosRed(Head1);
	UnosRed(Head1);

	IzbrisiRed(Head1);
	IzbrisiRed(Head1);

	printf("\nStog:");
	Push(Head2);
	Push(Head2);

	Pop(Head2);
	Pop(Head2);

	Ispis(Head1->Next);
	Ispis(Head2->Next);

	return 0;
}

int IzbrisiRed(Pozicija P)		//u redu se brise prvi	
{
	Pozicija temp = NULL;

	temp = P->Next;		//namjesta pokazivace i onda brise
	P->Next = temp->Next;
	free(temp);

	return 0;
}

int UnosRed(Pozicija P)		//u redu se unosi na kraj
{
	Pozicija temp = NULL;
	int min = 10;
	int max = 100;
	int RandBr;

	RandBr = rand() % (max - min) + min;		//generira random broj izmedu 10 i 100
	temp = StvoriNovu();

	while (P->Next != NULL)		//hoda do zadnjeg jer se u redu unosi na kraj
		P = P->Next;

	temp->El = RandBr;		//unosi i namjesta pokazivace
	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}

int Pop(Pozicija P)		//na stogu se brise zadnji
{
	Pozicija temp = NULL;
	if (P->Next == NULL)	printf("Prazan stog");

	while (P->Next != NULL)		//hoda do zadnjeg jer se u stogu brise zadnji
		P = P->Next;

	temp = P->Next;		//namjesta pokazivace i onda brise
	P->Next = temp->Next;
	free(temp);
	return 0;
}

int Push(Pozicija P)		//na stogu se unosi na prvo
{
	Pozicija temp = NULL;
	int min = 10;
	int max = 100;
	int RandBr;

	RandBr = rand() % (max - min) + min;		//generira random broj izmedu 10 i 100
	temp = StvoriNovu();

	while (P->Next != NULL)		//hoda do zadnjeg jer se u stogu unosi zadnji
		P = P->Next;

	temp->El = RandBr;		//unosi i namjesta pokazivace
	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}

int Ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf("%d\t", P->El);
		P = P->Next;
	}
	printf("\n");
	return 0;
}

Pozicija StvoriNovu()
{
	Pozicija Nova = NULL;
	Nova = (Pozicija)malloc(N_LENGHT *sizeof(struct Elementi));
	if (Nova == NULL)
	{
		printf("Greska!");
		return NULL;
	}
	Nova->Next = NULL;
	return Nova;
}