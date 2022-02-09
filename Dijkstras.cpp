#include "Dijkstras.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <iostream>
#include <queue>

//
// Created by Wolfgang M�ller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godk�nd av Martin Kjellqvist 2021-08-26
//

// V�ran grannlista "priority_queue" kommer inneh�lla b�de nod nummer och vikt till den noden.
typedef std::pair<double, int> pq_neighbours;


//������������������������������������������������������������������������������������������������������������������������������
//��������������������������������������������� Dijkstras algoritmen �����������������������������������������������������������
//������������������������������������������������������������������������������������������������������������������������������


// En funktion som letar reda p� om den nod vi h�mtar fr�n grannvektorn (alltid den med minst vikt ty min heap) har grannar.
// Skapades f�r att minska repetition.
void Neighbours(Matrix& adj_matrix, std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>>& neighbours, std::vector<int>&treated_nodes, std::vector<double>&treated_node_weights, std::vector<int>& path) {

	// L�ser in nod och vikt/l�ngd till den.
	double node_weight = neighbours.top().first;
	int node_no = neighbours.top().second;

	// Jag poppar den inl�sta noden fr�n grannvektorn.
	neighbours.pop();

	// Vi loopar oss genom raderna i matrisen f�r att unders�ka vilka grannar noden har.
	for (int i = 0; i < adj_matrix.adj_matrix.size(); i++)
	{

		// S� l�nge vikten inte �r negativ, och att den potentiella grann noden inte redan har behandlats  
		// s� tar vi den nod tillsammans med nodens vikt och l�gga den i grannlistan.
		if ((adj_matrix.adj_matrix[node_no][i] != -1) && (adj_matrix.adj_matrix[i][node_no] != -1) && (std::find(treated_nodes.begin(), treated_nodes.end(), i) == treated_nodes.end()))
		{
			// Vi l�ser in grann nodens vikt.
			double weight = adj_matrix.adj_matrix[node_no][i];

			//std::cout << "storlek1: " << weight << " och nod: "<< i << std::endl;

			// Vi adderar nodens vikt vi �r p� med grann nodens vikt
			// f�r att f� fram total vikt/l�ngd till den grannen.
			double total_weight = weight + node_weight;

			//std::cout << "storlek_tot: " << i << std::endl <<std::endl;
			
			// Vi l�gger noden tillsammans med den adderade vikten i grannlistan.
			neighbours.push(std::make_pair(total_weight, i));

			// Vi sparar nuvarande nod nr p� grann nodens indexplats i v�gbeskrivningen.
			path.at(i) = node_no;

		}
	}

	// Efter att vi har kollat efter grannar till v�ran nod s� vill vi l�gga in den i behandlad/bes�kt vektorn.
	// Innan vi g�r det vill vi f�rs�kra oss om att noden inte redan finns i den listan, om den redan 
	// finns d�r s� inneb�r det att det redan finns en kortare v�g fr�n startnoden till nuvarande nod.
	if (std::find(treated_nodes.begin(), treated_nodes.end(), node_no) == treated_nodes.end()) {
		treated_nodes.push_back(node_no);
		treated_node_weights.push_back(node_weight);
	}
}
//������������������������������������������������������������������������������������������������������������������������������


//������������������������������������������������������������������������������������������������������������������������������
//��������������������������������������������� Dijkstras algoritmen �����������������������������������������������������������
//������������������������������������������������������������������������������������������������������������������������������


double Dijsktra(Matrix adj_matrix, int start_node, int end_node) {
	
	// En prioritetsk� av typen "min heap" som inneh�ller noder och vikten till den noden.
	std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>> neighbours;

	// Vi skapar tv� vektorer f�r noder som �r behandlade. En f�r nod och en f�r vikter.
	std::vector<int>treated_nodes;
	std::vector<double>treated_node_weights;

	// Vi b�rjar med att l�gga in startnoden med vikten 0 i prioritetsk�n.
	neighbours.push(std::make_pair(0, start_node));

	// Jag skapar en vektor d�r jag l�gger in noder vars vikt �r baserade p� andra noder.
	// Resultatet blir en v�gbeskrivning d�r vi f�ljer destinationen till startpunkten.
	// Startnoden �r inte baserad p� n�gon tidigare vikt s� jag l�gger in den som om den
	// kommer fr�n sig sj�lvt.
	std::vector<int> path(adj_matrix.adj_matrix.size(), -1);
	path.at(start_node) = start_node;

	// Jag kollar vilka grannar noden har som �r i grannlistan just nu.
	// N�r vi har h�mtat grannarna s� l�gger vi in noden i behandlad vektorn och l�gger in grannarna i grann listan.
	Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	// Jag k�r s� l�nge vi har grannar som ej �r behandlade.
	while (!neighbours.empty()) {

		//Funktionen l�ser in grann noden med minst vikt, poppar den, och tar reda p� nodens grannar.
		Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	}

	// Skriver ut alla behandlade noder. Deaktivera eller ta bort f�r labben.
	/*
	for (int i = 0; i < treated_node_weights.size(); i++) {
		std::cout << "Vikterna i ordning: " << treated_node_weights.at(i) << " Nod nr: " << treated_nodes.at(i) << std::endl;
	}
	std::cout << std::endl;
	*/

	// Vi letar efter slut noden i bes�kt/behandlad vektorn f�r att f� fram dess index nummber.
	// Sen lagrar vi indexnumret i en variabel.
	// Sen lagrar vi den nodens vikt i en variabel med hj�lp av index numret f�r att till sist
	// skriva ut hur l�ng den kortaste v�gen �r.
	std::vector<int>::iterator itr = std::find(treated_nodes.begin(), treated_nodes.end(), end_node);
	int index = std::distance(treated_nodes.begin(), itr);
	double total_distance = treated_node_weights.at(index);
	std::cout << "Total str�cka �r: " << total_distance << std::endl;

	std::cout << std::endl;

	//Vi printar ut v�gbeskrivningen fr�n slutnoden till startnoden. 
	std::cout << "V�gbeskrivning: ";
	int start = end_node;
	std::cout << start << " ";
	while (start != start_node) {
		//start = path.at(start);
		std::cout << path.at(start) << " ";
		start = path.at(start);
		//std::cout << path.at(start) << " ";
	}

	//std::cout << path.at(end_node);
	/*
	// Skriver bara ut hela pathen. Deaktivera inf�r labben.
	std::cout << std::endl << std::endl;
	for (int i = 0; i < path.size(); i++) {
		std::cout << path.at(i) << " ";
	}
	*/

	return 0;
}