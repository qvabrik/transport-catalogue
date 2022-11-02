#include<algorithm>
#include<unordered_set>
#include<stdexcept>

#include "transport_catalogue.h"

Stop& TransportCatalogue::AddStop(std::string&& name, double const lat, double const lng) {
	if (!name.size())
		throw std::invalid_argument("Stop's name cannot be empty");

	Stop& result = stops_.emplace_back(std::move(Stop{ std::move(name), Coordinates{lat, lng} }));
	stopname_to_stopdata_[result.name] = &result;
	return result;
}

Bus& TransportCatalogue::AddBus(std::string&& name, bool const is_circle, std::vector<std::string>&& stops_names) {
	if (!name.size())
		throw std::invalid_argument("Bus's name cannot be empty");

	std::vector<const Stop*> stops;
	stops.reserve(stops_names.size());
	double lenght = 0.;

	//form a stops vector
	for (auto it = stops_names.begin(); it != stops_names.end(); ++it) {
		stops.push_back(stopname_to_stopdata_.at(*it));
		if (next(it) != stops_names.end())
			lenght += ComputeDistance(stopname_to_stopdata_.at(*it)->coordinates, stopname_to_stopdata_.at(*(next(it)))->coordinates);
	}
	if (!is_circle) {
		lenght *= 2;
		stops.reserve(stops_names.size() * 2);
		for (auto it = next(stops_names.rbegin()); it != stops_names.rend(); ++it)
			stops.push_back(stopname_to_stopdata_.at(*it));
	}

	std::sort(stops_names.begin(), stops_names.end());
	size_t unique_stops = std::unique(stops_names.begin(), stops_names.end()) - stops_names.begin();

	Bus& result = buses_.emplace_back(std::move(	Bus{ std::move(name), std::move(stops), lenght, unique_stops, is_circle	}));
	busname_to_busdata_[result.name] = &result;
	return result;
}

Stop* TransportCatalogue::FindStop(std::string const& name) {
	if (stopname_to_stopdata_.count(name))
		return stopname_to_stopdata_.at(name);
	return nullptr;
}

Bus* TransportCatalogue::FindBus(std::string const& name) {
	if (busname_to_busdata_.count(name))
		return busname_to_busdata_.at(name);
	return nullptr;
}

Bus const* TransportCatalogue::GetBusInfo(std::string const& name) const {
	if (!busname_to_busdata_.count(name))
		return nullptr;
	return busname_to_busdata_.at(name);
}

//============ private

size_t TransportCatalogue::PairStopHasher::operator()(Stop* lhs, Stop* rhs) const {
	return static_cast<size_t>(std::hash<std::string>{}(lhs->name) * 42 + std::hash<std::string>{}(rhs->name));
}