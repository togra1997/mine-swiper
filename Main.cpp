#include "DxLib.h"


int main_field[25]{
	0,0,0,0,0,
	0,1,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,1


};


int field_status[25]{
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0


};


//周りの爆弾の数の表示
int status[25]{
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0


};



void draw(int bomb,int field,int safe) {

	int x = 0, y = 0;
	for (int i = 0; i < 25; ++i) {


		y = i / 5;
		x = i % 5;

		if (field_status[i] == 1) {

			//爆弾引いたら爆弾のやつを出す
			if (main_field[i] == 1) {
				DrawGraph(32 + 32 * x, 32 + 32 * y, bomb, TRUE); // データハンドルを使って画像を描画
			}


			else DrawGraph(32 + 32 * x, 32 + 32 * y, safe, TRUE); // データハンドルを使って画像を描画

		}


		else DrawGraph(32 + 32 * x, 32 + 32 * y, field, TRUE); // データハンドルを使って画像を描画


	}


}




void text_mouse(int x,int y) {

	


	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(100, 100, Green, "座標[%d,%d]", x, y); // 文字を描画する
}


//周りの爆弾の数を表示する
void debug_text(int text,int x,int y) {


	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	//DrawFormatString(100, 150, Green, "%d", x); // 文字を描画する

	DrawFormatString(40 + 32 * x, 40 + 32 * y, Green, "%d", text, TRUE); // データハンドルを使って画像を描画

}

//入力情報から取っていく
//入力した箇所の周りの爆弾の数を表示
void check(int x,int y) {

	int a = y * 5 + x;

	status[a] = main_field[a + 1] + main_field[a - 1] + main_field[a + 5] + main_field[a - 5];
	
	
	
	
	
	for (int i = 0; i < 25; ++i) {

		if (field_status[i] == 1) {

			if (status[i] != 0) {

				int yy = i / 5;
				int xx = i % 5;


				debug_text(status[i], xx, yy);


			}

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
	field= LoadGraph("pictures/field.jpg"); // 画像をロード

	int safe;
	safe = LoadGraph("pictures/safe.png");

	int mouse_x=0;
	int mouse_y=0;

	

	while (1) {
		if (ProcessMessage() != 0) { // メッセージ処理
			break;//ウィンドウの×ボタンが押されたらループを抜ける
		}
		ClearDrawScreen(); // 画面を消す
		draw(bomb, field, safe);

		int Mouse;
		Mouse = GetMouseInput();                //マウスの入力状態取得


		GetMousePoint(&mouse_x, &mouse_y);
		int x = -1 + mouse_x / 32;
		int y = -1 + mouse_y / 32;
		//マウス入力途中
		if (Mouse & MOUSE_INPUT_LEFT) {


			if (field_status[y * 5 + x] != 1) {
				if ((x <= 4) && (0 <= x) && (y <= 4) && (0 <= y))
					field_status[y * 5 + x] = 1;
			}

			text_mouse(x, y);

		}

		check(x, y);


		ScreenFlip(); //裏画面を表画面に反映


	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}




