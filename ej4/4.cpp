#include <iostream>
#include <vector>

using namespace std;

int calcularciclo(int i, vector<int>& perm, vector<bool>& visited) {
	int largo = 0;
	int next = i;
	do {
		visited[next] = 1;
		next = perm[next];
		largo++;
	} while (next != i);
	return largo;
}

int mcd(int a, int b) {
	return (a == 0 ? b : mcd(b % a, a));
}

int main() {
	int n;
	cin >> n;
	vector<int> perm(n);
	for (int i = 0; i<n; i++) {
		cin >> perm[i];
		perm[i]--;
	}
	
	// Recorro el grafo calculando el largo de los ciclos
	vector<bool> visited(n);
	vector<int> ciclos;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) ciclos.push_back(calcularciclo(i, perm, visited));
	}

	//Si hay un ciclo par, la respuesta es 0. Si no, es el mcd de todos con todos o algo así
	int exp = 0;
	for (int i = 0; i < ciclos.size(); i++) {
		if (ciclos[i] % 2 == 0) {
			cout << 0 << endl;
			return 0;
		}
		exp += ciclos[i] / 2; 
		for (int j = i + 1; j < ciclos.size(); j++) {
			exp += mcd(ciclos[i], ciclos[j]);
		}
	}

	// La respuesta es 2^exp mod 10⁹ + 7
	int res = 1;
	for (int i = 0; i < exp; i++) {
		res <<= 1;
		res %= 1000000007;
	}
	cout << res << endl;
}
