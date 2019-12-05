
/*
11. Napisati kod koji za zadane podatke studenata (matični broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
ključ računa da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim računa
ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Studenti s istim
ključem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem ključu se nalaze
koji podaci) te ponuditi mogućnost da se za određenog studenta (prezime i ime) ispiše
njegov matični broj.
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



#define BUFFER_LENGTH 1024
#define N_LENGTH 1024
#define ERROR -1
#define SUCCESS 0

typedef struct Student* Pozicija;
typedef struct Student* Lista;
typedef struct hashTablica* hashTab;

struct Student{
	int maticniBroj;
	char ime[N_LENGTH];
	char prezime[N_LENGTH];
	Pozicija Next;
};

struct hashTablica{
	int velicinaTablice;
	Lista *hashLista; // zasto pokazivac na pokazivac? jer je hashLista zapravo polje pokazivaca na strukture tipa Student
};

//int StvoriNovogStud(Pozicija);
int CitajIzDat(Pozicija);
Pozicija StvoriNovogS();
int TESTIspisVezaneListe(Pozicija);
int IzracunajHashKljuc(char*, int);
hashTab InicijalizacijaTablice(int);
int UpisuHashTablicu(Pozicija, hashTab);
int IspisHashTablice(hashTab);
int IspisPojedinacnogStudenta(hashTab);
Pozicija TraziStudentaPoMatBr(hashTab, int);

int main()
{
	struct Student HeadS;
	hashTab HeadT;
	int hashZbroj = 0;
	int velicinaTablice = 11;
	char *V = "Mateafff"; // testna varijabla - brisat cemo

	HeadS.Next = NULL; // head liste studenti - lista koja se cita iz file-a

	if (CitajIzDat(&HeadS) == -1){ // ako nije nadjena datoteka - da ne nastavlja sa programom
		system("pause");
		return ERROR;
	}


	HeadT = InicijalizacijaTablice(velicinaTablice); // HeadT pokazuje na 0-ti element polja pokazivaca na liste studenti

	UpisuHashTablicu(HeadS.Next, HeadT); // upisuje sve elemente koristeci listu stvorenu u funkciji CitajIzDat - upisuje u odgovarajuce elemente hash tablice

	IspisHashTablice(HeadT);

	IspisPojedinacnogStudenta(HeadT);

	/*Ispis(HeadS.Next);*/
	system("pause");
	return 0;
}

Pozicija StvoriNovogS()
{
	Pozicija P = NULL;
	P = (Pozicija)malloc(sizeof(struct Student));
	return P;
}

hashTab InicijalizacijaTablice(int velicinaTablice)
{
	hashTab H = NULL; // stvaramo head element za strukturu tipa hashTablica, zato dolje ide malloc sa sizeof te strukture(hashTablica) -> (a ne velicina tablice)
	int i = 0;

	H = (hashTab)malloc(sizeof(struct hashTablica));
	if (!H) return ERROR;

	H->velicinaTablice = velicinaTablice;

	H->hashLista = (Lista *)malloc(sizeof(Lista)*velicinaTablice); // alociramo prostor za cijelu tablicu (nama 11 mjesta)
	if (!H->hashLista) return ERROR;

	for (i = 0; i < velicinaTablice; i++)
	{
 		H->hashLista[i] = NULL;
   	}

	return H;
}


int IzracunajHashKljuc(char *rijec, int velicinaTab)
{
	int hashZbroj = 0;
	int i = 0;

	// algoritam za kljuc 
	// vrlo jednostavan - zbroji ASCII vrijednosti prvih 5 znakova (zadano je 5) prezimena datog studenta i sa return vraca zadnju znamenku zbroja (modulo 10) to nam je kljuc za 1 element
	for (i = 0; i < 5; i++)
		hashZbroj += rijec[i];

	return hashZbroj % velicinaTab;
}


int CitajIzDat(Pozicija P) {

	Pozicija q = NULL, temp = P; // temp mi sluzi da izbjegnem jednu while petlju -> da zapamti zadnji element i doda na njega - pri tome ne dira Head	
	char* fileName = NULL;
	FILE* fp = NULL;

	fileName = (char*)malloc(sizeof(char)* BUFFER_LENGTH);



	if (!fileName){
		printf("Greska prilikom alokacije!\n");
		return ERROR;
	}

	printf("\nUnesite datoteku za citanje: ");		
	scanf(" %s", fileName);		

	fp = fopen(fileName, "r");		
	if (!fp){
		printf("\nDatoteka nije otvorena!\n");
		return ERROR;
	}

	// kao i ranije, stvaramo vezanu listu svih studenata, generiranu iz datoteke
	while (!feof(fp)) {	
		q = StvoriNovogS();
		fscanf(fp, " %d %s %s", &q->maticniBroj, q->ime, q->prezime);
		q->Next = temp->Next;
		temp->Next = q;

		temp = temp->Next;

	}
	fclose(fp);		

	return 0;		
}

int UpisuHashTablicu(Pozicija P, hashTab H)
{
	int i = 0, kljuc;
	int velTab = H->velicinaTablice;
	Pozicija temp = NULL; // stvaramo temp pokazivac jer triba listu stvorenu iz citanja file-a izbrisat, pa da ne minjamo pokazivace originala

	while (P != NULL){
		
		
		kljuc = IzracunajHashKljuc(P->prezime, velTab);

		// ako vec postoji student s istim kljucem - radi novu vezanu listu
		if (H->hashLista[kljuc] != NULL)
			H->hashLista[kljuc]->Next = P;
		else
			H->hashLista[kljuc] = P;

		// zasto temp? objasnjeno gore
		temp = StvoriNovogS();
		temp = P;
		P = P->Next;
		temp->Next = NULL;
	}
	/*for (i = 0; i < velTab; i++){
		P = (Pozicija)malloc(sizeof(struct Student));
		P->maticniBroj = i;
		H->hashLista[i] = P;
	}*/
}

// testna funkcija za ispis svih maticnih brojeva u vezanoj listi svih studenata - brisat za kraj
int TESTIspisVezaneListe(Pozicija P)
{

	if (!P) return ERROR;

	

	printf("Maticni brojevi:\n");

	while (P != NULL) {
		printf("%d\n", P->maticniBroj);
		P = P->Next;
	}

	return SUCCESS;

}

int IspisHashTablice(hashTab H)
{
	int i = 0;
	int firstInstance = 0;
	int velTab = H->velicinaTablice;
	Pozicija P = NULL;
	P = StvoriNovogS();

	if (!H) return ERROR;

	printf("\n\n\t%10s %10s %10s %10s\n", "Br. kljuca", "Maticni br.", "Prezime", "Ime");

	for (i = 0; i < velTab; i++)
	{
		if (H->hashLista[i] == NULL) continue; // ako nema studenta za pojedini kljuc, vrti opet petlju za iduci kljuc
		else {
			P = H->hashLista[i];
			while (P != NULL){
				printf("\t%10d %10d %10s %10s\n", i, P->maticniBroj, P->prezime, P->ime);
				P = P->Next;
			}
		}
	}

	printf("\n\n");

	return SUCCESS;
}

int IspisPojedinacnogStudenta(hashTab H)
{
	char unos[64];
	int unosINT = 0;
	Pozicija P = StvoriNovogS();

	while(1){
		printf("Unesite maticni broj trazenog studenta ili 0 za izlaz: ");
		scanf("%s", unos);

		if (isdigit(unos[0]) == 0) continue; // provjera ako nije unesen broj - ponavljanje petlje

		unosINT = atoi(unos);
		if (unosINT == 0) break; // izlazak iz petlje kad korinik odabere 0

		P = TraziStudentaPoMatBr(H, unosINT);

		if (!P) printf("Nismo nasli studenta s tim maticnim brojem!\n");

		printf("Trazeni student s maticnim brojem [%s] je: %s %s\n\n", unos, P->prezime, P->ime);

	} 
	printf("\n\n");
}
	
Pozicija TraziStudentaPoMatBr(hashTab H, int unos)
{
	int velTab = H->velicinaTablice;
	int i = 0;
	Pozicija P = NULL;

	P = StvoriNovogS();

	for (i = 0; i < velTab; i++)
	{
		if (H->hashLista[i] == NULL) continue;
		else {
			P = H->hashLista[i];
			while (P != NULL){
				if (P->maticniBroj == unos){
					return P;
				}
				P = P->Next;
			}
		}
	}

	return NULL;
}