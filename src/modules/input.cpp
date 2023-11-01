#include "input.h"
#include "SDL2/SDL.h"
#include <cctype>
#include <cstring>
#include "core/application.h"
#include "core/logger.h"
#include "modules/window.h"
#include "modules/importer.h"

MInput::MInput(bool start_enabled) : Module(start_enabled) {};
MInput::~MInput() {};

bool MInput::Init() {
    bool ret = true;
    LOG("Initializing the input event system as well as the timer");

    flags_ = SDL_INIT_EVENTS;
    if (SDL_InitSubSystem(flags_) != 0) {
        LOG("SDL Could not initialize events subsystem, error: %s", SDL_GetError());
        ret = false;
    }

    return ret;
}

bool MInput::Start()
{
    memset(keyboard_, KEY_IDLE, sizeof(KEY_STATE) *  kmax_keys);
    memset(mouse_, KEY_IDLE, sizeof(KEY_STATE) * kmax_buttons);

    return true;
}

update_status MInput::PreUpdate(float dt)
{
    update_status ret = UPDATE_CONTINUE;

    for (int i = 0; i < kmax_keys; ++i) {
        if (i < kmax_buttons && mouse_[i] == KEY_UP) {
            mouse_[i] = KEY_IDLE;
        }

        if (keyboard_[i] == KEY_UP) {
            keyboard_[i] == KEY_IDLE;
        }
    }


    mouse_wheel_ = 0;
    mouse_x_motion_ = mouse_y_motion_ = 0;
    is_mouse_scrolling_ = false;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_MOUSEWHEEL:
            mouse_wheel_ = e.wheel.y;
            is_mouse_scrolling_ = true;
            break;

        case SDL_MOUSEMOTION:
            mouse_x_ = e.motion.x / app->window->screen_size();
            mouse_y_ = e.motion.y / app->window->screen_size();

            mouse_x_motion_ = e.motion.xrel / app->window->screen_size();
            mouse_y_motion_ = e.motion.yrel / app->window->screen_size();
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (mouse_[e.button.button] == KEY_IDLE) {
                mouse_[e.button.button] = KEY_DOWN;
            }
            else {
                mouse_[e.button.button] = KEY_REPEAT;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            mouse_[e.button.button] = KEY_UP;
            break;

        case SDL_KEYDOWN:
            if (e.key.repeat) {
                keyboard_[e.key.keysym.scancode] = KEY_REPEAT;
            }
            else {
                keyboard_[e.key.keysym.scancode] = KEY_DOWN;
            }
            break;

        case SDL_KEYUP:
            keyboard_[e.key.keysym.scancode] = KEY_UP;
            break;

        case SDL_QUIT:
            return UPDATE_STOP;
            break;

        case SDL_WINDOWEVENT:
            switch (e.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                app->window->OnResize(e.window.data1, e.window.data2);
                break;
            case SDL_WINDOWEVENT_ENTER:
                is_mouse_focused_ = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                is_mouse_focused_ = false;
                break;
            }
            break;

        case SDL_DROPFILE:
            std::string file_path = e.drop.file;
            std::string extension = file_path.substr(file_path.find_last_of('.') + 1, file_path.size());
            for (char& character : extension) {
                character = std::tolower(character);
            }

            if (extension == "fbx") {
                app->importer->LoadMesh(file_path.c_str());
            }
            break;
        }
    }

    return ret;
}

bool MInput::CleanUp() {
    LOG("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(flags_);

    return true;
}

KEY_STATE MInput::GetKey(uint id) const {
    if (id > kmax_keys)
        return KEY_INVALID;
    return keyboard_[id];
}

KEY_STATE MInput::GetMouseButton(uint id) const {
        if (id > kmax_buttons)
        return KEY_INVALID;
    return mouse_[id];
}

bool MInput::is_mouse_scrolling() const     { return is_mouse_scrolling_; }
int MInput::mouse_x() const                 { return mouse_x_; }
int MInput::mouse_y() const                 { return mouse_y_; }
int MInput::mouse_wheel() const             { return mouse_wheel_; }
int MInput::mouse_x_motion() const          { return mouse_x_motion_; }
int MInput::mouse_y_motion() const          { return mouse_y_motion_; }
