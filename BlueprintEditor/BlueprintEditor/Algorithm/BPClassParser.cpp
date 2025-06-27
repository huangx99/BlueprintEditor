#include "BPClassParser.h"

BPClassParser::BPClassParser(rttr::instance obj):m_obj(obj)
{
    m_private = std::make_shared<BPClassParserPrivate>();
    m_private->root = std::make_shared<BPClassNode>();
    bulidParser(obj, m_private->root);
}

void BPClassParser::setValue(int level, int index, const rttr::variant& value, int arrayIndex, const String& mapIndex)
{
}

rttr::variant BPClassParser::getValue(int level, int index, int arrayIndex, const String& mapIndex)
{
	return rttr::variant();
}

void BPClassParser::bulidParser(rttr::instance obj, BPClassNodePtr node)
{
    test++;
    m_classLayer++;
    m_propIndex = -1;

    rttr::type t = obj.get_type();

    auto ty = t.get_wrapped_type();

    if (t.get_raw_type().get_wrapped_type().is_valid())
    {
        t = t.get_raw_type().get_wrapped_type();
    }

    for (auto& prop : t.get_properties()) {
        m_propIndex++;

        rttr::variant value = prop.get_value(obj);
        rttr::type valueType = value.get_type();

        int classLayer = m_classLayer;
        int propIndex = m_propIndex;

        // 是否为自定义结构体
        bool isCustomType = valueType.get_metadata("isCustomType").is_valid()
            && valueType.get_metadata("isCustomType").to_bool();

        BPClassNodePtr subNode = std::make_shared<BPClassNode>();;
        subNode->className = t.get_name().to_string();
        if (t.get_raw_type().is_valid())
        {
            subNode->className = t.get_raw_type().get_name().to_string();
        }
        subNode->propertyName = prop.get_name().to_string();
        subNode->layer = m_classLayer;
        subNode->index = m_propIndex;
        node->subNodes.push_back(subNode);
        if (isCustomType) {

            bulidParser(prop.get_value(obj), subNode);  // 递归
            
            continue;
        }
    }

    m_classLayer--;
}

