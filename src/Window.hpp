#pragma once

#include "string_view"
#include "user_input/Mouse.hpp"
#include "user_input/Keys.hpp"
#include "Camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
   public:
    static constexpr std::string_view kGameName = "FooBar";

    Window() : window_(glfwCreateWindow(width_, height_, "Boomerang Blitz", nullptr, nullptr)) {
        if (window_ == nullptr) {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow() failed");
        }

        glfwSetWindowUserPointer(window_, this);

        // Teclas
        glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mode) {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->KeyCallback(key, scancode, action, mode);
        });
        // Botões do mouse
        glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int mods) {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->MouseButtonCallback(button, action, mods);
        });
        // Cursor do mouse
        glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double xpos, double ypos) {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->CursorPosCallback(xpos, ypos);
        });
        // Scroll do mouse
        glfwSetScrollCallback(window_, [](GLFWwindow *window, double xoffset, double yoffset) {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->ScrollCallback(xoffset, yoffset);
        });
        // Tamanho da janela
        glfwSetFramebufferSizeCallback(window_, [](GLFWwindow *window, int width, int height) {
            Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
            self->FramebufferSizeCallback(width, height);
        });
    }

    void Start();

    void KeyCallback(int key, int  /*scancode*/, int action, int  /*mode*/) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
        }

        keys_.TakeAction(key, static_cast<Key::Action>(action));
    }

    void MouseButtonCallback(int button, int action, int mods) {
        // Caso o jogo esteja pausado
        if (this->isPaused_) {
            return;
        }

        // Caso o usuário pressione os botões do mouse
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            this->camera_.keys.M1 = true;
        }
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            this->camera_.keys.M1 = false;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            this->camera_.keys.M2 = true;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        {
            this->camera_.keys.M2 = false;
        }
    }
    void CursorPosCallback(double xpos, double ypos) {
        // Deslocamento do cursor do mouse em x e y de coordenadas de tela!
        float dx = xpos - this->lastCursorPosX;
        float dy = ypos - this->lastCursorPosY;

        // Caso esteja pausado, não atualiza a posição do cursor
        if (this->isPaused_) {
            this->lastCursorPosX = xpos;
            this->lastCursorPosY = ypos;
            return;
        }

        // Atualizamos parâmetros da câmera com os deslocamentos
        if (this->camera_.isUseFreeCamera()) {

            // Em câmera livre, calcula o ângulo rotação horizontal conforme a porcentagem da tela movida
            float angleX = dx/((float) this->screenWidth/2)  * 2 * M_PI;
            float angleY = dy/((float) this->screenHeight/2) * 2 * M_PI;
            this->camera_.updateViewVector(angleX, angleY);
            this->camera_.updateSphericAngles(angleX);
        }
        else {
            // Em câmera look-at, atualiza os angulos esféricos para os do cursor
            this->camera_.updateSphericAngles(dx, dy);
        }

        // Atualizamos as variáveis globais para armazenar a posição atual do cursor como sendo a última posição conhecida do cursor.
        this->lastCursorPosX = xpos;
        this->lastCursorPosY = ypos;
    }

   private:
    int height_ = 800;
    int width_  = 600;

    GLFWwindow* window_ = nullptr;
    Camera      camera_;
    Keys keys_;
    Mouse       mouse_{static_cast<double>(width_) / 2, static_cast<double>(height_) / 2};
};
