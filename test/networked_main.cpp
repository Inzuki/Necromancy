/*#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include "sockwrap.h"
#include <iostream>

#define MAX_PLAYERS 2

typedef void(*listenFunc)(char*);
void listenThread(char recvBuff[1024]);
void removeSignal(char recvBuff[1024]); // remove the identifier in front of the buffer

struct Players {
	bool exists;
	char name[1024];
	float x, y,
		  vel;
	bool w, a, s, d;
	bool shoot[4];
} players[MAX_PLAYERS];

struct Bullets {
	float x, y;
	int dir;
};

int id = -1;

int main(){
	// Initialize Window
	sf::ContextSettings cSettings;
	sf::RenderWindow window(sf::VideoMode(650, 750), "Dongon", sf::Style::Default, cSettings);
	window.setFramerateLimit(60);
	
	// get moniker
	char moniker[1024];
	//printf("Please enter a moniker:\n> ");
	//gets_s(moniker);
	sprintf_s(moniker, "Inzuki");

	// initialize client and attempt connection to server
	listenFunc l = &listenThread;
	char ip[16];
	sprintf_s(ip, "134.129.85.252"); // connect to my laptop
	Client client(ip, 3993, 1024, l);
	client.StartListenThread();
	
	printf("Connecting to %s...\n", ip);

	char srvrBuff[1024];
	sprintf_s(srvrBuff, "0%s", moniker);
	client.Send(srvrBuff);

	// initialize Players to hold client data
	for(int i = 0; i < MAX_PLAYERS; i++){
		sprintf_s(players[i].name, "AH&JD");

		players[i].exists   = false;
		players[i].x	    = 100.f;
		players[i].y        = 100.f;
		players[i].vel      = 3.f;
		players[i].w        = false;
		players[i].a        = false;
		players[i].s        = false;
		players[i].d        = false;
		players[i].shoot[0] = false;
		players[i].shoot[1] = false;
		players[i].shoot[2] = false;
		players[i].shoot[3] = false;
	}

	std::vector<Bullets> bullets;

	// Sprites
		// temporary player sprite
		sf::RectangleShape tempPlayer(sf::Vector2f(25, 25));
		tempPlayer.setFillColor(sf::Color::Green);

		// temporary bullet sprite
		sf::RectangleShape tempBullet(sf::Vector2f(10, 10));
		tempBullet.setOutlineColor(sf::Color(75, 25, 25));
		tempBullet.setFillColor(sf::Color(205, 55, 55));
		tempBullet.setOutlineThickness(1.f);

		// map(s)
		sf::Texture map1_text;
		map1_text.loadFromFile("map1.png"); // a shitty map
		sf::Sprite map1;
		map1.setTexture(map1_text);

		// simple GUI
			sf::RectangleShape bgGUI(sf::Vector2f(650, 200));
			bgGUI.setPosition(0.f, 550.f);
			bgGUI.setFillColor(sf::Color(155, 155, 155));

			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(0,   550)),
				sf::Vertex(sf::Vector2f(650, 550))
			};
			sf::Vertex line2[] = {
				sf::Vertex(sf::Vector2f(650 / 2, 550)),
				sf::Vertex(sf::Vector2f(650 / 2, 750))
			};

	// Text
		sf::Font arial; arial.loadFromFile("arial.ttf");

		sf::Text name("", arial);
		name.setCharacterSize(25);

	// prevent spamming the server with keypresses
	bool moveUp    = false,
		 moveLeft  = false,
		 moveDown  = false,
		 moveRight = false,
	     shootUp    = false,
		 shootLeft  = false,
		 shootDown  = false,
		 shootRight = false;

	sf::Clock timer;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				sprintf_s(srvrBuff, "1%i", id);
				client.Send(srvrBuff);
				window.close();
			}
			
			#pragma region keyboard player shooting
			// shoot up
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !shootUp){
				shootUp = true;
				sprintf_s(srvrBuff, "4%i,0;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up){
				shootUp = false;
				sprintf_s(srvrBuff, "5%i,0;", id);
				client.Send(srvrBuff);
			}
			
			// shoot left
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && !shootLeft){
				shootLeft = true;
				sprintf_s(srvrBuff, "4%i,1;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left){
				shootLeft = false;
				sprintf_s(srvrBuff, "5%i,1;", id);
				client.Send(srvrBuff);
			}
			
			// shoot down
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !shootDown){
				shootDown = true;
				sprintf_s(srvrBuff, "4%i,2;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down){
				shootDown = false;
				sprintf_s(srvrBuff, "5%i,2;", id);
				client.Send(srvrBuff);
			}

			// shoot right
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && !shootRight){
				shootRight = true;
				sprintf_s(srvrBuff, "4%i,3;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right){
				shootRight = false;
				sprintf_s(srvrBuff, "5%i,3;", id);
				client.Send(srvrBuff);
			}
			#pragma endregion
			#pragma region keyboard player movement

			// move up
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && !moveUp){
				moveUp = true;
				sprintf_s(srvrBuff, "2%i,0;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W){
				moveUp = false;
				sprintf_s(srvrBuff, "3%i,0;", id);
				client.Send(srvrBuff);
			}
			
			// move left
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A && !moveLeft){
				moveLeft = true;
				sprintf_s(srvrBuff, "2%i,1;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A){
				moveLeft = false;
				sprintf_s(srvrBuff, "3%i,1;", id);
				client.Send(srvrBuff);
			}
			
			// move down
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && !moveDown){
				moveDown = true;
				sprintf_s(srvrBuff, "2%i,2;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S){
				moveDown = false;
				sprintf_s(srvrBuff, "3%i,2;", id);
				client.Send(srvrBuff);
			}
			
			// move right
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D && !moveRight){
				moveRight = true;
				sprintf_s(srvrBuff, "2%i,3;", id);
				client.Send(srvrBuff);
			}else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D){
				moveRight = false;
				sprintf_s(srvrBuff, "3%i,3;", id);
				client.Send(srvrBuff);
			}
			#pragma endregion
		}

		window.clear();

		window.draw(map1);

		// display & run bullet info
		for(int i = 0; i < bullets.size(); i++){
			switch(bullets[i].dir){
				case 0:
					bullets[i].y -= 5.f;
				break;
				case 1:
					bullets[i].x -= 5.f;
				break;
				case 2:
					bullets[i].y += 5.f;
				break;
				case 3:
					bullets[i].x += 5.f;
				break;
			}

			tempBullet.setPosition(bullets[i].x, bullets[i].y);
			window.draw(tempBullet);

			if(bullets[i].x > 650.f || bullets[i].x < 0.f || bullets[i].y > 550.f || bullets[i].y < 0.f)
				bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
		}
		
		// display & run player info
		for(int i = 0; i < MAX_PLAYERS; i++){
			if(players[i].exists){
				if(players[i].shoot[0]){
					if(timer.getElapsedTime().asMilliseconds() > 300){
						timer.restart();

						Bullets bullet;
						bullet.x   = players[i].x;
						bullet.y   = players[i].y;
						bullet.dir = 0;
						bullets.push_back(bullet);
					}
				}
				if(players[i].shoot[1]){
					if(timer.getElapsedTime().asMilliseconds() > 300){
						timer.restart();

						Bullets bullet;
						bullet.x   = players[i].x;
						bullet.y   = players[i].y;
						bullet.dir = 1;
						bullets.push_back(bullet);
					}
				}
				if(players[i].shoot[2]){
					if(timer.getElapsedTime().asMilliseconds() > 300){
						timer.restart();

						Bullets bullet;
						bullet.x   = players[i].x;
						bullet.y   = players[i].y;
						bullet.dir = 2;
						bullets.push_back(bullet);
					}
				}
				if(players[i].shoot[3]){
					if(timer.getElapsedTime().asMilliseconds() > 300){
						timer.restart();

						Bullets bullet;
						bullet.x   = players[i].x;
						bullet.y   = players[i].y;
						bullet.dir = 3;
						bullets.push_back(bullet);
					}
				}

				// handle player movement
				if(players[i].w)
					players[i].y -= players[i].vel;
				if(players[i].s)
					players[i].y += players[i].vel;
				if(players[i].a)
					players[i].x -= players[i].vel;
				if(players[i].d)
					players[i].x += players[i].vel;
				
				// display players
				name.setCharacterSize(16);
				name.setPosition(players[i].x + 12.5f, players[i].y - 15);
				name.setString(players[i].name);
				name.setOrigin(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2);
				window.draw(name);

				tempPlayer.setPosition(players[i].x, players[i].y);
				window.draw(tempPlayer);
			}
		}

		// draw GUI
		window.draw(bgGUI);

		for(int i = 0; i < MAX_PLAYERS; i++){
			if(players[i].exists){
				if(i == 0){
					name.setCharacterSize(25);
					name.setPosition(15.f, 565.f);
					name.setString(players[i].name);
					name.setOrigin(0, 0);
					window.draw(name);
				}else if(i == 1){
					name.setCharacterSize(25);
					name.setPosition(635.f, 565.f);
					name.setString(players[i].name);
					name.setOrigin(name.getLocalBounds().width, 0);
					window.draw(name);
				}
			}
		}

		window.draw(line,  2, sf::Lines);
		window.draw(line2, 2, sf::Lines);

		window.display();
	}
	
	client.StopListenThread();

	return 0;
}

void listenThread(char recvBuff[1024]){
	switch(recvBuff[0]){
		case '0': // response from the server that client connected successfully
			removeSignal(recvBuff);
			
			id = atoi(recvBuff);

			printf("Connected successfully.\n---------------\n", id);

			players[id].exists = true;
		break;
		case '1': // server full
			printf("Server is full.\n");
		break;
		case '2':{ // player starts moving 
			removeSignal(recvBuff);
			
			int Cid = atoi(strtok(recvBuff, ",")),
				dir = atoi(strtok(NULL,	    ";"));

			if(dir == 0)
				players[Cid].w = true;
			else if(dir == 1)
				players[Cid].a = true;
			else if(dir == 2)
				players[Cid].s = true;
			else if(dir == 3)
				players[Cid].d = true;
		break;
		}
		case '3':{ // player stops moving
			removeSignal(recvBuff);
			
			int Cid = atoi(strtok(recvBuff, ",")),
				dir = atoi(strtok(NULL,	    ";"));
			
			if(dir == 0)
				players[Cid].w = false;
			else if(dir == 1)
				players[Cid].a = false;
			else if(dir == 2)
				players[Cid].s = false;
			else if(dir == 3)
				players[Cid].d = false;
		break;
		}
		case '4':{ // when connected, receive info on already connected players
			removeSignal(recvBuff);

			int Cid = atoi(strtok(recvBuff, ","));

			players[Cid].exists = true;
			sprintf(players[Cid].name, strtok(NULL, ";"));
			printf("%s is connected.\n", players[Cid].name);
		break;
		}
		case '5':{ // tell already connected clients a new client has connected
			removeSignal(recvBuff);

			int Cid = atoi(strtok(recvBuff, ","));

			players[Cid].exists = true;
			sprintf(players[Cid].name, strtok(NULL, ";"));
			printf("%s has connected.\n", players[Cid].name);
		break;
		}
		case '6':{ // player starts shooting
			removeSignal(recvBuff);
			
			int Cid = atoi(strtok(recvBuff, ",")),
				dir = atoi(strtok(NULL,	    ";"));

			if(dir == 0)
				players[Cid].shoot[0] = true;
			else if(dir == 1)
				players[Cid].shoot[1] = true;
			else if(dir == 2)
				players[Cid].shoot[2] = true;
			else if(dir == 3)
				players[Cid].shoot[3] = true;
		break;
		}
		case '7':{ // player stops shooting
			removeSignal(recvBuff);
			
			int Cid = atoi(strtok(recvBuff, ",")),
				dir = atoi(strtok(NULL,	    ";"));
			
			if(dir == 0)
				players[Cid].shoot[0] = false;
			else if(dir == 1)
				players[Cid].shoot[1] = false;
			else if(dir == 2)
				players[Cid].shoot[2] = false;
			else if(dir == 3)
				players[Cid].shoot[3] = false;
		break;
		}
	}
}

void removeSignal(char recvBuff[1024]){
	for(int i = 0; i < 1023; i++)
		recvBuff[i] = recvBuff[i + 1];
}*/