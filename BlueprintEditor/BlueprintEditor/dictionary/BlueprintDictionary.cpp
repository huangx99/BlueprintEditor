#include "BlueprintDictionary.h"

RTTR_REGISTRATION
{
    rttr::registration::enumeration<AccessSpecifierType>("AccessSpecifierType")
        (
            rttr::value("AST_public", AccessSpecifierType::AST_public),
            rttr::value("AST_private", AccessSpecifierType::AST_private),
            rttr::value("AST_protected", AccessSpecifierType::AST_protected)
        );

    rttr::registration::enumeration<VariableSetType>("VariableSetType")
        (
            rttr::value("VST_single", VariableSetType::VST_single),
            rttr::value("VST_array", VariableSetType::VST_array),
            rttr::value("VST_set", VariableSetType::VST_set),
            rttr::value("VST_map", VariableSetType::VST_map)
        );
}