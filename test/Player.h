#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

struct anim {
	char name[128];
	int frames;
	int startPixel;
	int width, height;
	int speed;
};

class Player {
	public:
		Player();
		Player(char[]);
		sf::Vector2f getPosition();
		void move(char *direction);

		char *getName();
		int level, exp;

		// for animations
		void loadSpriteSheet(char *filePath);
		void setAnim(char *animationName);
		sf::Sprite draw();
		void updatePlayer(bool);
		bool stop;

		void createAnim(char* animationName,
						int   startOfAnimation_Pixel,
						int   numberOfFrames,
						int   width,
						int   height,
						int   speedOfAnimation);

	private:
		char name[1024];
		float x, y, velocity;
		
		// for animations
		sf::Clock frameTime;
		anim currentAnim;
		int currentFrame;
		sf::Image spriteSheet_image;
		sf::Texture spriteSheet_text;
		sf::Sprite spriteSheet;
		std::vector<anim> anims;
};

#endif