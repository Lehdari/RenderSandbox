//
// Project: render_sandbox
// File: Window.hpp
//
// Copyright (c) 2022 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef RENDER_SANDBOX_WINDOW_HPP
#define RENDER_SANDBOX_WINDOW_HPP


#include <string>

#include <SDL.h>

#include "RenderContext.hpp"


class Window {
public:
    // Settings for the application
    struct WindowSettings {
        std::string name;
        int64_t width;
        int64_t height;
        int64_t framerateLimit;

        explicit WindowSettings(
            const std::string& name = "",
            int64_t width = 1280,
            int64_t height = 720,
            int64_t framerateLimit = 60) :
            name(name),
            width(width),
            height(height),
            framerateLimit(framerateLimit)
        {}
    };

    struct GLSettings {
        int32_t contextMajor;
        int32_t contextMinor;
        SDL_GLcontextFlag contextFlags;
        SDL_GLprofile profileMask;
        bool doubleBuffer;

        explicit GLSettings(
            int32_t contextMajor = 4,
            int32_t contextMinor = 5,
            SDL_GLcontextFlag contextFlags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
            SDL_GLprofile profileMask = SDL_GL_CONTEXT_PROFILE_CORE,
            bool doubleBuffer = true) :
            contextMajor(contextMajor),
            contextMinor(contextMinor),
            contextFlags(contextFlags),
            profileMask(profileMask),
            doubleBuffer(doubleBuffer)
        {}
    };

    // Struct for Window context to be passed to pipeline functions
    struct Context {
        WindowSettings* windowSettings;
        GLSettings*     glSettings;
        SDL_Window*     window;
        SDL_GLContext*  glContext;
        bool*           quit;

        Context(Window& app) :
            windowSettings  (&app._settings.window),
            glSettings      (&app._settings.gl),
            window          (app._window),
            glContext       (&app._glCtx),
            quit            (&app._quit)
        {}
    };

    struct Settings {
        WindowSettings window;
        GLSettings gl;

        // Pipeline function pointers for event handling and rendering
        void (*handleEvents)(SDL_Event& event, Context& windowContext);
        void (*render)(RenderContext& context, Context& windowContext);

        explicit Settings(
            const WindowSettings& window                                = WindowSettings(),
            const GLSettings& gl                                        = GLSettings(),
            void (*handleEvents)(SDL_Event&, Context& windowContext)    = nullptr,
            void (*render)(RenderContext&, Context& windowContext)      = nullptr
        ) :
            window          (window),
            gl              (gl),
            handleEvents    (handleEvents),
            render          (render)
        {}
    };

    explicit Window(
        const Settings& settings = Settings(),
        RenderContext* renderContext = nullptr);

    ~Window();

    void loop(void);

    void setRenderContext(RenderContext* renderContext);

private:
    Settings            _settings;
    SDL_Window*         _window;
    SDL_GLContext       _glCtx;
    bool                _quit; // flag for quitting the application
    uint32_t            _lastTicks;
    uint32_t            _frameTicks;

    Window::Context     _windowContext;
    RenderContext*      _renderContext;
};


#endif //RENDER_SANDBOX_WINDOW_HPP
