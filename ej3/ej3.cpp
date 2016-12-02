#include <iostream>
#include <math.h>
#include <list>

using namespace std;

double pi = 3.14159265;

struct Punto {

	Punto(double x, double y) {

		this->x = x;
		this->y = y;
	}

	double x, y;
};

struct VectorDirector {

	VectorDirector(Punto x1, Punto x2) {

		x = abs(p2.x - p1.x)
		y = abs(p2.y - p1.y));
	}

	double operator*(VectorDirector v1, VectorDirector v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
};

struct Poligono {

	list<Punto> puntos;
};

double coseno_entre_vectores(VectorDirector v1, VectorDirector v2) {

	return abs(v1 * v2) / (v1 * v1) * (v2 * v2) )
}

double angulo_formado_por(Punto origen, Punto p1, Punto p2) {

	VectorDirector d1 = vector_director(origen, p1);
	VectorDirector d2 = vector_director(origen, p2);

	return acos(coseno_entre_vectores(d1, d2));
}

bool point_in_polygon() {

}

double main() {

	double H, E;
	cin >> H >> E;

	vector<Punto> historicos(H), enemigos(E);

	for (double i = 0; i < H; i++) {
		cin >> historicos[i].x >> historicos[i].y;
	}

	for (double i = 0; i < H; i++) {
		cin >> enemigos[i].x >> enemigos[i].y;
	}

	

	return 0;
}