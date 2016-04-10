# include <algorithm>
# include <numeric>
# include <iostream>
# include <string>
# include <iterator>
# include <stdio.h>
# include <vector>

using namespace std;

int main() {

	// Input/output da/su file
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N;
	string segni;
	cin >> N >> segni;
	vector <int> permutazione(N);

	// permutazione = {1, 2, 3, ...}
	iota(permutazione.begin(), permutazione.end(), 1);

	do {
		bool rispetta = true;
		// Verifica che tutti i segni siano rispettati
		for (int i = 0; i < N - 1; i++) {
			if (segni[i] == '<') {
				rispetta &= (permutazione[i] < permutazione[i + 1]);
			} else {
				rispetta &= (permutazione[i] > permutazione[i + 1]);
			}
		}

		if (rispetta) {
			// Stampa gli elementi della permutazione (separati da spazio)
			copy(permutazione.begin(), permutazione.end(),
			ostream_iterator <int> (cout, " "));
			cout << endl;
			// Ci basta una sola soluzione
			break;
		}
	} while (next_permutation(permutazione.begin(), permutazione.end()));
}
