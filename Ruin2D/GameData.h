#ifndef __RUIN2D_GAMEDATA_H_
#define __RUIN2D_GAMEDATA_H_

#include <glm\glm.hpp>

namespace Ruin2D
{
	struct GameData
	{
		static const int MAX_PLAYERS = 2;
		static const int MAX_PLAYER_TYPES = 4;
		static const int MAX_ENEMIES = 20;
		static const int MAX_ENEMY_TYPES = 20;
		static const int MAX_PROJECTILES = 100;
		static const int MAX_PROJECTILE_TYPES = 20;
		static const int MAX_COLLECTIBLES = 50;
		static const int MAX_COLLECTIBLE_TYPES = 10;
		static const int MAX_ROOMS = 256;

		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 640;
		static const int FPS = 8;
		static const int MAP_TILE_SIZE = 32;

		// Entity Data
		glm::vec2*	entityPosition;
		glm::vec2*	entityScale;
		short*	entityZOrder;
		double*	entityOrientation;
		short*	entityType;
		glm::vec2*	entitySpeed;
		glm::vec2*	entityAccel;

		// Player Entity Type Data
		glm::ivec2*	playerBounds;
		short*	playerTexture;
		glm::vec2*	playerSpeed;
		glm::vec2*	playerAccel;
		int*	playerHealth;
		int*	playerPower;

		// Enemy Entity Type Data
		glm::ivec2*	enemyBounds;
		short*	enemyTexture;
		glm::vec2*	enemySpeed;
		glm::vec2*	enemyAccel;
		int*	enemyHealth;
		int*	enemyPower;
		short*	enemyAI;

		// Projectile Entity Type Data
		double*	projectileBounds;
		short*	projectileTexture;
		glm::vec2*	projectileSpeed;
		glm::vec2*	projectileAccel;
		int*	projectileDamage;

		// Collectible Entity Type Data
		double*	collectibleBounds;
		short*	collectibleTextures;
		glm::vec2*	collectibleBaseSpeeds;
		glm::vec2*	collectibleBaseAccels;

		// Map Data
		short**	mapRoomTiles;
		short*	mapRoomTextures;
	};
}

#endif