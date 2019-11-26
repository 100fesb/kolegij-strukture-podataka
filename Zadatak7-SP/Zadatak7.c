/*7. Napisati program koji iz datoteke èita postfiks izraz i
zatim korištenjem stoga raèuna rezultat.Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stog* Pozicija;

struct Stog
{
	int El;
	Pozicija Next;
};

Pozicija StvoriNovu();
int CitaIzFile(char*, Pozicija);
int Push(Pozicija, int);
int Pop(Pozicija);
int Racunaj(int, int, int*, char);
int Ispis(Pozicija);

int main()
{
	Pozicija temp = NULL;
	char filename[20];

	printf("Unesite ime datoteke iz koje zelite citati(pazi na .txt):\n");
	scanf(" %s", filename);

	temp = StvoriNovu();
	CitaIzFile(filename, temp);

	printf("Rezultat je:\n");
	Ispis(temp->Next);

	return 0;
}

int Racunaj(int X, int Y, int* Rezultat, char c)
{
	switch (c)		//provjerava o kojoj je operaciji rijec
	{
	case '+':
		*Rezultat = X + Y;
		break;
	case '-':
		*Rezultat = X - Y;
		break;
	case'*':
		*Rezultat = X * Y;
		break;
	case '/':
		if (Y == 0)		//ne mozemo dijeliti sa nulom
		{
			printf("Beskonacno!");
			return -1;
		}
		*Rezultat = X / Y;
		break;
	default:
		break;
	}

	return 0;
}

int Ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf("%d\t", P->El);
		P = P->Next;
	}
	return 0;
}

int Pop(Pozicija P)		//skida sa stoga one koje smo izracunali ali i vraca pokazivac na njih jer ih moramo koristiti u funkciji Racunaj
{
	int X;
	Pozicija temp = NULL;		

	if (P->Next == NULL)
	{
		return -1;
	}

	while (P->Next->Next != NULL)		
			P = P->Next;

	temp = P->Next;	
	X = temp->El;
	P->Next = temp->Next;

	free(temp);
	return X;
}

int Push(Pozicija P, int X)		//koristimo za staviti brojeve i rezultate na stog
{
	Pozicija temp = NULL;
	temp = StvoriNovu();

	temp->El = X;

	while (P->Next != NULL)	
			P = P->Next;

	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}

int CitaIzFile(char* filename, Pozicija P)
{
	char* buffer;
	FILE* fp = NULL;
	int X, Y;
	int rezultat;

	buffer = (char*)malloc(50 * sizeof(char));
	fp = fopen(filename, "r");
	if (fp == NULL)	printf("Greska u otvaranju datoteke!");

	while (!feof(fp))
	{
		memset(buffer, 0, 50);
		fscanf(fp, " %s", buffer);

		if (isdigit(buffer[0]))		//provjerava jeli broj
		{
			sscanf(buffer, "%d", &X);
			Push(P, X);
			printf(" %d", X);
		}
		else 		//ako nije broj racuna pomocu funkcije Racunaj
		{
			Y = Pop(P);
			X = Pop(P);
			Racunaj(X, Y, &rezultat, buffer[0]);
			printf("Medurezultat je %d.\n", rezultat);
			Push(P, rezultat);
		}
	}
	fclose(fp);
	free(buffer);
	return 0;
}

Pozicija StvoriNovu()
{
	Pozicija temp = NULL;
	temp = (Pozicija)malloc(sizeof(struct Stog));
	if (temp == NULL)	printf("Greska pri alokaciji memorije");

	temp->Next = NULL;

	return temp;
}
