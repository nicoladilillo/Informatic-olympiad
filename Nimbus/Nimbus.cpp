# include <fstream>
# include <iostream>
# include <algorithm>

using namespace std;

struct intervallo {
	int inizio, fine;
};

bool controllo(intervallo a, intervallo b) {
		return a.fine < b.fine;
}

int n;
intervallo giri[1000];

main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> n;
	for(int i=0; i<n; i++) 
	    in >> giri[i].inizio >> giri[i].fine;
	    
	sort(giri, giri+n, controllo);
	
	int fine_attuale = giri[0].inizio;
	int caramelle = 1;
	for (int i=1; i<n; i++)
	{
		if (fine_attuale < giri[i].inizio)
		{
			fine_attuale = giri[i].fine;
			caramelle++;
		}
	}

	out << caramelle << endl;
	return 0;

}
