#include "BFS_DFS.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>

//
// Created by Wolfgang M�ller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godk�nd av Martin Kjellqvist 2021-08-26
//


// Jag skapar en funktion som kollar om en nod har grannar.
// Finns det s� l�ggs grannen/grannarna i neighbours vektorn.
// Funktionen skapades f�r att minska repetition.
void Neighbours(Matrix &adj_matrix, std::deque<int> &neighbours, std::vector<int> &visited, int node) {

	// Vi loopar genom raderna i matrisen.
	for (int i = 0; i < adj_matrix.adj_matrix.size(); i++)
	{
		// Vi kollar om den nod som loopen �r en potentiell granne.
		// Om den har en granne s� kollar vi att den inte har bes�kts tidigare + att den inte finns i grann listan.
		if ((adj_matrix.adj_matrix[node][i] != -1) && (adj_matrix.adj_matrix[i][node] != -1) && (std::find(visited.begin(), visited.end(), i) == visited.end()) && (std::find(neighbours.begin(), neighbours.end(), i) == neighbours.end()))
		{
			// L�gger till grannen i vektorn/dequen.
			neighbours.push_back(i);
		}
	}
}

//Funktion som kollar om en graf �r sammankollad eller ej.
bool BFS(Matrix adj_matrix, int node)
{
	// D� vi vill poppa fronten av neighbours skapas en deque.
	std::deque<int> neighbours;
	std::vector<int> visited;

	//Startnoden l�ggs in i visited vektorn.
	visited.push_back(node);

	//Vi unders�ker om noden har obes�kta grannar. Om det finns, l�ggs dessa i neighbours vektorn.
	Neighbours( adj_matrix, neighbours, visited, node);

	// Vi forts�tter s� l�nge grannvektorn ej �r tom
	while (!neighbours.empty()) {

		// Vi l�ser in f�rsta noden fr�n grannvektorn.
		node = neighbours.front();
		
		// Sen poppar vi den..
		neighbours.pop_front();

		// Jag markerar den som visited genom att l�gga den i visited vektorn.
		visited.push_back(node);

		// Och s� kollar vi om noden har n�gra grannar.
		Neighbours(adj_matrix, neighbours, visited, node);

	}

	//std::cout << visited.size() << std::endl;
	
	// Om v�ran bes�kts lista inneh�ller lika m�nga noder som storleken av matrisen (som �r 
	// baserat p� antalet noder i f�rsta stycket i indatat) s� betyder det att vi kan n� alla 
	// noder fr�n den angivna startpunkten.
	if (visited.size() == adj_matrix.adj_matrix.size())
	{
		std::cout << "Grafen �r kopplad fr�n angiven punkt (BFS). " << std::endl;
		return true;
	}
	else
	{
		std::cout << "Grafen �r ej kopplad fr�n angiven punkt (BFS). " << std::endl;
		return false;
	}

}