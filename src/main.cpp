#include <iostream>
#include <cstdio>
#include "simulator.h"
#include "node.h"
#include "channel.h"

using namespace std;
const int duration = 10; /* time in seconds to simulate */

int main() {

    for (int scheme = 0; scheme < 3; scheme++) {
        for (int n = 5; n < 30; n += 5) {
            if (scheme == 2) {
                Simulator sim(10, scheme, n, 2);
                sim.simulate();
                continue;
            }

            for (int cw = 32; cw < 256; cw *= 2) {
                Simulator sim(duration, scheme, n, cw);
                sim.simulate();
            }
        }
    }

    return 0;
}
