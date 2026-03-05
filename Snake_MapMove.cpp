//Paiza練習問題「へび」
//マップ上をへびが移動していきます。
//マップの行数 H と列数 W, 障害物を '#' で移動可能な場所を '.' で表した H 行 W 列のマップ S_1 ... S_H, 現在の座標 sy, sx, 方向転換の回数 N が与えられます。
//続けて N 回の方向転換をおこなう時刻 t_1 ... t_N, 転換する向き d_1 ... d_N が与えられます。
//
//へびははじめは北を向いています。
//
//へびは進む先のマスに自分の身体や障害物がない時に移動ができます。
//時刻 0 から 99 までの間、へびは各時刻に次の行動を最大 100 回繰り返します。
//
//・ 方向転換をおこなう時刻の場合、指定の向きに方向転換したのち １ マス身体を伸ばす。そうでない時は、今向いている方向に １ マス身体を伸ばす。
//
//時刻が 99 の時の行動を終えるか、移動できなくなった時、移動を終了します。
//移動終了時にへびの体のあるマスを '*' にしたマップを出力してください。
//
//移動が可能であるということは、
//「移動先のマスに自分の身体や障害物がない かつ 移動先がマップの範囲外でない」
//ということを意味します。
//
//なお、マスの座標系は左上端のマスの座標を(y, x) = (0, 0) とし、
//下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。

//---入力される値
//H W sy sx N
//S_0
//...
//S_(H - 1)
//t_1 d_1
//...
//t_N d_N

//---条件
//すべてのテストケースにおいて、以下の条件をみたします。
//
//・ 1 ≦ H, W ≦ 50
//・ 1 ≦ N ≦ 100
//・ 0 ≦ sy < H
//・ 0 ≦ sx < W
//・ 1 ≦ t_i ≦ 99
//・ t_i < t_(i + 1)
//・ 時刻は 0 から始まり、99 の時の移動を終えるまで、もしくは移動ができなくなるまで移動を繰り返す。
//・ S_i は W 文字の文字列
//・ マップ上の(sy, sx) のマスは必ず '.'
//・ S の各文字は '.' または '#'
//・ d_i は、L, R のいずれかであり、それぞれ 左・右 を意味します。

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#ifdef _DEBUG
#include <fstream>
#endif
#include <assert.h>

struct Vec2 {
	int x;
	int y;
};

struct Snake {
	Vec2 pos;	// 現在座標
	Vec2 dir;	// 進行方向
};

struct Map {
	Vec2 size;
	std::vector<std::string> data;

	Map() : size({ 0, 0 }), data(0) {}
	const char operator ()(const Vec2 &pos) const;
	char& operator ()(const Vec2& pos);
};

struct Query {
	int timeStamp;
	char turn;
};

constexpr int TIME_START = 0;
constexpr int TIME_END = 99;

constexpr char MAP_CHAR_WALL = '#';
constexpr char MAP_CHAR_BLANK = '.';
constexpr char MAP_CHAR_MOVED = '*';

constexpr char QUERY_TURN_LEFT = 'L';
constexpr char QUERY_TURN_RIGHT = 'R';

constexpr Vec2 SNAKE_FIRST_DIR = {0, -1};	// 北向き

bool IsInside(const Map &map, const Vec2 &pos) {
	return pos.x >= 0 && pos.x < map.size.x && pos.y >= 0 && pos.y < map.size.y;
}

bool IsWall(const Map &map, const Vec2 &pos) {
	assert(IsInside(map, pos));
	return map.data[pos.y][pos.x] == MAP_CHAR_WALL;
}

bool IsMoved(const Map &map, const Vec2 &pos) {
	return map(pos) == MAP_CHAR_MOVED;
}

void TurnLeft(Snake& snake) {
	int tmp = snake.dir.x;
	snake.dir.x = snake.dir.y;
	snake.dir.y = -tmp;
}

void TurnRight(Snake& snake) {
	int tmp = snake.dir.x;
	snake.dir.x = -snake.dir.y;
	snake.dir.y = tmp;
}

// 進行方向に移動する
void Move(Map &map, Snake& snake) {
	// 位置座標を更新
	snake.pos.x += snake.dir.x;
	snake.pos.y += snake.dir.y;
	// マップ情報を更新
	map(snake.pos) = MAP_CHAR_MOVED;
}


int main() {
#ifdef _DEBUG
	std::ifstream in("input.txt");
	std::cin.rdbuf(in.rdbuf());
#endif

	Snake snake;
	Map map;
	int moveCnt;

	//-----------------------------------
	// 入力処理

	std::cin >> map.size.y >> map.size.x >> snake.pos.y >> snake.pos.x >> moveCnt;
	snake.dir = SNAKE_FIRST_DIR;

	// マップ情報読み込み
	map.data.resize(map.size.y);
	for (int i = 0; i < map.size.y; i++) {
		std::cin >> map.data[i];
	}
	map(snake.pos) = MAP_CHAR_MOVED;

	// 移動命令読み込み
	std::vector<Query> moveQuery(moveCnt);
	for (int i = 0; i < moveCnt; i++) {
		Query& query = moveQuery[i];
		std::cin >> query.timeStamp >> query.turn;
	}

	std::sort(moveQuery.begin(), moveQuery.end(), [](Query& a, Query& b) { return a.timeStamp < b.timeStamp; });
	int idxQuery = 0;

	//-----------------------------------
	// 移動処理
	for (int time = TIME_START; time <= TIME_END; time++) {
		if (idxQuery < moveQuery.size() && time == moveQuery[idxQuery].timeStamp) {
			// 方向転換処理
			const char turn = moveQuery[idxQuery].turn;
			if (turn == QUERY_TURN_LEFT) {
				TurnLeft(snake);
			}
			else if (turn == QUERY_TURN_RIGHT) {
				TurnRight(snake);
			}
			// インデックスカウンタの更新
			idxQuery++;
		}

		Vec2 nextPos = { snake.pos.x + snake.dir.x, snake.pos.y + snake.dir.y };
		if (!IsInside(map, nextPos) || 
			IsWall(map, nextPos) || 
			IsMoved(map, nextPos))
			break;

		Move(map, snake);
	}

	//-----------------------------------
	// 表示処理
	for (int i = 0; i < map.size.y; i++) {
		std::cout << map.data[i] << std::endl;
	}

	//-----------------------------------
	// 終了処理


	return 0;
}

const char Map::operator()(const Vec2& pos) const
{
	assert(IsInside(*this, pos));
	return this->data[pos.y][pos.x];
}

char& Map::operator()(const Vec2& pos)
{
	assert(IsInside(*this, pos));
	return this->data[pos.y][pos.x];
}
