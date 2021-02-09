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
				DrawGraph(32 * x, 32 * y, bomb, TRUE); // データハンドルを使って画像を描画
			}


			else DrawGraph(32 * x, 32 * y, safe, TRUE); // データハンドルを使って画像を描画

		}
			

		else DrawGraph( 32 * x,32 * y, field, TRUE); // データハンドルを使って画像を描画


	}


}

//入力情報から取っていく
void check() {






}


void text_mouse(int x,int y) {

	


	int Green = GetColor(0, 255, 0);      // 緑の色コードを取得

	DrawFormatString(100, 100, Green, "座標[%d,%d]", x, y); // 文字を描画する
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
		draw(bomb, field,safe);

		int Mouse;
		Mouse = GetMouseInput();                //マウスの入力状態取得
		

		GetMousePoint(&mouse_x, &mouse_y);
		text_mouse(mouse_x, mouse_y);
		//マウス入力途中
		if (Mouse & MOUSE_INPUT_LEFT) {


			
			int x = mouse_x / 32;
			int y = mouse_y / 32;

			field_status[y * 5 + x] = 1;

		}


		

		ScreenFlip(); //裏画面を表画面に反映


	}


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}




