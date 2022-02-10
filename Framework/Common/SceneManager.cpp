#include "SceneManager.hpp"
#include "AssetLoader.hpp"
#include "OGEX.hpp"

using namespace ProjectEngine;
using namespace std;

SceneManager::~SceneManager() {

}

int SceneManager::Initialize() {
    int result = 0;
    return result;
}

void SceneManager::Finalize()
{
}

void SceneManager::Tick()
{
}

void SceneManager::LoadScene(const char *scene_file_name)
{
    // now we only has ogex scene parser, call it directly
    LoadOgexScene(scene_file_name);
}

const Scene &SceneManager::GetSceneForRendering()
{
    return *m_pScene;
}

void SceneManager::LoadOgexScene(const char* ogex_scene_file_name)
{
    string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString(ogex_scene_file_name);

    OgexParser ogex_parser;
    m_pScene = ogex_parser.Parse(ogex_text);
}


