#include "Dijkstras.h"
#include <algorithm>
#include <iostream>
#include <deque>
#include <iostream>
#include <queue>

//
// Created by Wolfgang Müller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godkänd av Martin Kjellqvist 2021-08-26
//

// Våran grannlista "priority_queue" kommer innehålla både nod nummer och vikt till den noden.
typedef std::pair<double, int> pq_neighbours;


//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Dijkstras algoritmen ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤


// En funktion som letar reda på om den nod vi hämtar från grannvektorn (alltid den med minst vikt ty min heap) har grannar.
// Skapades för att minska repetition.
void Neighbours(Matrix& adj_matrix, std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>>& neighbours, std::vector<int>&treated_nodes, std::vector<double>&treated_node_weights, std::vector<int>& path) {

	// Läser in nod och vikt/längd till den.
	double node_weight = neighbours.top().first;
	int node_no = neighbours.top().second;

	// Jag poppar den inlästa noden från grannvektorn.
	neighbours.pop();

	// Vi loopar oss genom raderna i matrisen för att undersöka vilka grannar noden har.
	for (int i = 0; i < adj_matrix.adj_matrix.size(); i++)
	{

		// Så länge vikten inte är negativ, och att den potentiella grann noden inte redan har behandlats  
		// så tar vi den nod tillsammans med nodens vikt och lägga den i grannlistan.
		if ((adj_matrix.adj_matrix[node_no][i] != -1) && (adj_matrix.adj_matrix[i][node_no] != -1) && (std::find(treated_nodes.begin(), treated_nodes.end(), i) == treated_nodes.end()))
		{
			// Vi läser in grann nodens vikt.
			double weight = adj_matrix.adj_matrix[node_no][i];

			//std::cout << "storlek1: " << weight << " och nod: "<< i << std::endl;

			// Vi adderar nodens vikt vi är på med grann nodens vikt
			// för att få fram total vikt/längd till den grannen.
			double total_weight = weight + node_weight;

			//std::cout << "storlek_tot: " << i << std::endl <<std::endl;
			
			// Vi lägger noden tillsammans med den adderade vikten i grannlistan.
			neighbours.push(std::make_pair(total_weight, i));

			// Vi sparar nuvarande nod nr på grann nodens indexplats i vägbeskrivningen.
			path.at(i) = node_no;

		}
	}

	// Efter att vi har kollat efter grannar till våran nod så vill vi lägga in den i behandlad/besökt vektorn.
	// Innan vi gör det vill vi försäkra oss om att noden inte redan finns i den listan, om den redan 
	// finns där så innebär det att det redan finns en kortare väg från startnoden till nuvarande nod.
	if (std::find(treated_nodes.begin(), treated_nodes.end(), node_no) == treated_nodes.end()) {
		treated_nodes.push_back(node_no);
		treated_node_weights.push_back(node_weight);
	}
}
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤


//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ Dijkstras algoritmen ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤


double Dijsktra(Matrix adj_matrix, int start_node, int end_node) {
	
	// En prioritetskö av typen "min heap" som innehåller noder och vikten till den noden.
	std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>> neighbours;

	// Vi skapar två vektorer för noder som är behandlade. En för nod och en för vikter.
	std::vector<int>treated_nodes;
	std::vector<double>treated_node_weights;

	// Vi börjar med att lägga in startnoden med vikten 0 i prioritetskön.
	neighbours.push(std::make_pair(0, start_node));

	// Jag skapar en vektor där jag lägger in noder vars vikt är baserade på andra noder.
	// Resultatet blir en vägbeskrivning där vi följer destinationen till startpunkten.
	// Startnoden är inte baserad på någon tidigare vikt så jag lägger in den som om den
	// kommer från sig självt.
	std::vector<int> path(adj_matrix.adj_matrix.size(), -1);
	path.at(start_node) = start_node;

	// Jag kollar vilka grannar noden har som är i grannlistan just nu.
	// När vi har hämtat grannarna så lägger vi in noden i behandlad vektorn och lägger in grannarna i grann listan.
	Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	// Jag kör så länge vi har grannar som ej är behandlade.
	while (!neighbours.empty()) {

		//Funktionen läser in grann noden med minst vikt, poppar den, och tar reda på nodens grannar.
		Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	}

	// Skriver ut alla behandlade noder. Deaktivera eller ta bort för labben.
	/*
	for (int i = 0; i < treated_node_weights.size(); i++) {
		std::cout << "Vikterna i ordning: " << treated_node_weights.at(i) << " Nod nr: " << treated_nodes.at(i) << std::endl;
	}
	std::cout << std::endl;
	*/

	// Vi letar efter slut noden i besökt/behandlad vektorn för att få fram dess index nummber.
	// Sen lagrar vi indexnumret i en variabel.
	// Sen lagrar vi den nodens vikt i en variabel med hjälp av index numret för att till sist
	// skriva ut hur lång den kortaste vägen är.
	std::vector<int>::iterator itr = std::find(treated_nodes.begin(), treated_nodes.end(), end_node);
	int index = std::distance(treated_nodes.begin(), itr);
	double total_distance = treated_node_weights.at(index);
	std::cout << "Total sträcka är: " << total_distance << std::endl;

	std::cout << std::endl;

	//Vi printar ut vägbeskrivningen från slutnoden till startnoden. 
	std::cout << "Vägbeskrivning: ";
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
	// Skriver bara ut hela pathen. Deaktivera inför labben.
	std::cout << std::endl << std::endl;
	for (int i = 0; i < path.size(); i++) {
		std::cout << path.at(i) << " ";
	}
	*/

	return 0;
}