#include "Factory.h"

Plugin^ Factory::CreateInstance()
{
    return gcnew HelloPlugin(this);
}
