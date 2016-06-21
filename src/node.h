#pragma once
#include "channel.h"

class Node {
private:
    /* state - represents current node status
     * 0 : generating packet
     * 1 : ready to transmission
     * 2 : transmissing
     * 3 : collision occuered
     */
    int state;

    /* backoff strategy if collision is detected
     * 0 : uniform
     * 1 : binary
     */
    int strategy;

    /* Maximum Range CW */
    int cw;

    /* remaining counter to wait */
    int leftCounter;

    /* remaining collision detection counter */
    int leftcollisionDetection;

    /* the channel used by this node */
    Channel channel;

public:
    Node() { }
    Node(int _strategy, Channel &_channel);

    void setState(int _state);
    void setCW(int _cw);
    void setChannel(Channel &_channel);
    void setLeftCounter(int _left);

    void generate(void);
    void process(void);
};
