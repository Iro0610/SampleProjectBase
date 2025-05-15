﻿#include "Main.h"
#include "Defines.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneRoot.h"
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

ID3DBlob* g_pVSBlob = nullptr;
ID3DBlob* g_pPSBlob = nullptr;

//--- グローバル変数
std::shared_ptr<SceneRoot> g_pScene;


HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }
	Geometory::Init();
	Sprite::Init();
	InitInput();
	// 编译VS_WorldPosition.hlsl
	hr = D3DCompileFromFile(
		L"VS_WorldPosition.hlsl", 
		nullptr, nullptr,         
		"main",                   
		"vs_5_0",                
		0, 0,                     
		&g_pVSBlob, nullptr      
	);
	if (FAILED(hr)) { return hr; }

	// 编译PS_PhongSpecular.hlsl
	hr = D3DCompileFromFile(
		L"PS_PhongSpecular.hlsl",
		nullptr, nullptr,
		"main",
		"ps_5_0",
		0, 0,
		&g_pPSBlob, nullptr
	);
	if (FAILED(hr)) { return hr; }
	// シーン作成
	g_pScene = std::make_shared<SceneRoot>();
	g_pScene->Init();
	SetWindowText(hWnd, (APP_TITLE + g_pScene->GetSceneName()).c_str());

	// 初期リソース作成
	auto rtv = g_pScene->CreateObj<RenderTarget>("RTV");
	rtv->CreateFromScreen();
	auto dsv = g_pScene->CreateObj<DepthStencil>("DSV");
	hr = dsv->Create(width, height, false);

	SetRenderTargets(1, &rtv, dsv);

	return hr;
}

void Uninit()
{
	if (g_pVSBlob) { g_pVSBlob->Release(); g_pVSBlob = nullptr; }
	if (g_pPSBlob) { g_pPSBlob->Release(); g_pPSBlob = nullptr; }
	g_pScene->Uninit();
	g_pScene.reset();

	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	UninitDirectX();
}

void Update(HWND hWnd, float tick)
{
	UpdateInput();
	g_pScene->_update(tick);

	if (g_pScene->isSceneChange()) {
		SetWindowText(hWnd, (APP_TITLE + g_pScene->GetSceneName()).c_str());
	}
}

void Draw()
{
	auto rtv = g_pScene->GetObj<RenderTarget>("RTV");
	auto dsv = g_pScene->GetObj<DepthStencil>("DSV");
	float color[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
	GetContext()->ClearRenderTargetView(rtv->GetView(), color);
	GetContext()->ClearDepthStencilView(dsv->GetView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	g_pScene->_draw();
	
	SwapDirectX();
}

// EOF