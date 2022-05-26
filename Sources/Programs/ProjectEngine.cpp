#include <iostream>
#include "Platform/ArchDetect.h"
#include "Platform/Assert.h"
#include "Platform/BuildType.h"
#include "Platform/Platform.h"
#include "EngineConfig.h"

#include "Application/WindowsApplication.h"

using namespace std;
using namespace ProjectEngine;

#if defined(PROJECTENGINE_WINDOWS)
extern Application* GApp = GWindowsApplication::GetInstance();
#endif

int main()
{
    cout << "EngineVersion: " << Engine_Version_Major <<
    "."  << Engine_Version_Minor << endl;

    cout << "EngineArch: " << PROJECTENGINE_ARCH << endl;
    cout << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM << endl;
    cout << "EngineBuildType: " << BUILD_TYPE << endl;

#if defined(PROJECTENGINE_WINDOWS)

    CHECK_APPLICATION_INIT(GApp->Initialize());
    GApp->mWorld->LoadScene("Asset/Scene/aili_cycle.fbx");
    GApp->mWorld->DumpEntities();

    GApp->Run();
    GApp->Finalize();

#endif

    return 0;
}