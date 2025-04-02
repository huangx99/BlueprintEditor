#include "widget/BlueprintEditor.h"
#include <QtWidgets/QApplication>
#include <rttr/type>
using namespace rttr;

class Inner
{
public:
    int value = 10;
    int value2 = 10;
    int value3 = 10;
};

class Outer
{
public:
    Inner inner;
};

// ◊¢≤·∑¥…‰–≈œ¢
RTTR_REGISTRATION
{
    registration::class_<Inner>("Inner")
        .constructor<>()(rttr::policy::ctor::as_object)
        .property("value", &Inner::value)
        .property("value2", &Inner::value2)
        .property("value3", &Inner::value3);

    registration::class_<Outer>("Outer")

        .property("inner", &Outer::inner);
}

int i = -1;
int j = -1;

void fromjson_recursively(instance obj2, int& json_object, int c, int r)
{
    instance obj = obj2.get_type().get_raw_type().is_wrapper() ? obj2.get_wrapped_instance() : obj2;
    const auto prop_list = obj.get_derived_type().get_properties();
    i++;
    for (auto prop : prop_list)
    {
        const type value_t = prop.get_type();
        j++;
       if(value_t.is_class())
        {
        
            variant var = prop.get_value(obj);
            fromjson_recursively(var, json_object,1,2);
            prop.set_value(obj, var);
            break;
        }
       else
        {
            variant extracted_value = json_object;
            if (extracted_value.convert(value_t))
            {
                if(i == c && j == r)
                    prop.set_value(obj, extracted_value);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    Outer obj;
    int y = 1;
    fromjson_recursively(obj, y, 1, 2);
    QApplication a(argc, argv);
    BlueprintEditor w;
    w.show();
    return a.exec();
}
