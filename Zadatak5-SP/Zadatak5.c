/*5. Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno,
bitno je samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1 U L2, b) L1 !U L2.*/

#define _CRT_SECURE_NO_WARNINGS		
#define N_LENGHT 128		

#include <stdio.h>		
#include <stdlib.h>

typedef struct Skup* Pozicija;

struct Skup {
	int El;
	Pozicija Next;
};

int CitaIzFile(char*, Pozicija);
int Unija(Pozicija, Pozicija, Pozicija);
int Presjek(Pozicija, Pozicija, Pozicija);
Pozicija StvoriNovu();
int Ispis(Pozicija);

int main()
{
	Pozicija HeadS1 = NULL, HeadS2 = NULL, HeadUnija = NULL, HeadPresjek = NULL;
	char fileName[N_LENGHT];

	HeadS1 = StvoriNovu();
	HeadS2 = StvoriNovu();
	HeadUnija = StvoriNovu();
	HeadPresjek = StvoriNovu();

	printf("Unesite ime datoteke iz koje zelite citati prvi skup:\n");
	scanf(" %s", fileName);
	CitaIzFile(fileName, HeadS1);
	printf("Unesite ime datoteke iz koje zelite citati drugi skup:\n");
	scanf(" %s", fileName);
	CitaIzFile(fileName, HeadS2);

	printf("Skup1:\n");
	Ispis(HeadS1->Next);
	printf("Skup2:\n");
	Ispis(HeadS2->Next);

	Unija(HeadS1->Next, HeadS2->Next, HeadUnija);
	printf("Unija:\n");
	Ispis(HeadUnija->Next);

	Presjek(HeadS1->Next, HeadS2->Next, HeadPresjek);
	printf("Presjek:\n");
	Ispis(HeadPresjek->Next);

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
	Nova = (Pozicija)malloc(sizeof(struct Skup));
	if (Nova == NULL)	printf("Greska!");

	Nova->Next = NULL;

	return Nova;
}

int CitaIzFile(char* filename, Pozicija P)
{
	Pozicija temp1 = P;
	Pozicija temp2 = NULL;
	FILE* fp = NULL;
	char* buffer = NULL;
	buffer = (char*)malloc(N_LENGHT * sizeof(char));
	fp = fopen(filename, "r");
	if (fp == NULL)	printf("Greska!");

	while (!feof(fp))
	{
		memset(buffer, 0, N_LENGHT);
		fgets(buffer, N_LENGHT, fp);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			temp2 = StvoriNovu();
			sscanf(buffer, "%d", &temp2->El);
			P = temp1; 
			while (P->Next != NULL && P->Next->El > temp2->El)
				P = P->Next;
			temp2->Next = P->Next;
			P->Next = temp2;
		}
		else continue;
	}
	fclose(fp);
	buffer = NULL;
	return 0;
}

int Unija(Pozicija S1, Pozicija S2, Pozicija Unija)
{
	Pozicija temp1 = NULL;
	Pozicija temp2 = NULL;
	while (S1 != NULL && S2 != NULL)
	{
		temp1 = StvoriNovu();
		if (S1->El > S2->El)
		{
			temp1->El = S1->El;
			S1 = S1->Next;
		}
		else if (S1->El < S2->El)
		{
			temp1->El = S2->El;
			S2 = S2->Next;
		}
		else
		{
			temp1->El = S1->El;
			S1 = S1->Next;
			S2 = S2->Next;
		}
		temp1->Next = Unija->Next;
		Unija->Next = temp1;
		Unija = temp1;
	}
	return 0;
}

int Presjek(Pozicija S1, Pozicija S2, Pozicija Presjek)
{
	Pozicija temp = NULL;
	while (S1 != NULL && S2 != NULL)
	{
		if (S1->El > S2->El)
			S1 = S1->Next;
		else if (S1->El < S2->El)
			S2 = S2->Next;
		else {
			temp = StvoriNovu();
			temp->El = S1->El;
			S1 = S1->Next;
			S2 = S2->Next;

			temp->Next = Presjek->Next;
			Presjek->Next = temp;
			Presjek = temp;
		}
	}
	return 0;
}
