#include <iostream>
#include "Platform/ArchDetect.h"
#include "Platform/Assert.h"
#include "Platform/BuildType.h"
#include "Platform/Platform.h"
#include "EngineConfig.h"

#include "Application/WindowsApplication.h"

using namespace std;

int main()
{
    cout << "EngineVersion: " << Engine_Version_Major <<
    "."  << Engine_Version_Minor << endl;

    cout << "EngineArch: " << PROJECTENGINE_ARCH << endl;
    cout << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM << endl;
    cout << "EngineBuildType: " << BUILD_TYPE << endl;

#if defined(PROJECTENGINE_WINDOWS)

    cout << "Creating Windows..." << endl;
    ProjectEngine::WindowsApplication WinApp;
    CHECK_APPLICATION_INIT(WinApp.Initialize());
    WinApp.Run();
    WinApp.Finalize();

#endif

    return 0;
}