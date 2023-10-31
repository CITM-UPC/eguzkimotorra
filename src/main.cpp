#include "core/application.h"
#include "core/definitions.h"
#include "core/logger.h"

enum main_states {
    MAIN_CREATION,
    MAIN_START,
    MAIN_UPDATE,
    MAIN_FINISH,
    MAIN_EXIT
};

Application* app = nullptr;

int main(int argc, char* argv[]) {
    LOG("Starting the engine");

    int main_return = 1;
    main_states state = MAIN_CREATION;

    while (state != MAIN_EXIT) {
        switch (state) {
        case MAIN_CREATION:
            LOG("Creating the application");
            app = new Application();
            state = MAIN_START;
            break;

        case MAIN_START:
            LOG("Engine initialization")
            if (app->Init()) {
                LOG("Engine initialized succesfully");
                state = MAIN_UPDATE;
            }
            else {
                LOG("Engine init failed");
                state = MAIN_EXIT;
            }
            break;

        case MAIN_UPDATE:
            {
            update_status ret = app->Update();
            if (ret == UPDATE_ERROR) {
                LOG("Engine failed to update");
                state = MAIN_EXIT;
            }
            else if (ret == UPDATE_STOP) {
                state = MAIN_FINISH;
            }
            break;
            }

        case MAIN_FINISH:
            LOG("Cleaning up application");
            if (app->CleanUp()) {
                main_return = 0;
            }
            else {
                LOG("Engine cleanup error");
            }
            state = MAIN_EXIT;
            break;
        }
    }

    delete app;
    app = nullptr;
    LOG("Exiting the engine");
    return main_return;
}
