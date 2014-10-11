// list of usable generated maps/rooms

#ifndef MAPS_H
#define MAPS_H

#include "Map.h"

std::vector<mapInfo> map01_init(){
	int map[8][13] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};

	std::vector<mapInfo> mapStruct;

	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 13; x++){
			mapInfo mapStructInfo;
			mapStructInfo.x = x;
			mapStructInfo.y = y;
			mapStructInfo.type = map[y][x];
			mapStruct.push_back(mapStructInfo);
		}
	}

	return mapStruct;
}

#endif