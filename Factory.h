#pragma once
#include "Plugin.h"

using namespace System;
using namespace TFlex;
public ref class Factory : public PluginFactory
{
public:
    virtual Plugin^ CreateInstance() override;
    property Guid ID
    {
        Guid get() override
        {
            return Guid("{32F0C0D7-F517-4b69-837F-F14626598100}");
        }
    }
    property String^ Name
    {
        String^ get() override
        {
            return "HelloWorld";
        }
    }
};

