#include "TextureManager.h"

Utils::TextureManager::TextureManager()
{
	this->addResource(Shared::TextureId::TX_SPLASH_LOGO, "textures/logo.png");
	this->addResource(Shared::TextureId::TX_PLAYER, "textures/ship.png");
	this->addResource(Shared::TextureId::TX_ENEMY, "textures/enemy.png");
	this->addResource(Shared::TextureId::TX_LASER, "textures/laser.png");
}