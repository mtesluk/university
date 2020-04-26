#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include"funkcje.h"     

int czytaj(FILE *plik_we, t_obraz *obraz) {
	
  char buf[DL_LINII];    /*bufor pomocniczy do liczby magicznej*/     
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;



  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || koniec) {  /* Czy jest magiczne "P"? */
    fprintf(stderr,"Blad: To nie jest plik PGM ani PPM\n");
    return(0);
  }

  obraz->typ=atoi(&(buf[1]));

 if ( obraz->typ!=2 && (obraz->typ!=3)) {  /* Czy jest magiczne "P2 lub P3"? */
    fprintf(stderr,"Blad: To nie jest plik PGM ani PPM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */



  /* Pobranie wymiarow obrazu i liczby odcieni szarosci/kolorow */
  if (fscanf(plik_we,"%d %d\n%d",&(obraz->wymx),&(obraz->wymy),&(obraz->szarosci))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci/kolorow\n");
    return(0);
  }


  /* Pobranie obrazu i zapisanie w tablicy piksele*/
 if(obraz->typ==2){
  obraz->piksele = malloc(obraz->wymx*obraz->wymy*sizeof(int));
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;

  for (i=0;i<obraz->wymy;i++) 
    for (j=0;j<obraz->wymx;j++) 
      fscanf(plik_we,"%d",&(piksele[i][j]));}

  /* Pobranie obrazu i zapisanie w tablicy red, green, blue*/
 if(obraz->typ==3){
  obraz->red = malloc(obraz->wymx*obraz->wymy*sizeof(int));
  int (*red)[obraz->wymx];         
  red=(int(*)[obraz->wymx]) obraz->red;

  obraz->green = malloc(obraz->wymx*obraz->wymy*sizeof(int));
  int (*green)[obraz->wymx];         
  green=(int(*)[obraz->wymx]) obraz->green;

  obraz->blue = malloc(obraz->wymx*obraz->wymy*sizeof(int));
  int (*blue)[obraz->wymx];         
  blue=(int(*)[obraz->wymx]) obraz->blue;

  for (i=0;i<obraz->wymy;i++)
    for (j=0;j<obraz->wymx;j++){
      fscanf(plik_we,"%d",&(red[i][j]));
      fscanf(plik_we,"%d",&(green[i][j]));
      fscanf(plik_we,"%d",&(blue[i][j]));}}

	
	
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

int negatyw(t_obraz *obraz){
  int i,j;
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    {
    for(j=0;j<obraz->wymx;j++)piksele[i][j]=obraz->szarosci-piksele[i][j];
    }
}

int konturowanie(t_obraz *obraz){
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++)
      {      piksele[i][j]=(abs(piksele[i+1][j]-piksele[i][j])+abs(piksele[i][j+1]-piksele[i][j]))/2;}
}

int rozmywaniepoziome(t_obraz *obraz, int sr){ /*sk= skala rozmycia*/
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++)
      {      piksele[i][j]=((piksele[i-sr][j])+(piksele[i][j])+(piksele[i+sr][j]))/3;}
}

int rozmywaniepionowe(t_obraz *obraz, int sr){   /*sk= skala rozmycia*/
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++)
      {      piksele[i][j]=((piksele[i][j-sr])+(piksele[i][j])+(piksele[i][j+sr]))/3;}
}

int progowanie(t_obraz *obraz,int prog){
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++){
      if(piksele[i][j]<=(obraz->szarosci*prog/100)) piksele[i][j]=0;
      else piksele[i][j]=obraz->szarosci;}}
}

int progowaniebieli(t_obraz *obraz,int prog){
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++){
      if(piksele[i][j]>(obraz->szarosci*prog/100)) piksele[i][j]=obraz->szarosci;
      }}
}

int progowanieczerni(t_obraz *obraz,int prog){
  int i,j;
 
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++){
      if(piksele[i][j]<=(obraz->szarosci*prog/100)) piksele[i][j]=0;
	
      }}
}

int rozciaganie(t_obraz *obraz){
  int i,j,lmax,lmin;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  lmax=0 ;
  lmin=obraz->szarosci ;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++)
	{
	if(piksele[i][j]>lmax) lmax=piksele[i][j];		
	if(piksele[i][j]<lmin && piksele[i][j]!=0) lmin=piksele[i][j];
	}          

  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++)
	piksele[i][j]=((piksele[i][j]-lmin)*(obraz->szarosci)/(lmax-lmin));
}

int korekcjagamma(t_obraz *obraz,float gamma){
  int i,j; float x,a,b;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++){
       a =(float)piksele[i][j]/obraz->szarosci;
	b=1/gamma;
      x=pow(a,b);
      piksele[i][j]= x*(obraz->szarosci);
      }
}

int zmianapoziomow(t_obraz *obraz,int biel, int czern){
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  for(i=0;i<obraz->wymy;i++)
    for(j=0;j<obraz->wymx;j++){
      if(piksele[i][j]<=(obraz->szarosci*czern/100)) piksele[i][j]=0;
      else if(piksele[i][j]>=(obraz->szarosci*biel/100)) piksele[i][j]=obraz->szarosci;
      else  {(piksele[i][j]-(obraz->szarosci*czern/100))*obraz->szarosci/((obraz->szarosci*biel/100)-(obraz->szarosci*czern/100));}
      }
}

int konwersjaszarosci(FILE *plik_wy,t_obraz *obraz){
    int i,j;
    
    int (*red)[obraz->wymx];         
    red=(int(*)[obraz->wymx]) obraz->red;
    int (*green)[obraz->wymx];         
    green=(int(*)[obraz->wymx]) obraz->green;
    int (*blue)[obraz->wymx];         
    blue=(int(*)[obraz->wymx]) obraz->blue;         
    
	fprintf(plik_wy,"P2\n");
	fprintf(plik_wy,"%d %d\n%d\n",obraz->wymx,obraz->wymy,obraz->szarosci);
    for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++){
        fprintf(plik_wy,"%d ", (red[i][j]+green[i][j]+blue[i][j])/3);}
	fprintf(plik_wy,"\n");} 
free(red);free(green);free(blue);
}

int zapisz(FILE *plik_wy, t_obraz *obraz)
{
  int i,j;
  
  int (*piksele)[obraz->wymx];         
  piksele=(int(*)[obraz->wymx]) obraz->piksele;
  int (*red)[obraz->wymx];         
  red=(int(*)[obraz->wymx]) obraz->red;
  int (*green)[obraz->wymx];         
  green=(int(*)[obraz->wymx]) obraz->green;
  int (*blue)[obraz->wymx];         
  blue=(int(*)[obraz->wymx]) obraz->blue;

if(obraz->typ==2){
  fprintf(plik_wy,"P2\n");
  fprintf(plik_wy,"%d %d\n%d\n",obraz->wymx,obraz->wymy,obraz->szarosci);
  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++) fprintf(plik_wy,"%d ", piksele[i][j]);
  fprintf(plik_wy,"\n");} 
free(piksele);}

else if(obraz->typ==3){
  fprintf(plik_wy,"P3\n");
  fprintf(plik_wy,"%d %d\n%d\n",obraz->wymx,obraz->wymy,obraz->szarosci);
  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++)
fprintf(plik_wy,"%d %d %d ", red[i][j],green[i][j],blue[i][j]); 
  fprintf(plik_wy,"\n");}

free(red);
free(blue);
free(green);
}}

/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}
