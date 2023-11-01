#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "core/definitions.h"
#include "modules/module.h"
#include "utilities/timer.h"
#include <string>
#include <vector>

// Modules
class MWindow;

class Application {
public:
    Application();
    virtual ~Application();

    bool Init();
    update_status Update();
    bool CleanUp();

    void Log(const char* entry);
    void ClearLogs();

private:
    void PrepareUpdate();
    void FinishUpdate();

public:
    // TODO: Add modules
    MWindow* window = nullptr;

    std::string name_;
    std::string version_;
    std::string author_;

private:
    std::vector<Module*> modules_;
    std::vector<std::string> logs_;

    Timer delta_timer_;
    Timer engine_timer_;
    uint frame_count_ = 0;
    float deltatime_ = 0.f;
    float averagefps_ = 0.f;

    const uint kmax_logs_ = 1000;

};

extern Application* app;


#endif
