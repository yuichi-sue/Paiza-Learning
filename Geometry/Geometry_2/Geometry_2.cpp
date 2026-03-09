#include <iostream>

int main() {
	long long x1, y1, r;		// 円の情報.
	long long x2, y2, x3, y3;	// 軸並行長方形の情報.

	// 読み込み処理.
	if (!(std::cin >> x1 >> y1 >> r) ||
		!(std::cin >> x2 >> y2 >> x3 >> y3)) {
		return 0;
	}

	// 最小・最大の軸を設定.
	if (x2 > x3) {
		std::swap(x2, x3);
	}
	if (y2 > y3) {
		std::swap(y2, y3);
	}

	// 円に最も近い点を求める.
	long long px, py;
	px = std::min(std::max(x1, x2), x3);
	py = std::min(std::max(y1, y2), y3);

	// 点と円の内外判定.
	long long dx, dy;
	dx = px - x1;
	dy = py - y1;
	long long dsq = (dx * dx) + (dy * dy);
	if (dsq <= (r * r)) {
		std::cout << "Yes\n";
	}
	else {
		std::cout << "No\n";
	}
}
