#pragma once
#include <string>
#include <vector>
#include <rttr\registration.h>
using String = std::string;
struct BPClassNode;
using BPClassNodePtr = std::shared_ptr<BPClassNode>;

enum BPPropertyType
{
	//��ͨ����
	pt_normal,
	//����
	pt_array,
	//��
	pt_set,
	//ӳ��
	pt_map
};

struct BPClassNode
{
	//����
	String className;

	//������
	String propertyName;

	//����
	BPPropertyType type = pt_normal;

	//��㼶
	int layer = 0;

	//�����±�
	int index = 0;

	//�����±� - Ϊ������ʱʹ��
	int arrayIndex = -1;

	//ӳ���±�
	String mapIndex;

	//����
	rttr::variant data;

	//������
	std::vector<BPClassNodePtr> subNodes;

	//������
	std::vector<BPClassNodePtr> subArray;
};




struct BPClassParserPrivate
{
	BPClassNodePtr root;
};

using BPClassParserPrivatePtr = std::shared_ptr<BPClassParserPrivate>;


class BPClassParser
{
public:
	BPClassParser(rttr::instance obj);

	void setValue(int level, int index, const rttr::variant& value, int arrayIndex, const String& mapIndex);

	rttr::variant getValue(int level, int index, int arrayIndex, const String& mapIndex);
private:
	void bulidParser(rttr::instance obj, BPClassNodePtr node);

private:
	BPClassParserPrivatePtr m_private;

	rttr::instance m_obj;


	//ͨ�����������Զ�λǶ����ı����ڵڼ���Ƕ��
	 //��Ĳ㼶
	int m_classLayer = -1;
	//�������±�
	int m_propIndex = -1;
	//��ǰ��Ĳ㼶
	int m_currentClassLayer = -1;
	//��ǰ�������±�
	int m_currentPropIndex = -1;

	int test = 0;
};