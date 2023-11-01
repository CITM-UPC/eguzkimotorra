#include "window.h"
#include "core/logger.h"
#include "SDL2/SDL.h"

MWindow::MWindow(bool start_enabled) : Module (start_enabled) {
    window = nullptr;
    surface = nullptr;

    // TODO: Maybe consider not hardcoding these
    width_ = 1024;
    height_ = 720;
    screen_size_ = 1;
    aspect_ratio_ = width_ / float(height_);
}

MWindow::~MWindow() {}

bool MWindow::Init() {
    bool ret = true;

    // TODO: Will have to move this out of here eventually
    const uint flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    LOG("Initializing SDL Window");
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        LOG("SDL_VIDEO was not initialized, the error is: %s", SDL_GetError());
        ret = false;
    }
    else {
        window = SDL_CreateWindow("Eguzki Motorra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, flags);

        if (window) {
            surface = SDL_GetWindowSurface(window);
        }
        else {
            LOG("Window was not created, the error is: %s", SDL_GetError());
            ret = false;
        }
    }

    return ret;
}

bool MWindow::CleanUp() {
    LOG("Cleaning up SDL window and quitting SDL systems");
    if (window) {
        SDL_DestroyWindow(window); // This frees both window and its surface
        window = nullptr;
        surface = nullptr;
    }

    SDL_Quit();
    return true;
}

void MWindow::OnResize(uint width, uint height) {

    width_ = width;
    height_ = height;
    aspect_ratio_ = width_ / float(height_);
}

void MWindow::ChangeTitle(const char* title) const {
    if (window)
        SDL_SetWindowTitle(window, title);
}
