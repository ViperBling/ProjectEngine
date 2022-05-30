#include <iostream>
#include "Platform/ArchDetect.h"
#include "Platform/Assert.h"
#include "Platform/BuildType.h"
#include "Platform/Platform.h"
#include "EngineConfig.h"

#include "Application/WindowsApplication.h"
#include "Framework/Common/Utils/Logging.h"

using namespace std;
using namespace ProjectEngine;

namespace ProjectEngine
{
#if defined(PROJECTENGINE_WINDOWS)
    extern Application* GApp = GWindowsApplication::GetInstance();
#endif
}


int main()
{
    PROJECTENGINE_LOG(info) << "EngineVersion: " << Engine_Version_Major << "."  << Engine_Version_Minor;
    PROJECTENGINE_LOG(info) << "EngineArch: " << PROJECTENGINE_ARCH;
    PROJECTENGINE_LOG(info) << "EngineTargetPlatform: " << PROJECTENGINE_PLATFORM;
    PROJECTENGINE_LOG(info) << "EngineBuildType: " << BUILD_TYPE;

#if defined(PROJECTENGINE_WINDOWS)
//    GApp->SetSize(1280, 720);
    CHECK_APPLICATION_INIT(GApp->Initialize());
    GApp->mWorld->LoadScene("Asset/Scene/Rosalia.fbx");
    GApp->mWorld->DumpEntities();
    GApp->mWorld->GetRenderDebugSystem()->CreateDebugMesh();

    GApp->Run();
    GApp->Finalize();

#endif

    return 0;
}