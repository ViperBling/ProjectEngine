#include "AssetLoader.hpp"

int ProjectEngine::AssetLoader::Initialize()
{
    return 0;
}

void ProjectEngine::AssetLoader::Finalize()
{
    m_strSearchPath.clear();
}

void ProjectEngine::AssetLoader::Tick() {}

bool ProjectEngine::AssetLoader::AddSearchPath(const char *path)
{
    std::vector<std::string>::iterator src = m_strSearchPath.begin();

    while (src != m_strSearchPath.end())
    {
        if (!(*src).compare(path))
            return true;
        src++;
    }
    m_strSearchPath.push_back(path);
    return true;
}

bool ProjectEngine::AssetLoader::RemoveSearchPath(const char *path)
{
    std::vector<std::string>::iterator src = m_strSearchPath.begin();

    while (src != m_strSearchPath.end())
    {
        if (!(*src).compare(path)) {
            m_strSearchPath.erase(src);
            return true;
        }
        src++;
    }
    return true;
}

bool ProjectEngine::AssetLoader::FileExists(const char *filePath)
{
    AssetFilePtr fp = OpenFile(filePath, ProjectEngine_OPEN_BINARY);
    if (fp != nullptr)
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

ProjectEngine::AssetLoader::AssetFilePtr ProjectEngine::AssetLoader::OpenFile(const char *name, AssetOpenMode mode)
{
    FILE *fp = nullptr;

    // Loop N times up the hierarchy, testing at each level
    std::string upPath;
    std::string fullPath;

    for (int32_t i = 0; i < 10; i++)
    {
        std::vector<std::string>::iterator src = m_strSearchPath.begin();
        bool looping = true;
        while (looping)
        {
            fullPath.assign(upPath);
            if (src != m_strSearchPath.end())
            {
                fullPath.append(*src);
                fullPath.append("/Asset/");
                src++;
            }
            else
            {
                fullPath.append("Asset/");
                looping = false;
            }
            fullPath.append(name);
#ifdef DEBUG
            fprintf(stderr, "Trying to open %s\n", fullPath.c_str());
#endif

            switch (mode)
            {
                case ProjectEngine_OPEN_TEXT:
                    fp = fopen(fullPath.c_str(), "r");
                    break;

                case ProjectEngine_OPEN_BINARY:
                    fp = fopen(fullPath.c_str(), "rb");
                    break;
            }

            if (fp)
                return (AssetFilePtr)fp;
        }
        upPath.append("../");
    }
    return nullptr;
}

ProjectEngine::Buffer ProjectEngine::AssetLoader::SyncOpenAndReadText(const char *filePath)
{
    AssetFilePtr fp = OpenFile(filePath, ProjectEngine_OPEN_TEXT);
    Buffer* pBuff = nullptr;

    if (fp)
    {
        size_t length = GetSize(fp);

        pBuff = new Buffer(length + 1);
        fread(pBuff->m_pData, length, 1, static_cast<FILE*>(fp));
        pBuff->m_pData[length] = '\0';

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return *pBuff;
}

void ProjectEngine::AssetLoader::CloseFile(AssetFilePtr& fp)
{
    fclose((FILE*)fp);
    fp = nullptr;
}

size_t ProjectEngine::AssetLoader::GetSize(const AssetFilePtr& fp)
{
    FILE* _fp = static_cast<FILE*>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, ProjectEngine_SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, ProjectEngine_SEEK_SET);

    return length;
}

size_t ProjectEngine::AssetLoader::SyncRead(const AssetFilePtr& fp, Buffer& buf)
{
    size_t sz;

    if (!fp) {
        fprintf(stderr, "null file discriptor\n");
        return 0;
    }

    sz = fread(buf.m_pData, buf.m_szSize, 1, static_cast<FILE*>(fp));


#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return sz;
}

int32_t ProjectEngine::AssetLoader::Seek(AssetFilePtr fp, long offset, AssetSeekBase where)
{
    return fseek(static_cast<FILE*>(fp), offset, static_cast<int>(where));
}