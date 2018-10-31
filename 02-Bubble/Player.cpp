#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
	bJumping = false;

	spritesheetStandLeft.loadFromFile("images/standIzquierdaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteStandLeft = Sprite::createSprite(glm::ivec2(35, 64), glm::vec2(0.125, 1.00), &spritesheetStandLeft, &shaderProgram);
	spriteStandLeft->setNumberAnimations(1);
	
		spriteStandLeft->setAnimationSpeed(0, 2);
		spriteStandLeft->addKeyframe(0, glm::vec2(0.f, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f * 2, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f * 3, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f * 4, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f * 5, 0.f));
		spriteStandLeft->addKeyframe(0, glm::vec2(0.125f * 6, 0.f));

	spriteStandLeft->changeAnimation(0);
	tileMapDispl = tileMapPos;//solo una vez
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetStandRight.loadFromFile("images/standDerechaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteStandRight = Sprite::createSprite(glm::ivec2(35, 64), glm::vec2(0.125, 1.00), &spritesheetStandRight, &shaderProgram);
	spriteStandRight->setNumberAnimations(1);

	spriteStandRight->setAnimationSpeed(0, 2);
	spriteStandRight->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f * 2, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f * 3, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f * 4, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f * 5, 0.f));
	spriteStandRight->addKeyframe(0, glm::vec2(0.125f * 6, 0.f));

	spriteStandRight->changeAnimation(1);
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetMoveLeft.loadFromFile("images/caminarIzquierdaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMoveLeft = Sprite::createSprite(glm::ivec2(34, 64), glm::vec2(0.125f, 1.00), &spritesheetMoveLeft, &shaderProgram);
	spriteMoveLeft->setNumberAnimations(1);

	spriteMoveLeft->setAnimationSpeed(0, 8);
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 7, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 6, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 5, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 4, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 3, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f * 2, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.125f, 0.f));
	spriteMoveLeft->addKeyframe(0, glm::vec2(0.f, 0.f));
	
	spriteMoveLeft->changeAnimation(2);
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetMoveRight.loadFromFile("images/caminaDerechaHomer_strip8.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteMoveRight = Sprite::createSprite(glm::ivec2(34, 64), glm::vec2(0.125f, 1.00), &spritesheetMoveRight, &shaderProgram);
	spriteMoveRight->setNumberAnimations(1);
	
	spriteMoveRight->setAnimationSpeed(0, 8);
	spriteMoveRight->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 2, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 3, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 4, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 5, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 6, 0.f));
	spriteMoveRight->addKeyframe(0, glm::vec2(0.125f * 7, 0.f));
	
	spriteMoveRight->changeAnimation(3);
	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetHandHitRight.loadFromFile("images/punoDerechaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteHandHitRight = Sprite::createSprite(glm::ivec2(56, 74), glm::vec2(0.07692307692f, 1.00), &spritesheetHandHitRight, &shaderProgram);
	spriteHandHitRight->setNumberAnimations(1);

	spriteHandHitRight->setAnimationSpeed(0, 25);
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 2, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 3, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 4, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 5, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 6, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 7, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 8, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 9, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 10, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 11, 0.f));
	spriteHandHitRight->addKeyframe(0, glm::vec2(0.07692307692f * 12, 0.f));

	spriteHandHitRight->changeAnimation(4);
	spriteHandHitRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetHandHitLeft.loadFromFile("images/punoIzquierdaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteHandHitLeft = Sprite::createSprite(glm::ivec2(56, 74), glm::vec2(0.07692307692f, 1.00), &spritesheetHandHitLeft, &shaderProgram);
	spriteHandHitLeft->setNumberAnimations(1);

	spriteHandHitLeft->setAnimationSpeed(0, 25);
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 12, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 11, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 10, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 9, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 8, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 7, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 6, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 5, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 4, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 3, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f * 2, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.07692307692f, 0.f));
	spriteHandHitLeft->addKeyframe(0, glm::vec2(0.f, 0.f));
	
	spriteHandHitLeft->changeAnimation(5);
	spriteHandHitLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetPatadaDerecha.loadFromFile("images/patadaDerechaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritePatadaDerecha = Sprite::createSprite(glm::ivec2(59, 62), glm::vec2(0.1428571429f, 1.00), &spritesheetPatadaDerecha, &shaderProgram);
	spritePatadaDerecha->setNumberAnimations(1);

	spritePatadaDerecha->setAnimationSpeed(0, 25);
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f * 2, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f * 3, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f * 4, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f * 5, 0.f));
	spritePatadaDerecha->addKeyframe(0, glm::vec2(0.1428571429f * 6, 0.f));

	spritePatadaDerecha->changeAnimation(6);
	spritePatadaDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetPatadaIzquierda.loadFromFile("images/patadaIzquierdaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritePatadaIzquierda = Sprite::createSprite(glm::ivec2(59, 61), glm::vec2(0.1428571429f, 1.00), &spritesheetPatadaIzquierda, &shaderProgram);
	spritePatadaIzquierda->setNumberAnimations(1);

	spritePatadaIzquierda->setAnimationSpeed(0, 25);
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f * 6, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f * 5, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f * 4, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f * 3, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f * 2, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.1428571429f, 0.f));
	spritePatadaIzquierda->addKeyframe(0, glm::vec2(0.f, 0.f));

	spritePatadaIzquierda->changeAnimation(7);
	spritePatadaIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetSaltarDerecha.loadFromFile("images/saltarDerechaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSaltarDerecha = Sprite::createSprite(glm::ivec2(63, 65), glm::vec2(0.3333333333f, 1.00), &spritesheetSaltarDerecha, &shaderProgram);
	spriteSaltarDerecha->setNumberAnimations(1);

	spriteSaltarDerecha->setAnimationSpeed(0, 8);
	spriteSaltarDerecha->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteSaltarDerecha->addKeyframe(0, glm::vec2(0.3333333333f, 0.f));
	spriteSaltarDerecha->addKeyframe(0, glm::vec2(0.3333333333f * 2, 0.f));

	spriteSaltarDerecha->changeAnimation(20);
	spriteSaltarDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	spritesheetSaltarIzquierda.loadFromFile("images/saltarIzquierdaHomer.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spriteSaltarIzquierda = Sprite::createSprite(glm::ivec2(63, 65), glm::vec2(0.3333333333f, 1.00), &spritesheetSaltarIzquierda, &shaderProgram);
	spriteSaltarIzquierda->setNumberAnimations(1);

	spriteSaltarIzquierda->setAnimationSpeed(0, 20);
	spriteSaltarIzquierda->addKeyframe(0, glm::vec2(0.f, 0.f));
	spriteSaltarIzquierda->addKeyframe(0, glm::vec2(0.3333333333f, 0.f));
	spriteSaltarIzquierda->addKeyframe(0, glm::vec2(0.3333333333f * 2, 0.f));

	spriteSaltarIzquierda->changeAnimation(9);
	spriteSaltarIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::update(int deltaTime) {
	spriteStandLeft->update(deltaTime);
	spriteStandRight->update(deltaTime);
	spriteMoveLeft->update(deltaTime);
	spriteMoveRight->update(deltaTime);
	spriteHandHitRight->update(deltaTime);
	spriteHandHitLeft->update(deltaTime);
	spritePatadaDerecha->update(deltaTime);
	spritePatadaIzquierda->update(deltaTime);
	spriteSaltarDerecha->update(deltaTime);
	spriteSaltarIzquierda->update(deltaTime);
	//////izquierda/derecha
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {//boton izquierdo
		if(movement != 3)//diferente a MoveLeft, si ya es MoveLeft se queda asi
			spriteMoveLeft->changeAnimation(0);//animacion MoveLeft
		movement = 3;//movimiento a la izquierda
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64))) {//hay colision a la izquierda
			posPlayer.x += 2;
			spriteStandRight->changeAnimation(0);//mira a la derecha
			movement = 1;//movimiento de mirar a la derecha
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {//boton derecho
		if (movement != 4) {//diferente a MoveRight
			spriteMoveRight->changeAnimation(0);//cambia animacion a MoveLeft
			movement = 4;
		}
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 64))) {//hay colision a la derecha
			posPlayer.x -= 2;
			spriteStandLeft->changeAnimation(0);//mira a la izquierda
			movement = 2;//movimiento de mirar a la izquierda
		}
	}
	else if (Game::instance().getKey('z')) { ////////////golpe
			if (movement == 1 || movement == 4 || movement == 7) {//si esta del lado derecho
				spriteHandHitRight->changeAnimation(0);
				movement = 5;
			}
			else if (movement == 2 || movement == 3 || movement == 8) {//si esta del lado izquierdo
				spriteHandHitLeft->changeAnimation(0);
				movement = 6;
			}
	}
	else if (Game::instance().getKey('x')) {
		if (movement == 1 || movement == 4 || movement == 5) {
			spritePatadaDerecha->changeAnimation(0);
			movement = 7;
		}
		else if (movement == 2 || movement == 3 || movement == 6) {
			spritePatadaIzquierda->changeAnimation(0);
			movement = 8;
		}
	}
	else {//
		if (movement == 3 || movement == 6 || movement == 8) {//MoveLeft o golpe Left
			spriteStandLeft->changeAnimation(0);//se queda parado en StandLeft
			movement = 2;
		}
		else if (movement == 4 || movement == 5 || movement == 7) {//MoveRight o golpe right
			spriteStandRight->changeAnimation(0);//se queda parado en StandRight
			movement = 1;
		}
	}
	
	////////////En el aire
	if(bJumping) {//si esta saltando
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) {//si esta en un solido
			bJumping = false;//deja de saltar
			posPlayer.y = startY;
			
		}
		else {
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)//detecta colision de caida
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y);
			if (!bJumping) {
				if (movement == 9) {
					spriteStandRight->changeAnimation(0);//se queda parado en StandRight
					movement = 1;
				}
				else if (movement == 10) {
					spriteStandLeft->changeAnimation(0);//se queda parado en StandLeft
					movement = 2;
				}
			}
				//si hay colision se sale del aire, estas en el suelo
		}
	}
	else {//si no viene de un salto
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {//si hay colision abajo
			if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {//tecla saltar
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
				if (movement == 1 || movement == 4 || movement == 5) {
					spritePatadaDerecha->changeAnimation(0);
					movement = 9;
				}
				else if (movement == 2 || movement == 3 || movement == 6) {
					spriteSaltarIzquierda->changeAnimation(0);
					movement = 10;
				}
				
			}
		}
	}
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteHandHitRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteHandHitLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritePatadaDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritePatadaIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteSaltarDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteSaltarIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render() {
	switch (movement) {
	case 1: spriteStandRight->render();
		break;
	case 2: spriteStandLeft->render();
		break;
	case 3: spriteMoveLeft->render();
		break;
	case 4: spriteMoveRight->render();
		break;
	case 5: spriteHandHitRight->render();
		break;
	case 6: spriteHandHitLeft->render();
		break;
	case 7: spritePatadaDerecha->render();
		break;
	case 8: spritePatadaIzquierda->render();
		break;
	case 9: spriteSaltarDerecha->render();
		break;
	case 10: spriteSaltarIzquierda->render();
		break;
	}
}

void Player::setTileMap(TileMap *tileMap) {
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos) {
	posPlayer = pos;
	spriteStandLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteStandRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteMoveRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteHandHitRight->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteHandHitLeft->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritePatadaDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spritePatadaIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteSaltarDerecha->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	spriteSaltarIzquierda->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




