#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#define assertm(exp, msg) assert(((void)msg, exp))

#include "tests.h"
#include "transport_catalogue.h"

void TestAddStop() {
	TransportCatalogue ts;
	//TestEmptyName
	try {
		ts.AddStop("", 0., 0.);
		assertm(true, "Server shouldn't accept an empty stop's name");
	}
	catch (std::invalid_argument iaex) {
		std::string s{ "" };
		assert(ts.FindStop(s) == nullptr);
	}
	//TestNewStop
	std::string AddName{ "Panfila" };
	std::string SearchName{ "Panfila" };
	ts.AddStop(std::move(AddName), 34.345678, 35.345678);
	assert(ts.FindStop(SearchName)->name == "Panfila");
}
void TestAddBus() {
	TransportCatalogue ts;
	std::vector < std::tuple<std::string, double, double>> stops = {
		{"Panfila", 34.345678, 35.345678}, {"October", 36.345678, 37.345678}, {"Olga", 38.345678, 39.345678} 
	};
	for (auto [name, lan, lon] : stops) {
		ts.AddStop(std::move(name), lan, lon);
	}

	//TestEmptyName
	try {
		ts.AddStop("", 0., 0.);
		assertm(true, "Server shouldn't accept an empty stop's name");
	}
	catch (std::invalid_argument iaex) {
		std::string s{ "" };
		assert(ts.FindStop(s) == nullptr);
	}

	//TestLineWayBus
	ts.AddBus("10", false, { "Panfila", "October", "Olga" });
	assert(ts.FindBus("10")->name == "10");
	assert(ts.FindBus("10")->is_circle == false);
	assert(ts.FindBus("10")->route.size() == 3);
	assert(ts.FindBus("10")->unique_stops == 3);
	//TestCircleWayBus
	ts.AddBus("12", true, { "Panfila", "October", "Olga" });
	assert(ts.FindBus("12")->name == "12");
	assert(ts.FindBus("12")->is_circle == true);
	assert(ts.FindBus("12")->route.size() == 5);
	assert(ts.FindBus("12")->unique_stops == 3);

}

void RunAllTests() {
	TestAddStop();
	TestAddBus();
}