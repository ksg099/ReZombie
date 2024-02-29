#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(const std::string& name)
	:GameObject(name)
{
}

void Upgrade::Init()
{
	float textSize = 90.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	
	textMaxUp.Set(font, formatMaxUpgrade, textSize, sf::Color::White);
	textMaxUp.SetPosition({ 1920.f / 2.f , 200 });
	textMaxUp.SetOrigin(Origins::MC);

	textFireUp.Set(font, formatFireSpeed, textSize, sf::Color::White);
	textFireUp.SetPosition({ 1920.f / 2.f , 400 });
	textFireUp.SetOrigin(Origins::MC);

	textSpeedUp.Set(font, formatPlayerSpeed, textSize, sf::Color::White);
	textSpeedUp.SetPosition({ 1920.f / 2.f , 550 });
	textSpeedUp.SetOrigin(Origins::MC);

	textHealthUp.Set(font, formatMaxHealth, textSize, sf::Color::White);
	textHealthUp.SetPosition({ 1920.f / 2.f , 700 });
	textHealthUp.SetOrigin(Origins::MC);
	//Ui
	upgradeUi.Init();
	upgradeUi.SetTexture("graphics/background.png");
	upgradeUi.SetPosition({ 1920.f / 2.f , 1080.f / 2.f });
	upgradeUi.SetOrigin(Origins::MC);
	//upgradeUi.SetScale({ 0.5f, 0.5f });

	

}

void Upgrade::Reset()
{
	////Ui
	//textFireUp.Reset();
	//upgradeUi.Reset();
}

void Upgrade::Draw(sf::RenderWindow& window)
{
	//ui
	upgradeUi.Draw(window);
	textMaxUp.Draw(window);
	textFireUp.Draw(window);
	textSpeedUp.Draw(window);
	textHealthUp.Draw(window);
}

void Upgrade::AddFireCount(int f)
{
	this->FireCount += f;
	textFireUp.SetString(formatFireSpeed + std::to_string(this->FireCount));
	
}

void Upgrade::AddSpeedCount(int s)
{
	this->SpeedCount += s;
	textSpeedUp.SetString(formatPlayerSpeed + std::to_string(this->SpeedCount));
}

void Upgrade::AddHealthCount(int h)
{
	this->HealthCount += h;
	textHealthUp.SetString(formatMaxHealth + std::to_string(this->HealthCount));
}
