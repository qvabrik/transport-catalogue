#include <iostream>
#include <sstream>

#include "transport_catalogue.h"
#include "input_reader.h"
#include "stat_reader.h"
#include "tests.h"

std::string ReadLine() {
    std::string s;
    getline(std::cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    std::cin >> result;
    ReadLine();
    return result;
}

int main() {
	//RunAllTests();

    size_t times = ReadLineWithNumber();

    TransportCatalogue tcat;
    InputReader ir;

    //std::istringstream input("Stop Tolstopaltsevo: 55.611087, 37.208290\n"
    //    "Stop Marushkino: 55.595884, 37.209755\n"
    //    "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
    //    "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
    //    "Stop Rasskazovka: 55.632761, 37.333324\n"
    //    "Stop Biryulyovo Zapadnoye: 55.574371, 37.651700\n"
    //    "Stop Biryusinka: 55.581065, 37.648390\n"
    //    "Stop Universam: 55.587655, 37.645687\n"
    //    "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
    //    "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164);\n");

    std::string line;
    for (size_t i = 0; i < times; ++i) {
        line = ReadLine();
        ir.ReadQuery(std::move(line));
    }

    //for (size_t i = 0; i < times; ++i) {
    //    ir.ReadQuery(ReadLine());
    //}

    ir.Push(tcat);

    times = ReadLineWithNumber();
    StatReader sr;
    for (size_t i = 0; i < times; ++i) {
        sr.ProcessQuery(ReadLine(), tcat);
    }

//    InputReader ir;
//std::string s1{ "Stop Panfila: 10.234642, 11.123456" };
//std::string s2{ "Stop October: 37.544363, 33.235676" };
//std::string s3{ "Stop Olga: 38.590881, 34.724362" };
//std::string b1{ "Bus 10ka: Olga > October > Panfila" };
//std::string b2{ "Bus 12ka: Olga - October" };
//
//ir.ReadQuery(std::move(s1));
//ir.ReadQuery(std::move(b1));
//ir.ReadQuery(std::move(s2));
//ir.ReadQuery(std::move(s3));
//ir.ReadQuery(std::move(b2));
//
//ir.Push(tcat);
//
//std::string query{ "Bus 10ka" };
//std::string query1{ "Bus 12 ka" };
//std::string query2{ "Bus Marshrutos" };
//
//StatReader sr;
//
//sr.ProcessQuery(std::move(query), tcat);
//sr.ProcessQuery(std::move(query1), tcat);
//sr.ProcessQuery(std::move(query2), tcat);

	return 0;
}