#pragma once
#include "Scene.h"
#include <fstream>
#include <iostream>

class Player;
class Spawner;
class TileMap;
class Zombie;
class UiHud;
class SpriteGo;

class SceneGame : public Scene
{
public:
	enum class Status
	{
		Playing,
		NextWave,
	};
protected:
	Status currentStatus;

	Player* player = nullptr;
	TileMap* tileMap;

	std::vector<Spawner*> spawners;
	std::list<GameObject*> zombieList;

	UiHud* hud;
	SpriteGo* crosshair;

	int wave = 1;
	int Score = 0;
	int HiScore = 0;
	
	
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	const std::list<GameObject*>& GetZombieList() const { return zombieList; }

	UiHud* GetHud() const
	{
		return hud;
	}

	Status GetStatus() const { return currentStatus; }
	void SetStatus(Status newStatus);

	bool IsInTileMap(const sf::Vector2f& point);
	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddScore(int s);
	void AddHiScore(int s);
	void SaveHiScore();
	void LoadHiScore();
};

