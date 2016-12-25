#include <iostream>
#include <math.h>
#include "ej3.h"
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <set>

using namespace std;

double pi = 3.14159265;

int main() {

	double H, E;
	cin >> H >> E;

	vector<Punto> enemigos(E);

	set<Punto> setHistoricos;
	
	for (double i = 0; i < H; i++) {
		Punto p;
		cin >> p.x >> p.y;
		setHistoricos.insert(p);
	}

	for (double i = 0; i < E; i++) {
		cin >> enemigos[i].x >> enemigos[i].y;
	}
	//Idea: similar al punto A descomponer el poligono en triangulos y luego irme armando un poligono maximo a partir de todos los posibles triangulos
	vector<Punto> historicos(setHistoricos.begin(), setHistoricos.end());//conviene que esten ordenados en orden ascendente segun el eje x
	map<Punto, vector<pair<Triangulo, int> > > triangulos;//dado un punto guardo los triangulos que empiezan con ese punto y ademas por cada
	//triangulo tengo cuantos edificios historicos protege
	map<Triangulo,int>::iterator it;

	map<Punto, vector<pair<Triangulo, int> > >::iterator it_triangulos;

	for (int i = 0; i < historicos.size(); ++i)
	{
		for (int j = i + 1; j < historicos.size(); ++j)
		{
			for (int k = j+1; k < historicos.size(); ++k)
			{
				Triangulo abc;
				formar_triangulo(abc, historicos[i], historicos[j], historicos[k]);//voy a formar los triangulos con sus puntos en sentido horario

				if (noEnemigosDentro(abc, enemigos)){

					it_triangulos = triangulos.find(historicos[i]);
					pair<Triangulo, int>  nuevo_triangulo(abc,0);//hay un nuevo triangulo que agregar
        			
        			if (it_triangulos != triangulos.end()) //me fijo si el punto donde empieza el triangulo ya esta en el dicc
            			triangulos[historicos[i]].push_back(nuevo_triangulo);
            		else
            		{
            			vector<pair<Triangulo, int> > elem; elem.push_back(nuevo_triangulo);
            			triangulos[historicos[i]] = elem; 
            		} 
					cant_historicos_protegidos(historicos, triangulos, abc); //ahora actualizo el diccionario 
				}
			}
		}
	}

	if(triangulos.empty())
	{
		if (historicos.size() > 0)
			if (historicos.size() > 1)// no puedo formar un poligono pero si una recta
				cout << 2 << endl;
			else
				cout << 1 << endl;//hay un solo edificio protego ese
		else
			cout << 0 << endl;// no hay nada que proteger 
		return 0;
	}
	//formo los subgrupos a partir de los puntos inicios que tengo en triangulos

	int max_protegidos = 0;
	for (map<Punto, vector<pair<Triangulo, int> > >::iterator myIt = triangulos.begin(); myIt!=triangulos.end(); ++myIt)
	{
		map <Triangulo, int> poligonos;

		for (int i = 0; i < myIt->second.size(); ++i)
		{//voy a ver cuantos historicos protejo a partir de los triangulos que ya tenia pero uniendole otros para formar un poligono convexo
			poligonos[myIt->second[i].first] = myIt->second[i].second - 2;
		}

		set <Triangulo, SentidoAntihorario> triangulos_antihorario; 
		for (int i = 0; i < myIt->second.size(); ++i) //voy a ordenar los triangulos para saber para cada uno cual le puedo unir
			triangulos_antihorario.insert(myIt->second[i].first);

		for (set<Triangulo>::iterator sit = triangulos_antihorario.begin() ; sit != triangulos_antihorario.end(); sit++)
		{//voy a empezar a unirlos tomo uno y luego veo cual le sigue y asi

			Triangulo actual = *sit;
			formar_poligono(actual, triangulos_antihorario, poligonos);
		}
		max_protegidos = max(max_protegidos, maximo_value(poligonos));
	}
	cout << max_protegidos + 2 << endl;
	return 0;
}
