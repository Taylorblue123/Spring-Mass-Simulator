#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/gtc/type_ptr.hpp>
#include "SpringSystem.h"

// Global variables
SpringSystem* springSystem = nullptr;
float startX = -0.05f;
float totalLength = 0.5f;
int numNodes = 5;
float springMass = 2.0f;
float objectMass = 0.1f;
float k = 250.0f;
float damping = 0.0f;
int method = 2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void renderSpringSystem() {
    // Draw springs (blue lines)
    glColor3f(0.2f, 0.5f, 1.0f);
    glBegin(GL_LINES);
    for (const auto& spring : springSystem->GetSprings()) {
        const auto& p1 = spring.getMass1()->currentState.position;
        const auto& p2 = spring.getMass2()->currentState.position;
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    }
    glEnd();

    // Draw masses (red points)
    glPointSize(8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (const auto& mass : springSystem->GetMasses()) {
        if (mass.isFixed) glColor3f(0.0f, 1.0f, 0.0f); // �̶�����ɫ
        glVertex2f(mass.currentState.position.x, mass.currentState.position.y);
        if (mass.isFixed) glColor3f(1.0f, 0.0f, 0.0f);
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Spring System", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

     // Initialize GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

     // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Initialize Spring System
    springSystem = new SpringSystem(startX, totalLength, numNodes, springMass, objectMass, k, damping);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // ImGui֡
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui Setup
        ImGui::Begin("Control Panel");
        ImGui::SliderFloat("Start X", &startX, -1.0f, 1.0f);
        ImGui::SliderFloat("Total Length", &totalLength, 0.1f, 3.0f);
        ImGui::SliderInt("Nodes", &numNodes, 2, 20);
        ImGui::SliderFloat("Spring Mass", &springMass, 0.1f, 5.0f);
        ImGui::SliderFloat("Object Mass", &objectMass, 0.1f, 10.0f);
        ImGui::SliderFloat("Stiffness (k)", &k, 10.0f, 500.0f);
        ImGui::SliderFloat("Damping", &damping, 0.0f, 20.0f);
        ImGui::Combo("Method", &method, "Euler\0Midpoint\0RK4\0");

        if (ImGui::Button("Reset System")) {
            delete springSystem;
            springSystem = new SpringSystem(startX, totalLength, numNodes,
                springMass, objectMass, k, damping);
        }
        ImGui::End();

        // Step the simulation
        springSystem->StepSimulation(0.0016f, method);

        // renderSpringSystem
        renderSpringSystem();

        // ImGui Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up
    delete springSystem;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}