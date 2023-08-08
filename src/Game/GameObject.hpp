#pragma once

#include <vector>
#include <string>
#include "../UniversalRenderer/Sprite.hpp"
#include "../UniversalRenderer/Types.hpp"

namespace game
{
	enum GameObjectType
	{
		NORMAL,
		DRAWABLE,
		ANIMATED,
		COUNT
	};

	class GameObject
	{
	public:
		std::string name;
		std::vector<GameObject *> children;
		uint32_t tags;
		static int32_t lastId;
		int32_t id;
		GameObject()
		{
			id = ++lastId;
			printf("creating gameobject\n");
			UR::setBit(tags, GameObjectType::NORMAL);
		}

		~GameObject()
		{
			printf("Destroying GameObject\n");
		}

		virtual void Update(double deltaTime)
		{
			printf("Updating %d\n", id);
			for (auto child : children)
			{
				child->Update(deltaTime);
			}
		}

		void AddChild(GameObject *child)
		{
			children.push_back(child);
		}
	};

	int GameObject::lastId = 0;

	class GameObjectDrawable : public GameObject
	{
	public:
		UR::Sprite sprite;
		UR::PointF position = {0};
		UR::PointF velocity = {0};

		GameObjectDrawable(const char* bmpFile = nullptr) : sprite(bmpFile)
		{
			UR::setBit(tags, GameObjectType::DRAWABLE);
		}

		virtual void Update(double deltaTime)
		{
			GetSprite().position.x = position.x;
			GetSprite().position.y = position.y;
		}

		virtual UR::Sprite& GetSprite()
		{
			return sprite;
		}

		virtual void Draw(void)
		{
			sprite.DrawTransparentClipped();
		}
	};
} // END Game namespace