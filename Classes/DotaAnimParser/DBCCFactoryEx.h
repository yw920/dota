#pragma once

#include "cocos2d.h"
#include "DBCCRenderHeaders.h"
#include "DotaAnimParser.h"

class DBCCFactoryEx : public dragonBones::DBCCFactory
{
public:
	DBCCFactoryEx(void);
	virtual ~DBCCFactoryEx(void);

public:
	static DBCCFactoryEx* getInstanceEx();
	static void destroyInstanceEx();

	// ���ص��������*.fca�ļ�
	bool loadDotaFcaFile(const std::string &fcaFile);

	// ����DragonBones�������ļ�(sheet.pvr��texture.xml��skeleton.xml)
	bool exportDBConfigFile(const std::string &fcaFile, const std::string &savePath);

private:
	// ������������
	dragonBones::ITextureAtlas* loadDotaTextureAtlas(
		const std::string &fcaFile,
		const std::string &name = "");

	// ���ع�������
	dragonBones::DragonBonesData* loadDotaDragonBonesData(
		Dota_Skeleton_Data& dotaSkeletonData,
		dragonBones::ITextureAtlas& textureAtlas, 
		const std::string &name = "");

private:
	static DBCCFactoryEx *_instanceex;
};

