// list of usable generated maps/rooms

#ifndef MAPS_H
#define MAPS_H

#include "Map.h"

std::vector<mapInfo> map01_init(){
	int map[8][13] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
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

// pathfinding crap
void setUpMap(std::vector<mapInfo> &map, std::vector<mapInfoPF> &mapPF){ // keep for now?
	for(std::vector<mapInfoPF>::size_type i = 0; i < map.size(); i++){
		mapInfoPF mapPFPF;
		mapPFPF.x = map[i].x;
		mapPFPF.y = map[i].y;
		mapPFPF.type = map[i].type;
		mapPFPF.G = 0;
		mapPFPF.H = 0;
		mapPFPF.F = mapPFPF.G + mapPFPF.H;
		mapPFPF.checked = false;
		mapPFPF.path = false;
		mapPF.push_back(mapPFPF);
	}
}

void doPathFind(std::vector<mapInfoPF> &mapPF){
	int hTargetX = -1, hTargetY = -1,
		currentX = -2, currentY = -2,
		currentI = -1;

	for(std::vector<mapInfoPF>::size_type i = 0; i < mapPF.size(); i++){
		if(mapPF[i].type == 2){ // get start's coordinates
			currentX = mapPF[i].x;
			currentY = mapPF[i].y;
			currentI = i;
		}else if(mapPF[i].type == 3){ // get finish's coordinates
			hTargetX = mapPF[i].x;
			hTargetY = mapPF[i].y;
		}
	}

	for(std::vector<mapInfoPF>::size_type i = 0; i < mapPF.size(); i++){ // calculate hieuristics
		if(mapPF[i].type == 0)
			mapPF[i].H = (abs(mapPF[i].x - hTargetX)) * 10 + (abs(mapPF[i].y - hTargetY)) * 10;
	}

	int currentHighF = 666, // spoopy
		nextI = -1;

	bool done = false;

	while(!done){
		int checkAround[8] = { -1, 1, -13, 13, -14, -12, 12, 14 };
		// respectively: check left, right, above, below, top-left, top-right, bottom-left, bottom-right
		
		printf("Current Space: ( %i, %i )\nTarget Space: ( %i, %i )\n\n", currentX, currentY, hTargetX, hTargetY);

		for(int i = 0; i < 8; i++){
			if((mapPF[currentI + checkAround[i]].type == 0) && (mapPF[currentI + checkAround[i]].path == false)){
				if(mapPF[currentI + checkAround[i]].H == 10)
					done = true;

				if(i >= 0 && i < 4)
					mapPF[currentI + checkAround[i]].G = mapPF[currentI].G + 10;
				else
					mapPF[currentI + checkAround[i]].G = mapPF[currentI].G + 14;

				mapPF[currentI + checkAround[i]].F = mapPF[currentI + checkAround[i]].G + mapPF[currentI + checkAround[i]].H;
				mapPF[currentI + checkAround[i]].checked = true;

				if((mapPF[currentI + checkAround[i]].F < currentHighF)){
					currentHighF = mapPF[currentI + checkAround[i]].F;
					nextI = currentI + checkAround[i];
				}
			}
		}

		currentI = nextI;
		mapPF[currentI].path = true;
		currentX = mapPF[currentI].x;
		currentY = mapPF[currentI].y;
		currentHighF = 666;
	}
}

#endif