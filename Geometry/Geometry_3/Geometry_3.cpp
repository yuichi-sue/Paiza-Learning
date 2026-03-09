#include <iostream>

int main() {
	long long x1, y1, x2, y2, x3, y3, x4, y4;
	if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
		return 0;
	}

	// 入力値は昇順にソートされているものとし、チェックしない.

	// 各軸ごとに境界値を判定する.離れていれば接触していない.
	if ((x1 > x4) ||
		(x2 < x3) ||
		(y1 > y4) ||
		(y2 < y3)) {
		std::cout << "No\n";
	}
	else {
		std::cout << "Yes\n";
	}

	return 0;
}
