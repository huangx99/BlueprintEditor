#pragma once
#include <string>
#include <vector>
#include <rttr\registration.h>
using String = std::string;
struct BPClassNode;
using BPClassNodePtr = std::shared_ptr<BPClassNode>;

enum BPPropertyType
{
	//普通变量
	pt_normal,
	//数组
	pt_array,
	//集
	pt_set,
	//映射
	pt_map
};

struct BPClassNode
{
	//类名
	String className;

	//属性名
	String propertyName;

	//类型
	BPPropertyType type = pt_normal;

	//类层级
	int layer = 0;

	//属性下标
	int index = 0;

	//数组下标 - 为子数组时使用
	int arrayIndex = -1;

	//映射下标
	String mapIndex;

	//数据
	rttr::variant data;

	//子属性
	std::vector<BPClassNodePtr> subNodes;

	//子数组
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


	//通过这两个可以定位嵌套类的变量在第几层嵌套
	 //类的层级
	int m_classLayer = -1;
	//变量的下标
	int m_propIndex = -1;
	//当前类的层级
	int m_currentClassLayer = -1;
	//当前变量的下标
	int m_currentPropIndex = -1;

	int test = 0;
};