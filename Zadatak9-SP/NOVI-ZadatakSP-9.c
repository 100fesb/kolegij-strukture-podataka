/*
Napisati program koji omogu�ava rad s binarnim stablom pretra�ivanja. Treba
omogu�iti uno�enje novog elementa u stablo, ispis elemenata, brisanje i pronala�enje
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


typedef struct Cvor* Pos;
struct Cvor
{
	int El;
	Pos Right;
	Pos Left;
};

int PrintMeni();
Pos Unesi(Pos, int);
int Print(Pos); 
Pos FindMin(Pos);
Pos FindMax(Pos);
Pos Izbrisi(Pos, int);
Pos Find(Pos, int);

int main()
{
	Pos root = NULL;
	Pos nadjeni = NULL;
	int izbor = -1;
	int n = 0;



	do
	{
		PrintMeni();
		scanf("%d", &izbor);

		switch (izbor){
		case 1: // izbor unos elementa
			printf("Unesite zeljeni element za unos: ");
			scanf("%d", &n);
			root = Unesi(root, n);
			printf("\nroot je:%d\n", root->El);
			break;
		case 2: // izbor brisanja elementa
			if (!root) printf("Stablo je prazno!");
			else {
				printf("Koji element brisemo: ");
				scanf("%d", &n);
				root = Izbrisi(root, n);
			}
			break;
		case 3: // izbor trazenja elementa
			printf("Koji element trazimo: ");
			scanf("%d", &n);
			nadjeni = Find(root, n);

			if (!nadjeni) printf("Nismo nasli taj element");
			else{
				printf("Nasli smo %d na adresi 0x%xh.\n", n, nadjeni);
			}

			break;
		case 4: // izbor ispisa elemenata
			Print(root);
			break;
		default:
			printf("\nKrivi Unos!\n");
		}

	} while (izbor != 0);

	system("pause");
	return SUCCESS;
}

int PrintMeni()
{
	printf("\nIzaberite:\n\t1 za Unos elementa\n\t2 za Brisanje elementa\n\t3 za Trazenje elementa\n\t4 za Ispis elementa\n\t0 za Izlaz\nIzbor: ");

	return SUCCESS;
}

Pos Unesi(Pos P, int n)
{
	if (!P)
	{
		P = (Pos)malloc(sizeof(struct Cvor));
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


/*
	nije bas formatiran ispis -> sve isti red
*/
int Print(Pos P)
{
	

	if(P) {
		Print( P->Left);
		printf(" %d", P->El);
		Print(P->Right);
	}

	return SUCCESS;
}

Pos FindMin(Pos P)
{
	if (P != NULL && P->Left != NULL)
	{
		return FindMin(P->Left);
	}

	return P;
}

Pos FindMax(Pos P)
{
	if (P == NULL) return P;

	while (P->Right != NULL)
		P = P->Right;
	return P;
}

Pos Find(Pos P, int n)
{
	if (P == NULL)
		return P;

	if (P->El > n)
		return Find(P->Left, n);
	else if (P->El < n)
		return Find(P->Right, n);
	else
		return P;
}

Pos Izbrisi(Pos P, int n)
{
	Pos tmp;
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
			tmp = FindMin(P->Right);
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

