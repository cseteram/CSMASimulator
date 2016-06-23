#pragma once
#include <random>
#include "channel.h"

typedef long long ll;

extern std::mt19937 gen;
extern std::uniform_real_distribution<> dis;

class Statistic {
private:
    /* represents current counter */
    ll currentCounter;

    /* stats about throughput */
    ll transmittedPacket;
    
    /* stats about mean packet delay */
    ll packetDelay, packetDelayCount;

    /* stats about transmission collision probability */
    ll collisionCount, totalTransmission;

public:
    Statistic();
    ll getCurrentCounter(void);
    ll getTransmittedPacket(void);
    ll getPacketDelay(void);
    ll getPacketDelayCount(void);
    ll getCollisionCount(void);
    ll getTotalTransmission(void);

    void addCurrentCounter(ll count);
    void addTransmittedPacket(ll packets);
    void addPacketDelay(ll delay);
    void addPacketDelayCount(ll count);
    void addCollisionCount(ll count);
    void addTotalTransmission(ll transmissions);
};

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
    * 1 : binary exponential
    */
    int strategy;

    /* Maximum Range CW */
    ll cw;

    /* remaining counter to wait */
    ll leftCounter;

    /* remaining collision detection counter */
    ll leftcollisionDetection;

    /* statistics to measure */
    Statistic *stats;

    /* the channel used by this node */
    Channel *channel;

    /* the time when the last packet is generated */
    ll lastGeneratedCount;

public:
    Node() { }
    Node(int _strategy, Channel *_channel, Statistic *_stats);

    void setState(int _state);
    void setCW(ll _cw);
    void setChannel(Channel *_channel);
    void setLeftCounter(ll _left);

    /* node will generate next packet */
    void generate(void);

    /* node will do own processing in this counter */
    void process(void);
};
