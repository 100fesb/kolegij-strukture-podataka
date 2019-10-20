<<<<<<< HEAD
﻿/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, 
tj. koliko ima studenata zapisanih u datoteci. Nakon toga potrebno je 
dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) 
i učitati iz datoteke sve zapise. Na ekran ispisati ime, prezime,apsolutni 
i relativni broj bodova. Napomena: Svaki redak datoteke sadrži ime i 
prezime studenta, te broj bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100 */
=======
/*
Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

#define _CRT_SECURE_NO_WARNINGS

#define BUFFER_LEN 1024
#define MAX_PATH 1025
#define NAME_BUFFER_LENGTH 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _student _STUDENT;
typedef struct _student* _pstud;

struct _student
{
	char ime[NAME_BUFFER_LENGTH];
	char prezime[NAME_BUFFER_LENGTH];
	int bodovi;
};


int CountRecords(char*);
int ReadRecords(int, _pstud, char*);
int PrintRecords(int, _pstud, int);

int main()
{

	char* fileName = NULL;
	int lineN = 0;
	_pstud popis = NULL;
	int maxPoints = 0;

	fileName = (char*)malloc(sizeof(char) * MAX_PATH);
	if (fileName == NULL){
		printf("Greska prilikom alokacije buffera za file :(((");
		return -1;
	}

	printf("Unesite ime datoteke: ");
	scanf(" %s", fileName);

	lineN = CountRecords(fileName);

	if (lineN > 0)
	{
		printf("Izbrojeno %d zapisa.", lineN);
		popis = (_pstud)malloc(sizeof(_STUDENT) * lineN);
		if (popis == NULL){
			printf("Greska prilikom alokacije popisa studenata :(");
			return -1;
		}

		maxPoints = ReadRecords(lineN, popis, fileName);
		printf("\nMaksimalni broj bodova: %d", maxPoints);

		PrintRecords(lineN, popis, maxPoints);
	}
	else {
		printf("Nema zapisa u datoteci.");
	}





	return 0;
}

int CountRecords(char* fName)
{
	FILE* fp = NULL;
	char* buff = NULL;
	int n = 0;

	fp = fopen(fName, "r");
	if (fp == NULL){
		printf("Nije bilo moguce otvoriti datoteku '%s'. Provjerite tocnost unosa.", fName);
		return -1;
	}
	buff = (char*)malloc(sizeof(char) * BUFFER_LEN);
	if (buff == NULL){
		printf("Greska prilikom alokacije buffera :((");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buff, BUFFER_LEN, fp);
		n++;
	}

	fclose(fp);
	return n;
}

int ReadRecords(int n, _pstud P, char* fName)
{
	FILE* fp = NULL;
	char* buff = NULL;
	int maxP = 0;

	fp = fopen(fName, "r");
	if (fp == NULL){ 
		printf("Nije bilo moguce otvoriti datoteku '%s'. Provjerite tocnost unosa.", fName);
		return -1;
	}
	
	buff = (char*)malloc(sizeof(char) * BUFFER_LEN);
	if (buff == NULL){
		printf("Greska prilikom alokacije buffera :((");
		return -1;
	}
	
	while (!feof(fp))
	{
		fgets(buff, BUFFER_LEN, fp);
		sscanf(buff, "  %d %s %s", &P->bodovi, P->ime, P->prezime);

		if (P->bodovi > maxP)
			maxP = P->bodovi;
		P++;
	}

	fclose(fp);
	return maxP;
}

int PrintRecords(int n, _pstud P, int maxPoint)
{
	int i = 0;
	printf("\nNova tablica ucenika glasi:\n\n\t\t%15s %15s %4s %4s", "Ime", "Prezime", "Aps bodovi", "Relativni bodovi");
	for (i = 0; i < n; i++)
	{
		printf("\n\t\t%15s %15s %5d %8d/%d = %6.2f", P->ime, P->prezime, P->bodovi, P->bodovi, maxPoint, ((float)P->bodovi / maxPoint) * 100);
		P++;
	}

	return 0;
}
>>>>>>> 6cdc4fbbd5efa425d3506fc3df6a1acc25691820
 