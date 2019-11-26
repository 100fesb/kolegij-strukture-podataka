/*10. Napisati program koji iz datoteke èita postfiks izraz
i zatim stvara stablo proraèuna.Iz gotovog stabla proraèuna
upisati u datoteku infiks izraz.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Stablo* StabloP;
typedef struct Stog* Pozicija;

struct Stablo
{
	char* El;
	StabloP Left;
	StabloP Right;
};

struct Stog
{
	StabloP Cvor;
	Pozicija Next;
};

Pozicija StvoriNoviStog();
StabloP CitaIzFile(char*, StabloP, Pozicija);
StabloP StvoriNovoStablo();
int Push(Pozicija, StabloP);
StabloP Pop(Pozicija);
int Ispis(StabloP);

int main()
{
	StabloP S = NULL;
	Pozicija P = NULL;
	char filename[20];

	P = StvoriNoviStog();
	printf("Unesite ime datoteke iz koje zelite citati postfix izraz:\r\n");
	scanf(" %s", filename);

	S = CitaIzFile(filename, S, P);
	Ispis(S);

	return 0;
}

int Ispis(StabloP S)
{
	if (S != NULL)
	{
		if (!atoi(S->El) || isalpha(S->El[0]))		//atoi je string u integer a isalpha provjerava jeli slovo
		printf("(");

		Ispis(S->Left);
		printf(" %s ", S->El);
		Ispis(S->Right);

		if (!atoi(S->El) || isalpha(S->El[0]))	
		printf(")");
	}
	return 0;
}

Pozicija StvoriNoviStog()
{
	Pozicija Novi = NULL;
	Novi = (Pozicija)malloc(sizeof(struct Stog));

	if (Novi == NULL)
	{
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	Novi->Cvor = NULL;
	Novi->Next = NULL;

	return Novi;
}

StabloP StvoriNovoStablo()
{
	StabloP Novo = NULL;
	Novo = (StabloP)malloc(sizeof(struct Stablo));

	if (Novo == NULL)
	{
		printf("Greska pri alokaciji memorije!");
		return NULL;
	}

	Novo->El = (char*)malloc(sizeof(char) * 5);
	Novo->Left = NULL;
	Novo->Right = NULL;

	return Novo;
}

StabloP CitaIzFile(char* filename, StabloP S, Pozicija P)
{
	FILE* fp = NULL;
	char* buffer;
	buffer = (char*)malloc(50 * sizeof(char));

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!");
		return NULL;
	}

	while (!feof(fp))
	{
		memset(buffer, 50, 0);
		fscanf(fp, " %s", buffer);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			S = StvoriNovoStablo();
			sscanf(buffer, " %s", S->El);
			if (atoi(S->El) || isalpha(S->El[0]))
			{
				Push(P, S);
			}
			else
			{
				S->Right = Pop(P);
				S->Left = Pop(P);
				Push(P, S);
			}
		}
		else continue;
	}

	fclose(fp);
	free(buffer);
	S = Pop(P);

	return S;
}

StabloP Pop(Pozicija P)
{
	Pozicija temp = NULL;
	StabloP S = NULL;

	if (P->Next == NULL)
	{
		printf("Greska!");
		return NULL;
	}

	temp = P->Next;
	S = temp->Cvor;
	P->Next = temp->Next;

	free(temp);
	return S;
}

int Push(Pozicija P, StabloP S)
{
	Pozicija temp = NULL;
	temp = StvoriNoviStog();

	temp->Cvor = S;
	temp->Next = P->Next;
	P->Next = temp;

	return 0;
}
