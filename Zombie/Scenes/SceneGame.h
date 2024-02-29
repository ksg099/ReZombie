#pragma once
#include "Scene.h"

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

	std::vector<Spawner*> zspawners;
	std::vector<Spawner*> ispawners;

	std::list<GameObject*> zombieList;

	UiHud* hud;
	SpriteGo* crosshair;

	int wave = 1;

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
};

