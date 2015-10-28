#include <string>
#include <vector>
#include <map>

class Dota_Bone_Data			// ��ͷ����
{
public:
	std::string name;			// ��ͷ����
	std::string textureName;	// ��ͷʹ�õ���������
	int index;					// ��ͷ����
};

class Dota_Slot_Data			// ������
{
public:
	short boneIndex;			// ��ͷ����
	unsigned char opacity;		// ͸����
	float x, y;					// �����
	float skX, skY;				// ��бϵ��
	float scX, scY;				// ����ϵ��
	int zOrder;					// ת����ʽ�����������ݴ�Ĺ�ͷ���ڵ�z������
	std::string soundName;		// ת����ʽ�����������ݴ�������ļ�����
};

class Dota_Frame_Data			// ����֡����
{
public:
	Dota_Frame_Data(void){}
	~Dota_Frame_Data(void)
	{
		for (int i = 0; i < (int)slotDataList.size(); i++)
		{
			delete slotDataList[i];
		}
		slotDataList.clear();
	}

public:
	int type;									// ����֡����
	int unknownData1;							// δ֪����1
	std::string soundName;						// �����ļ�����
	unsigned char soundData[32];				// δ֪��������
	int unknownData2;							// δ֪����2
	std::vector<Dota_Slot_Data *> slotDataList;	// �������б�
};

class Dota_Anim_Data		// ��������
{
public:
	Dota_Anim_Data(void){}
	~Dota_Anim_Data(void)
	{
		for (int i = 0; i < (int)frameDataList.size(); i++)
		{
			delete frameDataList[i];
		}
		frameDataList.clear();
	}

public:
	std::string name;								// ��������
	unsigned char unknownData[4];					// δ֪����
	std::vector<Dota_Frame_Data *> frameDataList;	// ����֡�����б�
};

typedef std::map<std::string, Dota_Slot_Data *> Dota_Timeline_Data;		// ʱ����<�ڼ�֡��������>
typedef std::map<std::string, Dota_Timeline_Data *> Dota_Anim_Data2;	// ��������2<��ͷ����ʱ����>
typedef std::map<std::string, Dota_Slot_Data *> Dota_First_Frame_Data;	// �洢ÿ����ͷ�ĵ�һ֡����<��ͷ����������>

class Dota_Skeleton_Data	// �Ǽ�����
{
public:
	Dota_Skeleton_Data(void){}
	~Dota_Skeleton_Data(void)
	{
		for (int i = 0; i < (int)boneDataList.size(); i++)
		{
			delete boneDataList[i];
		}
		boneDataList.clear();

		for (int i = 0; i < (int)animDataList.size(); i++)
		{
			delete animDataList[i];
		}
		animDataList.clear();

		std::map<std::string, Dota_Anim_Data2 *>::iterator iter;
		for (iter = animDataMap.begin(); iter != animDataMap.end(); iter++)
		{
			Dota_Anim_Data2 * animData2 = iter->second;
			if (nullptr == animData2)
				continue;

			Dota_Anim_Data2::iterator iter2;
			for (iter2 = animData2->begin(); iter2 != animData2->end(); iter2++)
			{
				Dota_Timeline_Data * timelineData = iter2->second;

				// 				Dota_Timeline_Data::iterator iter3;
				// 				for (iter3 = timelineData->begin(); iter3 != timelineData->end(); iter3++)
				// 				{
				// 					delete iter3->second;
				// 				}

				timelineData->clear();
				delete timelineData;
			}
			animData2->clear();
			delete animData2;
		}
		animDataMap.clear();
		firstFrameOfBoneMap.clear();
	}

public:
	std::string name;										// �Ǽ�����
	std::vector<Dota_Bone_Data *> boneDataList;				// ��ͷ�����б�
	std::vector<Dota_Anim_Data *> animDataList;				// ���������б�
	std::map<std::string, Dota_Anim_Data2 *> animDataMap;	// �������ݼ�ֵ��<�������ƣ���������2>
	Dota_First_Frame_Data firstFrameOfBoneMap;				// ��ȡÿ����ͷ�ĵ�һ֡����<��ͷ������ͷ�ĵ�һ֡>
};