#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
#include "ItemSpawner.h"
#include "UiHud.h"

SceneGame::SceneGame(SceneIds id)
	: Scene(id)
{

}

void SceneGame::SetStatus(Status newStatus)
{
	currentStatus = newStatus;
	switch (currentStatus)
	{
	case SceneGame::Status::Playing:
		FRAMEWORK.SetTimeScale(1.f);
		break;
	case SceneGame::Status::NextWave:
		FRAMEWORK.SetTimeScale(0.f);
		break;
	}
}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);;
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);
	return Utils::Clamp(point, rect);
}

void SceneGame::Init()
{
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ItemSpawner());

	for (auto s : spawners)
	{
		s->SetPosition({ 0.f, 0.f});
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;
	AddGo(tileMap);

	crosshair = new SpriteGo("Crosshair");
	crosshair->sortLayer = -1;
	crosshair->SetTexture("graphics/crosshair.png");
	crosshair->SetOrigin(Origins::MC);

	AddGo(crosshair, Scene::Layers::Ui);

	hud = new UiHud("Hud");
	AddGo(hud, Scene::Layers::Ui);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({ -1000.f, -1000.f });

	Scene::Enter();

	hud->SetScore(0);
	hud->SetHiScore(0);
	hud->SetAmmo(0, 0);
	
	SetStatus(Status::Playing);
	spawners[0]->SetActive(false);
	spawners[0]->Spawn(5);
	wave = 1;
	hud->SetWave(wave);
}

void SceneGame::Exit()
{
	Scene::Exit();
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
}

void SceneGame::Update(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	hud->SetZombieCount(zombieList.size());

	Scene::Update(dt);
	
	crosshair->SetPosition(ScreenToUi((sf::Vector2i)InputMgr::GetMousePos()));

	sf::Vector2f worldViewCenter = worldView.getCenter();
	worldViewCenter = Utils::Lerp(worldViewCenter, player->GetPosition(), dt * 2.f);
	worldView.setCenter(worldViewCenter);

	switch (currentStatus)
	{
	case SceneGame::Status::Playing:
		if (zombieList.size() == 0)
		{
			SetStatus(Status::NextWave);
		}
		break;
	case SceneGame::Status::NextWave:
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			SetStatus(Status::Playing);
			hud->SetWave(++wave);
			spawners[0]->Spawn(5 * wave);
		}

		break;
	}
}

void SceneGame::FixedUpdate(float dt)
{
	FindGoAll("Zombie", zombieList, Layers::World);
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
