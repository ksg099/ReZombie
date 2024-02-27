#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
#include "TextGo.h"

class UiHud : public GameObject
{
protected:
	std::string formatScore = "SCORE: ";
	std::string formatHighScore =	"HIGH SCORE: ";
	std::string formatWave = "WAVE: ";
	std::string formatZombieCount = "ZOMBIES: ";

	TextGo textScore;
	TextGo textHiScore;

	SpriteGo imgAmmoIcon;
	TextGo textAmmo;
	sf::RectangleShape gaugeHp;
	TextGo textWave;
	TextGo textZombieCount;

	sf::Vector2f gaugeHpSize = { 400.f, 50.f };

	sf::Vector2f referenceResolution = { 1920.f, 1080.f };
	sf::Vector2f resolution = referenceResolution;


public:
	UiHud(const std::string& name = "");
	~UiHud() override = default;

	void SetResoultion(const sf::Vector2f resoution);

	void SetScore(int s);
	void SetHiScore(int s);
	
	void SetAmmo(int current, int total);
	void SetHp(int hp, int max);
	void SetWave(int w);
	void SetZombieCount(int count);

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
};

