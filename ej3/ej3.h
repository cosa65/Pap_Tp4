#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <set> 
using namespace std;


struct Punto {

	double x, y;

	Punto& operator=(Punto p){
		x = p.x; y = p.y;
	}

	bool operator==(const Punto &p) const{
		return x == p.x && y == p.y;
	}

	bool operator<(const Punto &p) const{
		if (x == p.x)
			return y < p.y;
		else
			return x < p.x;
	}

};

typedef  vector<Punto> Triangulo;

struct VectorDirector {

	double x, y;
	VectorDirector(Punto p1, Punto p2) {

		x = p2.x - p1.x;
		y = p2.y - p1.y;
	}

	double operator*(VectorDirector v) {
		return v.x * x + v.y * y;
	}

	bool operator==(VectorDirector v){
		return (v.x == x && v.y == y);
	}
};

void mostrarPunto(Punto p){
	cout << p.x << " " << p.y << " ";
}

void mostrarTriangulos(Triangulo abc){
	mostrarPunto(abc[0]); mostrarPunto(abc[1]); mostrarPunto(abc[2]);
}

float sign (Punto p1, Punto p2, Punto p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool point_in_triangle(Triangulo &abc, Punto &point) {//determina si un punto cae dentro de un triangulo

	if (point == abc[0] || point == abc[1] || point == abc[2])
		return true;

	bool b1, b2, b3;

    b1 = sign(point, abc[0], abc[1]) < 0.0f;
    b2 = sign(point, abc[1], abc[2]) < 0.0f;
    b3 = sign(point, abc[2], abc[0]) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}


double coseno_entre_vectores(VectorDirector v1, VectorDirector v2) {

	return (v1 * v2) / sqrt((v1 * v1) * (v2 * v2));
}

double angulo_formado_por(Punto origen, Punto p1, Punto p2) {

	VectorDirector d1 = VectorDirector(origen, p1);
	VectorDirector d2 = VectorDirector(origen, p2);

	if (sqrt((d1 * d1) * (d2 * d2)) == 0) return M_PI/2.0;

	return acos(coseno_entre_vectores(d1, d2));
}

bool noEnemigosDentro(Triangulo &abc, vector<Punto> &enemigos){
	for (int i = 0; i < enemigos.size(); ++i)
	{
		if(point_in_triangle(abc, enemigos[i])){
			return false;
		}
	}
	return true;
}



void cant_historicos_protegidos(vector<Punto> &historicos, map<Punto, vector<pair<Triangulo, int> > > &triangulos, Triangulo &abc){

	map<Punto, vector<pair<Triangulo, int> > >::iterator it;
	Punto origen = abc[0];
	
	int ultimoAgregado = (triangulos[origen]).size() - 1;
	for (int l = 0; l < historicos.size(); ++l)
	{
		if (point_in_triangle(abc, historicos[l]))
            	triangulos[origen][ultimoAgregado].second++;
	}
}	

void formar_triangulo(Triangulo &abc, Punto &a, Punto &p1, Punto &p2){// al triangulo lo quiero en sentido horario

	abc.push_back(a);//se que el primero es el que tiene la x mas a la izquierda
	Punto origen = {0, 0};

	Punto d1 = {p1.x - a.x, p1.y - a.y};
	Punto d2 = {p2.x - a.x, p2.y - a.y};

	double ang_p1 = atan2(d1.y, d1.x);
	double ang_p2 = atan2(d2.y, d2.x);

	if (ang_p1 > ang_p2){
		abc.push_back(p1);
		abc.push_back(p2);
	} else {
		abc.push_back(p2);
		abc.push_back(p1);
	}
}

struct SentidoAntihorario
{
	bool operator() (const Triangulo& t1, const Triangulo& t2) const {

		Punto origen = t1[0]; //ambos tienen el mismo origen difieren en los otros puntos
		Punto vector_origen = {origen.x, origen.y};

		Punto d1 = {t1[1].x - origen.x, t1[1].y - origen.y};
		Punto d2 = {t2[1].x - origen.x, t2[1].y - origen.y};		

		double ang_p1 = atan2(d1.y, d1.x);
		double ang_p2 = atan2(d2.y, d2.x);

		if (ang_p1 == ang_p2) {
			Punto d1 = {t1[2].x - origen.x, t1[2].y - origen.y};
			Punto d2 = {t2[2].x - origen.x, t2[2].y - origen.y};		

			ang_p1 = atan2(d1.y, d1.x);
			ang_p2 = atan2(d2.y, d2.x);
		}
		
		return ang_p1 < ang_p2;			
	}
};

bool convexo(Triangulo &t1, Triangulo t2)
{
	VectorDirector v = VectorDirector(t1[2], t1[1]);
	VectorDirector u = VectorDirector(t2[1], t2[2]);
	return u.x*v.y - u.y*v.x <= 0;
}

void formar_poligono(Triangulo &actual, set <Triangulo, SentidoAntihorario> &triangulos_antihorario, map <Triangulo, int> &poligonos)
{
	int res = 0;
	Triangulo tri_actual = Triangulo(actual);

	for (set<Triangulo>::iterator myIt = triangulos_antihorario.begin(); myIt != triangulos_antihorario.end(); myIt++) {

		if(actual[0] == (*myIt)[0] && actual[2] == (*myIt)[1]) //dado que cada punto esta en sentido horario primero me fijo que tengan un lado en comun
		{
			if(convexo(tri_actual, *myIt))
			{
				res = max(res, poligonos[*myIt]);
			}
		}
	}
	poligonos[actual]+= res; 

}

int maximo_value(map <Triangulo, int> &poligonos){

	int res = 0;
	for (map <Triangulo, int>::iterator myIt = poligonos.begin(); myIt!=poligonos.end(); ++myIt)
	{
		res = max(res, myIt->second);
	}
	return res;
}