#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheetStandLeft;
	Texture spritesheetStandRight;
	Texture spritesheetMoveLeft;
	Texture spritesheetMoveRight;

	Texture spritesheetHandHitRight;
	Texture spritesheetHandHitLeft;

	Texture spritesheetPatadaDerecha;
	Texture spritesheetPatadaIzquierda;

	Texture spritesheetSaltarDerecha;
	Texture spritesheetSaltarIzquierda;

	Sprite *spriteStandLeft;
	Sprite *spriteStandRight;
	Sprite *spriteMoveLeft;
	Sprite *spriteMoveRight;

	Sprite *spriteHandHitRight;
	Sprite *spriteHandHitLeft;

	Sprite *spritePatadaDerecha;
	Sprite *spritePatadaIzquierda;

	Sprite *spriteSaltarDerecha;
	Sprite *spriteSaltarIzquierda;

	TileMap *map;
	int movement = 1;
};


#endif // _PLAYER_INCLUDE


