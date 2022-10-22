#include "Window.hpp"

#include <imgui.h>


void handleEvents(SDL_Event& event, Window::Context& windowContext)
{
    // Handle SDL events
    switch (event.type) {
        case SDL_QUIT:
            *windowContext.quit = true;
            break;

        case SDL_KEYDOWN:
            // Skip events if imgui widgets are being modified
            if (ImGui::IsAnyItemActive())
                return;
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    *windowContext.quit = true;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void render(RenderContext& renderContext, Window::Context& windowContext)
{

}

int main() {
    Window::Settings settings;
    settings.handleEvents = handleEvents;
    settings.render = render;

    Window window(settings);
    window.loop();

    return 0;
}
