#pragma once
#include "Spawner.h"
#include "Item.h"

class ItemSpawner : public Spawner
{
protected:
	//Item* item;
	int value = 0;
public:
	std::vector<Item::Types> itemTypes;
	ItemSpawner(const std::string& name = "");
	~ItemSpawner() = default;

	GameObject* Create() override;

	void Reset() override;

	void OnDrop(const sf::Vector2f& position);
};

