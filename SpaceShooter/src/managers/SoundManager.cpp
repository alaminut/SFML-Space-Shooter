#include "SoundManager.h"

Utils::SoundManager::SoundManager()
{
	this->addResource(Shared::SoundId::S_LASER, "sounds/laser.wav");
	this->addResource(Shared::SoundId::S_PLAYER_DEATH, "sounds/player_death.wav");
	this->addResource(Shared::SoundId::S_ENEMY_DEATH, "sounds/enemy_death.wav");
	this->addResource(Shared::SoundId::S_GAME_MUSIC, "sounds/game_music.wav");
}
