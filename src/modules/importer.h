#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "module.h"
#include "core/definitions.h"

class MImporter : public Module {
public:
    MImporter(bool start_enabled = true);
    ~MImporter();

    bool Init();
    bool CleanUp();

    void LoadMesh(const char* file_path);


};

#endif
