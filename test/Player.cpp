#include "Player.h"

Player::Player(){
	sprintf_s(name, "JD & AH");
	x = 100.f;
	y = 100.f;
	velocity = 3.f;
	currentFrame = 0;
	stop = false;
	level = 0;
	exp = 0;
}

Player::Player(char nameInit[]){
	sprintf_s(name, nameInit);
	x = 100.f;
	y = 100.f;
	velocity = 3.f;
	currentFrame = 0;
	stop = false;
	level = 0;
	exp = 0;
}

sf::Vector2f Player::getPosition(){
	return sf::Vector2f(x, y);
}

char *Player::getName(){
	return name;
}

void Player::move(char *dir){
	if(strcmp(dir, "up") == 0)
		y -= velocity;
	else if(strcmp(dir, "left") == 0)
		x -= velocity;
	else if(strcmp(dir, "down") == 0)
		y += velocity;
	else if(strcmp(dir, "right") == 0)
		x += velocity;
}

void Player::loadSpriteSheet(char *file){
	spriteSheet_image.loadFromFile(file);
	spriteSheet_image.createMaskFromColor(sf::Color::Magenta);
	spriteSheet_text.loadFromImage(spriteSheet_image);
	spriteSheet.setTexture(spriteSheet_text);
}

void Player::createAnim(char *animName, int startPixel, int frames, int width, int height, int speed){
	anim animation;
	sprintf_s(animation.name, animName);
	animation.frames = frames;
	animation.startPixel = startPixel;
	animation.width = width;
	animation.height = height;
	animation.speed = speed;
	anims.push_back(animation);
}

void Player::setAnim(char *animName){
	for(int i = 0; i < anims.size(); i++)
		if(strcmp(anims[i].name, animName) == 0)
			currentAnim = anims[i];
}

sf::Sprite Player::draw(){
	spriteSheet.setTextureRect(sf::IntRect(
		currentFrame * currentAnim.width,
		currentAnim.startPixel,
		currentAnim.width,
		currentAnim.height
	));

	return spriteSheet;
}

void Player::updatePlayer(bool necroBook){
	if((frameTime.getElapsedTime().asMilliseconds() > currentAnim.speed) && !stop && !necroBook){
		frameTime.restart();

		currentFrame++;

		if(currentFrame >= currentAnim.frames)
			currentFrame = 0;
	}else if(stop)
		currentFrame = 0;

	spriteSheet.setPosition(x, y);
}