#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "module.h"
#include "core/definitions.h"
#include <queue>

enum KEY_STATE {
    KEY_IDLE = 0,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP,
    KEY_INVALID
};

class MInput : public Module {
public:
    MInput(bool start_enabled = true);
    ~MInput();

    bool Init();
    bool Start();
    update_status PreUpdate(float dt);
    bool CleanUp();

    // Getters
    KEY_STATE GetKey(uint id) const;
    KEY_STATE GetMouseButton(uint id) const;
    bool is_mouse_scrolling() const;
    int mouse_x() const;
    int mouse_y() const;
    int mouse_wheel() const;
    int mouse_x_motion() const;
    int mouse_y_motion() const;

    static const uint kmax_keys = 300;
    static const uint kmax_buttons = 5;

private:
    KEY_STATE keyboard_[kmax_keys];
    KEY_STATE mouse_[kmax_buttons];
    int mouse_x_, mouse_y_, mouse_wheel_;
    int mouse_x_motion_, mouse_y_motion_;
    bool is_mouse_focused_;
    bool is_mouse_scrolling_;

    uint flags_;
};

#endif
