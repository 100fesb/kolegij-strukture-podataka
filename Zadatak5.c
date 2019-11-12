/*5. Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1 U L2,
b) L1 !U L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.*/

#define _CRT_SECURE_NO_WARNINGS
#define N_LENGHT 1024

#include <stdio.h>
#include <stdlib.h>

typedef struct Lista *Position;

struct Lista{
	int Broj;
	Position Next;
};

Position stvoriNovu();
int citaizFile(Position);
int Ispis(Position);
int Unija(Position,Position,Position);
int Presjek(Position,Position,Position);

int main()
{
	Position L1 = NULL, L2 = NULL, Presjek = NULL, Unija = NULL;
	L1=stvoriNovu();
	L2=stvoriNovu();
	Presjek=stvoriNovu();
	Unija=stvoriNovu();

	citaizFile(L1);
	citaizFile(L2);

	Ispis(L1);
	Ispis(L2);

	system("pause");
	return 0;
}

Position stvoriNovu()
{
	Position P;

	P = (Position)malloc(sizeof(struct Lista));
	if (!P){
		printf("Greska pri alokaciji za novu listu.");
		return NULL;
	}
	P->Next = NULL;

	return P;
}

int citaizFile(Position P)
{
	char *fName = NULL;
	FILE *fp = NULL;
	char* buffer = NULL;

	if(!P){
		printf("Greska, P u citanju je NULL.");
		return -1;
	}

	buffer = (char*)malloc(N_LENGHT * sizeof(buffer));
	if (!buffer){
		printf("Greska pri alociranju za buffer.");
		return -1;
	}

	printf("Unesite ime datoteke za citanje (sa .txt):\n");
	scanf(" %s", fName);
	fp = fopen(fName, "r");
	if (!fp){
		printf("Greska pri èitanju file-a.");
		return -1;
	}

	while (!feof(fp))		
	{
		memset(buffer, 0, N_LENGHT);		 
		fgets(buffer, N_LENGHT, fp);		
		if (buffer[0] != '\n' && buffer[0] != '\0')		
		{
			sscanf(buffer, " %d", &P->Broj);
			P=P->Next;
		}
		else continue;		
	}
	buffer = NULL;		
	fclose(fp);		
	return 0;		

}


int Ispis(Position P)		//funkcija za ispis prima pokazivac na prvi clan onoga kojeg ispisuje
{
	while (P != NULL)		//izvrsava se petlja dok P nije NULL
	{
		printf("%d \n", P->Broj);		//ispisuje polinom
		P = P->Next;		//prebacuje pokazivac na sljedeci
	}
	return 0;		//vraca nulu ako je sve u redu
}
