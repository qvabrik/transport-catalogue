#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <deque>
#include <unordered_map>
#include <optional>

#include "geo.h"

struct Stop {
	std::string name;
	Coordinates coordinates {0., 0.};
};

struct Bus {
	std::string name;
	std::vector<const Stop*> route;
	double lenght = 0.;
	size_t unique_stops = 0;
	bool is_circle = false;
};

class TransportCatalogue {
public:
	TransportCatalogue() = default;

	Stop& AddStop(std::string&& name, double const lat, double const lng);
	Bus& AddBus(std::string&& name, bool const is_circle, std::vector<std::string>&& stops_names);

	//std::optional<const Stop*> FindStop(std::string& name);
	Stop* FindStop(std::string const& name);
	Bus* FindBus(std::string const& name);

	Bus const* GetBusInfo(std::string const& name) const;

private:
	//stops storage
	std::deque<Stop> stops_;
	std::unordered_map<std::string_view, Stop*> stopname_to_stopdata_;
	//buses storage
	std::deque<Bus> buses_;
	std::unordered_map<std::string_view, Bus*> busname_to_busdata_;
	//distance between stops
	class PairStopHasher {
	public:
		size_t operator()(Stop* lhs, Stop* rhs) const;
	};
	std::unordered_map<Stop*, Stop*, PairStopHasher> distances_;
};
