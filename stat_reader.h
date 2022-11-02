#pragma once
#include <string>

#include "transport_catalogue.h"

class StatReader {
public:
	void ProcessQuery(std::string&& line, TransportCatalogue const& tcat) const;
	void PrintBusInfo(std::string&& bus, TransportCatalogue const& tcat) const;
};