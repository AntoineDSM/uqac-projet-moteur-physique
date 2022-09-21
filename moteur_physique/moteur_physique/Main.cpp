//Date de création :
//Créer par :
//Date de dernière modification :
//Modifié par : 

#pragma once //optimisation de compilation

#include <GLFW/glfw3.h>
#include <Windows.h>
#include <dos.h>
#include <string.h>

#include "Timing.h"
#include "Ballistic.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Vector3D.h"

using namespace moteurJeux;

Ballistic* ball;

int main(int argc, char** argv)
{

    //------------------------------------------------------------TEST PARTIE 1, TEST DES VECTEURS3D-------------------------------------------------------------------
    
    //-----------------------TEST DES FONCTIONS IMPLEMENTEES SUR CONSOLE--------------

    /*
    //compteur d'actualisation
    int cpt = 0;
    
    //mes vecteurs
    Vector3D myVec = Vector3D(1,1,1);
    Vector3D mySecondVec = Vector3D(2, 2, 3);
    Vector3D vitesse = Vector3D(0.1, 0.1, 0.1);
    Vector3D acceleration = Vector3D(0.1,0.1,0.1);
    
    //scalaire
    double myScalarValue = 5;

    //addition of  2 vectors
    Vector3D result = Vector3D();
    result = (myVec + mySecondVec);
    result.display("addition : ");
    //soustraction of 2 vectors
    result = (myVec - mySecondVec);
    result.display("soustraction : ");
    //multiplication  by scalar value
    result = myVec * myScalarValue;
    result.display("multiplication by scalar :");
    //normalisation of vector
    result = moteurJeux::Vector3D::get_normalization(mySecondVec);
    result.display("normalization : ");
    //produit scalaire et vectoriel
    double scalarResult = myVec.scalarProduct(mySecondVec);
    std::cout << "scalar product :  " <<scalarResult << "\n";

    result = myVec.vectorialProduct(mySecondVec);
    result.display("vectorial product : ");
    
    while (cpt < 100)
    {
        myVec += vitesse;
        myVec.display("nouvelle position : ");

        vitesse += acceleration;
        vitesse.display("evolution vitesse : ");

        cpt++;
    }
    return 0;
    */

    //-----------------------------------------------------------TEST PARTIE 2, PARTICULES et CONSOLE----------------------------------------------------------------------

    //-----------------------------DUREE DE RAFRAICHISSEMENT VARIABLE-----------------

    /*
    TimingData::init();

    ball = new Ballistic();

    bool shotOne = true;

    while (1)
    {
        //test pour ne lancer qu'une balle a la fois tant que l'interaction clavier/souris n'est pas mise en place.
        if (shotOne)
        {
            ball->setCurrentType(Ballistic::ShotType::FIREBALL);//changer le type ici pour voir les comportements des differents projectiles.
            ball->Shoot();
            shotOne = false;
        }
        TimingData::update();
        ball->UpdateVariousFrameRate();
        ball->Display();
    }

    TimingData::deinit();
    
    return 0;
    */

    //------------------------------DUREE DE RAFRAICHISSEMENT FIXE--------------------

    /*
    TimingData::init();

    //nous fixons un rafraichissement de 30 fois par seconde.
    int frameRATE = 30;
    double framesMs = 1000 / frameRATE;

    ball = new Ballistic();

    bool shotOne = true;

    while (1)
    {
        int tempsLancement = TimingData::getTime();//prise du temps au lancement de la boucle

        //test pour ne lancer qu'une balle a la fois tant que l'interaction clavier/souris n'est pas mise en place.
        if (shotOne)
        {
            ball->setCurrentType(Ballistic::ShotType::PISTOL);//changer le type ici pour voir les comportements des differents projectiles.
            ball->Shoot();
            shotOne = false;
        }
        TimingData::update();
        ball->UpdateFixedFrameRate(framesMs);
        ball->Display();

        int tempsFin = TimingData::getTime();//prise du temps a la fin, necessaire au traitement des calculs et de l'affichage
        int delaieNecessaire = framesMs - (tempsFin - tempsLancement);//determination du temps d'attente necessaire pour avoir 30 fps.
        //Ici nous voulons sortir de la boucle si nos operations sur le projectile sont finies.
        if (delaieNecessaire == 33)
        {
            break;
        }

        std::cout << "Nous avons attendu : " + std::to_string(delaieNecessaire) + " ms pour ce tour de boucle\n" ;
        Sleep(delaieNecessaire);
    }

    TimingData::deinit();

    return 0;

    */

    //-------------------------------------------------------------TEST PARTIE 3, PARTICULES et OPENGL--------------------------------------------------------------

    /*
    GLFWwindow* window;

    glGetString(GL_VERSION);
    //Initialize the library //
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    //Make the window's context current //
    glfwMakeContextCurrent(window);
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    // Variables to be changed in the ImGUI window
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };



    // Loop until the user closes the window //
    while (!glfwWindowShouldClose(window))
    {
        // Render here //
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // ImGUI window creation
        ImGui::Begin("Window to modify parameters :");
        // Text that appears in the window
        ImGui::Text("Triangle modification");
        // Checkbox that appears in the window
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        // Slider that appears in the window
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        // Fancy color editor that appears in the window
        ImGui::ColorEdit4("Color", color);
        // Ends the window
        ImGui::End();

        // Renders the ImGUI elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glBegin(GL_TRIANGLES);
        glColor3f(color[0], color[1], color[2]);
        glVertex3f(0, 0, size);
        glVertex3f(size, 0, 0);
        glVertex3f(0, size, 0);
        glEnd();

        // Swap front and back buffers //
        glfwSwapBuffers(window);

        // Poll for and process events //
        glfwPollEvents();
    }

    // Deletes all ImGUI instances
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    */
}


