#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

#include "module.h";
#include "core/definitions.h"

struct SDL_Window;
struct SDL_Surface;

class MWindow : public Module {
public:
    MWindow(bool start_enabled = true);
    ~MWindow();

    bool Init();
    bool CleanUp();

    void OnResize(uint width, uint height);
    void ChangeTitle(const char* title) const;

    // Getters
    const uint width() const { return width_; }
    const uint height() const { return height_; }
    const uint screen_size() const { return screen_size_; }

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;

    private:
    uint width_, height_, screen_size_;
    float aspect_ratio_;
};

#endif
