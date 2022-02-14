#include <iostream>
#include "Platform/ArchDetect.h"
#include "Platform/Assert.h"
#include "Platform/BuildType.h"
#include "Platform/Platform.h"
#include "EngineConfig.h"

#include "Application/WindowsApplication.h"

namespace ProjectEngine
{
    extern Application* GApp = GWindowsApplication::GetInstance();
}

using namespace std;
using namespace ProjectEngine;

int main()
{
    cout << "EngineVersion: " << Engine_Version_Major <<
    "."  << Engine_Version_Minor << endl;

    cout << "EngineArch: " << PROJECTENGINE_ARCH << endl;
    cout << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM << endl;
    cout << "EngineBuildType: " << BUILD_TYPE << endl;


    CHECK_APPLICATION_INIT(GApp->Initialize());
    GApp->mWorld->LoadScene("E:\\Program\\ProjectEngine\\Asset\\Scene\\aili_cycle.fbx");
    GApp->mWorld->DumpEntities();

    GApp->Run();
    GApp->Finalize();

    return 0;
}