#pragma once
#include <vector>

class Node;

class Channel {
private:
	/*
	 * 0 if the channel is idle
	 * 1 if the channel is busy
	 */
	int state;
	std::vector<Node*> nodes;

public:
	int GetState(void);
	void SetState(int _state);
	std::vector<Node*> GetNodes(void);
	void add(Node *node);
	bool remove(Node *node);
};