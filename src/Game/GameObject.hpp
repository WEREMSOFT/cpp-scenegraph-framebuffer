#pragma once

#include <vector>
#include <string>
#include "../UniversalRenderer/Sprite.hpp"

namespace game
{

	class GameObject
	{
		public:
			std::string name;
			std::vector<GameObject*> children;
			static int lastId;
			int id;
			GameObject()
			{
				id = ++lastId;
				printf("creating gameobject\n");
			}

			~GameObject()
			{
				printf("Destroying GameObject\n");
			}

			void Update(double deltaTime)
			{
				printf("Updating %d\n", id);
				for(auto child: children)
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
} // END Game namespace