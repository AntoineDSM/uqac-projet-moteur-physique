//Date de cr�ation :
//Cr�er par :
//Date de derni�re modification :
//Modifi� par : 

#pragma once //optimisation de compilation

#include <Windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <dos.h>
#include <string.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>



#include "Timing.h"
#include "Ballistic.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Vector3D.h"
#include "ParticleForceGenerator.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleDrag.h"
#include "ParticleBuoyancy.h"
#include "ParticleForceRegistry.h"

using namespace moteurJeux;

Ballistic* ball;
bool buttonPressedRecently = false;

//Permet d'attendre avant de detecter un appui car �a peut etre le meme.
void StartTimer()
{
    Sleep(100);
    buttonPressedRecently = false;
}

void GestionSouris(float listParams[], bool initialValues)//(int button, int state, int x,int y)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonPressedRecently)
    {
        buttonPressedRecently = true;
        //Eviter de prendre plusieurs entrees en une.
        StartTimer();
        ball->Shoot(listParams, initialValues);
    }
    //ball->MouseInput(button,state,x,y);
}

void GestionClavier()//(unsigned char key,int x, int y)
{
    ball->KeyboardInput();
    //ball->KeyboardInput(key);
}


//Fonction permettant la cr�ation d'un repere x,y,z orthonorme.
void DessineRepereOrthonorme(int posCamX = 90, int posCamY = 70, int posCamZ = 100)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //permet de regarder un point precis a partir d'un point de vue.
    gluLookAt(posCamX, posCamY, posCamZ, 0, 0, 0, 0, 1, 0); // original :  gluLookAt(posCamX, posCamY, posCamZ, 0, 0, 0, 0, 1, 0);

    //Repere XYZ
    glBegin(GL_LINES);

    glColor3ub(0, 0, 255); //axe bleue
    glVertex3d(0, 0, 0);  glVertex3d(70, 0, 0); // X

    glColor3ub(0, 255, 0); //axe vert
    glVertex3d(0, 0, 0);  glVertex3d(0, 70, 0); // Y

    glColor3ub(255, 0, 0); //axe rouge
    glVertex3d(0, 0, 0);  glVertex3d(0, 0, 70); // Z

    //Dessine flipper
     glColor3ub(252, 252, 252); //blanc
   
    glVertex3d(70, 70, 70);  glVertex3d(30, 0, 45); 
    
    glColor3ub(0, 0, 252); //vert
    glVertex3d(35, 70, 70);  glVertex3d(30, 0, 45); 

    glColor3ub(0, 252, 0); //bleu
    glVertex3d(50, 70, 30);  glVertex3d(30, 0, 45);

    glColor3ub(252, 0, 0); //rouge

    glVertex3d(20, 70, 50);  glVertex3d(30, 0, 45);
    glEnd();
}


int main(int argc, char** argv)
{

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
    //particule
    int posCamX = 100;
    int posCamY = 50;
    int posCamZ = 100;
    float posXObj, posYObj, posZObj = 0;
    float vitXObj, vitYObj, vitZObj = 0;
    float accXObj, accYObj, accZObj = 0;
    float dampingObj = 0;
    float masseObj = 0;
    float radiusObj = 20;
    float forceAccumObj = 0;
    float gravXObj, gravYObj, gravZObj = 0;
    float m_k1Obj, float m_k2Obj, float m_kObj, float m_restLength= 0;
    float m_maxDepthObj,float m_volumeObj, float m_waterHeightObj, float m_LiquiDensityObj = 0;
    //autre particule (test)
    float posXOther, posYOther, posZOther = 0;
    float vitXOther, vitYOther, vitZOther = 0;
    float accXOther, accYOther, accZOther = 0;
    float dampingOther = 0;
    float masseOther = 0;
    float radiusOther = 20;
    float forceAccumOther = 0;
    float gravXOther, gravYOther, gravZOther = 0;
    float m_k1Other, float m_k2Other, float m_kOther, float m_restLength = 0;
    float m_maxDepthOther, float m_volumeOther, float m_waterHeightOther, float m_LiquiDensityObj = 0;
         
    //Pour choisir si l'objet selectionne sera lance avec les valeurs initiales du code en dur ou avec les parametres modifiables ci dessus.
    bool initialValues = true;

    //lancement du timer.
    TimingData::init();

    //creation de notre objet.
    ball = new Ballistic();

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
        //Slider pour choisir la taille d'un element.
        ImGui::Text("Changer la position de la cam�ra sur X :");
        ImGui::SliderInt("Pos X 0-300", &posCamX, 0, 300);
        //Slider pour choisir la taille d'un element.
        ImGui::Text("Changer la position de la cam�ra sur Y :");
        ImGui::SliderInt("Pos Y 0-100", &posCamY, 0, 100);
        //Slider pour choisir la taille d'un element.
        ImGui::Text("Changer la position de la cam�ra sur Z :");
        ImGui::SliderInt("Pos Z 0-300", &posCamZ, 0, 300);
        //Fonctionnement
        ImGui::Text("Appuyez sur click droit de la souris pour tirer.");
        ImGui::Text("A : PISTOL, Z : ARTILLERY, E : FIREBALL, R : LASER,T : ARROW.");
        //Projectile selectionne 
        //FAIRE LA FONCTION ADAPTE
        //Changer la masse de l'objet
        ImGui::Text("Changer la masse de l'objet :");
        ImGui::SliderFloat("Masse 0-20", &masseObj, 0, 20);
        // Position Obj
        ImGui::Text("Changer la position initiale de l'objet :");
        ImGui::SliderFloat("Pos X 0-150", &posXObj, 0, 150);
        ImGui::SliderFloat("Pos Y 0-150", &posYObj, 0, 150);
        ImGui::SliderFloat("Pos Z 0-150", &posZObj, 0, 150);
        // Vitesse Obj
        ImGui::Text("Changer la vitesse initiale de l'objet :");
        ImGui::SliderFloat("Vit X 0-50", &vitXObj, 0, 50);
        ImGui::SliderFloat("Vit Y 0-50", &vitYObj, 0, 50);
        ImGui::SliderFloat("Vit Z 0-50", &vitZObj, 0, 50);
        // Acceleration Obj
        ImGui::Text("Changer l'acceleration de l'objet :");
        ImGui::SliderFloat("Acc X -50-50", &accXObj, -50, 50);
        ImGui::SliderFloat("Acc Y -50-50", &accYObj, -50, 50);
        ImGui::SliderFloat("Acc Z -50-50", &accZObj, -50, 50);
        //Changer l'ammortissement
        ImGui::Text("Changer le facteur d'ammortissement de l'objet :");
        ImGui::SliderFloat("Damp 0-1", &dampingObj, 0, 1);
        //Changer le type d'initialisation du projectile
        ImGui::Text("Changer le type d'initialisation de la particule, TRUE > valeurs par defaut, FALSE > valeurs inserees ici :");
        ImGui::Checkbox("Valeurs par defaut", &initialValues);
        //La fenetre est complete.
        ImGui::End();

        //-----------------------------------------------Recuperer les interactions clavier/souris de l'utilisateur.----------------------------------------------
        float listParams[11] = { masseObj, posXObj,posYObj,posZObj,vitXObj,vitYObj,vitZObj,accXObj,accYObj,accZObj,dampingObj };
        GestionClavier();
        GestionSouris(listParams, initialValues);
        //-----------------------------------------------------Actualisation des positions des projectiles.--------------------------------------------------------
        TimingData::update();
        ball->UpdateVariousFrameRate();
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        DessineRepereOrthonorme(posCamX, posCamY, posCamZ);
        //--------------------------------------------------------------Rendre nos projectiles.--------------------------------------------------------------------
        ball->DisplayOpenGL();
        //---------------------Boucle globale de tous les elements ajoutes en tant que callback, les fonctions ci-dessus de facon plus generale.-------------------

        //Affichage des elements de IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Forcer l'actualisation
        glFlush();
        // Swap front and back buffers //
        glfwSwapBuffers(window);
        // Poll for and process events //
        glfwPollEvents();
    }

    //arret du timer.
    TimingData::deinit();

    //Si nous quitter la boucle, on d�initialise les elements de OpenGL et de IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}