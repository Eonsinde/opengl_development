#ifndef __hAPPLICATION_H__
#define __hAPPLICATION_H__

#ifdef _WIN32
    #pragma once
    #define _CRT_SECURE_NO_WARNINGS 
    
    #define WIN32_LEAN_AND_MEAN
    #undef APIENTRY
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(t) sleep(t)
#endif


#include <glad/glad.h>
#include <KHR/khrplatform.h>
#include <GLFW/glfw3.h>

#include <iostream>

// ImGUI
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_glfw.h"
#include "../ImGUI/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


#include "../scene/Scene.h"


namespace Hound {
	class Application {
    public:
        struct APPINFO
        {
            char title[128];
            int windowWidth;
            int windowHeight;
            int majorVersion;
            int minorVersion;
            int samples;
            union
            {
                struct
                {
                    unsigned int    fullscreen : 1;
                    unsigned int    vsync : 1;
                    unsigned int    cursor : 1;
                    unsigned int    stereo : 1;
                    unsigned int    debug : 1;
                    unsigned int    robust : 1;
                };
                unsigned int        all;
            } flags;
        };

        Application() = default;
        virtual ~Application() = default;

        virtual void run(Hound::Application* the_app, Hound::Scene* the_scene) {
            bool running = true;
            mApp = the_app;
            mCurrentScene = the_scene;

            // init glfw and create gl context
            if (!glfwInit())
            {
                std::cerr << "ERR::Failed to initialize GLFW\n";
                return;
            }

#pragma region CreateGLContext
            // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
            // GL ES 2.0 + GLSL 100
            const char* glsl_version = "#version 100";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
            // GL 3.2 + GLSL 150
            const char* glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
            // GL 3.0 + GLSL 130
            const char* glsl_version = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
#pragma endregion

            // initialize App Info with scene data, create window, set context and init glad
            init(mCurrentScene->mSceneInfo.title, mCurrentScene->mSceneInfo.width, mCurrentScene->mSceneInfo.height);

            mWindow = glfwCreateWindow(800, 600, mInfo.title, NULL, NULL);
            if (mWindow == NULL)
            {
                std::cout << "ERR::Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(mWindow);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "ERR::Failed to initialize GLAD" << std::endl;
                return;
            }
            else {
                std::cout << "============================\n";
                std::cout << "Rendering API: OpenGL\n" << "Major Version: " << GLVersion.major << "\n" << "Minor Version: " << GLVersion.minor << "\n";
                std::cout << "============================\n";
            }

#pragma region SETUP_IMGUI
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
           
            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
            ImGui_ImplOpenGL3_Init(glsl_version);

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();
            io.Fonts->AddFontFromFileTTF("./assets/fonts/bitter_static/Bitter-Medium.ttf", 18.0f);
#pragma endregion

            // register event callbacks
            glfwSetWindowSizeCallback(mWindow, glfw_onResize);
            glfwSetKeyCallback(mWindow, glfw_onKey);
            glfwSetMouseButtonCallback(mWindow, glfw_onMouseButton);
            glfwSetCursorPosCallback(mWindow, glfw_onMouseMove);
            glfwSetScrollCallback(mWindow, glfw_onMouseWheel);

            if (!mInfo.flags.cursor)
            {
                glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            }

            if (mInfo.flags.vsync) {
                // enable v-sync
                std::cout << "V-sync enabled\n";
                setVsync(1);
            }

            // init and load scene's resources
            mCurrentScene->Init();
            mCurrentScene->LoadScene();

            float currentTime=0, prevTime=0;
            
            // game loop 
            do
            {
                glfwPollEvents();
#pragma region StartImGUI
                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
#pragma endregion
                mApp->renderUI();
                ImGui::Begin("ImGui Stats");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();

                // draw
                mCurrentScene->Draw();

                // calculate delta time
                currentTime = glfwGetTime();
                mDeltaTime = currentTime - prevTime;
                prevTime = currentTime;

                // update 
                mCurrentScene->Update(mDeltaTime);

#pragma region TriggerImGUIRenderer
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion

                glfwSwapBuffers(mWindow);

                running &= (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
                running &= (glfwWindowShouldClose(mWindow) != GL_TRUE);
            } while (running);
            
            shutdown();
        }

        virtual void init(const char* windowTitle, int width, int height)
        {
            strcpy_s(mInfo.title, strlen(windowTitle)+1, windowTitle); // use (no of chars * 1) to get size of windowTitle string
            mInfo.windowWidth = width;
            mInfo.windowHeight = height;
#ifdef __APPLE__
            mInfo.majorVersion = 3;
            mInfo.minorVersion = 2;
#else
            mInfo.majorVersion = 4;
            mInfo.minorVersion = 3;
#endif
            mInfo.samples = 0;
            //mInfo.flags.all = 0;
            //mInfo.flags.cursor = 0;
#ifdef _DEBUG
            mInfo.flags.debug = 1;
#endif
        }

        virtual void renderUI() {
            // this method is to support ImGUI UI rendering for a given application instance
        }

        virtual void shutdown()
        {
            if (mCurrentScene)
                mCurrentScene->UnloadScene();

#pragma region ImGUICleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
#pragma endregion
            
            glfwDestroyWindow(mWindow);
            glfwTerminate();
        }

        static GLFWwindow* & GetWindow() { // return a reference to the window ptr
            return mApp->mWindow;
        }

        static float GetDeltaTime() {
            return mApp->mDeltaTime;
        }

    protected:
        static      Application* mApp;
        static      Scene* mCurrentScene;

        GLFWwindow* mWindow;

        APPINFO     mInfo;

        float       mDeltaTime;


    public:
        void setWindowTitle(const char* title)
        {
            glfwSetWindowTitle(mWindow, title);
        }

        // this methods are called inside glfw_callback functions 
        virtual void onResize(int w, int h)
        {
            mInfo.windowWidth = w;
            mInfo.windowHeight = h;
        }

        virtual void onKey(int key, int action)
        {
        }

        virtual void onMouseButton(int button, int action)
        {
        }

        virtual void onMouseMove(int x, int y)
        {
        }

        virtual void onMouseWheel(int yOffset)
        {
            // usually +1 for zoom in and -1 for zoom out
        }

        // this are the glfw_callback functions that are registered with our mWindow instance calls the methods aboev
        static void glfw_onResize(GLFWwindow* window, int w, int h)
        {
            mApp->onResize(w, h);
            glViewport(0, 0, w, h);
            mApp->mCurrentScene->mSceneInfo.height = h;
            mApp->mCurrentScene->mSceneInfo.width = w;
        }

        static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            mApp->onKey(key, action);
        }

        static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
        {
            mApp->onMouseButton(button, action);
        }

        static void glfw_onMouseMove(GLFWwindow* window, double x, double y)
        {
            mApp->onMouseMove(static_cast<int>(x), static_cast<int>(y));
        }

        static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
        {
            mApp->onMouseWheel(static_cast<int>(yoffset));
        }

        void setVsync(bool enable)
        {
            mInfo.flags.vsync = enable ? 1 : 0;
            glfwSwapInterval((int)mInfo.flags.vsync);
        }
	}; // end of Application
} // end of Hound namespace



// the Tapp and Tscene stands for type of app/ type of scene
// defined App's static attributes                       
#if defined _WIN32
#define DECLARE_MAIN(Tapp, Tscene)                       \
                                                         \
Hound::Application* Hound::Application::mApp = 0;        \
Hound::Scene* Hound::Application::mCurrentScene = 0;     \
                                                         \
int WINAPI main(HINSTANCE hInstance,                     \
                     HINSTANCE hPrevInstance,            \
                     LPSTR lpCmdLine,                    \
                     int nCmdShow)                       \
{                                                        \
    Tapp* app = new Tapp;                                \
    Tscene* scene = new Tscene;                          \
    app->run(app, scene);                                \
    delete scene;                                        \
    delete app;                                          \
    return 0;                                            \
}                                                        
#elif defined _LINUX || defined __APPLE__
Hound::Application* Hound::Application::mApp = 0;        \
Hound::Scene* Hound::Application::mCurrentScene = 0;     \
                                                         \
int main(int argc, const char ** argv)                   \
{                                                        \
    Tapp* app = new Tapp;                                \
    Tscene* scene = new Tscene;                          \
    app->run(app, scene);                                \
    delete scene;                                        \
    delete app;                                          \
    return 0;                                            \
}
#else
#error Undefined platform!
#endif


#endif /* __hAPPLICATION_H__ */