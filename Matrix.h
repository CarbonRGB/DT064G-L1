#pragma once
#include <string>
#include <vector>
#include "reader.h"

//
// Created by Wolfgang Müller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godkänd av Martin Kjellqvist 2021-08-26
//

//Matrisens struktur
struct Matrix
{
	Matrix(adjacency_list_t data);
	int number_of_nodes(adjacency_list_t data);
	edge read_edge(adjacency_list_t data, int pos);
	size_t edge_size(adjacency_list_t data);

	std::vector<std::vector<double>> adj_matrix;
};