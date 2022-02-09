#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

//
// Created by Wolfgang Müller
// Laboration 1 - Grafer
// Redovisat 2021-08-26 
// Godkänd av Martin Kjellqvist 2021-08-26
//

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::_Implementationen_för_reader.h, taget från tipset med godkännande av Martin Kjellqvist_::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


enum token {
    COMMENT, META, EDGE, END_OF_FILE
};

token get_line_type(std::istream& is) {
    switch (is.peek()) {
    case std::istream::traits_type::eof():      return END_OF_FILE;
    case '#':                                   return COMMENT;
    case 'M':                                   return META;
    };
    return EDGE;
}

meta_t meta;

edge read_edge(std::istream& is) {
    edge e;
    is >> e.n1 >> e.n2 >> e.weight;
    std::getline(is, e.description);
    return e;
}

void read_meta(std::istream& is) {
    char discard;
    node_id_t vertex_id;
    std::string name;
    is >> discard >> vertex_id;
    std::getline(is, name);
    meta[vertex_id] = name;
}

adjacency_list_t parse_file(std::string filename) {
    std::ifstream in(filename);
    token l;
    edge_list_t edge_list;
    while ((l = get_line_type(in)) != END_OF_FILE) {
        edge e;
        switch (l) {
        case token::EDGE:
            e = read_edge(in);
            edge_list.push_back(e);
            break;
        case token::META:
            read_meta(in);
            break;
        default:
            std::string comment;
            std::getline(in, comment);
        }
    }
    return adjacency_list_t{ meta, edge_list };
}