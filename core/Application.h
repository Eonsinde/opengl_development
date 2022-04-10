#ifndef __hAPPLICATION_H__
#define __hAPPLICATION_H__

#ifdef _WIN32
    #pragma once
    #define _CRT_SECURE_NO_WARNINGS 1

    #define WIN32_LEAN_AND_MEAN 1
    #include <Windows.h>
#else
    #include <unistd.h>
    #define Sleep(t) sleep(t)
#endif


#include <glad/glad.h>
#include <KHR/khrplatform.h>

#include <GLFW/glfw3.h>


#include <iostream>

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
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            // initialize App Info, create window, set context and init glad
            init(mCurrentScene->mSceneInfo.title, mCurrentScene->mSceneInfo.width, mCurrentScene->mSceneInfo.height);

            mWindow = glfwCreateWindow(800, 600, "Testing", NULL, NULL);
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

            // init and load scene's resources
            mCurrentScene->Init();
            mCurrentScene->LoadScene();

            float currentTime=0, prevTime=0;
            
            // game loop 
            do
            {
                glfwPollEvents();
                
                // draw
                mCurrentScene->Draw();

                // calculate delta time
                currentTime = glfwGetTime();
                mDeltaTime = currentTime - prevTime;
                prevTime = currentTime;
                // update 
                mCurrentScene->Update(mDeltaTime);

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
            mInfo.flags.all = 0;
            mInfo.flags.cursor = 0;
#ifdef _DEBUG
            mInfo.flags.debug = 1;
#endif
        }

        virtual void shutdown()
        {
            if (mCurrentScene)
                mCurrentScene->UnloadScene();
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
        APPINFO     mInfo;
        static      Application* mApp;
        static      Scene* mCurrentScene;
        GLFWwindow* mWindow;

        float mDeltaTime;


    public:
        void setWindowTitle(const char* title)
        {
            glfwSetWindowTitle(mWindow, title);
        }

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

        virtual void onMouseWheel(int pos)
        {
        }

    

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
	};
}



// the Tapp and Tscene stands for type of app/ type of scene
// defined App's static attributes                       
#if defined _WIN32
#define DECLARE_MAIN(Tapp, Tscene)                       \
                                                         \
Hound::Application* Hound::Application::mApp = 0;        \
Hound::Scene* Hound::Application::mCurrentScene = 0;     \
                                                         \
int CALLBACK main(HINSTANCE hInstance,                   \
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
#define DECLARE_MAIN(Tapp, Tscene)                       \
Hound::Application* Hound::Application::mApp = 0;        \
Hound::Scene* Hound::Application::mCurrentScene = 0;     \
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