#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funkcje.h"

/******************************************************************/
int push(t_elem **lista,int wartosc) {
	/*PRE:zainicjowany stos
	  POST:	stos z elementem na szczycie*/

	t_elem *pom;

	pom=(t_elem*)malloc(sizeof(t_elem));
	pom->dana=wartosc;
	pom->nast=*lista;			
	*lista=pom;
	return 0;
}
/******************************************************************/
int pop(t_elem **lista,int *wartosc) {
	/*PRE:zainicjowany stos
	  POST:	zdjety element ze stosu*/


	t_elem *pom;

	if (*lista==NULL) fprintf(stderr,"Stos pusty");
	else {
		pom=(*lista)->nast;
		*wartosc=(*lista)->dana;
		free(*lista);
		*lista=pom;
		return 0;
	}
}

/******************************************************************/
int print(t_elem **lista) {
	/*PRE:zainicjowany stos
	  POST:	wyswietlenie elementow stosu*/


	t_elem *elem;
	
	elem=*lista;
	
	while (elem!=NULL) {
		printf("%d ", elem->dana);
		elem=elem->nast;
	}	
	printf("\n");
	
}	

/*****************************************************************/
int empty(t_elem **lista) {
	/*PRE:zainicjowany stos
	  POST:	wyswietlenie ilosci elementow na stosie*/

	int licz;
	t_elem *elem;
	
	if (*lista==NULL)	
		return 0;
	elem=*lista;
	for(licz=0;elem!=NULL;licz++)
		elem=elem->nast;
	return licz;
}
/*****************************************************************/
void inicjuj(t_elem **lista){
	/*PRE:zdeklarowana zmienna
	  POST:	zainicjowany stos*/
	*lista=NULL;}
/*******************************************************************/
