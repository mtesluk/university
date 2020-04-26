#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"funkcje.h"     



void wyzeruj_opcje(w_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->negatyw=0;
  wybor->konturowanie=0;
  wybor->progowanie=0;
  wybor->wyswietlenie=0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

/************************************************************************/
/*            -w = wczytaj
/*            -z = zapisz
/*            -d = wyswietl
/*            -n = negatyw
/*            -k = konturowanie  
/*            -p = progowanie
/*            -b = progowanie bieli
/*            -c = progowanie czerni
/*            -l = zmiana poziomow
/*            -x = rozmywanie poziome
/*            -y = rozmywanie pionowe
/*            -g = korekcja gamma
/*            -r = rozciaganie
/*            -q = konwersja kolorowego do szarosci
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
  int i, prog,biel,czern,sr,plik; float gamma;
  char *nazwa_pliku_we, *nazwa_pliku_wy;
  t_obraz mainobraz;

  wyzeruj_opcje(wybor);
  wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
    case 'w': {                 /* opcja z nazwa pliku wejsciowego */
     if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_we=argv[i];
	if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
	 wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	else{                          /* otwieramy wskazany plik   */
	 wybor->plik_we=fopen(nazwa_pliku_we,"r");
		if (wybor->plik_we != NULL) {      
    		czytaj(wybor->plik_we,&mainobraz);
    		fclose(wybor->plik_we);
    	}}} 
      else 
	return B_BRAKNAZWY;                  
      break;
    }
    case 'z': {                 /* opcja z nazwa pliku wyjsciowego */
     if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	 wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
	zapisz(wybor->plik_wy,&mainobraz);
 	 fclose(wybor->plik_wy);
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'p': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowanie=1;
	  wybor->w_progu=prog;
	progowanie(&mainobraz, prog);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }
    case 'b': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu bieli */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowaniebieli=1;
	  wybor->w_progu=prog;
	progowaniebieli(&mainobraz, prog);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu bieli */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu bieli */
      break;
    }

    case 'c': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu czerni */
	if (sscanf(argv[i],"%d",&prog)==1) {
	  wybor->progowanieczerni=1;
	  wybor->w_progu=prog;
	progowanieczerni(&mainobraz, prog);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu czerni */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu czerni */
      break;
    }

    case 'l': {  
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc bieli */
	if (sscanf(argv[i],"%d",&biel)==1) {
	  wybor->zmianapoziomow=1;
	  wybor->w_bieli=biel;
	 czern = 40;
	zmianapoziomow(&mainobraz, biel,czern);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc bieli */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci bieli */
      break;
    }

    case 'n': {                 /* mamy wykonac negatyw */
     wybor->negatyw=1;
	negatyw(&mainobraz);
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
     wybor->konturowanie=1;
	konturowanie(&mainobraz);
      break;
    }

   case 'x': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc skali rozmycia */
	if (sscanf(argv[i],"%d",&sr)==1) {
	  wybor->rozmywaniepoziome=1;
	  wybor->w_sr=sr;
	rozmywaniepoziome(&mainobraz, sr);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc skali */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci skali */
      break;
    }
   
   case 'y': {  
      if (++i<argc) {  /* wczytujemy kolejny argument jako wartosc skali rozmycia */
	if (sscanf(argv[i],"%d",&sr)==1) {
	  wybor->rozmywaniepionowe=1;
	  wybor->w_sr=sr;
	rozmywaniepionowe(&mainobraz, sr);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc skali */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci skali */
      break;
    }

   

   case 'r': {                 /* mamy wykonac rozciaganie */
     wybor->rozciaganie=1;
	rozciaganie(&mainobraz);
      break;
    }

    case 'g': {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc gammy */
	if (sscanf(argv[i],"%f",&gamma)==1) {
	  wybor->korekcjagamma=1;
	  wybor->w_gamma=prog;
	korekcjagamma(&mainobraz, gamma);
	} else
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc gammy */
      } else 
	return B_BRAKWARTOSCI;             /* blad: brak wartosci gammy */
      break;
    }
    case 'd': {                 /* mamy wyswietlic obraz */
      wybor->wyswietlenie=1;
wyswietl(nazwa_pliku_wy);
      break;
    }
    case 'q': {                 /* opcja z nazwa pliku wyjsciowego */
     if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	nazwa_pliku_wy=argv[i];
	if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
	  wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	else                              /* otwieramy wskazany plik    */
	 wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
	konwersjaszarosci(wybor->plik_wy,&mainobraz);
 	 fclose(wybor->plik_wy);
      } else 
	return B_BRAKNAZWY;  }break;
    default:                    /* nierozpoznana opcja */
     return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}

