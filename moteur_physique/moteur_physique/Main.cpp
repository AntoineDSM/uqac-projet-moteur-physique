//Date de crï¿½ation :
//Crï¿½er par :
//Date de derniï¿½re modification : 22/09/2022
//Modifiï¿½ par : Victor Guiraud

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

void GestionSouris(int button, int state, int x,int y)
{
    ball->MouseInput(button,state,x,y);
}

void GestionClavier(unsigned char key,int x, int y)
{
    ball->KeyboardInput(key);
}


//Fonction permettant la création d'un repere x,y,z orthonorme.
void DessineRepereOrthonorme()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //permet de regarder un point precis a partir d'un point de vue.
    gluLookAt(3, 2, 3, 0, 0, 0, 0, 1, 0);

    //Repere XYZ
    glBegin(GL_LINES);

    glColor3ub(0, 0, 255); //axe bleue
    glVertex3d(0, 0, 0);  glVertex3d(1, 0, 0); // X

    glColor3ub(0, 255, 0); //axe vert
    glVertex3d(0, 0, 0);  glVertex3d(0, 1, 0); // Y

    glColor3ub(255, 0, 0); //axe rouge
    glVertex3d(0, 0, 0);  glVertex3d(0, 0, 1); // Z

    glEnd();
}


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

    //Creation de l'objet correspondant a notre fenetre.
    GLFWwindow* window;

    glGetString(GL_VERSION);
    //Initialisation de la librairie de OpenGL.
    if (!glfwInit())
        return -1;

    //Creer une fenetre OpenGL.
    window = glfwCreateWindow(1280, 720, "Ballistic & particule", NULL, NULL);
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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    //Parametres d'affichages de notre monde.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)640 / 480, 1, 1000);
    glEnable(GL_DEPTH_TEST);

    //Liste des variables modifiables par IMGUI.
    bool drawTriangle = true;
    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

    //lancement du timer.
    TimingData::init();

    //Boucle while jusqu'a une fermeture de fenetre de la part de l'utilisateur.
    while (!glfwWindowShouldClose(window))
    {
        //On peut rendre des elements dans cette boucle.
        glClear(GL_COLOR_BUFFER_BIT);

        //Dire a OpenGL que une nouvelle image va devoir etre affichee.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Creation fenetre IMGUI.
        ImGui::Begin("Modify attributes here :");
        //Texte dans la fenetre.
        ImGui::Text("......");
        //Slider pour choisir la taille d'un element.
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        //Choix de la couleur de l'element.
        ImGui::ColorEdit4("Color", color);
        //La fenetre est complete.
        ImGui::End();

        //-----------------------------------------------Recuperer les interactions clavier/souris de l'utilisateur.----------------------------------------------
        glutKeyboardFunc(GestionClavier);
        glutMouseFunc(GestionSouris);
        //-----------------------------------------------------Actualisation des positions des projectiles.--------------------------------------------------------
        TimingData::update();
        ball->UpdateVariousFrameRate();
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        DessineRepereOrthonorme();
        //--------------------------------------------------------------Rendre nos projectiles.--------------------------------------------------------------------
        ball->DisplayOpenGL();
        //---------------------Boucle globale de tous les elements ajoutes en tant que callback, les fonctions ci-dessus de facon plus generale.-------------------
        glutMainLoop();

        //Affichage des elements de IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers //
        glfwSwapBuffers(window);
        // Poll for and process events //
        glfwPollEvents();
    }

    //arret du timer.
    TimingData::deinit();

    //Si nous quitter la boucle, on déinitialise les elements de OpenGL et de IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

