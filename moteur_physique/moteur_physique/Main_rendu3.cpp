
#pragma once


#include "DemoCube.h"
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

using namespace moteurJeux;
using namespace Timing;


//-------------------------------------------------------------------------PARAMETRE POUR IMGUI------------------------------------------------------------------------------------------------------------------------
DemoCube* demoCube;
bool buttonPressedRecently = false;
std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

//Liste des variables modifiables par IMGUI.

//parametre de position de la camera dans notre repère
int posCamX = 50;
int posCamY = 20;
int posCamZ = 50;
//Mettre en pause l'evolution des elements
bool pause = false;


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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //permet de regarder un point precis a partir d'un point de vue.
    gluLookAt(posCamX, posCamY, posCamZ, 0, 0, 0, 0, 1, 0);

    //Repere XYZ
    glBegin(GL_LINES);

    glColor3ub(0, 0, 255); //axe bleue
    glVertex3d(0, 0, 0);  glVertex3d(20, 0, 0); // X

    glColor3ub(0, 255, 0); //axe vert
    glVertex3d(0, 0, 0);  glVertex3d(0, 20, 0); // Y

    glColor3ub(255, 0, 0); //axe rouge
    glVertex3d(0, 0, 0);  glVertex3d(0, 0, 20); // Z

    glEnd();
}

//---------------------------------------------------------------------MAIN TEST RENDU 2, FORCES ET CONTACTS--------------------------------------------------------------------------------------------------------------

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

        //On peut rendre des elements dans cette boucle.
        glClear(GL_COLOR_BUFFER_BIT);

        //Dire a OpenGL que une nouvelle image va devoir etre affichee.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        IMGUI_Utils();

        //----------------------------Actualisation des positions des particules + gestion des contacts entre nos particules, et ceux des murs--------------------------------------------------------
        demoCube->UpdateVariousFrameRate(pause, getLastFrameDuration(startTime, endTime));
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        DessineRepereOrthonorme(posCamX, posCamY, posCamZ);
        //--------------------------------------------------------------Rendre nos particules et nos murs.--------------------------------------------------------------------
        demoCube->DisplayOpenGL();

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