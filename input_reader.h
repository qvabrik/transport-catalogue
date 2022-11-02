#pragma once
#include <tuple>
#include <vector>
#include <string>

#include "geo.h"
#include "transport_catalogue.h"

class InputReader {
public:
	void ReadQuery(std::string&& line);
	void Push(TransportCatalogue& tcat);
private:
	std::vector<std::tuple<std::string, double, double>> stops_;
	std::vector<std::tuple<std::string, bool, std::vector<std::string>>> buses_;

	void ProcessStopQuery(std::string&& line);
	void ProcessBusQuery(std::string&& line);
};