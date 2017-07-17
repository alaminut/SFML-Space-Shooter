#include "Playing.h"
#include "GameOver.h"
#include "../Application.h"
#include "../Display.h"

State::Playing::Playing(Application& application) :
	GameState(application),
	maxStars(200),
	maxEnemy(0),
	currentEnemyLimit(0),
	enemySpawnInterval(4.f),
	enemySpawnIntervalMin(1.5f),
	difficultyIncreaseInterval(25.f),
	gameOver(false),
	m_ui(this->getFont(Shared::FontId::F_UI))
{
	//Create player
	this->m_p_player = new GameObjects::Player(this->getTexture(Shared::TextureId::TX_PLAYER), this->getResourceManager());
	this->m_p_player->SetPosition(sf::Vector2f(0.f, 50.f));

	this->maxEnemy = this->m_p_player->getCurrentLevel() * 4;
	this->currentEnemyLimit = this->maxEnemy;

	//Create background
	this->FillBackground();

	this->enemySpawnClock.restart();
	this->difficultyIncreaseClock.restart();

	//Start scene music
	this->m_sceneAudio.setBuffer(this->getAudio(Shared::SoundId::S_GAME_MUSIC));
	this->m_sceneAudio.setVolume(Shared::MUSIC_VOLUME);
	this->m_sceneAudio.setLoop(true);
	this->m_sceneAudio.play();
}

State::Playing::~Playing()
{
	delete this->m_p_player;
}

void State::Playing::input()
{
	if (!this->gameOver)
		this->m_p_player->HandleInput(Display::getWindow().getSize());
}

void State::Playing::update(const float dt)
{
	//Game over condition
	if (this->gameOver && this->m_p_player->isDestoryComplete())
	{
		this->m_p_application->changeState(std::make_unique<GameOver>(*this->m_p_application, this->m_p_player->getScore()));
		return;
	}

	//Update background objects
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		float x = this->rng.getFloat(0.f, 2.f);
		(*it).move(-1.f * x * dt * 60.f, 0.f);
	}

	//Update player
	if (!this->gameOver)
	{
		//Update ui
		this->m_ui.update(this->m_p_player->getScore(), this->m_p_player->getCurrentHp(), dt);

		//update player
		this->m_p_player->Update(dt, Display::getWindow().getSize());

		//Spawn an enemy every enemySpawnSeconds interval.
		if (this->enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval && this->enemies.size() < this->currentEnemyLimit)
		{
			this->SpawnEnemy();
			this->enemySpawnClock.restart();
		}
	}

	//Enemy update cycle
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		(*it).Update(dt);
	}

	if (!this->gameOver)
	{
		//Handle combat
		this->HandleCombat();

		//Increase difficulty
		this->IncreaseDifficulty();
	}

	//Clear objects
	this->ClearObjects();
}

void State::Playing::draw()
{
	//Draw UI
	this->m_ui.draw();

	//Draw background objects
	sf::RenderStates renderOptions(sf::BlendAlpha);
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		Display::getWindow().draw((*it), renderOptions);
	}

	this->m_p_player->Draw(Display::getWindow());

	//Draw enemies
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (!(*it).isDestroyed())
			(*it).Draw(Display::getWindow());
	}
}

void State::Playing::SpawnEnemy()
{
	if (!this->gameOver)
	{
		float minX = static_cast<float>(Display::getWindow().getSize().x);
		float maxX = static_cast<float>(Display::getWindow().getSize().x) * 2.f;
		float maxY = static_cast<float>(Display::getWindow().getSize().y) - 90.f;
		
		int level = this->m_p_player->getCurrentLevel() + 1;
		float minSpeed = std::min<float>(5.f, std::max<float>(1.0f, level / 4.2f));
		float maxSpeed = std::min<float>(10.f, std::max<float>(minSpeed * 1.4f, level / 1.2f));

		float xPos = this->rng.getFloat(minX, maxX);
		float yPos = this->rng.getFloat(55.f, maxY);
		float speed = this->rng.getFloat(minSpeed, maxSpeed);


		this->enemies.emplace_back(
			level,
			&this->getTexture(Shared::TextureId::TX_ENEMY),
			&this->getResourceManager(),
			sf::Vector2f(xPos, yPos),
			speed);
	}
}

void State::Playing::IncreaseDifficulty()
{
	if (this->difficultyIncreaseClock.getElapsedTime().asSeconds() > this->difficultyIncreaseInterval)
	{
		if (this->currentEnemyLimit < this->maxEnemy)
			this->currentEnemyLimit += this->m_p_player->getCurrentLevel();

		if (this->enemySpawnInterval > this->enemySpawnIntervalMin)
			this->enemySpawnInterval -= 0.5f;

		this->maxEnemy = this->m_p_player->getCurrentLevel() * 4;
		this->difficultyIncreaseInterval -= static_cast<float>(this->m_p_player->getCurrentLevel()) / 4.f;

		if (this->difficultyIncreaseInterval < 10.f)
			this->difficultyIncreaseInterval = 10.f;

		this->difficultyIncreaseClock.restart();
	}
}


void State::Playing::FillBackground()
{
	float maxX = static_cast<float>(Display::getWindow().getSize().x);
	float maxY = static_cast<float>(Display::getWindow().getSize().y);

	for (unsigned i = this->stars.size(); i < this->maxStars; i++)
	{
		sf::CircleShape star(this->rng.getFloat(0.3f, 1.5f));
		star.setFillColor(sf::Color::White);

		star.setPosition(this->rng.getFloat(0.f, maxX), this->rng.getFloat(0.f, maxY));
		this->stars.push_back(star);
	}
}

void State::Playing::HandleCombat()
{
	if (this->m_p_player->getCurrentHp() <= 0)
	{
		this->m_p_player->Destroy();
		this->gameOver = true;
	}

	//Player & enemy collision check
	auto playerBox = this->m_p_player->getBoundingBox();
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		auto enemyBox = (*it).getBoundingBox();
		if (enemyBox.intersects(playerBox) && (!(*it).isDestroying() && !(*it).isDestroyed()))
		{
			this->m_p_player->TakeDamage((*it).getCurrentHp());
			(*it).TakeDamage((*it).getCurrentHp());

			if ((*it).isDestroying() || (*it).isDestroyed())
				this->m_p_player->AddScore((*it).getLevel());

			break;
		}
	}

	//Bullet & enemy collision check
	for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy)
	{
		if (!(*enemy).isDestroying() && !(*enemy).isDestroyed())
		{
			if (!this->m_p_player->getBullets().empty())
			{
				for (auto bullet = this->m_p_player->getBullets().begin(); bullet != this->m_p_player->getBullets().end(); ++bullet)
				{
					if ((*bullet).getBoundingBox().intersects(enemy->getBoundingBox()))
					{
						enemy->TakeDamage(this->m_p_player->getDamage());
						this->m_p_player->getBullets().erase(bullet);

						if (enemy->isDestroying() || enemy->isDestroyed())
							this->m_p_player->AddScore(enemy->getLevel());

						break;
					}
				}
			}
		}
	}
}


void State::Playing::ClearObjects()
{
	//Player bullet GC
	if (!this->m_p_player->getBullets().empty())
	{
		for (auto bullet = this->m_p_player->getBullets().begin(); bullet != this->m_p_player->getBullets().end(); ++bullet)
		{
			if ((bullet->getPosition().x < 0 ||
				bullet->getPosition().y < 0 ||
				bullet->getPosition().x > Display::getWindow().getSize().x ||
				bullet->getPosition().y > Display::getWindow().getSize().y) || this->gameOver)
			{
				this->m_p_player->getBullets().erase(bullet);
				break;
			}
		}
	}

	//Enemy GC
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (it->getPosition().x < -100)
		{
			if (!it->isDestroyed())
			{
				//If player missed the enemy takes 1 damage
				this->m_p_player->TakeDamage(1);
			}

			//vector::erase kullanmiyoruz cunku erase() vector degerlerini kopyaliyor.
			//kopyalanan enemy degerleri de o sirada her hangi bir enemy sound playing
			//durumunda sesi erken kesiyor.
			std::swap(*it, this->enemies.back());
			this->enemies.pop_back();
			break;
		}
	}

	//Background objects GC
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		if ((*it).getPosition().x < -10.f)
		{
			this->stars.erase(it);
			this->FillBackground();
			break;
		}
	}
}
