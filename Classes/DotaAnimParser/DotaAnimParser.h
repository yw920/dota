#pragma once

#include "cocos2d.h"
#include "DBCCRenderHeaders.h"
#include "DBCCTextureAtlasEx.h"
#include "Utils.h"
#include "ByteArray.h"
#include "DotaAnimData.h"

class DotaAnimParser	// ��������������
{
public:
	DotaAnimParser(void);
	~DotaAnimParser(void);

public:
	// �����������Ǽ�����
	Dota_Skeleton_Data* parseDotaSkeletonData(const std::string &fcaFile);

	// ������DB��������
	dragonBones::TextureAtlasData* parseTextureAtlasData(
		const std::string &fcaFile, float scale = 1.f);

	// ������DB��������
	dragonBones::DragonBonesData* parseDragonBonesData(
		Dota_Skeleton_Data& dotaSkeletonData,
		dragonBones::ITextureAtlas& textureAtlas, float scale = 1.f);

	// ����DragonBones�������ļ�(sheet.pvr��texture.xml��skeleton.xml)
	bool exportDBConfigFile(const std::string &fcaFile, const std::string &savePath);

private:
	void parseTimeline(dragonBones::Timeline &timeline);
	void addHideTimeline(dragonBones::AnimationData *animationData, const dragonBones::ArmatureData *armatureData);
	void transformAnimationData(dragonBones::AnimationData *animationData, const dragonBones::ArmatureData *armatureData);
	void transformArmatureData(dragonBones::ArmatureData *armatureData);
	void setFrameTransform(dragonBones::AnimationData *animationData, const dragonBones::ArmatureData *armatureData, const dragonBones::BoneData *boneData, dragonBones::TransformFrame *frame);
	void getTimelineTransform(const dragonBones::TransformTimeline *timeline, int position, dragonBones::Transform *retult, bool isGlobal);

	dragonBones::TransformFrame * newBlankKeyframes(int duration, const std::string& sound);
	dragonBones::TransformFrame * newKeyframes(int zOrder, unsigned char opacity, 
		float x, float y, float skX, float skY, float scX, float scY, 
		const std::string& sound);
	void setTransform(dragonBones::Transform &transform, float x, float y, 
		float skX, float skY, float scX, float scY);
	void setPivot(dragonBones::Point &pivot, float pX, float pY);
	void setColorTransform(dragonBones::ColorTransform &colorTransform, unsigned char opacity);

	// ����DragonBones������ͼƬ(sheet.pvr)
	void exportDBTexturePic(const std::string &savePath, const std::string &fcaFile);

	// ����DragonBones����������(texture.xml)
	void exportDBTextureData(const std::string &savePath,
		dragonBones::ITextureAtlas& textureAtlas);

	// ����DragonBones�Ĺ�������(skeleton.xml)
	void exportDBSkeletonData(const std::string &savePath,
		Dota_Skeleton_Data& dotaSkeletonData,
		dragonBones::ITextureAtlas& textureAtlas);

private:
	mutable float _armatureScale;
	mutable int _frameRate;
};

