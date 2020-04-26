#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"funkcje.h"

int main(int argc, char ** argv) {
  t_obraz mainobraz;    /*definiowanie struktur*/
  w_opcje opcje;
  

  int prog,biel,czern,sr;  /*zmienne pomocnicze do funkcji*/
  float korekta;   /* sr = skala rozmycia */
  int wyb,wyb1;

  int odczytano = 0;
  FILE *plik;
  char nazwa[100];

if(argc>1)  printf("%d\n", przetwarzaj_opcje(argc,argv,&opcje));  /*flagi*/
else{	system("clear");     /*lub normalne menu*/
  do{
	printf("\n 1 - Wczytaj");
	printf("\n 2 - Edycja obrazu");
	printf("\n 3 - Zapisz i wyswietl");
	printf("\n 4 - Zapisz jako konwersja kolorowego obrazu do szarsci");  
	printf("\n 5 - Zapisz");
	printf("\n 6 - Wyswietl");
	printf("\n 0 - Wyjdz");
	printf("\n   Wybor: ");

    scanf("%d",&wyb);
    switch(wyb){
    case 1:   printf("Podaj nazwe pliku:");
    scanf("%s",nazwa);
    plik=fopen(nazwa,"r");
    if (plik != NULL) {       /* co spowoduje zakomentowanie tego warunku */
     odczytano = czytaj(plik,&mainobraz);
     fclose(plik);
     system("clear");
     printf("Wczytano %s!!!\n\n",nazwa);
     }break;

    case 2: {
  	system("clear");
	printf("\nEdycja obrazu:\n");
	printf("\t1 - Negatyw\n");
	printf("\t2 - Progowanie\n");
	printf("\t3 - Progowanie bieli\n");
	printf("\t4 - Progowanie czerni\n");
	printf("\t5 - Konturowanie\n");
	printf("\t6 - Rozciaganie histogramu\n");
	printf("\t7 - Korekcja gamma\n");
	printf("\t8 - Zmiana poziomow\n");
	printf("\t9 - Rozmywanie poziome\n");
	printf("\t10 - Rozmywanie pionowe\n");
	
	
	printf("\t Wybor: ");

	scanf("%d", &wyb1);
	switch(wyb1){  /* switch w switchu */

	case 1: 
	if(odczytano != 0){
      	negatyw(&mainobraz);
	system("clear");
      	printf("Negatyw- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 2: 
	if(odczytano != 0){
	printf("Podaj wartosc procentowa progu:");
      	scanf("%d", &prog);
      	progowanie(&mainobraz, prog);
	system("clear");
      	printf("Progowanie- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 3: 
	if(odczytano != 0){
	printf("Podaj wartosc procentowa progu:");
      	scanf("%d", &prog);
      	progowaniebieli(&mainobraz, prog);
	system("clear");
      	printf("Progowanie bieli- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 5: 
	if(odczytano != 0){
      	konturowanie(&mainobraz);
	system("clear");
      	printf("Konturowanie- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 6: 
	if(odczytano != 0){
      	rozciaganie(&mainobraz);
	system("clear");
      	printf("Rozciaganie histogramu- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 4: 
	if(odczytano != 0){
	printf("Podaj wartosc procentowa progu:");
      	scanf("%d", &prog);
      	progowanieczerni(&mainobraz, prog);
	system("clear");
      	printf("Progowanie czerni- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 7: 
	if(odczytano != 0){
	printf("Podaj wartosc korekty:");
      	scanf("%f", &korekta);
      	korekcjagamma(&mainobraz,korekta);
	system("clear");
      	printf("Korekta gamma- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 8: 
	if(odczytano != 0){
	printf("Podaj wartosc procentowa bieli:");
      	scanf("%d", &biel);
	printf("Podaj wartosc procentowa czerni:");
	scanf("%d", &czern);
      	zmianapoziomow(&mainobraz,biel,czern);
	system("clear");
      	printf("Zmiana poziomow- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 9: 
	if(odczytano != 0){
	printf("Podaj skale rozmycia(0,1,2):");
      	scanf("%d", &sr);
      	rozmywaniepoziome(&mainobraz,sr);
	system("clear");
      	printf("Rozmywanie poziome- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	case 10: 
	if(odczytano != 0){
      	printf("Podaj wartosc skali rozmycia(0,1,2):");
      	scanf("%d", &sr);
      	rozmywaniepionowe(&mainobraz,sr);
	system("clear");
      	printf("Rozmywanie pionowe- udalo sie!!!");}
      	else printf("Brak pliku!!!");
    	break;

	}break;


    case 5: 
    if(odczytano != 0) {
      printf("Podaj nazwe zapisywanego pliku:");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"w");
      zapisz(plik,&mainobraz);
      fclose(plik);
      system("clear");
      printf("Zapisano jako %s!!!\n\n",nazwa); }
    else printf("Blad\n");
    break;

    case 3: if(odczytano != 0){  /*zapisz i wyswietl*/
      printf("Podaj nazwe zapisywanego pliku:");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"w");
      zapisz(plik,&mainobraz);
      fclose(plik);
      system("clear");
      printf("Zapisano jako %s!!!\n\n",nazwa);
      wyswietl(nazwa);}
	break;

    case 6: if(odczytano != 0) wyswietl(nazwa);
    break;

    case 4: if(odczytano != 0){  /*konwersja kolorowego do szarego*/
	printf("Podaj nazwe zapisywanego pliku:");	
	scanf("%s",nazwa);
	plik=fopen(nazwa,"w");
      	konwersjaszarosci(plik,&mainobraz);
	fclose(plik);
	system("clear");
      	printf("Zapisano jak okonwersje szarosci!!!");
      	wyswietl(nazwa);}
    	break;

  
    case 0: system("clear");
	printf("Koniec programu!!!\n\n");
    break;
  	}}}while(wyb != 0);}




return 0;}


	
