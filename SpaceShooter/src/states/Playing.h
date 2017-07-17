#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/Random.h"
#include "../entity/Player.h"
#include "../entity/Enemy.h"
#include "../entity/UI.h"
#include "GameState.h"

namespace State
{
	class Playing : public GameState
	{
	public:
		explicit Playing(Application& application);
		~Playing();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		unsigned maxStars;
		unsigned maxEnemy;
		unsigned currentEnemyLimit;
		float enemySpawnInterval;
		float enemySpawnIntervalMin;
		float difficultyIncreaseInterval;
		bool gameOver;

		Utils::RandomNumberGenerator rng;

		sf::Clock enemySpawnClock;
		sf::Clock difficultyIncreaseClock;

		GameObjects::UI m_ui;
		GameObjects::Player* m_p_player;

		std::vector<GameObjects::Enemy> enemies;
		std::vector<GameObjects::Enemy> enemyGCList;

		std::vector<sf::CircleShape> stars;

		void SpawnEnemy();
		void IncreaseDifficulty();
		void FillBackground();
		void HandleCombat();
		void ClearObjects();
	};
}
