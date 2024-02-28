#include "pch.h"
#include "Upgrade.h"

Upgrade::Upgrade(const std::string& name)
	:GameObject(name)
{
}

void Upgrade::Init()
{
	float textSize = 120.f;
	sf::Font& font = RES_MGR_FONT.Get("fonts/zombiecontrol.ttf");
	
	textFireUp.Set(font, formatFireSpped, textSize, sf::Color::White);
	textFireUp.SetPosition({ 1920.f / 2.f , 1080.f / 2.f });
	textFireUp.SetOrigin(Origins::MC);
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
	textFireUp.Draw(window);
}
