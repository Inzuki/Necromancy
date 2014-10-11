#include "Map.h"

Map::Map(){ // initialize blank map
	int x = 0, y = 0;
	for(int i = 0; i < 104; i++){
		mapInfo map;
		map.x = x;
		map.y = y;
		map.type = 0;
		mapStruct.push_back(map);

		x++;
		if(x > 12){
			y++;
			x = 0;
		}
	}
}

std::vector<mapInfo> Map::getMap(){
	return mapStruct;
}

void Map::setMap(std::vector<mapInfo> mapStructInfo){
	mapStruct = mapStructInfo;
}