#include "importer.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "core/application.h"
#include "core/logger.h"


void AssimpStreamCallback(const char* msg, char* userData) {
    app->Log(msg);
}

MImporter::MImporter(bool start_enabled) : Module(start_enabled) {}

MImporter::~MImporter() {}

bool MImporter::Init() {
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    stream.callback = AssimpStreamCallback;
    aiAttachLogStream(&stream);
}

bool MImporter::CleanUp() {
    aiDetachAllLogStreams();
}

void LoadMesh(const char* file_path) {
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes()) {
        // TODO: Create entities and their meshes
        aiReleaseImport(scene);
    }
    else
        LOG("Error loading the file %s", file_path);
}
