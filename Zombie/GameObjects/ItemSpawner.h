#pragma once
#include "Spawner.h"
#include "Item.h"

class ItemSpawner : public Spawner
{
protected:
	int Ammovalue = 10;
	int Healthvalue = 50;
	int value = 0;
public:
	std::vector<Item::Types> itemTypes;
	ItemSpawner(const std::string& name = "");
	~ItemSpawner() = default;

	GameObject* Create() override;

	void Reset() override;

	void OnDrop(const sf::Vector2f& position);
	int GetAmmovalue(int a);
	void GetHealthvalue(int h);
};

