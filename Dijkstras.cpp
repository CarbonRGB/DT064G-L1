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
// Godk鄚d av Martin Kjellqvist 2021-08-26
//

// V緳an grannlista "priority_queue" kommer inneh嶚la b嶟e nod nummer och vikt till den noden.
typedef std::pair<double, int> pq_neighbours;


//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
//中中中中中中中中中中中中中中中中中中中中中中� Dijkstras algoritmen 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中�
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中


// En funktion som letar reda p� om den nod vi h鄝tar fr幩 grannvektorn (alltid den med minst vikt ty min heap) har grannar.
// Skapades f顤 att minska repetition.
void Neighbours(Matrix& adj_matrix, std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>>& neighbours, std::vector<int>&treated_nodes, std::vector<double>&treated_node_weights, std::vector<int>& path) {

	// L酲er in nod och vikt/l鄚gd till den.
	double node_weight = neighbours.top().first;
	int node_no = neighbours.top().second;

	// Jag poppar den inl酲ta noden fr幩 grannvektorn.
	neighbours.pop();

	// Vi loopar oss genom raderna i matrisen f顤 att unders闥a vilka grannar noden har.
	for (int i = 0; i < adj_matrix.adj_matrix.size(); i++)
	{

		// S� l鄚ge vikten inte 酺 negativ, och att den potentiella grann noden inte redan har behandlats  
		// s� tar vi den nod tillsammans med nodens vikt och l輍ga den i grannlistan.
		if ((adj_matrix.adj_matrix[node_no][i] != -1) && (adj_matrix.adj_matrix[i][node_no] != -1) && (std::find(treated_nodes.begin(), treated_nodes.end(), i) == treated_nodes.end()))
		{
			// Vi l酲er in grann nodens vikt.
			double weight = adj_matrix.adj_matrix[node_no][i];

			//std::cout << "storlek1: " << weight << " och nod: "<< i << std::endl;

			// Vi adderar nodens vikt vi 酺 p� med grann nodens vikt
			// f顤 att f� fram total vikt/l鄚gd till den grannen.
			double total_weight = weight + node_weight;

			//std::cout << "storlek_tot: " << i << std::endl <<std::endl;
			
			// Vi l輍ger noden tillsammans med den adderade vikten i grannlistan.
			neighbours.push(std::make_pair(total_weight, i));

			// Vi sparar nuvarande nod nr p� grann nodens indexplats i v輍beskrivningen.
			path.at(i) = node_no;

		}
	}

	// Efter att vi har kollat efter grannar till v緳an nod s� vill vi l輍ga in den i behandlad/bes闥t vektorn.
	// Innan vi g顤 det vill vi f顤s鄢ra oss om att noden inte redan finns i den listan, om den redan 
	// finns d酺 s� inneb酺 det att det redan finns en kortare v輍 fr幩 startnoden till nuvarande nod.
	if (std::find(treated_nodes.begin(), treated_nodes.end(), node_no) == treated_nodes.end()) {
		treated_nodes.push_back(node_no);
		treated_node_weights.push_back(node_weight);
	}
}
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中


//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中
//中中中中中中中中中中中中中中中中中中中中中中� Dijkstras algoritmen 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中�
//中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中


double Dijsktra(Matrix adj_matrix, int start_node, int end_node) {
	
	// En prioritetsk� av typen "min heap" som inneh嶚ler noder och vikten till den noden.
	std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>> neighbours;

	// Vi skapar tv� vektorer f顤 noder som 酺 behandlade. En f顤 nod och en f顤 vikter.
	std::vector<int>treated_nodes;
	std::vector<double>treated_node_weights;

	// Vi b顤jar med att l輍ga in startnoden med vikten 0 i prioritetsk霵.
	neighbours.push(std::make_pair(0, start_node));

	// Jag skapar en vektor d酺 jag l輍ger in noder vars vikt 酺 baserade p� andra noder.
	// Resultatet blir en v輍beskrivning d酺 vi f闤jer destinationen till startpunkten.
	// Startnoden 酺 inte baserad p� n嶓on tidigare vikt s� jag l輍ger in den som om den
	// kommer fr幩 sig sj鄟vt.
	std::vector<int> path(adj_matrix.adj_matrix.size(), -1);
	path.at(start_node) = start_node;

	// Jag kollar vilka grannar noden har som 酺 i grannlistan just nu.
	// N酺 vi har h鄝tat grannarna s� l輍ger vi in noden i behandlad vektorn och l輍ger in grannarna i grann listan.
	Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	// Jag k顤 s� l鄚ge vi har grannar som ej 酺 behandlade.
	while (!neighbours.empty()) {

		//Funktionen l酲er in grann noden med minst vikt, poppar den, och tar reda p� nodens grannar.
		Neighbours(adj_matrix, neighbours, treated_nodes, treated_node_weights, path);

	}

	// Skriver ut alla behandlade noder. Deaktivera eller ta bort f顤 labben.
	/*
	for (int i = 0; i < treated_node_weights.size(); i++) {
		std::cout << "Vikterna i ordning: " << treated_node_weights.at(i) << " Nod nr: " << treated_nodes.at(i) << std::endl;
	}
	std::cout << std::endl;
	*/

	// Vi letar efter slut noden i bes闥t/behandlad vektorn f顤 att f� fram dess index nummber.
	// Sen lagrar vi indexnumret i en variabel.
	// Sen lagrar vi den nodens vikt i en variabel med hj鄟p av index numret f顤 att till sist
	// skriva ut hur l幩g den kortaste v輍en 酺.
	std::vector<int>::iterator itr = std::find(treated_nodes.begin(), treated_nodes.end(), end_node);
	int index = std::distance(treated_nodes.begin(), itr);
	double total_distance = treated_node_weights.at(index);
	std::cout << "Total str踄ka 酺: " << total_distance << std::endl;

	std::cout << std::endl;

	//Vi printar ut v輍beskrivningen fr幩 slutnoden till startnoden. 
	std::cout << "V輍beskrivning: ";
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
	// Skriver bara ut hela pathen. Deaktivera inf顤 labben.
	std::cout << std::endl << std::endl;
	for (int i = 0; i < path.size(); i++) {
		std::cout << path.at(i) << " ";
	}
	*/

	return 0;
}