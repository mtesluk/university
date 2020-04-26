typedef struct element { 
	int dana;
	struct element *nast;
} t_elem;

int push(t_elem **lista,int wartosc);
int pop(t_elem **lista, int *wartosc);
int empty(t_elem **lista);
int print(t_elem **lista);
void inicjuj(t_elem **lista);


