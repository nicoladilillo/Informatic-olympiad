#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list> // list
#define MAXNODI 100001
// N.B. Si ipotizza che i nodi del grafo siano numerati a partire da 1: si "sacrifica" la prima posizione nei vettori lasciandola inutilizzata 
// e facendo partire i cicli da 1, se invece la numerazione dei nodi del grafo prevede il nodo 0 occorre modificare i cicli nel programma!
using namespace std;

struct arc {
	int v; // nodo adiacente
	int w; // peso dell'arco
};

int d[MAXNODI]; // distanze minime dal nodo di partenza verso ciascun nodo. 
			    // Per es. d[z] e' la distanza minima per raggiungere il nodo z partendo dal nodo di partenza x
int u[MAXNODI]; // nodo di provenienza di ciascun nodo nel percorso migliore al momento trovato
				// Per es. u[z] è il nodo da cui giungere a z (con peso d[z]) nel percorso più conveniente trovato
bool v[MAXNODI]; // booleano per indicare se il nodo z è passato in S, ovvero l'insieme dei nodi visitati
				 // Per es. v[z] sara' true se z è un nodo visitato, false altrimenti
				 
list <arc> adiacenti[MAXNODI]; // nodi adiacenti ciascun nodo con i rispettivi pesi: 
							   // Per es. la lista adiacenti[z] include tutti i nodi adiacenti a z (ovvero direttamente raggiungibili dal nodo z)

int n;  // numero totale nodi 
int nA; // numero archi
int x; // nodo di partenza 
int y; // nodo di arrivo

FILE *fin,*fout;

int main() {
  fin=fopen("input.txt","r");
  fout=fopen("output.txt","w");
  int i,da; // i: indice cicli,   da: nodo di inizio arco
  struct arc arco; // arco da aggiungere nella lista di adiacenza del nodo da (inizio arco)
  
  fscanf(fin,"%d%d%d%d",&n,&nA,&x,&y);  // n: numero nodi,  nA: numero archi,  x: nodo di partenza,  y: nodo di arrivo
//  printf("Letti:  %d %d %d %d \n",n,nA,x,y); // da cancellare (debug)
  // inizializzazione vettori distanze e booleani (nodi visitati)
  for(i=1; i<=n; i++) {
  	 d[i]=INT_MAX; // distanza minima per raggiungere i da x (all'inizio infinito)
  	 u[i]=-1; // nodo di provenienza ideale indefinito
  	 v[i]=false; // nodo non ancora visitato
  } 
  
  // caricamento grafo 
  for(i=0;i<nA;i++) {
	  fscanf(fin,"%d%d%d",&da,&arco.v,&arco.w); // da: nodo inizio arco,   arco.v: nodo fine arco,   arco.w: peso arco
//  	  printf("dal nodo %5d al nodo %5d con peso %2d\n",da,arco.v,arco.w); // da cancellare (debug)
	  adiacenti[da].push_back(arco);
	  // N.B. se l'arco è monodirezionale (grafo orientato) commentare le seguenti istruzioni
	  int a=arco.v;
	  arco.v=da;
	  adiacenti[a].push_back(arco);
  }
 
  // 1. Inizializzazione dell'algoritmo di Dijkstra
  d[x]=0; // nodo di partenza
  v[x]=true; // visitato
  for (list <arc>::iterator it = adiacenti[x].begin(); it!=adiacenti[x].end(); it++) {
  	  d[it->v]=it->w; // distanza minima per giungere al nodo (it->v)
  	  u[it->v]=x; // nodo di provenienza x per il nodo (it->v)
//  	  printf("Aggiunto nodo adiacente a x; %d con peso %2d\n",it->v,d[it->v]); // da cancellare (debug)
  }

  int j, minD; // nodo: nodo da visitare,   minD: distanza minima tra i nodi da visitare
  while(1) {
	   // 2. Assegnazione etichetta permanente
	  minD=INT_MAX;  // minima distanza iniziale impostata a infinito
	  for(i=1; i<=n; i++) {
		  if (!v[i] && d[i]<minD) {
		  	  j=i; // nuovo nodo con distanza minima
		  	  minD=d[j]; // nuova distanza minima;
//		  	  printf("Nuovo nodo con distanza minima: %d con peso %2d \n",j,d[j]); // da cancellare (debug)
		  }
	  } 
	   if(minD==INT_MAX) {  // nei nodi da visitare non esiste un nodo con cammino_minimo != infinito;
//		   printf("\n Uscita per mancanza nodi da visitare con peso_minimo diverso da infinito \n"); // da cancellare (debug)
		   break;
	   }
	   v[j]=true; // il nodo j passa tra i nodi visitati
//	   printf("\n Trasferito nodo %d dai non visitati ai visitati \n", j); // da cancellare (debug)
	   if (j==y) {
//		   printf("\n Uscita per trasferimento del nodo terminale y \n"); // da cancellare (debug)
	   	   break;
	   }
	   
	   // 3. Assegnazione etichetta provvisoria
	  for (list <arc>::iterator it = adiacenti[j].begin(); it!=adiacenti[j].end(); it++) {
//		  printf("\n ESAMINATO nodo %d adiacente a nodo %d \n",it->v,j); // da cancellare (debug)
	  	  if (d[it->v]>d[j]+it->w) { // se la distanza minima per giungere al nodo (it->v) va aggiornata passando per il nodo appena visitato j
	  	  	  d[it->v]=d[j]+it->w;	// si aggiorna la distanza minima del nodo (it->v)
			  u[it->v]=j; // si aggiorna il nodo di provenienza, ovvero j, per il nodo (it->v)
		  }
	  }

  }
  
   if(minD==INT_MAX)   // nei nodi da visitare non esiste un nodo con cammino_minimo != infinito;
//	   printf("\n Uscita per mancanza nodi da visitare con peso_minimo diverso da infinito \n"); // da cancellare (debug)
	   fprintf(fout,"NON CI SONO PERCORSI POSSIBILI DA X A Y");
   else{
//	   fprintf(fout,"%d",d[y]); // distanza percorso minimo per giungere al nodo y
	   fprintf(fout, "\n Percorso ottimale a ritroso: \n");
	   int b=y; // b: cursore che parte dal nodo di arrivo e va a ritroso
	   while( u[b]!=false ) {
	        fprintf(fout, "nodo: %d    distanza minima: %d \n",b,d[b]);
	        b = u[b];
	   }	
   }
  return 0;
}

