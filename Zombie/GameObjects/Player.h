#pragma once
#include "SpriteGo.h"

class SceneGame;
class Item;

class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f, 0.f };
	sf::Vector2f look = { 1.0f, 0.f };
	float speed = 500.f;

	SceneGame* sceneGame = nullptr;

	float fireInterval = 0.1f;
	float bulletSpeed = 1000.f;
	int bulletDamage = 1000;

	int maxHp = 100000;
	int hp = maxHp;
	int maxAmmo = 20;
	int ammo = maxAmmo;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTime = 0.5f;
	float noDamageTimer = 0.f;

	bool isFiring = false;
	float fireTimer = 0.f;

public:
	Player(const std::string& name = "");
	~Player() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void Fire();

	void OnDamage(int damage);
	void OnDie();
	void OnItem(Item* item);
};

