#include "Window.hpp"

#include <imgui.h>
#include <gut_opengl/GLTFLoader.hpp>


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

void render(gut::RenderContext& renderContext, Window::Context& windowContext)
{
    static int64_t t = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double tt = (t*0.04538651 + cos(t*0.0234237))*0.003;
    double y = 0.5-0.5*cos(M_PI*tt*3.0);
    renderContext.camera.lookAt(
        Vec3f(7.0f*sin(M_PI*tt*7.0f), 1.0f+y*8.0f, 2.4f*cos(M_PI*tt*13.0f)),
        Vec3f(-5.0f*cos(M_PI*tt*5.0f), 1.5f+y*7.0f+1.5f*sin(t*0.004276539), 5.0f*sin(M_PI*tt*5.0f)),
        Vec3f(0.0f, 1.0f, 0.0f)
    );

    renderContext.render();

    ++t;
}

int main() {
    gut::RenderContext renderContext;

    Window::Settings settings;
    settings.handleEvents = handleEvents;
    settings.render = render;

    Window window(settings, &renderContext);

    // Load Sponza
    gut::GLTFLoader gltfLoader;
    gltfLoader.loadFromFile(std::string(RES_DIR) + "sponza/main_sponza/Main.1_Sponza/NewSponza_Main_glTF_002.gltf");

    gltfLoader.constructObjects(renderContext.root, renderContext.meshes);
    renderContext.shader.load(
        std::string(RES_DIR) + "shaders/VS_Simple.glsl",
        std::string(RES_DIR) + "shaders/FS_Simple.glsl"
    );

    renderContext.camera.projection(M_PI*0.5f, 16.0f/9.0f, 0.1f, 100.0f);

    window.loop();

    return 0;
}
