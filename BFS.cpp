#include "BFS_DFS.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>

//
// Created by Wolfgang Müller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godkänd av Martin Kjellqvist 2021-08-26
//


// Jag skapar en funktion som kollar om en nod har grannar.
// Finns det så läggs grannen/grannarna i neighbours vektorn.
// Funktionen skapades för att minska repetition.
void Neighbours(Matrix &adj_matrix, std::deque<int> &neighbours, std::vector<int> &visited, int node) {

	// Vi loopar genom raderna i matrisen.
	for (int i = 0; i < adj_matrix.adj_matrix.size(); i++)
	{
		// Vi kollar om den nod som loopen är en potentiell granne.
		// Om den har en granne så kollar vi att den inte har besökts tidigare + att den inte finns i grann listan.
		if ((adj_matrix.adj_matrix[node][i] != -1) && (adj_matrix.adj_matrix[i][node] != -1) && (std::find(visited.begin(), visited.end(), i) == visited.end()) && (std::find(neighbours.begin(), neighbours.end(), i) == neighbours.end()))
		{
			// Lägger till grannen i vektorn/dequen.
			neighbours.push_back(i);
		}
	}
}

//Funktion som kollar om en graf är sammankollad eller ej.
bool BFS(Matrix adj_matrix, int node)
{
	// Då vi vill poppa fronten av neighbours skapas en deque.
	std::deque<int> neighbours;
	std::vector<int> visited;

	//Startnoden läggs in i visited vektorn.
	visited.push_back(node);

	//Vi undersöker om noden har obesökta grannar. Om det finns, läggs dessa i neighbours vektorn.
	Neighbours( adj_matrix, neighbours, visited, node);

	// Vi fortsätter så länge grannvektorn ej är tom
	while (!neighbours.empty()) {

		// Vi läser in första noden från grannvektorn.
		node = neighbours.front();
		
		// Sen poppar vi den..
		neighbours.pop_front();

		// Jag markerar den som visited genom att lägga den i visited vektorn.
		visited.push_back(node);

		// Och så kollar vi om noden har några grannar.
		Neighbours(adj_matrix, neighbours, visited, node);

	}

	//std::cout << visited.size() << std::endl;
	
	// Om våran besökts lista innehåller lika många noder som storleken av matrisen (som är 
	// baserat på antalet noder i första stycket i indatat) så betyder det att vi kan nå alla 
	// noder från den angivna startpunkten.
	if (visited.size() == adj_matrix.adj_matrix.size())
	{
		std::cout << "Grafen är kopplad från angiven punkt (BFS). " << std::endl;
		return true;
	}
	else
	{
		std::cout << "Grafen är ej kopplad från angiven punkt (BFS). " << std::endl;
		return false;
	}

}