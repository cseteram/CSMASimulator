#include "channel.h"

int Channel::GetState()
{
	return state;
}

void Channel::SetState(int _state)
{
	state = _state;
}

std::vector<Node*> Channel::GetNodes(void)
{
	return nodes;
}

void Channel::add(Node *node)
{
	nodes.push_back(node);
}

bool Channel::remove(Node *node)
{
	for (int i = 0; i < (int)nodes.size(); i++) {
		if (nodes[i] == node) {
			nodes.erase(nodes.begin() + i);
			return true;
		}
	}

	return false;
}