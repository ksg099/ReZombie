#include "pch.h"
#include "ItemSpawner.h"
#include "GameObject.h"
#include "SceneGame.h"

ItemSpawner::ItemSpawner(const std::string& name)
    : Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
    //switch (itemType)
    //{
    //case Item::Types::Ammo:
    //    value = 10;
    //    break;
    //case Item::Types::Health:
    //    value = 50;

    //    break;
    //}

    //-1, 0 , 1을 반환 RandomValue 이떄 범위를 지정해서 나오는 범위만큼 확률
    if (itemTypes.empty())
        return nullptr;

    Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
    if (Utils::RandomValue() < 0.2f)
    {
        itemType = Item::Types::Ammo;
        value = 30;
    }
    else if (Utils::RandomValue() < 0.21f)
    {
        itemType = Item::Types::Health;
        value = 50;
    }
    /*else
    {
        itemType = Item::Types::None;
        value = 0;
    }*/
    return Item::Create(itemType, value);
}

void ItemSpawner::Reset()
{
    Spawner::Reset();
    itemTypes.clear();

    itemTypes.push_back(Item::Types::Ammo);
    itemTypes.push_back(Item::Types::Health);

    interval = 5.f;
    spawnCount = 0;
    radius = 500.f;
}

void ItemSpawner::OnDrop(const sf::Vector2f& position)
{
    //itemTypes.push_back(Item::Types::Health);
    GameObject* newItem = Create();

    newItem->Init();
    newItem->Reset();
    newItem->SetPosition(position);
    newItem->SetOrigin(Origins::MC);

    SCENE_MGR.GetCurrentScene()->AddGo(newItem);

}
