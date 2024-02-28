#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"
class Upgrade : public GameObject
{

protected:
	SpriteGo upgradeUi;
	std::string formatFireSpped 
		= "1- UPGRADE FIRE SPEED\n2- UPGRADE REN SPEED\n3- UPGRADE MAX HEALTH";

	TextGo* text;
	//std::string formatFireSpped = "1 - INCREASED RATE OF FIRE";
	
	TextGo textFireUp;

public:
	Upgrade(const std::string& name = "");
	~Upgrade() override = default;

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;

	
};

