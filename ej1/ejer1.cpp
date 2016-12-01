#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
#include <math.h>
#include <cstddef>
#include <utility>      // std::pair, std::make_pair
using namespace std;


typedef pair<double, double> vertice;

typedef pair<vertice, vertice> lado;

void agregar_ladosYcantidad(vector<lado> &lados, map<lado,int> &cant_lados)
{

    map<lado,int>::iterator it;

    for (int j = 0; j < lados.size(); ++j)
    {
        it = cant_lados.find(lados[j]);//si ese lado ya esta definido incremento la cantidad
        if (it != cant_lados.end()) 
            cant_lados[lados[j]]++;
        else
        {   
            lado lado_swap;//puede que al levantar los datos el lado me aparezca a b ó b a entonces lo busco de ambas formas
            lado_swap.first = lados[j].second; lado_swap.second = lados[j].first; 
            it = cant_lados.find(lado_swap);
            if (it != cant_lados.end()) 
                cant_lados[lado_swap]++;
            else
            {
                cant_lados[lado_swap] = 1; //sino esta lo defino
            }
        }   
    }
}

void vertice_YsusVecinos(map<vertice,vector<vertice> > &vertices_vecinos, map<lado,int> &cant_lados)
{
    map<vertice,vector<vertice> >::iterator it_vecinos;//voy a definir un nuevo diccionario donde para vertice voy a tener 
//un vector con los vertices vecinos, en el poligono original cada vertice solo esta conectado con otros dos vertices
    for ( map<lado,int>::iterator myIt = cant_lados.begin(); myIt!=cant_lados.end(); ++myIt)
    {
        if (myIt->second == 1)//solamente me sriven los vertices que forman un lado que aparece solo una vez en la descomposicion
        {//ya que estos son los lados del poligono original
            it_vecinos = vertices_vecinos.find(myIt->first.first);
            
            if (it_vecinos != vertices_vecinos.end())
                vertices_vecinos[myIt->first.first].push_back(myIt->first.second);      
            else 
            {
                vector<vertice> vecinos;
                vecinos.push_back(myIt->first.second);
                vertices_vecinos[myIt->first.first] = vecinos;
            }
    
            it_vecinos = vertices_vecinos.find(myIt->first.second);
        
            if (it_vecinos != vertices_vecinos.end())
                vertices_vecinos[myIt->first.second].push_back(myIt->first.first);
            else 
            {
                vector<vertice> vecinos;
                vecinos.push_back(myIt->first.first);
                vertices_vecinos[myIt->first.second] = vecinos;
            }
        }
    }
}

vertice vertice_aMenorAngulo(map<vertice,vector<vertice> > &vertices_vecinos, vertice inicial)
{
    vertice inicial_vecino1 = vertices_vecinos[inicial][0];
    vertice inicial_vecino2 = vertices_vecinos[inicial][1];

// defino los vectores conformados tanto por el vertice inicial como el de sus vecinos
    pair<double, double> vector_inicial(0, 10);//10 es un valor arbitrario para el inicial
    pair<double, double> vector_vecino1(inicial_vecino1.first - inicial.first, inicial_vecino1.second - inicial.second);
    pair<double, double> vector_vecino2(inicial_vecino2.first - inicial.first, inicial_vecino2.second - inicial.second);

// el angulo es igual a acos( (U*V)/|U|*|V| ) 
    double num_vecino1 = vector_inicial.first*vector_vecino1.first + vector_inicial.second*vector_vecino1.second;
    double den_vecino1 = (sqrt(pow(vector_inicial.first,2) + pow(vector_inicial.second,2)))*(sqrt(pow(vector_vecino1.first,2) + pow(vector_vecino1.second,2)));
    double angulo_vecino1 = acos(num_vecino1/den_vecino1);

    double num_vecino2 = vector_inicial.first*vector_vecino2.first + vector_inicial.second*vector_vecino2.second;
    double den_vecino2 = (sqrt(pow(vector_inicial.first,2) + pow(vector_inicial.second,2)))*(sqrt(pow(vector_vecino2.first,2) + pow(vector_vecino2.second,2)));
    double angulo_vecino2 = acos(num_vecino2/den_vecino2);

    if (angulo_vecino1 < angulo_vecino2)
        return vertices_vecinos[inicial][0];
    else
        return vertices_vecinos[inicial][1];  
}
 
void armar_poligono(vertice anterior, vertice actual, map<vertice,vector<vertice> > &vertices_vecinos, int cantidad)
{
    map<vertice,vector<vertice> >::iterator it_res;
    cout << anterior.first << " " << anterior.second << " ";
    //finalmente tengo el nodo inicial, el siguiente asi que puedo continuar
    for (int i = 0; i < cantidad - 1 ; ++i)
    {
        cout << actual.first << " " << actual.second << " ";
        it_res = vertices_vecinos.find(actual);
        if (it_res->second[0] != anterior)
        {
            anterior = actual;
            actual = it_res->second[0];
        }
        else
        {
            anterior = actual;
            actual = it_res->second[1];
        }
    }
    cout << endl; 
}    


int main() {

	int n;
	cin >> n;
    
    map<lado,int> cant_lados;//diccionario que me dice cuantas veces aparece cada lado

    vertice inicial;//aca va a estar el vertice por el que tengo que empezar a armar el poligono
    inicial.first = numeric_limits<double>::max(); inicial.second = numeric_limits<double>::max();

    for (int i = 0; i < n - 2; ++i)
    {
        vertice a, b, c;
        vector<vertice> vertices;
        vector<lado> lados;
        cin >> a.first >> a.second >> b.first >> b.second >> c.first >> c.second;//levanto los 3 vertices del triangulo
        
        vertices.push_back(a); vertices.push_back(b); vertices.push_back(c);
        
        for (int k = 0; k < vertices.size(); ++k)//me quedo con el vertice de menor x y en caso de haber mas de uno con el 
        {//de menor y
            if (inicial.first == vertices[k].first)
            {
            	if (inicial.second > vertices[k].second)
            		inicial.second = vertices[k].second;
            } 
            else 
            { 
            	if (inicial.first > vertices[k].first)
            	{
            		inicial.first = vertices[k].first; inicial.second = vertices[k].second;
            	}
        	}
        }

        lado ab, ac, bc;//formo los lados del triangulo como el par de vertices que lo forma
        ab.first = a; ab.second = b;
        ac.first = a; ac.second = c;
        bc.first = b; bc.second = c;

        lados.push_back(ab); lados.push_back(ac); lados.push_back(bc); 
        
        agregar_ladosYcantidad(lados, cant_lados);//me guardo cuantas veces esta ese lado en toda la descomposicion
    }

 	map<vertice,vector<vertice> > vertices_vecinos;

    vertice_YsusVecinos(vertices_vecinos, cant_lados);//obtengo para cada vertice una lista con los vertices vecinos (que son dos)

    vertice actual = vertice_aMenorAngulo(vertices_vecinos, inicial); //obtengo el vertice cuyo vector forma el menor angulo con el vector que contiene
    //al vertice inicial
   
	vertice anterior = inicial;

    armar_poligono(anterior, actual, vertices_vecinos, n);
    
    return 0;
}