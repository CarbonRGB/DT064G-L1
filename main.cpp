#include <iostream>
#include "reader.h"
#include "Matrix.h"
#include "BFS_DFS.h"
#include "Dijkstras.h"
#include <queue>

//
// Created by Wolfgang M�ller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godk�nd av Martin Kjellqvist 2021-08-26
//

int main()
{
    // G�r det m�jligt att visa nordiska bokst�ver i utskrifterna.
    system("chcp 1252 >nul");

    // L�ser in filen med hj�lp av den kod som labbinstrukt�ren gav.
    adjacency_list_t list = parse_file("export.txt");

    /*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    ::::::::::::::::::::::::::_TEST_AV_OLIKA_UTSKRIFTER_ENLIGT_LABBTIPS_1_:::::::::::::::::::::::::::::::::::::::::
    :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

    /*
    //L�ser in noder och tillh�rande beskrivning
    for (auto it = list.first.begin(); it != list.first.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    */

    /*
    //L�ser in noderna med tillh�rande vikter och beskrivning.
    for (auto it = list.second.begin(); it != list.second.end(); it++)
    {
        std::cout << it->n1 << " " << it->n2 << " " << it->weight << " " << it->description << std::endl;
    }
    */

    /*
    auto no = list.second.begin()+7;
    std::cout << no->description << std::endl;
    */


    /*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    :::::::::::::::::::::::::::_Skriver_ut_matrisen_med_vikterna_:::::::::::::::::::::::::::::::
    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

    /*
    
    //Matrix Matrix = list;
    //Skriver ut matrisens storlek
    //std::cout << Matrix.adj_matrix.size() << std::endl;

    for (int i = 0; i < Matrix.adj_matrix.size(); i++) {

        Matrix.adj_matrix[i][0];

        std::cout <<" "<<std::endl;

        for (int j = 0; j < Matrix.adj_matrix.size(); j++) {

            std::cout <<" "<< Matrix.adj_matrix[i][j]<<" ";
        }
    }
    std::cout << " " << std::endl;

    */
   
    //Vikten/avst�ndet mellan angivna noder
    //std::cout <<  Matrix.adj_matrix[15][16] << std::endl;


    /*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    :::::::::::::::::::::::::::::::::::_TEST_BFS_DFS_:::::::::::::::::::::::::::::::::::::::::::::::
    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

    std::cout << "\n\n�����������������������������������������������������������������������������������������\n\n";

    std::cout << "Testar om det g�r att n� samtliga noder fr�n st�ngd pizzeria." << std::endl;
    BFS(list, 21);
    DFS(list, 21);

    //Vikten/avst�ndet mellan angivna noder
    //std::cout << Matrix.adj_matrix[15][16] << std::endl;

    /*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    :::::::::::::::::::::::::::_SKRIVER_UT_UPPGIFTERNA_ENLIGT_INSTRUKTIONERNA_:::::::::::::::::::::::::
    :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

    
    std::cout << "\n\n�����������������������������������������������������������������������������������������\n\n";

    std::cout << "Testar om det g�r att n� alla noder fr�n Nackstav�gen.." << std::endl;

    BFS(list, 24);
    DFS(list, 24);
    std::cout << std::endl;

    std::cout << "Avst�ndet och v�gbeskrivningen mellan Nackstav�gen (Axv�gen 1) till F�rr�det." << std::endl << std::endl;

    Dijsktra(list, 24, 37);
    
    std::cout << "\n\n�����������������������������������������������������������������������������������������\n\n";


    std::cout << "Testar om det g�r att n� alla noder fr�n Universitetet.." << std::endl;

    BFS(list, 20);
    DFS(list, 20);
    std::cout << std::endl;

    std::cout << "Avst�ndet och v�gbeskrivningen mellan Universitetet (rondellen) till Bite Line V�stra." << std::endl << std::endl;

    Dijsktra(list, 20, 19);

    std::cout << "\n\n�����������������������������������������������������������������������������������������\n\n";

    std::cout << "Testar om det g�r att n� alla noder fr�n L319.." << std::endl;

    BFS(list, 46);
    DFS(list, 46);
    std::cout << std::endl;

    std::cout << "Avst�ndet och v�gbeskrivningen mellan L319 till D025." << std::endl << std::endl;

    Dijsktra(list, 46, 47);

    std::cout << "\n\n�����������������������������������������������������������������������������������������\n\n";
    


    //���������������������������������������������������������������������������������������������������������
    //���������������������������������    TEST AV PRIORITETSK�N    �������������������������������������������
    
    /*
    
    //En prioritetsk� som inneh�ller noder och vikten till den noden.
    //Detta �r en min heap d�r noden med minst vikt hamnar �verst.
    std::priority_queue<pq_neighbours, std::vector<pq_neighbours>, std::greater<pq_neighbours>> neighbours;

    //Vektor som inneh�ller behandlade noder
    //std::vector<treated_neighbours, std::vector<treated_neighbours>> treated;
    //std::vector<std::pair<double, int>> treated;
    std::vector<int>treated_nodes;
    std::vector<double>treated_node_weights;
    //treated.push_back(std::make_pair(3.14, 1));

    treated_nodes.push_back(5);
    treated_nodes.push_back(4);
    treated_nodes.push_back(1);
    treated_node_weights.push_back(3.14);
    treated_node_weights.push_back(7.18);
    treated_node_weights.push_back(5.32);

    int test = *std::min_element(treated_nodes.begin(), treated_nodes.end());

    std::cout << "Minsta elementet �r: " << test << std::endl;

    */
    
    //��������������������������������������������������������������������������������������������������������� 



    /*
    for (int i = 0; i < treated_nodes.size(); i++) {

        std::vector<int>::iterator itr = std::find(treated_nodes.begin(), treated_nodes.end(), i);

        if (itr != treated_nodes.end()) {
            std::cout << "Element funnen p� index: " << std::distance(treated_nodes.begin(), itr) <<std::endl;
            std::cout << "Nod no is: " << treated_nodes.at(itr)
        }
        
        //std::cout << "Node found. Node no is: " << i << " and weight is: " << treated_node_weights.at(i-1) << std::endl;
        
    }
    */


    //K�r en tests�kning
    /*
    auto weight_search = std::find_if(treated.begin(), treated.end(), [](std::pair<double, int> const& ref) {
    return ref.first == 3.14;
    });
    */
    
    //��������������������������������������������������������������������������������������������������������� 


}

