
#pragma once


#include "DemoCube.h"
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
DemoCube* demoCube;
SkyBox skyBox;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool buttonPressedRecently = false;
std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

//Variable pour inpits
float lastX = 1600 / 2.0f;
float lastY = 1000 / 2.0f;
bool firstMousePress = true;
bool firstMouseRelease = true;

//Liste des variables modifiables par IMGUI.

//parametre de position de la camera dans notre repère
int posCamX = 50;
int posCamY = 20;
int posCamZ = 50;
//Mettre en pause l'evolution des elements
bool pause = true;


void IMGUI_Utils()
{
    //Creation fenetre IMGUI.
    ImGui::Begin("Vous pouvez modifier des attributs de fonctionnement ici :");
    //Slider pour choisir la taille d'un element.
    ImGui::Text("Changer la position de la caméra sur X :");
    ImGui::SliderInt("Pos X 0-300", &posCamX, 0, 300);
    //Slider pour choisir la taille d'un element.
    ImGui::Text("Changer la position de la caméra sur Y :");
    ImGui::SliderInt("Pos Y 0-100", &posCamY, 0, 100);
    //Slider pour choisir la taille d'un element.
    ImGui::Text("Changer la position de la caméra sur Z :");
    ImGui::SliderInt("Pos Z 0-300", &posCamZ, 0, 300);
    //Mettre en pause l'evolution des elements
    ImGui::Checkbox("Pause : ", &pause);
    //La fenetre est complete.
    ImGui::End();
}

//-------------------------------------------------------------------------METHODES ADDITIONNELLES------------------------------------------------------------------------------------------------------------------------

//Permet d'attendre avant de detecter un appui car ça peut etre le meme.
void StartTimer()
{
    Sleep(100);
    buttonPressedRecently = false;
}

//Fonction permettant la création d'un repere x,y,z orthonorme.
void DessineRepereOrthonorme(int posCamX = 100, int posCamY = 50, int posCamZ = 100)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //permet de regarder un point precis a partir d'un point de vue.
    gluLookAt(posCamX, posCamY, posCamZ, 0, 0, 0, 0, 1, 0);

    //Repere XYZ
    glBegin(GL_LINES);

    glColor3ub(255, 166, 0); //axe orange
    glVertex3d(0, 0, 0);  glVertex3d(20, 0, 0); // X

    glColor3ub(0, 255, 0); //axe vert
    glVertex3d(0, 0, 0);  glVertex3d(0, 20, 0); // Y

    glColor3ub(255, 0, 0); //axe rouge
    glVertex3d(0, 0, 0);  glVertex3d(0, 0, 20); // Z

    glEnd();
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

//---------------------------------------------------------------------MAIN TEST RENDU 2, FORCES ET CONTACTS--------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{

    GLFWwindow* window;

    //GLFW initialization
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1600, 1000, "Rendu 3, Quaternion, rigidbody et rotation", NULL, NULL);
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
    demoCube = new DemoCube(window, camera);

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
    // This might help with seams on some systems
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);


    // Cycles through all the textures and attaches them to the cubemap object
  /*  for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D
            (
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
            stbi_image_free(data);
        }
    }*/

    while (!glfwWindowShouldClose(window))
    {
        startTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> work_time = startTime - endTime;

        //Setup View
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        int frameRATE = 30;
        double framesMs = 1000 / frameRATE;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //----------------------------Actualisation des positions des particules + gestion des contacts entre nos particules, et ceux des murs--------------------------------------------------------
        demoCube->UpdateVariousFrameRate(pause, framesMs);// getLastFrameDuration(startTime, endTime));


        //---------------------------------------------------------Affichage-------------------------------------------------------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //--------------------------------------------------------------Rendre nos particules et nos murs.--------------------------------------------------------------------
        demoCube->DisplayOpenGL();
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        //DessineRepereOrthonorme(posCamX, posCamY, posCamZ);
        
        //Swap buffer and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();

        endTime = std::chrono::system_clock::now();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate;


}

/*
int main(int argc, char** argv)
{
    //Creation de l'objet correspondant a notre fenetre.
    GLFWwindow* window;

    glGetString(GL_VERSION);

    //Initialisation de la librairie de OpenGL.
    if (!glfwInit())
        return -1;

    //Creer une fenetre OpenGL.
    window = glfwCreateWindow(1600, 1000, "Rendu 3, Quaternion, rigidbody et rotation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Donner le contexte a la fenetre actuelle.
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << GLEW_VERSION << "\n";
        exit(1); // or handle the error in a nicer way
    }
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    {
        std::cout << GLEW_VERSION << "\n";
        exit(1); // or handle the error in a nicer way
    }

    //Initialiser IMGUI.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    //Parametres d'affichages de notre monde.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)640 / 480, 1, 1000);
    glEnable(GL_DEPTH_TEST);

    //creation de notre objet.
    demoCube = new DemoCube();
    demoCube->window = window;

    //Boucle while jusqu'a une fermeture de fenetre de la part de l'utilisateur.
    while (!glfwWindowShouldClose(window))
    {

        startTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> work_time = startTime - endTime;

        //Dire a OpenGL que une nouvelle image va devoir etre affichee.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        IMGUI_Utils();

        glClearColor(0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //----------------------------Actualisation des positions des particules + gestion des contacts entre nos particules, et ceux des murs--------------------------------------------------------
        demoCube->UpdateVariousFrameRate(pause, getLastFrameDuration(startTime, endTime));
        //--------------------------------------------------------------Rendre nos particules et nos murs.--------------------------------------------------------------------
        demoCube->DisplayOpenGL();
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        DessineRepereOrthonorme(posCamX, posCamY, posCamZ);

        //Affichage des elements de IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Forcer l'actualisation
        glFlush();
        // Swap front and back buffers //
        glfwSwapBuffers(window);
        // Poll for and process events //
        glfwPollEvents();

        endTime = std::chrono::system_clock::now();
    }

    //Si nous quitter la boucle, on déinitialise les elements de OpenGL et de IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
*/