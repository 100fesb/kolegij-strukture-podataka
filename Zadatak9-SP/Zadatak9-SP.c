/*9. Napisati program koji omoguæava rad s binarnim 
stablom pretraživanja.Treba omoguæiti unošenje novog elementa 
u stablo, ispis elemenata, brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stablo* StabloP;

struct Stablo
{
	int El;
	StabloP Left;
	StabloP Right;
};

StabloP StvoriNovo();
StabloP Umetni(StabloP, int);
StabloP Trazi(StabloP, int);
StabloP Brisi(StabloP, int);
StabloP TraziNajmanji(StabloP);
int Ispis(StabloP);

int main()
{
	StabloP S = NULL;
	char Izbor = 0;
	int Broj=0;
	StabloP Trazeni = NULL;

	while (Izbor != 'k' && Izbor != 'K')		//ako unesemo k/K program se prekida
	{
		printf("Unesite svoj izbor:\n1-Unos elementa u stablo\n2-Brisanje elementa\n3-Trazenje elementa\n4 - Ispis stabla\n");
		scanf(" %c", &Izbor);

		switch (Izbor)
		{
		case'1':
			printf("Koji element zelite unijeti u stablo?\r\n");
			scanf("%d", &Broj);
			S = Umetni(S, Broj);
			break;
		case '2':
			printf("Koji element zelite izbrisati iz stabla?\r\n");
			scanf("%d", &Broj);
			S = Brisi(S, Broj);
			break;
		case '3':
			printf("Koji element zelite pronaci?\r\n");
			scanf("%d", &Broj);
			Trazeni = Trazi(S, Broj);
			if (Trazeni != NULL)
				printf("Trazeni element %d je u stablu!\r\n", Trazeni->El);
			break;
		case'4':
			printf("Vase stablo:\r\n");
			Ispis(S);
			break;
		case'k':
			break;
		case'K':
			break;
		}
	}

	return 0;
}

int Ispis(StabloP S)		//ispisuje pomocu rekurzije sljedeci pravilo prvo lijevo pa desno
{
	if (S != NULL)
	{
		Ispis(S->Left);
		printf("%d\t", S->El);
		Ispis(S->Right);
	}

	return 0;
}

StabloP TraziNajmanji(StabloP S)		//ova nam funkcija treba kad brisemo jer moramo paziti da su poredani po velicini
{
	if (S != NULL)
	{
		while (S->Left != NULL)
			S = S->Left;
	}
	return S;
}

StabloP Brisi(StabloP S, int X)		
{
	StabloP temp;

	if (S == NULL)
	{
		printf("Element koji zelite izbrisati ne postoji!");
		return NULL;
	}
	else if (S->El > X)		//pomocu ova dva else if odredujemo u koje cemo granu stabla dalje traziti
		S->Left = Brisi(S->Left, X);
	else if (S->El < X)
		S->Right = Brisi(S->Right, X);
	else
	{
		if (S->Left != NULL && S->Right != NULL)		//ako je list onda ovako brisemo 
		{
			temp = TraziNajmanji(S->Right);
			S->El = temp->El;
			S->Right = Brisi(S->Right, S->El);
		}
		else {		//ako nije list onda moramo gledamo na koju stranu povezujemo 
			temp = S;
			if (S->Left == NULL)
				S = S->Right;
			else if (S->Right == NULL)
				S = S->Left;
			free(temp);
		}
	}

	return S;
}

StabloP Trazi(StabloP S, int X)
{
	if (S == NULL)
	{
		printf("Element koji trazite ne postoji!");
		return NULL;
	}
	else if (S->El > X)
		return Trazi(S->Left, X);
	else if (S->El < X)
		return Trazi(S->Right, X);

	else return S;
}

StabloP Umetni(StabloP S, int X)
{
	if (S == NULL)
	{
		S = StvoriNovo();
		S->El = X;
	}
	else if (S->El > X)
		S->Left = Umetni(S->Left, X);
	else if (S->El < X)
		S->Right = Umetni(S->Right, X);
	else printf("Ovaj element u stablu vec postoji!");

	return S;
}

StabloP StvoriNovo()
{
	StabloP S = NULL;
	S = (StabloP)malloc(sizeof(struct Stablo));

	if (S == NULL)
	{
		printf("Greska prilikom alokacije memorije!");
		return NULL;
	}

	S->Left = NULL;
	S->Right = NULL;

	return S;
}
