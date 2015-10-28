#include "DBCCFactoryEx.h"
#include "DBCCTextureAtlasEx.h"
#include "Utils.h"

USING_NS_DB;

DBCCFactoryEx* DBCCFactoryEx::_instanceex = nullptr;

DBCCFactoryEx::DBCCFactoryEx(void)
{
}


DBCCFactoryEx::~DBCCFactoryEx(void)
{
}

DBCCFactoryEx* DBCCFactoryEx::getInstanceEx()
{
	if (!_instanceex)
	{
		_instanceex = new DBCCFactoryEx();
	}
	return _instanceex;
}

void DBCCFactoryEx::destroyInstanceEx()
{
	if (_instanceex)
	{
		CC_SAFE_DELETE(_instanceex);
	}
}

// ���ص��������*.fca�ļ�
bool DBCCFactoryEx::loadDotaFcaFile(const std::string &fcaFile)
{
	DotaAnimParser parser;
	Dota_Skeleton_Data* skeletonData = parser.parseDotaSkeletonData(fcaFile);
	if (nullptr == skeletonData)
		return false;

	ITextureAtlas* textureAtlas = loadDotaTextureAtlas(fcaFile, skeletonData->name);
	if (nullptr == skeletonData)
	{
		delete skeletonData;
		return false;
	}

	DragonBonesData* dragonBonesData = loadDotaDragonBonesData(*skeletonData, *textureAtlas, skeletonData->name);
	if (nullptr == dragonBonesData)
	{
		delete skeletonData;
		return false;
	}

	delete skeletonData;
	return true;
}

// ����DragonBones�������ļ�(sheet.pvr��texture.xml��skeleton.xml)
bool DBCCFactoryEx::exportDBConfigFile(const std::string &fcaFile, 
									   const std::string &savePath)
{
	DotaAnimParser parser;
	return parser.exportDBConfigFile(fcaFile, savePath);
}

// ������������
ITextureAtlas* DBCCFactoryEx::loadDotaTextureAtlas(
	const std::string &fcaFile,
	const std::string &name/* = ""*/)
{
	ITextureAtlas *existTextureAtlas = getTextureAtlas(name);

	if (existTextureAtlas)
	{
		refreshTextureAtlasTexture(name.empty() ? existTextureAtlas->textureAtlasData->name : name);
		return existTextureAtlas;
	}

	// textureAtlas scale
	float scale = cocos2d::Director::getInstance()->getContentScaleFactor();

	DotaAnimParser parser;
	DBCCTextureAtlasEx *textureAtlas = new DBCCTextureAtlasEx();
	textureAtlas->_fcaFile = fcaFile;
	textureAtlas->textureAtlasData = parser.parseTextureAtlasData(fcaFile, scale);
	textureAtlas->textureAtlasData->name = name;

	addTextureAtlas(textureAtlas, name);
	refreshTextureAtlasTexture(name.empty() ? textureAtlas->textureAtlasData->name : name);
	return textureAtlas;
}

// ���ع�������
DragonBonesData* DBCCFactoryEx::loadDotaDragonBonesData(
	Dota_Skeleton_Data& dotaSkeletonData,
	ITextureAtlas& textureAtlas, 
	const std::string &name/* = ""*/)
{
	DragonBonesData *existDragonBonesData = getDragonBonesData(name);

	if (existDragonBonesData)
	{
		return existDragonBonesData;
	}

	// armature scale
	float scale = cocos2d::Director::getInstance()->getContentScaleFactor();

	DotaAnimParser parser;
	DragonBonesData *dragonBonesData = parser.parseDragonBonesData(dotaSkeletonData, textureAtlas, scale);
	addDragonBonesData(dragonBonesData, name);
	return dragonBonesData;
}

