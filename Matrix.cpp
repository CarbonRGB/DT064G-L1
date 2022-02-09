#include <iostream>
#include "Matrix.h"

//
// Created by Wolfgang Müller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godkänd av Martin Kjellqvist 2021-08-26
//

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::: Skapar Matrisen mha indatat :::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

//Returnerar antalet noder.
int Matrix::number_of_nodes(adjacency_list_t data)
{
	return data.first.size();
}

//Returnerar nod nummer
edge Matrix::read_edge(adjacency_list_t data, int node_no)
{
	return data.second[node_no];
}


//Returnerar antal vikter som ska in i matrisen från filen.
size_t Matrix::edge_size(adjacency_list_t data)
{
	return data.second.size();
}


Matrix::Matrix(adjacency_list_t data)
{
	// Jag läser av antalet noder i första avsnittet som ligger till grund för storleken på matrisen.
	int size = number_of_nodes(data);

	//std::cout << "Antal noder: " << size << std::endl;

	// Ett standardvärde jag använder i matrisen som skapas.
	// Detta värde symboliserar att det ej finns någon koppling mellan noderna.
	int default_value = -1;

	// Jag skapar en vektor med vektorer (2d matris) som fylls med standard värdet.
	// https://www.techiedelight.com/initialize-two-dimensional-vector-cpp/
	std::vector<double> vector(size, default_value);
	std::vector<std::vector<double>> empty_matrix(size, vector);

	//Ett mer kompaktare sätt att skriva en matris/2d vektor på.
	//std::vector<std::vector<double>> empty_matrix(size, std::vector<double>(size, default_value));

	adj_matrix = empty_matrix;

	// I loopen läser jag in noderna och vikterna mellan noderna från indatat.
	// Jag placerar sedan vikten i rätt plats i matrisen.
	for (int i = 0; i < edge_size(data); i++)
	{
		// Jag läser in noderna från andra stycket i indatat.
		int node1 = read_edge(data, i).n1; // Noden 1
		int node2 = read_edge(data, i).n2; // Noden 2

		// Jag läser in vikten mellan aktuella noder från indata filen.
		adj_matrix[node1][node2] = read_edge(data, i).weight;
	}
}

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/