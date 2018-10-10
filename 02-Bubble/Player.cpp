#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;

	spritesheetStandLeft.loadFromFile("images/standLeft_strip7.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteStandLeft = Sprite::createSprite(glm::ivec2(35, 64), glm::vec2(0.1428571429, 1.00), &spritesheetStandLeft, &shaderProgram);
	spriteStandLeft->setNumberAnimations(4);
	
		spriteStandLeft->setAnimationSpeed(STAND_LEFT, 8);
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.1428571429f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.2857142858f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.4285714287f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.5714285716f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.7142857145f, 0.f));
		spriteStandLeft->addKeyframe(STAND_LEFT, glm::vec2(0.8571428574f, 0.f));

	spriteStandLeft->changeAnimation(0);
	tileMapDispl = tileMapPos;
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetStandRight.loadFromFile("images/standRight_strip5.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteStandRight = Sprite::createSprite(glm::ivec2(29, 64), glm::vec2(0.20, 1.00), &spritesheetStandRight, &shaderProgram);
	spriteStandRight->setNumberAnimations(4);

	spriteStandRight->setAnimationSpeed(STAND_RIGHT, 8);
	spriteStandRight->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	spriteStandRight->addKeyframe(STAND_RIGHT, glm::vec2(0.20f, 0.f));
	spriteStandRight->addKeyframe(STAND_RIGHT, glm::vec2(0.40f, 0.f));
	spriteStandRight->addKeyframe(STAND_RIGHT, glm::vec2(0.60f, 0.f));
	spriteStandRight->addKeyframe(STAND_RIGHT, glm::vec2(0.80f, 0.f));

	spriteStandRight->changeAnimation(1);
	
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetMoveLeft.loadFromFile("images/moveLeft_strip6.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMoveLeft = Sprite::createSprite(glm::ivec2(33, 64), glm::vec2(0.1666666667, 1.00), &spritesheetMoveLeft, &shaderProgram);
	spriteMoveLeft->setNumberAnimations(4);

	spriteMoveLeft->setAnimationSpeed(MOVE_LEFT, 8);
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.1666666667f, 0.f));
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.3333333334f, 0.f));
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.5000000001f, 0.f));
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.6666666668f, 0.f));
	spriteMoveLeft->addKeyframe(MOVE_LEFT, glm::vec2(0.8333333335f, 0.f));

	spriteMoveLeft->changeAnimation(2);
	
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetMoveRight.loadFromFile("images/moveRigth_strip6.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMoveRight = Sprite::createSprite(glm::ivec2(35, 64), glm::vec2(0.1666666667, 1.00), &spritesheetMoveRight, &shaderProgram);
	spriteMoveRight->setNumberAnimations(4);

	spriteMoveRight->setAnimationSpeed(MOVE_RIGHT, 8);
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.1666666667f, 0.f));
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.3333333334f, 0.f));
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.5000000001f, 0.f));
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.6666666668f, 0.f));
	spriteMoveRight->addKeyframe(MOVE_RIGHT, glm::vec2(0.8333333335f, 0.f));

	spriteMoveRight->changeAnimation(3);

	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::update(int deltaTime)
{
	spriteStandLeft->update(deltaTime);
	spriteStandRight->update(deltaTime);
	spriteMoveLeft->update(deltaTime);
	spriteMoveRight->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(movement != 3)
			spriteMoveLeft->changeAnimation(MOVE_LEFT);
		movement = 3;
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64)))
		{
			posPlayer.x += 2;
			spriteStandLeft->changeAnimation(STAND_LEFT);
			movement = 2;
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (movement != 4) {
			spriteMoveRight->changeAnimation(MOVE_RIGHT);
			movement = 4;
		}
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
		{
			posPlayer.x -= 2;
			spriteStandRight->changeAnimation(STAND_RIGHT);
			movement = 1;
		}
	}
	else
	{
		if (movement == 3) {
			spriteStandLeft->changeAnimation(STAND_LEFT);
			movement = 2;
		}
		else if (movement == 4) {
			spriteStandRight->changeAnimation(STAND_RIGHT);
			movement = 1;
		}
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::render()
{
	switch (movement)
	{
	case 1: spriteStandRight->render();
		break;
	case 2: spriteStandLeft->render();
		break;
	case 3: spriteMoveLeft->render();
		break;
	case 4: spriteMoveRight->render();
		break;
	}
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




