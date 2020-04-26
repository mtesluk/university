#define MAX 512            
#define DL_LINII 1024  
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

typedef struct {	/*struktura do flag*/
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,progowaniebieli,konturowanie,rozciaganie,wyswietlenie;
  int progowanieczerni,korekcjagamma,zmianapoziomow,rozmywaniepoziome,rozmywaniepionowe;  
  int w_progu; float w_gamma;
  int w_bieli, w_czerni, w_sr;
} w_opcje;    




typedef struct {
  int wymx, wymy, szarosci;
  void *piksele;
  void *red, *green, *blue;
  int typ;
} t_obraz;



int czytaj(FILE *plik_we, t_obraz *obraz); 
int negatyw(t_obraz *obraz);
int konturowanie(t_obraz *obraz);
int rozmywaniepoziome(t_obraz *obraz,int sr);
int rozmywaniepionowe(t_obraz *obraz, int sr);
int progowanie(t_obraz *obraz,int prog);
int progowaniebieli(t_obraz *obraz,int prog);
int progowanieczerni(t_obraz *obraz,int prog);
int rozciaganie(t_obraz *obraz);
int zmianapoziomow(t_obraz *obraz, int biel, int czern);
int korekcjagamma(t_obraz *obraz, float gamma);
int konwersjaszarosci(FILE *plik_wy,t_obraz *obraz);
int zapisz(FILE *plik_wy, t_obraz *obraz);
void wyswietl(char *n_pliku) ;
void wyzeruj_opcje(w_opcje * wybor) ;
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);
