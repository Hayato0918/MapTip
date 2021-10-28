/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include <stdio.h>

/*
■説明
左クリックで枠内を塗れる
塗り終わったら、Enterキーを押す
このプログラムが入ってるファイル内に"マップチップデータ.txt"が生成されてる
*/


//できてるかな


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PIXEL_X 10
#define PIXEL_Y 10

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float Mouse_X;
float Mouse_Y;
bool Mouse_LClick;

D3DXCOLOR color;

PIXEL pixel[PIXEL_X][PIXEL_Y];
TIP tip[PIXEL_X][PIXEL_Y];
int check[PIXEL_X][PIXEL_Y];

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int pixel_texture = 0;
static int red_texture = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	//テクスチャ読み込み
	pixel_texture = LoadTexture("data/TEXTURE/pixel.png");
	red_texture = LoadTexture("data/TEXTURE/red.png");

	for (int i = 0; i < PIXEL_Y; i++)
	{
		for (int j = 0; j < PIXEL_X; j++)
		{
			pixel[j][i].pos = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_X * i, SCREEN_HEIGHT / PIXEL_Y * j);
			pixel[j][i].size = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_X, SCREEN_HEIGHT / PIXEL_Y);

			tip[j][i].pos = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_X * i, SCREEN_HEIGHT / PIXEL_Y * j);
			tip[j][i].size = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_X, SCREEN_HEIGHT / PIXEL_Y);
			tip[j][i].drawflag = false;

			check[j][i] = 0;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Mouse_X = GetMousePosX();
	Mouse_Y = GetMousePosY();
	Mouse_LClick = GetMouseLClick();

	//マップお絵かき
	for (int i = 0; i < PIXEL_Y; i++)
	{
		for (int j = 0; j < PIXEL_X; j++)
		{
			//if (Mouse_X > pixel[j][i].pos.x && Mouse_X < pixel[j + 1][i + 1].pos.x && Mouse_Y > pixel[j][i].pos.y && Mouse_Y < pixel[j + 1][i + 1].pos.y)
			if (Mouse_X > pixel[j][i].pos.x && Mouse_X < pixel[j][i].pos.x + pixel[j][i].size.x &&
				Mouse_Y > pixel[j][i].pos.y && Mouse_Y < pixel[j][i].pos.y + pixel[j][i].size.y)
			{
				if (Mouse_LClick == true)
					tip[j][i].drawflag = true;
			}

			if (tip[j][i].drawflag == true)
			{
				check[j][i] = 1;
			}
		}
	}

	//.txt出力処理
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		FILE* fp;
		fp = fopen("マップチップデータ.txt", "w");
		for (int i = 0; i < PIXEL_Y; i++)
		{
			fprintf(fp, "{");
			for (int j = 0; j < PIXEL_X; j++)
			{
				fprintf(fp, "%d", check[i][j]);
				if (j < PIXEL_X - 1)
					fprintf(fp, ",");
			}
			fprintf(fp, "}");
			if(i < PIXEL_Y - 1)
			fprintf(fp, ",\n");
		}
		fclose(fp);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	for (int i = 0; i < PIXEL_Y; i++)
	{
		for (int j = 0; j < PIXEL_X; j++)
		{
			DrawSpriteLeftTop(pixel_texture, pixel[j][i].pos.x, pixel[j][i].pos.y, pixel[j][i].size.x, pixel[j][i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			{
				if (tip[j][i].drawflag == true)
					DrawSpriteLeftTop(red_texture, tip[j][i].pos.x, tip[j][i].pos.y, tip[j][i].size.x, tip[j][i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}
}