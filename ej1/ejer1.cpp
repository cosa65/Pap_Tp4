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

int main() {

	int n;
	cin >> n;
    
    map<lado,int> cant_lados;

    map<lado,int>::iterator it;

    vertice inicial;
    inicial.first = numeric_limits<double>::max(); inicial.second = numeric_limits<double>::max();

    for (int i = 0; i < n - 2; ++i)
    {
        vertice a, b, c;
        vector<vertice> vertices;
        vector<lado> lados;
        cin >> a.first >> a.second >> b.first >> b.second >> c.first >> c.second;
        
        vertices.push_back(a); vertices.push_back(b); vertices.push_back(c);
        for (int k = 0; k < vertices.size(); ++k)
        {
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

        lado ab, ac, bc;
        ab.first = a; ab.second = b;
        ac.first = a; ac.second = c;
        bc.first = b; bc.second = c;

        lados.push_back(ab); lados.push_back(ac); lados.push_back(bc); 

        for (int j = 0; j < lados.size(); ++j)
        {
            it = cant_lados.find(lados[j]);
            if (it != cant_lados.end()) 
                cant_lados[lados[j]]++;
   			else
   			{	
   				lado lado_swap;
   				lado_swap.first = lados[j].second; lado_swap.second = lados[j].first; 
   				it = cant_lados.find(lado_swap);
            	if (it != cant_lados.end()) 
                	cant_lados[lado_swap]++;
            	else
            	{
                	cant_lados[lado_swap] = 1;
            	}
            }	
        }
    }

 	map<vertice,vector<vertice> > vertices_vecinos;
 	map<vertice,vector<vertice> >::iterator it_vecinos;

    for ( map<lado,int>::iterator myIt = cant_lados.begin(); myIt!=cant_lados.end(); ++myIt)
    {
    	if (myIt->second == 1)
    	{
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
 
    vertice inicio_vecino1 = vertices_vecinos[inicial][0];
    vertice inicio_vecino2 = vertices_vecinos[inicial][1];

    pair<double, double> vector_inicial(0, 10);
    pair<double, double> vector_vecino1(inicio_vecino1.first - inicial.first, inicio_vecino1.second - inicial.second);
    pair<double, double> vector_vecino2(inicio_vecino2.first - inicial.first, inicio_vecino2.second - inicial.second);

	double num_vecino1 = vector_inicial.first*vector_vecino1.first + vector_inicial.second*vector_vecino1.second;
	double den_vecino1 = (sqrt(pow(vector_inicial.first,2) + pow(vector_inicial.second,2)))*(sqrt(pow(vector_vecino1.first,2) + pow(vector_vecino1.second,2)));
	double angulo_vecino1 = acos(num_vecino1/den_vecino1);

	double num_vecino2 = vector_inicial.first*vector_vecino2.first + vector_inicial.second*vector_vecino2.second;
	double den_vecino2 = (sqrt(pow(vector_inicial.first,2) + pow(vector_inicial.second,2)))*(sqrt(pow(vector_vecino2.first,2) + pow(vector_vecino2.second,2)));
	double angulo_vecino2 = acos(num_vecino2/den_vecino2);

	vertice anterior = inicial;
	vertice actual;

	if (angulo_vecino1 < angulo_vecino2)
		actual = vertices_vecinos[inicial][0];
	else
		actual = vertices_vecinos[inicial][1];	
    
 	map<vertice,vector<vertice> >::iterator it_res;
 	cout << anterior.first << " " << anterior.second << " ";

    for (int i = 0; i < n - 1 ; ++i)
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
    
    return 0;
}