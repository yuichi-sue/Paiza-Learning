#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>

struct Vec2 {
    int x;
    int y;
};

struct Node {
    int index;
    int cost;
};

struct CompareNode {
    bool operator ()(Node a, Node b) const {
        return a.cost > b.cost;
    }
};

enum MOVE {
    RIGHT = 0,
    DOWN,
    LEFT,
    UP,
    MAX,

    EXIT = -1,
};

constexpr Vec2 MOVE_DIR[MOVE::MAX] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

int toIndex(int x, int y, int width) {
    return y * width + x;
}

Vec2 toPoint(int index, int width) {
    Vec2 pos = { index % width, index / width };
    return pos;
}

int main(void) {
    Vec2 size;
    std::cin >> size.y >> size.x;
    int indexGoal = toIndex(size.x - 1, size.y - 1, size.x);
    std::vector<Node> grid(size.y * size.x);

    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            int index = toIndex(x, y, size.x);
            Node& node = grid[index];
            node.index = index;
            std::cin >> node.cost;
        }
    }

    std::priority_queue<Node, std::vector<Node>, CompareNode> dijkstra;
    std::vector<int> indexParents(grid.size(), -1);
    std::vector<int> nodeCosts(grid.size(), std::numeric_limits<int>::max());

    dijkstra.push({ 0, grid[0].cost });
    indexParents[0] = -1;
    nodeCosts[0] = grid[0].cost;

    while (!dijkstra.empty()) {
        Node current = dijkstra.top();
        dijkstra.pop();

        if (current.index == indexGoal) {
            break;
        }

        if (current.cost > nodeCosts[current.index]) {
            continue;
        }

        Vec2 pos = toPoint(current.index, size.x);
        for (int i = 0; i < MOVE::MAX; i++) {
            Vec2 dir = MOVE_DIR[i];
            Vec2 nextPos = { pos.x + dir.x, pos.y + dir.y };
            if (nextPos.x < 0 || nextPos.x >= size.x || nextPos.y < 0 || nextPos.y >= size.y) {
                continue;
            }

            Node next;
            next.index = toIndex(nextPos.x, nextPos.y, size.x);
            next.cost = current.cost + grid[next.index].cost;

            if (next.cost >= nodeCosts[next.index]) {
                continue;
            }
            nodeCosts[next.index] = next.cost;;
            indexParents[next.index] = current.index;

            dijkstra.push(next);
        }
    }

    std::cout << nodeCosts[indexGoal] << '\n';

    int current = indexGoal;
    while (current != -1) {
        int parent = indexParents[current];
        Vec2 currentPos = toPoint(current, size.x);

        std::cout << currentPos.y << ' ' << currentPos.x << '\n';

        current = parent;
    }

    std::ofstream output("output.txt");
    if (output.is_open()) {
        std::vector<std::string> strings(size.y);
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                strings[y] += '.';
            }
        }

        int current = indexGoal;
        while (current != -1) {
            Vec2 pos = toPoint(current, size.x);
            strings[pos.y][pos.x] = '*';
            current = indexParents[current];
        }

        for (std::string& str : strings) {
            output << str << '\n';
        }
    }

    return 0;
}
