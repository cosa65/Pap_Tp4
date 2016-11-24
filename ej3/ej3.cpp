#include <iostream>

sruct Position {
	int x, y;
};



int main() {

	int H, E;
	cin >> H >> E;

	vector<Position> historicos(H), enemigos(E);

	for (int i = 0; i < H; i++) {
		cin >> historicos[i].x >> historicos[i].y;
	}

	for (int i = 0; i < H; i++) {
		cin >> enemigos[i].x >> enemigos[i].y;
	}

	return 0;
}