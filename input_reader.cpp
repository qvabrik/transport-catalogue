#include <algorithm>

#include "input_reader.h"

//private

void InputReader::ProcessStopQuery(std::string&& line) {
	stops_.push_back(std::move(std::make_tuple(
		line.substr(0, line.find(':')), /*name*/
		std::stod(line.substr(line.find(':') + 2, 9)), /*lat*/
		std::stod(line.substr(line.find(',') + 2, 9)) /*lng*/
		)));
}

void InputReader::ProcessBusQuery(std::string&& line) {
	//figure out: circle or not
	bool is_circle = false;
	if (line.find('>') != std::string::npos)
		is_circle = true;
	
	//make a stops vector
	std::string_view linesv{ line };
	std::vector<std::string> stops;

	auto cursor = (linesv.find(':')) + 2;
	linesv.remove_prefix(cursor);
	while (cursor != std::string::npos) {
		cursor = linesv.find_first_of("->");
		stops.push_back(std::string{ linesv.substr(0, cursor - 1) });
		linesv.remove_prefix(linesv.find_first_of("->") + 2);
	}

	buses_.push_back(std::move(std::make_tuple(
		line.substr(0, line.find(':')), /*name*/
		is_circle,
		std::move(stops)
	)));
}


//public

void InputReader::ReadQuery(std::string&& line) {
	if (!line.size())
		return;
	auto cursor = line.find(' ');
	line.substr(0, cursor) == "Stop" ? ProcessStopQuery(std::move(line.substr(cursor + 1))) : ProcessBusQuery(std::move(line.substr(cursor + 1)));
}

void InputReader::Push(TransportCatalogue& tcat) {
	for (auto& [name, lat, lng] : stops_)
		tcat.AddStop(std::move(name), lat, lng);
	for (auto& [name, is_circle, stops] : buses_)
		tcat.AddBus(std::move(name), is_circle, std::move(stops));
	stops_.clear();
	buses_.clear();
}