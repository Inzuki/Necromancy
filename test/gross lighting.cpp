/*
BLEHHH

void simulate(int(&map)[100][100], int(&map2)[100][100]){
	for(int y = 0; y < 100; y++){
		for(int x = 0; x < 100; x++){
			int neighbors = checkNeighbors(map, x, y);

			if(map2[x][y] == 1){
				if(neighbors < 4)
					map[x][y] = 0;
				else
					map[x][y] = 1;
			}else {
				if(neighbors > 4)
					map[x][y] = 1;
				else
					map[x][y] = 0;
			}
		}
	}

	for(int y = 0; y < 100; y++){
		for(int x = 0; x < 100; x++){
			map2[x][y] = map[x][y];
		}
	}
}

int checkNeighbors(int map[100][100], int x, int y){
	int count = 0;

	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			int neighborX = x + i;
			int neighborY = y + j;

			if(i == 0 && j == 0){
				// don't count the space you are in
			}else if(neighborX < 1 || neighborY < 1 || neighborX > 98 || neighborY > 98) // so it doesn't check out of array bounds
				count++;
			else if(map[neighborX][neighborY] == 1)
				count++;
		}
	}

	return count;
}

BLEHHH

void calculateLight(int(&map)[100][100], int map2[100][100]);
int checkNeighborLights(int map2[100][100], int x, int y);
int checkNeighborEdgeLights(int map2[100][100], int x, int y, int dir);

void calculateLight(int(&map)[100][100], int map2[100][100]){
	for(int y = 0; y < 100; y++){
		for(int x = 0; x < 100; x++){
			int neighbors;

			if(x == 0 && y == 0){
				neighbors = checkNeighborEdgeLights(map2, x, y, 4);

				if(neighbors == 1)
					map[x][y] = 2;
			}else if(x == 99 && y == 99){
				neighbors = checkNeighborEdgeLights(map2, x, y, 5);

				if(neighbors == 1)
					map[x][y] = 2;
			}else if(x == 0){
				neighbors = checkNeighborEdgeLights(map2, x, y, 0);

				if(neighbors == 1)
					map[x][y] = 2;
			}else if(x == 99){
				neighbors = checkNeighborEdgeLights(map2, x, y, 1);

				if(neighbors == 1)
					map[x][y] = 2;
			}else if(y == 0){
				neighbors = checkNeighborEdgeLights(map2, x, y, 2);

				if(neighbors == 1)
					map[x][y] = 2;
			}else if(y == 99){
				neighbors = checkNeighborEdgeLights(map2, x, y, 3);

				if(neighbors == 1)
					map[x][y] = 2;
			}else {
				neighbors = checkNeighborLights(map2, x, y);

				if(map2[x][y] == 1 && neighbors == 1)
					map[x][y] = 2;
				else if(map2[x][y] == 0 && neighbors == 3)
					map[x][y] = 4;
			}
		}
	}

	for(int y = 0; y < 100; y++){
		for(int x = 0; x < 100; x++){
			map2[x][y] = map[x][y];
		}
	}

	for(int y = 0; y < 100; y++){
		for(int x = 0; x < 100; x++){
			int neighbors;
			
			if(x == 0 && y == 0){
				neighbors = checkNeighborEdgeLights(map2, x, y, 4);
				
				if(neighbors == 1)
					map[x][y] = 3;
			}else {
				neighbors = checkNeighborLights(map2, x, y);

				if(map2[x][y] == 2 && neighbors == 2)
					map[x][y] = 3;
			}
		}
	}
}

int checkNeighborEdgeLights(int map2[100][100], int x, int y, int dir){ // use for checking values for light
	int count = 0, returnNum = 0,
		ii = 0, jj = 0,
		iii = 0, jjj = 0;

	switch(dir){
		case 0:
			ii = 0; jj = -1,
			iii = 2, jjj = 2;
		break;
		case 1:
			ii = -1; jj = -1,
			iii = 1, jjj = 2;
		break;
		case 2:
			ii = -1; jj = 0,
			iii = 2, jjj = 2;
		break;
		case 3:
			ii = -1; jj = -1,
			iii = 2, jjj = 1;
		break;
		case 4: // if x and y = 0
			ii = 0; jj = 0,
			iii = 2, jjj = 2;
		break;
		case 5: // if x and y = 99
			ii = -1; jj = -1,
			iii = 1, jjj = 1;
		break;
	}

	for(int i = ii; i < iii; i++){
		for(int j = jj; j < jjj; j++){
			int neighborX = x + i;
			int neighborY = y + j;

			if(i == 0 && j == 0){
				// don't count the space you are in
			}else {
				count += map2[neighborX][neighborY];

				if(count == 5)
					returnNum = 1;
				else if(count == 3 && (dir == 4 || dir == 5))
					returnNum = 1;
			}
		}
	}

	return returnNum;
}

int checkNeighborLights(int map2[100][100], int x, int y){ // use for checking values for light
	int count = 0, returnNum = 0;

	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			int neighborX = x + i;
			int neighborY = y + j;

			if(i == 0 && j == 0){
				// don't count the space you are in
			}else {
				if(neighborX >= 0 && neighborY >= 0 && neighborX <= 99 && neighborY <= 99){
					count += map2[neighborX][neighborY];

					if(count == 8)
						returnNum = 1;
					else if(count == 16)
						returnNum = 2;
					else if(count != 0)
						returnNum = 3;
				}
			}
		}
	}

	return returnNum;
}
*/