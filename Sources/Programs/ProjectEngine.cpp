#include <iostream>
#include "Platform/ArchDetect.h"
#include "Platform/Assert.h"
#include "Platform/BuildType.h"
#include "Platform/Platform.h"
#include "EngineConfig.h"

using namespace std;

int main()
{
    cout << "EngineVersion: " << Engine_Version_Major <<
    "."  << Engine_Version_Minor << endl;

    cout << "EngineArch: " << PROJECTENGINE_ARCH << endl;
    cout << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM << endl;
    cout << "EngineBuildType: " << BUILD_TYPE << endl;

    int a, b;
    a = 1, b = 2;

    PROJECTENGINE_ASSERT(a > b);

    return 0;
}