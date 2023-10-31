#ifndef __MODULE_H__
#define __MODULE_H__

#include "core/definitions.h"

class Module {
private:
    bool enabled_;

public:
    Module(bool start_enabled = true) : enabled_(start_enabled) {}
    virtual ~Module() {}

    virtual bool Init() {
        return true;
    }

    virtual bool Start() {
        return true;
    }

    virtual bool Stop() {
        return true;
    }

    virtual update_status PreUpdate(float dt) {
        return UPDATE_CONTINUE;
    }

    virtual update_status Update(float dt) {
        return UPDATE_CONTINUE;
    }

    virtual update_status PostUpdate(float dt) {
        return UPDATE_CONTINUE;
    }

    virtual bool CleanUp() {
        return true;
    }

    bool is_enabled() const {
        return enabled_;
    }
};

#endif
