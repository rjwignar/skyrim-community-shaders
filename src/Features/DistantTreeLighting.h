#pragma once

#include "Buffer.h"
#include "Feature.h"

struct DistantTreeLighting : Feature
{
	static DistantTreeLighting* GetSingleton()
	{
		static DistantTreeLighting singleton;
		return &singleton;
	}

	virtual inline std::string GetName() { return "Tree LOD Lighting"; }
	virtual inline std::string GetShortName() { return "TreeLODLighting"; }

	struct Settings
	{
		std::uint32_t EnableComplexTreeLOD = 1;
		std::uint32_t EnableDirLightFix = 1;
		float SubsurfaceScatteringAmount = 0.5;
		float FogDimmerAmount = 1.0;
	};

	struct alignas(16) PerPass
	{
		DirectX::XMFLOAT4 EyePosition;
		DirectX::XMFLOAT3X4 DirectionalAmbient;
		DirectX::XMFLOAT4 DirLightColor;
		DirectX::XMFLOAT4 DirLightDirection;
		float DirLightScale;
		std::uint32_t ComplexAtlasTexture;
		Settings Settings;
		float pad0;
		float pad1;
	};

	Settings settings;
	ConstantBuffer* perPass = nullptr;

	RE::TESWorldSpace* lastWorldSpace = nullptr;
	bool complexAtlasTexture = false;

	virtual void SetupResources();
	virtual inline void Reset() {}

	virtual void DrawSettings();
	void ModifyDistantTree(const RE::BSShader* shader, const uint32_t descriptor);
	virtual void Draw(const RE::BSShader* shader, const uint32_t descriptor);

	virtual void Load(json& o_json);
	virtual void Save(json& o_json);
};
