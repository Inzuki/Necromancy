// list of usable generated maps/rooms

#ifndef MAPS_H
#define MAPS_H

#include <vector>

class Maps {
	public:
		Maps();
		std::vector<std::vector<int>> getMap(int);

	private:
		std::vector<std::vector<int>>map01;
};

#endif