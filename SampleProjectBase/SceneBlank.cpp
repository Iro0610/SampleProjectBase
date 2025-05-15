#include "math.h"
#include "SceneBlank.h"
#include "Geometory.h"
#include "DebugLog.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void SceneBlank::Init()
{
	// シェーダーの読み込み処理
	Shader* shader[] = {
		CreateObj<VertexShader>("VS_WorldPosition"),
		CreateObj<PixelShader>("PS_PhongSpecular"),

	};
	const char* file[] = {
		"Assets/Shader/VS_WorldPosition.cso",
		"Assets/Shader/PS_PhongSpecular.cso",
	};
	int shaderNum = _countof(shader);
	for (int i = 0; i < shaderNum; ++i)
	{
		if (FAILED(shader[i]->Load(file[i])))
		{
			MessageBox(NULL, file[i], "Shader Error", MB_OK);
		}
	}
}
void SceneBlank::Uninit()
{

}
void SceneBlank::Update(float tick)
{
	Shader* shader[] = {
		  
		   GetObj<Shader>("VS_WorldPosition"),
		   
		   GetObj<Shader>("PS_PhongSpecular"),
	};

}
void SceneBlank::Draw()
{

}
