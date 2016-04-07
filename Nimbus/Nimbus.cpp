# include <fstream>
# include <iostream>
# include <algorithm>

struct intervallo {
	int inizio, fine;
};

bool controllo( const intervallo &a, const intervallo int &b) {
	return a.fine < b.fine;
}

int n;
intervallo giri[1000];

int main()
{
	ifstream in("input.txt");
	ofstream on("output.txt");
	in >> N;
	for( i=0; i<n; i++) 
	    in >> giri[i].inizio >> giri[i].fine;
	    
	sort(giri, giri+n, controllo)
	
	int fine_attuale

}
