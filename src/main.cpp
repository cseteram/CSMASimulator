#include <iostream>
#include <cstdio>
#include <ctime>
#include "simulator.h"

using namespace std;
const int duration = 32; /* time in seconds to simulate */

std::mt19937 gen;
std::uniform_real_distribution<> dis;

void print(td3 result)
{

    cout << get<0>(result) << " ";
    cout << get<1>(result) << " ";
    cout << get<2>(result) << endl;

}

int main() {

    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(0, 1);
    srand((unsigned int)time(NULL));

    // freopen("result.out", "w", stdout);

    for (int scheme = 0; scheme < 3; scheme++) {
        if (scheme == 2) {
            for (int n = 1; n < 26; n += 1) {
                printf("simulation start (scheme = %d, n = %d, cw = %d)\n", 
                    scheme, n, 2);

                for (int attempt = 0; attempt < 10; attempt++) {
                    Simulator sim(duration, scheme, n, 2);
                    sim.simulate();
                    print(sim.getResult());
                }
            printf("\n");
            }
            continue;
        }

        for (int cw = 32; cw < 256; cw *= 2) {
            for (int n = 1; n < 26; n += 1) {
                printf("simulation start (scheme = %d, n = %d, cw = %d)\n",
                    scheme, n, cw);

                for (int attempt = 0; attempt < 10; attempt++) {
                    Simulator sim(duration, scheme, n, cw);
                    sim.simulate();
                    print(sim.getResult());
                }
            printf("\n");
            }
        }
    }

    return 0;
}
