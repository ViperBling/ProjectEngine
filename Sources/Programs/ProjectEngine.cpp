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
<<<<<<< HEAD
=======

#if defined(PROJECTENGINE_WINDOWS)
extern Application* GApp = GWindowsApplication::GetInstance();
#endif
>>>>>>> remotes/origin/Branch_Rebase

int main()
{
    cout << "EngineVersion: " << Engine_Version_Major <<
    "."  << Engine_Version_Minor << endl;

    cout << "EngineArch: " << PROJECTENGINE_ARCH << endl;
    cout << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM << endl;
    cout << "EngineBuildType: " << BUILD_TYPE << endl;


<<<<<<< HEAD
    CHECK_APPLICATION_INIT(GApp->Initialize());
    GApp->mWorld->LoadScene("E:\\Program\\CG\\ProjectEngine\\Asset\\Scene\\Teapot.fbx");
    GApp->mWorld->DumpEntities();
    GApp->mWorld->GetRenderDebugSystem()->CreateDebugMesh();
=======
    cout << "Creating Windows..." << endl;
    CHECK_APPLICATION_INIT(GApp->Initialize());
    GApp->Run();
    GApp->Finalize();
>>>>>>> remotes/origin/Branch_Rebase

    GApp->Run();
    GApp->Finalize();

    return 0;
}