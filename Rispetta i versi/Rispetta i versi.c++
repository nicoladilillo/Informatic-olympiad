#include <stdio.h>
#include <iostream>
#include <string>

int main() {
	// Input/output da/su file
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	unsigned N;
	std::string segni;
	std::cin >> N >> segni;
	unsigned min = 1, max = N;
	for (unsigned i = 0; i < N - 1; i++) {
		if (segni[i] == '<') {
			std::cout << min << " ";
                        min++;
		}
		else {
			std::cout << max << " ";
  			max--;
		}
	}
	std::cout << min << std::endl;
}

