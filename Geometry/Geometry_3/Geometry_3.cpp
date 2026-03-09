#include <iostream>

inline bool IsIntersectsQuad(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x4, long long y4) {
	return (x1 <= x4) &&
		(x2 >= x3) &&
		(y1 <= y4) &&
		(y2 >= y3);
}

int main() {
	long long x1, y1, x2, y2, x3, y3, x4, y4;
	if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
		return 0;
	}

	// 境界座標のチェック.最小と最大の座標を設定する.
	if (x1 > x2)	std::swap(x1, x2);
	if (x3 > x4)	std::swap(x3, x4);
	if (y1 > y2)	std::swap(y1, y2);
	if (y3 > y4)	std::swap(y3, y4);

	// 各軸ごとに境界値を判定する.離れていれば接触していない.
	if (IsIntersectsQuad(x1, y1, x2, y2, x3, y3, x4, y4)) {
		std::cout << "Yes\n";
	}
	else {
		std::cout << "No\n";
	}

	return 0;
}
