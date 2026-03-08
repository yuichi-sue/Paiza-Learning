#include <iostream>

int main() {
    long long x1, y1, r1, x2, y2, r2;
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    // 距離の2乗を計算.
    long long dx = x2 - x1;
    long long dy = y2 - y1;
    long long dsq = (dx * dx) + (dy * dy);

    // 円と円の内外判定（接点含む）.
    if (dsq <= (r1 + r2) * (r1 + r2)) {
        std::cout << "Yes\n";
    }
    else {
        std::cout << "No\n";
    }
    return 0;
}
