#pragma once
#include <vector>
#include <string>

class Node
{
	public:
		std::vector<Node> children;

		Node(std::string name)
		{
			printf("%s\n", name.c_str());
		}

		Node()
		{
			printf("constructing\n");
			children = std::vector<Node>();
			children.reserve(10);

		}

		~Node()
		{
			printf("destructing\n");
		}
};