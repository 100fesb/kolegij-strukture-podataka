/*8. Napisati program koji pomoæu vezanih listi(stabala) predstavlja strukturu 
direktorija.Omoguæiti unos novih direktorija i pod - direktorija, ispis sadržaja 
direktorija i povratak u prethodni direktorij.Toènije program treba preko menija 
simulirati korištenje DOS naredbi : 
1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Direktorij *PozicijaD;		//ne kuzim ove direktorije
typedef struct Stog *PozicijaS;

struct Direktorij
{
    char Ime[20];
    PozicijaD NextD;
    PozicijaD Osoba;
};

struct Stog
{
    PozicijaD Podatci;
    PozicijaS NextS;
};

int Push(PozicijaS,PozicijaD);
PozicijaS StvoriNoviS();
PozicijaD StvoriNoviD();
int StvoriDirektorij(PozicijaD,PozicijaS);
int UnesiPodatke(PozicijaD);
int IspisDirektorij(PozicijaD);
PozicijaD PromjeniDirektorij(PozicijaD);
PozicijaD Trazi(char*,PozicijaD);
PozicijaD cdt(PozicijaS);

int main()
{
    PozicijaD Root=NULL;
    Root=StvoriNoviD();
    PozicijaD Trenutni=Root;
    PozicijaS Stog=NULL;
    Stog=StvoriNoviS();
    char Izbor=0;

     printf("Unesite ime Root direktorija:");
    scanf(" %s",Root->Ime);

    while(Izbor!='k'&&Izbor!='K')
    {
        printf("Unesite svoj izbor:\n1-Make directory\n2-Change directory\n3-Print directory\n4-Vrati se u prethodni direktorij tj. cd..\nK-kraj\n");
        scanf(" %c",&Izbor);
        switch(Izbor)
        {
        case '1':
            StvoriDirektorij(Trenutni,Stog);
            break;
        case '2':
            Trenutni=PromjeniDirektorij(Trenutni);
            break;
        case '3':
            IspisDirektorij(Trenutni);
            break;
        case '4':
            Trenutni=cdt(Stog);
            break;
        case 'k':
			break;
        case 'K':
            break;
        default:
            break;
        }
    }
    return 0;
}

PozicijaD cdt(PozicijaS Stog)
{
    PozicijaD temp1=NULL;
    PozicijaS temp2=NULL;

    temp1=StvoriNoviD();

    temp2=Stog->NextS;
    temp1=temp2->Podatci;
    Stog->NextS=temp2->NextS;
    free(temp2);

    return temp1;
}

int IspisDirektorij(PozicijaD P)
{
    int BrojDirektorija=0;

    if(P==NULL)	 printf("Nema Root direktorija!");

    printf("Direktorij %s:\n",P->Ime);

    P=P->Osoba;

    if(P==NULL) return 1;

    while(P!=NULL)
    {
        printf(" %s\n",P->Ime);
        P=P->NextD;
        BrojDirektorija++;
    }

    printf("%d je BrojDirektorija\n",BrojDirektorija);

    return 0;
}

PozicijaD Trazi(char* Ime,PozicijaD P)
{
    if(P==NULL)	 printf("Greska!");

    P=P->Osoba;

    while(P!=NULL&&strcmp(P->Ime,Ime)!=0)
			 P=P->NextD;

    if(P==NULL)		printf("Trazeni direktorij nije pronaden!");

    return P;
}

PozicijaD PromjeniDirektorij(PozicijaD P)
{
    PozicijaD temp=NULL;
    char ImeDirektorija[20];

    temp=StvoriNoviD();

    printf("Unesite ime zeljenog direktorija:");
    scanf(" %s",ImeDirektorija);

    temp=Trazi(ImeDirektorija,P);

    return temp;
}

int UnesiPodatke(PozicijaD P)
{
    printf("Unesite ime direktorija:\n");

    scanf(" %s",P->Ime);

    return 0;
}

int Push(PozicijaS Stog,PozicijaD P)
{
    PozicijaS temp=NULL;

    temp=StvoriNoviS();

    temp->Podatci=P;
    temp->NextS=Stog->NextS;
    Stog->NextS=temp;

    return 0;
}

PozicijaS StvoriNoviS()
{
    PozicijaS Novi=NULL;
    Novi=(PozicijaS)malloc(sizeof(struct Stog));

    if(Novi==NULL)	 printf("Greska pri alokaciji memorije!");

    Novi->NextS=NULL;
    Novi->Podatci=NULL;

    return Novi;
}

int StvoriDirektorij(PozicijaD P,PozicijaS Stog)
{
    PozicijaD temp=NULL;
    if(P==NULL)	 printf("Nema Root direktorija!");

    Push(Stog,P);
    temp=StvoriNoviD();
    UnesiPodatke(temp);

    if(P->Osoba==NULL)
    {
           P->Osoba=temp;
           return 0;
    }

    P=P->Osoba;

    while(P->NextD!=NULL)
		    P=P->NextD;

    temp->NextD=P->NextD;
    P->NextD=temp;

    return 0;
}

PozicijaD StvoriNoviD()
{
    PozicijaD Novi=NULL;
    Novi=(PozicijaD)malloc(sizeof(struct Direktorij));

    if(Novi==NULL)	 printf("Greska pri alokaciji memorije!");

    Novi->NextD=NULL;
    Novi->Osoba=NULL;

    return Novi;
}
