
#pragma once


#include "DemoRigidBodiesCollision.h"
#include "SkyBox.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Windows.h>

#include <dos.h>
#include <string.h>
#include "Utils/Timing.h"
#include "Vector3D/Vector3D.h"
#include "Camera.h"
#include<filesystem>

using namespace moteurJeux;
using namespace Timing;
using namespace std;

//-------------------------------------------------------------------------PARAMETRE POUR IMGUI------------------------------------------------------------------------------------------------------------------------

//quel comportement voulez vous observer
int APPLICATION_WANTED = 0;

//variables utiles initialisation
DemoRigidBodiesCollision* demoRigidbodiesCollision;
SkyBox skyBox;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLFWwindow* window;
std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

//Variable pour inpits
float lastX = 1600 / 2.0f;
float lastY = 1000 / 2.0f;
bool firstMousePress = true;
bool firstMouseRelease = true;

//variables pour frame rate fixe
int frameRATE = 30;

//-------------------------------------------------------------------------METHODES ADDITIONNELLES------------------------------------------------------------------------------------------------------------------------

void StartTimer();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ChooseWitchApplicationIsWanted(GLFWwindow* window);
void InitOpenGL();
void TerminateOpenGL(GLFWwindow* window);
void SetupOpeGLView(GLFWwindow* window);
void SwapOpenGLBuffers(GLFWwindow* window);

//---------------------------------------------------------------------MAIN TEST RENDU 3, QUATERNION & RIGIDBODY--------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{

    InitOpenGL();

    while (!glfwWindowShouldClose(window))
    {
        startTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> work_time = startTime - endTime;

        SetupOpeGLView(window);
        double framesMs = 1000 / frameRATE;

        //----------------------------Actualisation des positions des particules + gestion des contacts entre nos particules, et ceux des murs--------------------------------------------------------
        demoRigidbodiesCollision->UpdateFixedFrameRate(true, framesMs);
        //---------------------------------------------------------Affichage-------------------------------------------------------------------------
        glClearColor(1, 1, 1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //--------------------------------------------------------------Rendre nos particules et nos murs.--------------------------------------------------------------------
        demoRigidbodiesCollision->DisplayOpenGL();

        SwapOpenGLBuffers(window);

        endTime = std::chrono::system_clock::now();
    }

    TerminateOpenGL(window);

}

//Permet d'attendre avant de detecter un appui car ça peut etre le meme.
void StartTimer()
{
    Sleep(100);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (firstMousePress)
        {
            lastX = xpos;
            lastY = ypos;
            firstMousePress = false;
            firstMouseRelease = true;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        if (firstMouseRelease)
        {
            firstMouseRelease = false;
            firstMousePress = true;
        }
    }
}

void ChooseWitchApplicationIsWanted(GLFWwindow* window)
{
    //Initialiser et creer demoRigidbodiesCollision;
}

void InitOpenGL()
{
    //GLFW initialization
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1600, 1000, "Rendu 4, RigidBodies collision", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    //Initialiser IMGUI.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    glEnable(GL_DEPTH_TEST);

    // inputs
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    //creation de notre objet.
    ChooseWitchApplicationIsWanted(window);

    // Create VAO, VBO, and EBO for the skybox
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyBox.skyboxVertices), &skyBox.skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyBox.skyboxIndices), &skyBox.skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    string facesCubemap[6] =
    {
        "/Sources/ImgSkyBox/droite.jpg", // droite
        "/Sources/ImgSkyBox/gauche.png", // gauche
        "/Sources/ImgSkyBox/haut.png", // haut
        "/Sources/ImgSkyBox/bas.png", // bas
        "/Sources/ImgSkyBox/face.png", // face
        "/Sources/ImgSkyBox/fond.png"  // fond
    };

    // Creates the cubemap texture object
    unsigned int cubemapTexture;
    glGenTextures(1, &cubemapTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // These are very important to prevent seams
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TerminateOpenGL(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate;
}

void SetupOpeGLView(GLFWwindow* window)
{
    //Setup View
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SwapOpenGLBuffers(GLFWwindow* window)
{
    //Swap buffer and check for events
    glfwSwapBuffers(window);
    glfwPollEvents();
}