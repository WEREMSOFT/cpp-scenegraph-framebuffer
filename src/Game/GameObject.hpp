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
		UR::PointF position = {0};
		UR::PointF velocity = {0};
		UR::Sprite sprite;

		GameObjectDrawable(char* bmpFile = nullptr) : sprite(bmpFile)
		{
			UR::setBit(tags, GameObjectType::DRAWABLE);
		}

		virtual void Update(double deltaTime)
		{
			sprite.position.x = position.x;
			sprite.position.y = position.y;
		}

		virtual void Draw(void)
		{
			sprite.DrawTransparentClipped();
		}
	};
} // END Game namespace