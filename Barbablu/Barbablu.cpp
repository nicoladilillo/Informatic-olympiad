#include <iostream>
#include <fstream>
#include <list>
#include <limits.h>
#include <algorithm>
#define MAX 1000

struct arc {
	int n;//nodo
	int w;//peso
};

int d[MAX];  //distanze minimine di ogni punto
int u[MAX];  //indica la sorgente del nodo
bool v[MAX]; //indica se il nodo è stato verificato

int respiro[MAX]; //valore che porta il conto dei metri fatti in apnea

int N;  //numero cabine
int M;  //numero corridoi
int C;  //cabina del tesoro
int K;  //numero cabine con sacca d'aria

bool aria[31];
std::list <arc> adiacenze[MAX]; //list di adiacenza

main() {
	//caricamento liste di adiacenza
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> N >> M >> C >> K;
	//std::cout << N  << ' ' << M << ' '  << C << ' '  << K;

	std::fill (d, d+N+1, INT_MAX);
	std::fill (u, u+N+1, -1);
	std::fill (v, v+N+1, false);
	
	int i;	
	//cabine con l'aria
	for ( i=1; i<=K; i++ ) {
		int p;
		in >> p;
		aria[p] = true;
		//std::cout << p << '\t';
	}

	int da;
	struct arc app;
	//lista di adiacenze
	for ( i=1; i<=M; i++ ) {
		in >> da >> app.n >> app.w;
		//std::cout << da  << ' ' << app.n << ' ' << app.w << '\t';
		adiacenze[da].push_back(app);
		//perchè il grafo non è orientato si eseguono le seguenti istruzioni
		int a = app.n;
		app.n = da;
		da = a;
		//std::cout << da << ' ' << app.n << ' ' << app.w << '\n';
		adiacenze[da].push_back(app);		
	}

	//inizializzazione
	d[1] = 0;
	v[1] = true;  //nodo di partenza

	int j = 1; //provenienza cammino minimo
	int minD;  //valore cammino minimo
	respiro[1] = 0;
	while ( true ) {
		//assegnazione etichette provvisorie
		for ( std::list <arc>::iterator it = adiacenze[j].begin(); it != adiacenze[j].end(); it++ ) { 
			if ( d[it->n]>(d[j]+it->w) || respiro[it->n]>20 ) {
				//std::cout << d[it->n] << '\t';
				d[it->n] = d[j]+it->w;
				//std::cout << d[it->n] << '\t';
				u[it->n] = j;
				//std::cout << u[it->n] << '\t';
			    respiro[it->n] = respiro[j] + it->w;
				//std::cout << "respiro " << respiro[it->n] << '\n';
			}
		} 

		minD = INT_MAX;
		//assegnazione etichetta permanente
		for ( i=1; i<=N; i++) { 
			if ( !v[i] && d[i]<minD && respiro[i]<=20 ) {
				if ( aria[i]==true ) {
					//std::cout << "ARIA AZZERATA NEL NODO " << i << '\n';
					respiro[i] = 0;
				}
				minD = d[i];
				j = i;
			}
		} 
		v[j] = true; //conferma etichetta permanente

		//termina while perchè siamo giunti a destinazione
		if ( j==C ) break;

		//termina while perchè è impossibile raggiungere la nostra destinazione
		if ( minD==INT_MAX ) break;

	}

	if ( minD==INT_MAX )
		out << -1 << std::endl;
	else
		out << d[C] << std::endl;


}
