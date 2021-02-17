#include "DxLib.h"
#include "math.h"
//配列の数の定義
#define field_number 36
#define delx 32
#define pix  32


int main_field[field_number + 1]{
	0,0,0,0,0,0,
	0,1,0,0,1,0,
	1,0,1,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,1,0,
	0,0,0,0,1,0,0
};

//開けているかどうかの判定
int field_status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0
};


//周りの爆弾の数の表示
int status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0
};


//旗立てる処理のやつ
int flag_status[field_number + 1]{
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0

};




//フィールドのルートとったもの（1次元の配列を二次元に変換するために）
int feald_sqart = 6;

//マウスが押されたら１押されていなければ0
int muse_input_status = 0;

//ゲームが続けられるかの判定　生きている　０　死んでいる　１ クリア２
int game_status = 0;

//爆弾の数の定
int bakudan = 6;



//表示用のやつ
void draw(int bomb, int field, int safe,int flag) {

	int x = 0, y = 0;

	int a = 0;

	for (int i = 0; i < field_number; ++i) {

		y = i / feald_sqart;
		x = i % feald_sqart;


		if (field_status[i] == 1) {

			field_status[i] = 1;

			//爆弾引いたら爆弾の画像を出す
			if (main_field[i] == 1) {
				DrawGraph(delx + pix * x, delx + pix * y, bomb, TRUE); // 爆弾の画像描画
				game_status = 1;
			}

			else DrawGraph(delx + pix * x, delx + pix * y, safe, TRUE); // 赤いタイルの表示

			//開けたフィールドの数を数える。
			a += 1;


			if (a == (field_number - bakudan)) {
				//ゲームクリアの判定
				game_status = 2;
			}


		}

		else {

			field_status[i] = 0;
			DrawGraph(delx + pix * x, delx + pix * y, field, TRUE); // 白いタイルの表示	


			if (flag_status[i] == 1) {

				DrawGraph(delx + pix * x, delx + pix * y, flag, TRUE); // 爆弾の画像描画

			}

		}




		int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

		DrawFormatString(delx * 10 + 8 + pix * x, delx + 8 + pix * y, Green, "%d", field_status[i], TRUE); // データハンドルを使って画像を描画

	}

}




void text_mouse(int x,int y) {

	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(100, 100, Green, "座標[%d,%d]", x, y); // 文字を描画する

}


//周りの爆弾の数を表示する
void debug_text(int text, int x, int y) {

	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(delx + 8 + pix * x, delx + 8 + pix * y, Green, "%d", text, TRUE); // データハンドルを使って画像を描画

}


void game_over() {

	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(300,100, Green, "game over", TRUE); // データハンドルを使って画像を描画

}


void game_clear() {

	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(300, 100, Green, "game clear", TRUE); // データハンドルを使って画像を描画


}


//入力情報から取っていく
//入力した箇所の周りの爆弾の数を表示
void check(int x, int y) {


	int a = y * feald_sqart + x;

	//各点の位置のやつ。
	int b[4];

	//0:左 1:上　2:右　3:下
	b[0] = a - 1;
	b[1] = a - feald_sqart;
	b[2] = a + 1;
	b[3] = a + feald_sqart;


	for (int i = 0; i < 4; ++i) {

		//上下二オーバーフローした時のもの
		if ((b[i] < 0) || (b[i] > field_number)) {
			b[i] = 0;

		}

		//左端の時用
		if (((a % feald_sqart) == 0)) {
			b[0] = 0;

		}
		//右端の時用
		if ((a % feald_sqart) == (feald_sqart - 1)) {

			b[2] = 0;
		}

	}

	status[a] = main_field[b[0]] + main_field[b[1]] + main_field[b[2]] + main_field[b[3]];


}


void bomb_number() {
	//選んだパネルの周りの数字を表示
	for (int i = 0; i < field_number; ++i)
		//パネルが空いているかつ、爆弾ではない場合
		if ((field_status[i] == 1) && (main_field[i] != 1))
			if (status[i] != 0) {

				int yy = i / feald_sqart;
				int xx = i % feald_sqart;

				debug_text(status[i], xx, yy);

			}
}

//マウス押されて土岐の処理
void muse_input_left() {

	int mouse_x = 0;
	int mouse_y = 0;


	GetMousePoint(&mouse_x, &mouse_y);
	int x = -1 + mouse_x / pix;
	int y = -1 + mouse_y / pix;
	if (field_status[y * feald_sqart + x] != 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			field_status[y * feald_sqart + x] = 1;

			check(x, y);

		}
	}
}


//マウス押されて土岐の処理
void muse_input_rigtt() {

	int mouse_x = 0;
	int mouse_y = 0;


	GetMousePoint(&mouse_x, &mouse_y);
	int x = -1 + mouse_x / pix;
	int y = -1 + mouse_y / pix;


	//二回押したら消えるようにする
	if (flag_status[y * feald_sqart + x] == 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			flag_status[y * feald_sqart + x] = 0;

		}


	}

	if (field_status[y * feald_sqart + x] != 1) {
		if ((x <= feald_sqart - 1) && (0 <= x) && (y <= feald_sqart - 1) && (0 <= y)) {

			flag_status[y * feald_sqart + x] = 1;

		}
	}
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	SetDrawScreen(DX_SCREEN_BACK);

	DxLib_Init(); // DXライブラリ初期化処理


	int bomb;     // データハンドル格納用変数
	bomb = LoadGraph("pictures/bomb.jpg"); // 画像をロード

	int field;
	field = LoadGraph("pictures/field.jpg"); // 画像をロード

	int safe;
	safe = LoadGraph("pictures/safe.png");

	int flag;
	flag = LoadGraph("pictures/flag.jpg");




	while (1) {

		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}


		if (game_status == 0) {
			ClearDrawScreen(); // 画面を消す
			draw(bomb, field, safe, flag);

			int Mouse;
			Mouse = GetMouseInput();                //マウスの入力状態取得


			//左のマウス入力
			if (Mouse & MOUSE_INPUT_LEFT) {

				if (muse_input_status == 0)
				{
					muse_input_left();
				}
				//マウスが押されたらステータスの変更
				if (muse_input_status == 0)
				{
					muse_input_status = 1;
				}

			}
			else
			{
				muse_input_status = 0;
			}


			//右のマウス入力
			if (Mouse & MOUSE_INPUT_RIGHT) {

				if (muse_input_status == 0)
				{
					muse_input_rigtt();
				}
				//マウスが押されたらステータスの変更
				if (muse_input_status == 0)
				{
					muse_input_status = 1;
				}

			}

			else
			{
				muse_input_status = 0;
			}


			bomb_number();


		}


		else if (game_status == 1) game_over();

		else if (game_status == 2) game_clear();


		ScreenFlip(); //裏画面を表画面に反映

	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
