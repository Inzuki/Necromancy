#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Maps.h"

void loadSpriteFromTexture(sf::Texture &texture, sf::Sprite &sprite, char *file);
void loadSpriteFromImage(sf::Image &image, sf::Texture &texture, sf::Sprite &sprite, char *file);

int main(){
	Maps maps;

	// Initialize Window
	sf::ContextSettings cSettings;
	sf::RenderWindow window(sf::VideoMode(650, 750), "Necromancy", sf::Style::Close, cSettings);
	window.setVerticalSyncEnabled(true);

	#pragma region imageLoading
	// Sprites
		// map(s)
		sf::Texture map1_text; sf::Sprite map1;
		loadSpriteFromTexture(map1_text, map1, "Resources/Images/map1.png");

		// simple GUI
			// bg
			sf::Texture bgGUI_text; sf::Sprite bgGUI;
			loadSpriteFromTexture(bgGUI_text, bgGUI, "Resources/Images/BGGUI.png");
			bgGUI.setPosition(0, 550);

			// necronomicon
			sf::Image necroBGStart_image; sf::Texture necroBGStarter_text; sf::Sprite necroBGStarter;
			loadSpriteFromImage(necroBGStart_image, necroBGStarter_text, necroBGStarter, "Resources/Images/NecronomiconBGStarter.png");

			sf::Image necroBG_image; sf::Texture necroBG_text; sf::Sprite necroBG;
			loadSpriteFromImage(necroBG_image, necroBG_text, necroBG, "Resources/Images/NecronomiconBG.png");
			float necroX = 50, necroY = 50;
			
			sf::Texture tile_text; sf::Sprite tile;
			loadSpriteFromTexture(tile_text, tile, "Resources/Images/test.png");
			tile.setColor(sf::Color(255, 255, 255, 5));
			
			sf::Image rock_image; sf::Texture rock_text; sf::Sprite rock;
			loadSpriteFromImage(rock_image, rock_text, rock, "Resources/Images/rock.png");
	// Text
		sf::Font arial; arial.loadFromFile("Resources/Font/arial.ttf");
		sf::Text name("", arial);
		name.setCharacterSize(25);
	#pragma endregion

	Player james("Inzuki");
		james.loadSpriteSheet("Resources/Images/James.png");
		james.createAnim("walk_down",  0,   4, 32, 87, 200);
		james.createAnim("walk_up",    87,  4, 32, 87, 200);
		james.createAnim("walk_right", 174, 4, 32, 87, 200);
		james.createAnim("walk_left",  261, 4, 32, 87, 200);
		james.setAnim("walk_down");

	bool necroBook = false;

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Q)) // toggle Necronomicon
				necroBook = !necroBook;
		}
		
		#pragma region movement
		/*if(
			(!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		){
			james.stop = true;
		}else
			james.stop = false;

		if(!necroBook){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				james.move("up");
				james.setAnim("walk_up");
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				james.move("down");
				james.setAnim("walk_down");
			}
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				james.move("left");
				james.setAnim("walk_left");
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				james.move("right");
				james.setAnim("walk_right");
			}
		}*/
		#pragma endregion

		window.clear();
		window.draw(map1);
		
		 for(std::vector<std::vector<int>>::size_type y = 0; y < maps.getMap(1).size(); y++){
			for(std::vector<std::vector<int>>::size_type x = 0; x < maps.getMap(1)[y].size(); x++){
				if(maps.getMap(1)[y][x] == 0){
					tile.setPosition((float)x * 50, 140 + ((float)y * 50));
					window.draw(tile);
				}else if(maps.getMap(1)[y][x] == 1){
					rock.setPosition((float)x * 50, 140 + ((float)y * 50));
					window.draw(rock);
				}
			}
		}
		
		//james.updatePlayer(necroBook);
		//window.draw(james.draw());

		// draw GUI
		window.draw(bgGUI);

		if(necroBook){
			necroX += 2.f;
			necroY += 1.f;
			necroBGStarter.setPosition(50.f + (sin(necroX / 50.f) * 3.f), (50.f + cos(necroY / 12.5f) * 2.f));
			window.draw(necroBGStarter);
		}

		window.display();
	}

	return 0;
}

void loadSpriteFromTexture(sf::Texture &texture, sf::Sprite &sprite, char *file){
	texture.loadFromFile(file);
	sprite.setTexture(texture);
}

void loadSpriteFromImage(sf::Image &image, sf::Texture &texture, sf::Sprite &sprite, char *file){
	image.loadFromFile(file);
	image.createMaskFromColor(sf::Color::Magenta);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}