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





//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PIXEL_NUM 10

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float Mouse_X;
float Mouse_Y;
bool Mouse_LClick;

D3DXCOLOR color;

PIXEL pixel[PIXEL_NUM][PIXEL_NUM];
TIP tip[PIXEL_NUM][PIXEL_NUM];
int check[PIXEL_NUM][PIXEL_NUM];

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

	for (int i = 0; i < PIXEL_NUM; i++)
	{
		for (int j = 0; j < PIXEL_NUM; j++)
		{
			pixel[j][i].pos = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_NUM * i, SCREEN_HEIGHT / PIXEL_NUM * j);
			pixel[j][i].size = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_NUM, SCREEN_HEIGHT / PIXEL_NUM);

			tip[j][i].pos = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_NUM * i, SCREEN_HEIGHT / PIXEL_NUM * j);
			tip[j][i].size = D3DXVECTOR2(SCREEN_WIDTH / PIXEL_NUM, SCREEN_HEIGHT / PIXEL_NUM);
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
	for (int i = 0; i < PIXEL_NUM; i++)
	{
		for (int j = 0; j < PIXEL_NUM; j++)
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
		for (int i = 0; i < PIXEL_NUM; i++)
		{
			fprintf(fp, "{");
			for (int j = 0; j < PIXEL_NUM; j++)
			{
				fprintf(fp, "%d", check[i][j]);
				if (j < PIXEL_NUM - 1)
					fprintf(fp, ",");
			}
			fprintf(fp, "}");
			if(i < PIXEL_NUM - 1)
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
	for (int i = 0; i < PIXEL_NUM; i++)
	{
		for (int j = 0; j < PIXEL_NUM; j++)
		{
			DrawSpriteLeftTop(pixel_texture, pixel[j][i].pos.x, pixel[j][i].pos.y, pixel[j][i].size.x, pixel[j][i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			{
				if (tip[j][i].drawflag == true)
					DrawSpriteLeftTop(red_texture, tip[j][i].pos.x, tip[j][i].pos.y, tip[j][i].size.x, tip[j][i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}

	//DrawSpriteColor(pixel_texture, 80 * 2.5, 80 * 9.5, 80 * 3, 80, 0.0f, 0.0f, 1.0f, 1.0f, color);
}