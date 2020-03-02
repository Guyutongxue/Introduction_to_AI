// TIME LIMIT EXCEEDED, ANOTHER ANSWER EXPECTED
// TIME LIMIT EXCEEDED, ANOTHER ANSWER EXPECTED
// TIME LIMIT EXCEEDED, ANOTHER ANSWER EXPECTED

#include <iostream>
#include <queue>

int m, n;
bool closed[1002][1002][2] = {};

struct Status {
    int leftMissionary;
    int leftCannibal;
    bool isBoatLeft;
    int step;
    Status(int m, int c, bool b = true, int s = 0)
        : leftMissionary(m), leftCannibal(c), isBoatLeft(b), step(s) {}
    bool canMove(int movingMissonary, int movingCannibal) {
        int& i = movingMissonary;
        int& j = movingCannibal;
        if ((i >= j || i == 0) && (i + j <= n)) {
            if (isBoatLeft) {
                return (leftMissionary - i >= leftCannibal - j || leftMissionary - i == 0) &&
                       (m - leftMissionary + i >= m - leftCannibal + j ||
                        m - leftMissionary + i == 0) &&
                       !closed[leftMissionary - i][leftCannibal - j][!isBoatLeft];
            } else {
                return (leftMissionary + i >= leftCannibal + j || leftMissionary + i == 0) &&
                       (m - leftMissionary - i >= m - leftCannibal - j ||
                        m - leftMissionary - i == 0) &&
                       !closed[leftMissionary + i][leftCannibal + j][!isBoatLeft];
            }
        } else
            return false;
    }
    Status generate(int movingMissonary, int movingCannibal) {
        Status result = *this;
        if (isBoatLeft) {
            result.leftMissionary -= movingMissonary;
            result.leftCannibal -= movingCannibal;
        } else {
            result.leftMissionary += movingMissonary;
            result.leftCannibal += movingCannibal;
        }
        result.isBoatLeft ^= true;
        result.step++;
        closed[result.leftMissionary][result.leftCannibal][result.isBoatLeft] = true;
        return result;
    }
};

std::queue<Status> fringe;

int main() {
    std::cin >> m >> n;
    fringe.push(Status(m, m));
    closed[m][m][1] = true;
    while (!fringe.empty()) {
        Status node = fringe.front();
        fringe.pop();
        if (node.leftCannibal == 0 && node.leftMissionary == 0) {
            std::cout << node.step << std::endl;
            return 0;
        }
        if (node.isBoatLeft) {
            for (int i = node.leftMissionary; i >= 0; i--) {
                for (int j = node.leftCannibal; j >= 0; j--) {
                    if (i == j && j == 0)
                        continue;
                    if (node.canMove(i, j)) {
                        fringe.push(node.generate(i, j));
                    }
                }
            }
        } else {
            for (int i = 0; i <= m - node.leftMissionary; i++) {
                for (int j = 0; j <= m - node.leftCannibal; j++) {
                    if (i == j && j == 0)
                        continue;
                    if (node.canMove(i, j)) {
                        fringe.push(node.generate(i, j));
                    }
                }
            }
        }
    }
    std::cout << "-1" << std::endl;
}