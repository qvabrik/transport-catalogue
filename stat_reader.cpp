#include <iostream>
#include <iomanip>

#include "stat_reader.h"

void StatReader::ProcessQuery(std::string&& line, TransportCatalogue const& tcat) const {
	PrintBusInfo(	std::move(line.substr(line.find(' ') + 1)), tcat	);
}

void StatReader::PrintBusInfo(std::string&& bus, TransportCatalogue const& tcat) const {
	std::cout << "Bus " << bus << ": ";
	Bus const* bus_info = tcat.GetBusInfo(bus);
	if (!bus_info) {
		std::cout << "not found" << std::endl;
		return;
	}
	std::cout << std::setprecision(6);
	std::cout << bus_info->route.size() << " stops on route, "
		<< bus_info->unique_stops << " unique stops, "
		<< bus_info->lenght << " route length" << std::endl;
}