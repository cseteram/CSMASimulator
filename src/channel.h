#pragma once
#include <vector>

class Node;

class Channel {
private:
    /* state - represents current channel status
    * 0 if the channel is idle
    * 1 if the channel is busy
    */
    int state;

    /* nodes that use this channel */
    std::vector<Node*> nodes;

public:
    Channel();
    int getState(void);
    void setState(int _state);
    std::vector<Node*> getNodes(void);

    /* record that node use this channel */
    void add(Node *node);

    /* delete node from nodes */
    bool remove(Node *node);
};
