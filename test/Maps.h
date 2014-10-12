// list of usable generated maps/rooms

#ifndef MAPS_H
#define MAPS_H

#include "Map.h"

/* a blank map

	int map[8][13] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
*/

std::vector<mapInfo> map01_init(){
	int map[8][13] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 2, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 3 }
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
		mapPFPF.F = 0;
		mapPFPF.checked = false;
		mapPFPF.path = false;
		mapPF.push_back(mapPFPF);
	}
}

void doPathFind(std::vector<mapInfoPF> &mapPF){
	int hTargetX = -1, hTargetY = -1,
		currentI = -1;

	for(std::vector<mapInfoPF>::size_type i = 0; i < mapPF.size(); i++){
		if(mapPF[i].type == 2) // get start's coordinates
			currentI = i;
		else if(mapPF[i].type == 3){ // get finish's coordinates
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

	//while(!done){
		int checkAround[8] = { -1, 1, -13, 13, -14, -12, 12, 14 };
		// respectively: check left, right, above, below, top-left, top-right, bottom-left, bottom-right

		for(int a = 0; a < 5; a++){
		for(int i = 0; i < 8; i++){
			// don't go out of bounds
			if((currentI + checkAround[i]) > 0 && (currentI + checkAround[i]) < 104){
				// check if the space isn't a wall AND check if the space is not already on the path list
				if((mapPF[currentI + checkAround[i]].type != 1) && (mapPF[currentI + checkAround[i]].path == false)){
					// make sure the check doesn't wrap around the map
					if(mapPF[currentI].x == 0 && mapPF[currentI + checkAround[i]].x == 12){
						// do fuck all
					}else {
						// check if the neighbor is is the finish
						if(mapPF[currentI + checkAround[i]].type == 3){
							done = true;
						}else {
							printf("%i\n", mapPF[currentI].G);

							if(i > 3 && i < 8) // if the space is in the X (the diagonals)
								mapPF[currentI + checkAround[i]].G = mapPF[currentI].G + 14;
							else // if the space is in the cross
								mapPF[currentI + checkAround[i]].G = mapPF[currentI].G + 10;

							mapPF[currentI + checkAround[i]].F = mapPF[currentI + checkAround[i]].G + mapPF[currentI + checkAround[i]].H;
						
							// check if the current F score is the lowest out of all the neighbors
							if((mapPF[currentI + checkAround[i]].F) < currentHighF){
								currentHighF = mapPF[currentI + checkAround[i]].F;
								nextI = currentI + checkAround[i];
							}

							mapPF[currentI + checkAround[i]].checked = true;
						}
					}
				}
			}
		}
		//}

		currentI = nextI;
		mapPF[currentI].path = true;
		currentHighF = 666;
	}
}

#endif