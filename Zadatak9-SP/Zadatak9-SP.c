/*
Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.
*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define ERROR -1
#define SUCCESS 0
#define BUFFER_LENGTH 1024

typedef struct Stablo* Pozicija;

struct Stablo
{
	int El;
	Pozicija Right;
	Pozicija Left;
};

int Izbornik();
Pozicija Unesi(Pozicija, int);
int Print(Pozicija);
Pozicija TraziNajmanji(Pozicija);
Pozicija Izbrisi(Pozicija, int);
Pozicija Trazi(Pozicija, int);

int main()
{
	Pozicija root = NULL;
	Pozicija nadjeni = NULL;
	int izbor = -1;
	int n = 0;

	do
	{
		Izbornik();
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:		// izbor unos elementa
			printf("Unesite zeljeni element za unos: ");
			scanf("%d", &n);
			root = Unesi(root, n);
			printf("\nroot je:%d\n", root->El);
			break;
		case 2:		// izbor brisanja elementa
			if (!root) printf("Stablo je prazno!");
			else {
				printf("Koji element brisemo: ");
				scanf("%d", &n);
				root = Izbrisi(root, n);
			}
			break;
		case 3:		// izbor trazenja elementa
			printf("Koji element trazimo: ");
			scanf("%d", &n);
			nadjeni = Trazi(root, n);

			if (!nadjeni) printf("Nismo nasli taj element");
			else {
				printf("Nasli smo %d na adresi 0x%xh.\n", n, nadjeni);
			}

			break;
		case 4:		// izbor ispisa elemenata
			Print(root);
			break;
		default:
			printf("\nKrivi Unos!\n");
		}

	} while (izbor != 0);

	system("pause");
	return SUCCESS;
}

int Izbornik()
{
	printf("\nIzaberite:\n\t1 za Unos elementa\n\t2 za Brisanje elementa\n\t3 za Trazenje elementa\n\t4 za Ispis elementa\n\t0 za Izlaz\nIzbor: ");

	return SUCCESS;
}

Pozicija Unesi(Pozicija P, int n)
{
	if (!P)
	{
		P = (Pozicija)malloc(sizeof(struct Stablo));
		if (!P)
		{
			printf("Greska alokacije memorije");
			return P;
		}

		P->El = n;
		P->Left = NULL;
		P->Right = NULL;
	}
	else if (P->El < n)
		P->Right = Unesi(P->Right, n);
	else if (P->El > n)
		P->Left = Unesi(P->Left, n);
	else
		printf("Element vec postoji.");
	return P;
}

int Print(Pozicija P)		//ispis je sve u isti red
{
	if (P) {
		Print(P->Left);
		printf(" %d", P->El);
		Print(P->Right);
	}

	return SUCCESS;
}

Pozicija TraziNajmanji(Pozicija P)
{
	if (P != NULL)
	{
		while (P->Left != NULL)
			P = P->Left;
	}

	return P;
}

Pozicija Trazi(Pozicija P, int n)
{
	if (P == NULL)
		return P;

	if (P->El > n)
		return Trazi(P->Left, n);
	else if (P->El < n)
		return Trazi(P->Right, n);
	else
		return P;
}

Pozicija Izbrisi(Pozicija P, int n)
{
	Pozicija tmp;
	if (P == NULL)
	{
		printf("Element nije pronadjen.");
	}
	else if (n < P->El)
		P->Left = Izbrisi(P->Left, n);
	else if (n > P->El)
		P->Right = Izbrisi(P->Right, n);
	else
	{
		if (P->Left != NULL && P->Right != NULL)
		{
			tmp = TraziNajmanji(P->Right);
			P->El = tmp->El;
			P->Right = Izbrisi(P->Right, tmp->El);
		}
		else
		{
			tmp = P;
			if (P->Left == NULL)
				P = P->Right;
			else
				P = P->Left;
			free(tmp);
		}
	}

	return P;
}
