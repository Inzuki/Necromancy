#ifndef MAP_H
#define MAP_H

#include <vector>

struct mapInfo {
	int x, y;
	int type;
};

struct mapInfoPF {
	int x, y;
	int type;
	int F, G, H;
	bool checked, path;
};

class Map {
	public:
		Map();
		std::vector<mapInfo> getMap();
		void setMap(std::vector<mapInfo>);

	private:
		std::vector<mapInfo> mapStruct; // array that holds map values
};

#endif