#pragma once

#include "Core.h"

namespace Aurora
{
    enum class ValueType
    {
        Int, Float, Bool, Short
    };

    struct AurValue
    {
        ValueType Type;
        
        union
        {
            float mFloat;
            int mInt;
            bool mBool;
            short mShort;
        };
    };

    struct AUR_API AurObject
    {
        AurObject(AurValue* value) : Value(value)
        {
        }

        AurValue* Value;
    };
}
