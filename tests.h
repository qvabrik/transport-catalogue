#pragma once

void TestAddStop();
void TestAddBus();
void TestGetBusInfo();

void RunAllTests();



//InputReader ir;
//std::string s1{ "Stop Panfila: 10.234642, 11.123456" };
//std::string s2{ "Stop October: 37.544363, 33.235676" };
//std::string s3{ "Stop Olga: 38.590881, 34.724362" };
//std::string b1{ "Bus 10ka: Olga > October > Panfila" };
//std::string b2{ "Bus 12 ka: Olga - October - Panfila" };
//
//ir.ReadQuery(std::move(s1));
//ir.ReadQuery(std::move(b1));
//ir.ReadQuery(std::move(s2));
//ir.ReadQuery(std::move(s3));
//ir.ReadQuery(std::move(b2));
//
//ir.Push(Tcat);
//
//std::string query{ "Bus 10ka" };
//std::string query1{ "Bus 12 ka" };
//std::string query2{ "Bus Marshrutos" };
//
//StatReader sr;
//
//sr.ProcessQuery(std::move(query), Tcat);
//sr.ProcessQuery(std::move(query1), Tcat);
//sr.ProcessQuery(std::move(query2), Tcat);