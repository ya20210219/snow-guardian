/*==============================================================================

   �X�v���C�g�`�惂�W���[�� [sprite.cpp]
                                                         Author : Youhei Sato
                                                         Date   : 2018/06/17
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3dx9.h>
#include <math.h>
#include "MyDirect3d.h"
#include "texture.h"


/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/
// �QD�|���S�����_�\����
typedef struct Vertex2D_tag
{
    D3DXVECTOR4 position; // ���_���W�i���W�ϊ��ςݒ��_�j
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} Vertex2D;
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) // �QD�|���S�����_�t�H�[�}�b�g


/*------------------------------------------------------------------------------
   �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
static D3DCOLOR g_Color = 0xffffffff;
// static D3DCOLOR g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);



/*------------------------------------------------------------------------------
   �֐���`
------------------------------------------------------------------------------*/

// �X�v���C�g�|���S���̒��_�J���[�ݒ�
void Sprite_SetColor(D3DCOLOR color)
{
	g_Color = color;
}

// �X�v���C�g�`��
// ���e�N�X�`���𑜓x�Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int colortype)
{
	LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
    if( !pDevice ) return;

    // �e�N�X�`���̕��A�����擾
	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	//��{
	if (colortype == 0)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//��
	if (colortype == 1)
	{
		g_Color = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//���F
	if (colortype == 2)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 0, 255);
	}
	//��
	if (colortype == 3)
	{
		g_Color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}

	//���Â�
	if (colortype == 4)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 255, 10);
	}

    // ���_�f�[�^
    Vertex2D vertexes[] = {
        { D3DXVECTOR4(dx     - 0.5f, dy     - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 0.0f) },
        { D3DXVECTOR4(dx + w - 0.5f, dy     - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(dx     - 0.5f, dy + h - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR4(dx + w - 0.5f, dy + h - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(1.0f, 1.0f) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);                             // �f�o�C�X�ɒ��_�̍\���v�f��ݒ�
	pDevice->SetTexture(0, Texture_GetTexture(texture_index)); // �f�o�C�X�Ƀe�N�X�`����ݒ�

     // �v���~�e�B�u�̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}


// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɕ`�悷��
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty,int tw, int th, int colortype)
{
	LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
    if( !pDevice ) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

    // UV���W�v�Z
    float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	//��{
	if (colortype == 0)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//��
	if (colortype == 1)
	{
		g_Color = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//���F
	if (colortype == 2)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 0, 255);
	}
	//��
	if (colortype == 3)
	{
		g_Color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}
	//���Â�
	if (colortype == 4)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 255, 10);
	}

    Vertex2D vertexes[] = {
        { D3DXVECTOR4(dx      - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
        { D3DXVECTOR4(dx + tw - 0.5f, dy      - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(dx      - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(dx + tw - 0.5f, dy + th - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
    };

    pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
    pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}

// �X�v���C�g�`��
// ���e�N�X�`���؂��蕝�A�����Ɠ����傫���̃X�v���C�g���w����W�ɔz�u���ăX�v���C�g�̎w����W�𒆐S�Ɋg��A��]�`�悷��
void Sprite_Draw(TextureIndex texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation, int colortype)
{
	LPDIRECT3DDEVICE9 pDevice = MyD3D_GetDevice();
	if (!pDevice) return;

	float w = (float)Texture_GetWidth(texture_index);
	float h = (float)Texture_GetHeight(texture_index);

	float u[2], v[2];
	u[0] = (float)tx / w;
	v[0] = (float)ty / h;
	u[1] = (float)(tx + tw) / w;
	v[1] = (float)(ty + th) / h;

	// ���W�ϊ�
	float px[4], py[4];
	px[0] = -cx * sx * cosf(rotation) - -cy * sy * sinf(rotation);
	py[0] = -cx * sx * sinf(rotation) + -cy * sy * cosf(rotation);
	px[1] = (-cx + tw) * sx * cosf(rotation) - -cy * sy * sinf(rotation);
	py[1] = (-cx + tw) * sx * sinf(rotation) + -cy * sy * cosf(rotation);
	px[2] = -cx * sx * cosf(rotation) - (-cy + th) * sy * sinf(rotation);
	py[2] = -cx * sx * sinf(rotation) + (-cy + th) * sy * cosf(rotation);
	px[3] = (-cx + tw) * sx * cosf(rotation) - (-cy + th) * sy * sinf(rotation);
	py[3] = (-cx + tw) * sx * sinf(rotation) + (-cy + th) * sy * cosf(rotation);

	//float baseAngle = D3DX_PI / 4; // D3DXToRadian(45)
	//float size = 100.0f;
	//px[0] = size * cosf(rotation - baseAngle * 3);
	//py[0] = size * sinf(rotation - baseAngle * 3);
	//px[1] = size * cosf(rotation - baseAngle);
	//py[1] = size * sinf(rotation - baseAngle);
	//px[2] = size * cosf(rotation + baseAngle * 3);
	//py[2] = size * sinf(rotation + baseAngle * 3);
	//px[3] = size * cosf(rotation + baseAngle);
	//py[3] = size * sinf(rotation + baseAngle);

	//��{
	if (colortype == 0)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	//��
	if (colortype == 1)
	{
		g_Color = D3DCOLOR_RGBA(255, 0, 0, 255);
	}
	//���F
	if (colortype == 2)
	{
		g_Color = D3DCOLOR_RGBA(255, 255, 0, 255);
	}
	//��
	if (colortype == 3)
	{
		g_Color = D3DCOLOR_RGBA(0, 255, 0, 255);
	}
	//���Â�
	if (colortype == 4)
	{
		g_Color = D3DCOLOR_RGBA(120, 120, 120, 255);
	}


	Vertex2D vertexes[] = {
		{ D3DXVECTOR4(px[0] + dx - 0.5f, py[0] + dy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[0]) },
		{ D3DXVECTOR4(px[1] + dx - 0.5f, py[1] + dy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[0]) },
		{ D3DXVECTOR4(px[2] + dx - 0.5f, py[2] + dy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[0], v[1]) },
		{ D3DXVECTOR4(px[3] + dx - 0.5f, py[3] + dy - 0.5f, 0.0f, 1.0f), g_Color, D3DXVECTOR2(u[1], v[1]) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);
	pDevice->SetTexture(0, Texture_GetTexture(texture_index));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertexes, sizeof(Vertex2D));
}



