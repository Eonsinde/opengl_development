#ifndef __hAPPLICATION_H__
#define __hAPPLICATION_H__

#include <iostream>
#include <GLFW/glfw3.h>


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

        virtual void run(Hound::Application* the_app) {
            bool running = true;
            mApp = the_app;
        }

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

    protected:
        APPINFO     mInfo;
        static      Application* mApp;
        GLFWwindow* mWindow;

        static void glfw_onResize(GLFWwindow* window, int w, int h)
        {
            mApp->onResize(w, h);
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

#endif