// Paiza練習問題「いびつなリバーシ対戦」
// 1 から N のプレイヤー番号が与えられた N 人でいびつなオセロの対戦をします。
// 盤面・ゲームをする人数・合計のターン数・各行動についての情報が与えられます。
// 盤面に穴の空いているマスは '#', 何も置かれていないマスは '.' になっています。
// 
// プレイヤー達は、各行動ごとに次の操作をおこないます。
// 
// ・ 盤面のマス(Y_i, X_i)に石を置く。既に相手の石が置かれている場合は相手の石を自分の石に置き換える。
// ・ 次に、今置いた自分の石と、既存の自分の石で縦横斜めにはさんだ連続した穴の空いていないマスに自分の石を置く。相手の石が置かれている場合は相手の石を自分の石に置き換えて、操作を終了する。
// 
// 操作を終えた後の盤面を出力してください。
// ただし、番号 i のプレイヤーの石のあるマスを i として出力してください。
// 
// なお、マスの座標系は左上端のマスの座標を(y, x) = (0, 0) とし、
// 下方向が y 座標の正の向き、右方向が x 座標の正の向きとします。
// https://paiza.jp/works/mondai/a_rank_level_up_problems/a_rank_pincerattack_boss


#include<iostream>
#include<vector>
#include<string>
#include <cassert>

//--------------------------------------
// 定数定義

constexpr char GRID_CHAR_HOLE = '#';
constexpr char GRID_CHAR_EMPTY = '.';
constexpr int GRID_DATA_HOLE = -1;
constexpr int GRID_DATA_EMPTY = 0;
constexpr int DIR_MAX = 8;

//--------------------------------------
// クラス定義

// 盤面情報
struct Board {
	int height;		// 盤面の高さ
	int width;		// 盤面の幅
	int playerNum;	// 参加プレイヤー数

	std::vector<int> data;	// 盤面データ(1次元配列として管理)

	int& operator ()(int y, int x) {
		assert(y >= 0 && y < height && x >= 0 && x < width);
		return data[(this->width * y) + x];
	}
};

//--------------------------------------
// 関数定義

// 盤面の内外定義
// \return	true:盤面内, false:盤面外
// \param	board	盤面情報
// \param	x		X座標
// \param	y		Y座標
bool IsInside(Board& board, int y, int x) {
	return y >= 0 && y < board.height && x >= 0 && x < board.width;
}

// 指定プレイヤーで裏返すことが可能か判定する
// \return	true:裏返し可能, false:裏返し不可
// \param	board		盤面情報
// \param	playerID	指定プレイヤー
// \param	py			Y軸基準座標
// \param	px			X軸基準座標
// \param	dy			Y軸移動ベクトル
// \param	dx			X軸移動ベクトル
bool IsPossibleReverse(Board& board, int playerID, int py, int px, int dy, int dx) {
	if (!IsInside(board, py + dy, px + dx) || playerID == board(py + dy, px + dx)) {
		// 盤面外、または直後のIDが指定プレイヤーと同一
		return false;
	}

	for (int y = py + dy, x = px + dx; IsInside(board, y, x); y += dy, x += dx) {
		int id = board(y, x);

		// 裏返し不可データ判定
		if (id == GRID_DATA_HOLE)
			return false;
		// 裏返し可能データ判定
		if (id == playerID)
			return true;
	}

	// 盤面外、または裏返し可能データが見つからなかった
	return false;
}

// 指定プレイヤーで裏返す.かならず前処理として裏返し可能判定をすること
// \return	true:裏返し可能, false:裏返し不可
// \param	board		盤面情報
// \param	playerID	指定プレイヤー
// \param	py			Y軸基準座標
// \param	px			X軸基準座標
// \param	dy			Y軸移動ベクトル
// \param	dx			X軸移動ベクトル
void Reverse(Board& board, int playerID, int py, int px, int dy, int dx) {
	for (int y = py + dy, x = px + dx; IsInside(board, y, x) && board(y, x) != playerID; y += dy, x += dx) {
		board(y, x) = playerID;
	}
};

//--------------------------------------
// 問題ソースコード
int main() {
	Board board;
	int queryCnt;	// 要求処理の実行行数
	std::vector<int> dirX = {1, 0, -1, 0, 1, -1, -1, 1};
	std::vector<int> dirY = {0, 1, 0, -1, 1, 1, -1, -1};

	//--------------------------------------
	//読み込み処理

	std::cin >> board.height >> board.width >> board.playerNum >> queryCnt;
	board.data.resize(board.height * board.width);

	// 盤面データ解析処理
	for (int i = 0; i < board.height; i++) {
		std::string str;

		std::cin >> str;
		if (str.size() != board.width) {
			std::cout << i << ":" << "行サイズエラー" << std::endl;
			return -1;
		}

		for (int j = 0; j < board.width; j++) {
			if (str[j] == GRID_CHAR_EMPTY) {
				board(i, j) = GRID_DATA_EMPTY;
			}
			else if (str[j] == GRID_CHAR_HOLE) {
				board(i, j) = GRID_DATA_HOLE;
			}
			else {
				std::cout << i << "," << j << ":入力文字エラー" << std::endl;
				return -2;
			}
		}
	}

	//--------------------------------------
	//要求処理


	for (int count = 0; count < queryCnt; count++) {
		int playerID;
		int posX;
		int posY;

		std::cin >> playerID >> posY >> posX;

		// 盤面のマス(Y_i, X_i)に石を置く。既に相手の石が置かれている場合は相手の石を自分の石に置き換える。
		board(posY, posX) = playerID;
		// 今置いた自分の石と、既存の自分の石で縦横斜めにはさんだ連続した穴の空いていないマスに自分の石を置く。
		// 相手の石が置かれている場合は相手の石を自分の石に置き換えて、操作を終了する。
		for (int dirCnt = 0; dirCnt < DIR_MAX; dirCnt++) {
			int dy = dirY[dirCnt];
			int dx = dirX[dirCnt];
			if (IsPossibleReverse(board, playerID, posY, posX, dy, dx)) {
				Reverse(board, playerID, posY, posX, dy, dx);
			}
		}


	}

	//--------------------------------------
	// 表示処理

	for (int i = 0; i < board.height; i++) {
		for (int j = 0; j < board.width; j++) {
			const int data = board(i, j);
			if (data == GRID_DATA_EMPTY) {
				std::cout << GRID_CHAR_EMPTY;
			}
			else if (data == GRID_DATA_HOLE) {
				std::cout << GRID_CHAR_HOLE;
			}
			else {
				std::cout << data;
			}
		}

		std::cout << std::endl;
	}


	//--------------------------------------
	// 終了処理
	return 0;
}