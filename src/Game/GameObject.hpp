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
		GameObject* parent = NULL;

		UR::PointF localPosition = {0};
		UR::PointF worldPosition = {0};

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
			if(parent != NULL)
			{
				worldPosition.x = parent->worldPosition.x + localPosition.x;
				worldPosition.y = parent->worldPosition.y + localPosition.y;
			} else
			{
				worldPosition.x = localPosition.x;
				worldPosition.y = localPosition.y;
			}

			for (auto child : children)
			{
				child->Update(deltaTime);
			}
		}

		void AddChild(GameObject *child)
		{
			child->parent = this;
			children.push_back(child);
		}
	};

	int GameObject::lastId = 0;

	class GameObjectDrawable : public GameObject
	{
	public:
		UR::Sprite sprite;
		UR::PointF velocity = {0};

		GameObjectDrawable(const char* bmpFile = nullptr) : sprite(bmpFile)
		{
			UR::setBit(tags, GameObjectType::DRAWABLE);
		}

		virtual void Update(double deltaTime)
		{
			GameObject::Update(deltaTime);
			
			GetSprite().position.x = worldPosition.x;
			GetSprite().position.y = worldPosition.y;
		}

		virtual UR::Sprite& GetSprite()
		{
			return sprite;
		}

		virtual void Draw(void)
		{
			if(UR::isBitSet(tags, GameObjectType::DRAWABLE))
				sprite.DrawTransparentClipped();

			for (auto child : children)
			{
				if(UR::isBitSet(child->tags, GameObjectType::DRAWABLE))
				{
					((GameObjectDrawable*)child)->Draw();
				}
			}
		}
	};
} // END Game namespace