#include "application.h"
#include "core/logger.h"
#include "modules/window.h"

Application::Application() {
    //TODO: Create modules
    window = new MWindow();
    modules_.push_back(window);

}

Application::~Application() {
    for (auto& element : modules_) {
        delete element;
    }

    modules_.clear();
}

bool Application::Init() {
    bool ret = true;

    // Call init in all modules
    auto item = modules_.begin();
    while (item != modules_.end() && ret == true) {
        ret = (*item)->Init();
        item++;
    }

    LOG("Starting engine modules");
    // Call start in all modules
    item = modules_.begin();
    while(item != modules_.end() && ret == true) {
        ret = (*item)->Start();
        item++;
    }

    engine_timer_.Start();

    return ret;
}

void Application::PrepareUpdate() {
    frame_count_++;

    deltatime_ = delta_timer_.ReadSeconds();
    delta_timer_.Start();
}

void Application::FinishUpdate() {
    averagefps_ = frame_count_ / engine_timer_.ReadSeconds();
}

update_status Application::Update() {
    update_status ret = UPDATE_CONTINUE;
    PrepareUpdate();

    // Pre-Update Modules
    auto item = modules_.begin();
    while (item != modules_.end() && ret == UPDATE_CONTINUE) {
        ret = (*item)->PreUpdate(deltatime_);
        item++;
    }

    // Update Modules
    item = modules_.begin();
    while (item != modules_.end() && ret == UPDATE_CONTINUE) {
        ret = (*item)->Update(deltatime_);
        item++;
    }

    // Post-Update Modules
    item = modules_.begin();
    while (item != modules_.end() && ret == UPDATE_CONTINUE) {
        ret = (*item)->PostUpdate(deltatime_);
        item++;
    }

    FinishUpdate();
    return ret;
}

bool Application::CleanUp() {
    bool ret = true;

    for (auto item : modules_) {
        ret = item->CleanUp() && ret;
    }

    return ret;
}

void Application::Log(const char* entry) {
    // Make space for a new log if we're at max
    if (logs_.size() > kmax_logs_)
        logs_.erase(logs_.begin());

    logs_.push_back(entry);
}

void Application::ClearLogs() {
    logs_.clear();
}
