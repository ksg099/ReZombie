#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
class Upgrade : public GameObject
{

protected:
	SpriteGo upgradeUi;
	std::string formatMaxUpgrade = "UPGRADE MAX: 10";
	std::string formatFireSpeed = "1- UPGRADE FIRE SPEED  UP: ";
	std::string formatPlayerSpeed = "2- UPGRADE REN SPEED  UP: ";
	std::string formatMaxHealth = "3- UPGRADE MAX HEALTH  UP: ";

	TextGo* text;
	
	
	TextGo textMaxUp;
	TextGo textFireUp;
	TextGo textSpeedUp;
	TextGo textHealthUp;

	int FireCount = 0;
	int SpeedCount = 0;
	int HealthCount = 0;

public:
	Upgrade(const std::string& name = "");
	~Upgrade() override = default;

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	void AddFireCount(int f);
	void AddSpeedCount(int s);
	void AddHealthCount(int h);

	
};

