

#pragma once

#include <Windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <dos.h>
#include <string.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


#include "Utils/Timing.h"
#include "PhysicWorld.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include "Vector3D/Vector3D.h"
#include "TimingData.h"

using namespace TimingOldMethod;
using namespace moteurJeux;
using namespace Timing;

//----division d'une particule puis reassembler : au clic de souris sur une particule (ou avec IMGUI un booléen pour une particule), on supp la particule et on en créer deux a la place, ces deux sont ajoutées a la liste
//		des particules et un lien (contact link) leur est directement attribué, elles etre rassembler si la distance les separants depasse une limite, on les rapproches, les supprime et on remet celle d'origine. OU au changement
//		du meme booléen dans IMGUI

//--PERMETTRE LA MISE EN PAUSE DU PROGRAMME AVEC UN BOOLEEN SUR IMGUI, LAISSER LE TEMPS A L'UTILISATEUR DE CREER SES ELEMENTS


//-------------------------------------------------------------------------METHODES ADDITIONNELLES------------------------------------------------------------------------------------------------------------------------

PhysicWorld* physicWorld;
bool buttonPressedRecently = false;
//std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
//std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

//Liste des variables modifiables par IMGUI.
//parametre de position de la camera dans notre repère
int posCamX = 70;
int posCamY = 5;
int posCamZ = 0;
//attribut d'une particule
int posXObj = 0, posYObj = 0, posZObj = 0;
int vitXObj = 0, vitYObj = 0, vitZObj = 0;
int accXObj = 0, accYObj = 0, accZObj = 0;
float dampingObj = 0.9;
float masseObj = 1;
double radius = 2;
//attribut de restitution d'un mur
float restitution = 0;
int posXMurA = 0, posYMurA = 0, posZMurA = 0;
int posXMurB = 0, posYMurB = 0, posZMurB = 0;
int planXMur = 0, planYMur = 0, planZMur = 0;
//Choisir entre instancier mur ou particule, un contact ou un generateur
bool instancierMur = false;
bool instancierParticule = false;
bool InstancierGenerateurForce = false;
bool InstancierContact = false;

//Mettre en pause l'evolution des elements
bool pause = false;

//Ajout des parametres pour les generateurs de force à appliquer sur les particules
int typeGenerateurForce=0;
//buoancy
float m_maxDepth = 0, m_volume = 0, m_waterHeight = 0, m_liquidDensity = 0;
//drag
double m_k1Drag = 0, m_k2Drag = 0;
//gravity
int posXGravity = 0, posYGravity = 0, posZGravity = 0;
//spring
float m_k = 0;
float m_restLength = 0;

//Ajout des parametres pour les types de contacts entre particules
int typeContact=0;
//cable
float maxLength = 0;
float restitutionContacts = 0;
//rod
float length = 0;

//la premiere particule sera toujours celle affecte par un generateur de force, le binome sera utilisé pour l'ajout de contact
int first_currentParticuleSelected = 0;
int second_currentParticuleSelected = 0;


//Permet d'attendre avant de detecter un appui car ça peut etre le meme.
void StartTimer()
{
    Sleep(100);
    buttonPressedRecently = false;
}

void GestionSouris(float listParamsParticule[], float listParamsMur[], float listeParamsGenerateurForce[], float listeParamsContacts[], int typeGenerateurForce, int typeContact, Particle* particule1, Particle* particule2, Vector3D plan,bool InstancierParticule = false, bool InstancierMur = false)
{
    buttonPressedRecently = true;
    //Eviter de prendre plusieurs entrees en une.
    StartTimer();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonPressedRecently && InstancierParticule)
    {
        physicWorld->InstancierParticule(listParamsParticule);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonPressedRecently && InstancierMur)
    {
        physicWorld->InstancierMur(plan, listParamsMur);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonPressedRecently && InstancierGenerateurForce)
    {
        physicWorld->CreerGenerateurForce(typeGenerateurForce, particule1, listeParamsGenerateurForce, particule2);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !buttonPressedRecently && InstancierContact)
    {
        physicWorld->CreerTypeContactParticules(typeContact ,particule1, particule2, listeParamsContacts);
    }
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

void IMGUI_ParticulesMursParameters()
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
    //Changer la masse de l'objet
    ImGui::Text("Changer la masse de l'objet :");
    ImGui::InputFloat("Masse 0-20", &masseObj, 0, 20);
    // Position Obj
    ImGui::Text("Changer la position initiale de l'objet :");
    ImGui::InputInt("Pos X 0-150", &posXObj, 0, 150);
    ImGui::InputInt("Pos Y 0-150", &posYObj, 0, 150);
    ImGui::InputInt("Pos Z 0-150", &posZObj, 0, 150);
    // Vitesse Obj
    ImGui::Text("Changer la vitesse initiale de l'objet :");
    ImGui::InputInt("Vit X -50-50", &vitXObj, -50, 50);
    ImGui::InputInt("Vit Y -50-50", &vitYObj, -50, 50);
    ImGui::InputInt("Vit Z -50-50", &vitZObj, -50, 50);
    // Acceleration Obj
    ImGui::Text("Changer l'acceleration de l'objet :");
    ImGui::InputInt("Acc X -50-50", &accXObj, -50, 50);
    ImGui::InputInt("Acc Y -50-50", &accYObj, -50, 50);
    ImGui::InputInt("Acc Z -50-50", &accZObj, -50, 50);
    //Changer l'ammortissement
    ImGui::Text("Changer le facteur d'ammortissement de l'objet :");
    ImGui::InputFloat("Damp 0-1", &dampingObj, 0, 1);
    //Changer le rayon
    ImGui::Text("Changer le rayon de l'objet :");
    ImGui::InputDouble("Radius 1-10", &radius, 2, 10);
    //Insertion pour instanciation nouveau mur
    ImGui::Text("Changer la position initiale de l'extremite A du mur :");
    ImGui::InputInt("Pos Ax 0-150", &posXMurA, 0, 150);
    ImGui::InputInt("Pos Ay 0-150", &posYMurA, 0, 150);
    ImGui::InputInt("Pos Az 0-150", &posZMurA, 0, 150);
    ImGui::Text("Changer la position initiale de l'extremite B du mur :");
    ImGui::InputInt("Pos Bx 0-150", &posXMurB, 0, 150);
    ImGui::InputInt("Pos By 0-150", &posYMurB, 0, 150);
    ImGui::InputInt("Pos Bz 0-150", &posZMurB, 0, 150);
    ImGui::Text("Changer l'orientation du plan de notre mur :");
    ImGui::InputInt("Plan X mur 0-1", &planXMur, 0, 1);
    ImGui::InputInt("Plan Y mur 0-1", &planYMur, 0, 1);
    ImGui::InputInt("Plan Z mur 0-1", &planZMur, 0, 1);
    ImGui::Text("Changer la valeur de restitution du mur en cas de contact :");
    ImGui::InputFloat("0-1", &restitution, 0, 1);
    //La fenetre est complete.
    ImGui::End();
}

void IMGUI_AjoutForceGenerator()
{
    //Creation fenetre IMGUI.
    ImGui::Begin("Vous pouvez modifier des attributs de force generateur ici :");

    ImGui::Text("Changer le type de force generator a instancier, 0>Buoancy, 1>Drag, 2>Gravity, 3>Spring :");
    ImGui::SliderInt("Type : ", &typeGenerateurForce,0, 3);

    ImGui::Text("Changer les attributs du generateur buoancy :");
    ImGui::InputFloat("Max depth : ", &m_maxDepth, 0, 50);
    ImGui::InputFloat("Volume : ", &m_volume, 0, 50);
    ImGui::InputFloat("Water height :", &m_waterHeight, 0, 50);
    ImGui::InputFloat("Liquid density : ", &m_liquidDensity, 0, 50);

    ImGui::Text("Changer les attributs pour le generateur Drag :");
    ImGui::InputDouble("K1 drag : ", &m_k1Drag, 0, 10);
    ImGui::InputDouble("K2 drag : ", &m_k2Drag, 0, 10);

    ImGui::Text("Changer le vecteur du generateur de gravite :");
    ImGui::InputInt("Y : ", &posYGravity, -50, 50);

    ImGui::Text("Changer les attributs du generateur Spring :");
    ImGui::InputFloat("K : ", &m_k, 0, 10);
    ImGui::InputFloat("Rest length : ", &m_restLength, 0, 10);

    ImGui::End();
}

void IMGUI_AjoutTypeContacts()
{
    //Creation fenetre IMGUI.
    ImGui::Begin("Vous pouvez modifier des attributs de type de contact ici :");

    ImGui::Text("Changer le type de contact a appliquer sur deux particules, 0>Cable, 1>Rod :");
    ImGui::SliderInt("Type : ", &typeContact, 0, 1);

    ImGui::Text("Changer les attributs du contact cable :");
    ImGui::InputFloat("Max length : ", &maxLength, 0, 50);
    ImGui::InputFloat("Restitution : ", &restitutionContacts, 0, 50);

    ImGui::Text("Changer les attributs du contact rod :");
    ImGui::InputFloat("Length :", &length, 0, 50);

    ImGui::End();
}

void IMGUI_ChoixParticleUnique_Binome()
{
    //Creation fenetre IMGUI.
    ImGui::Begin("Vous choisir la particule/ le binome de particule qui seront affectes :");

    ImGui::InputInt("Particule 1 : ", &first_currentParticuleSelected, 0, physicWorld->listeParticules.size());
    ImGui::InputInt("Particule 2 :", &second_currentParticuleSelected, 0, physicWorld->listeParticules.size());

    ImGui::End();
}

void IMGUI_ChoixInstanciation()
{
    //Creation fenetre IMGUI.
    ImGui::Begin("Vous choisir la particule/ le binome de particule qui seront affectes :");

    //Mettre en pause l'evolution des elements
    ImGui::Checkbox("Pause : ", &pause);

    //instancier l'un ou l'autre
    ImGui::Text("Si vous voulez autoriser l'instanciation d'un mur et d'une particule :");
    ImGui::Checkbox("Instancier particule : ", &instancierParticule);
    ImGui::Checkbox("Instancier Mur : ", &instancierMur);
    ImGui::Checkbox("Instancier Generateur Force : ", &InstancierGenerateurForce);
    ImGui::Checkbox("Instancier Contact : ", &InstancierContact);


    ImGui::End();
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
    window = glfwCreateWindow(1600, 1000, "PhysicWorld, ammat de particules, forces et contacts", NULL, NULL);
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

    //lancement du timer.
    TimingData::init();

    //creation de notre objet.
    physicWorld = new PhysicWorld();

    //--------------------------------------------------------------------------------------------------------------------------TEST FORCES OK
    // masseObj, posXObj,posYObj,posZObj,vitXObj,vitYObj,vitZObj,accXObj,accYObj,accZObj,dampingObj, radius
    // m_maxDepth, m_volume, m_waterHeight, m_liquidDensity, m_k1Drag, m_k2Drag, posYGravity, m_k, m_restLength
    //GRAVITY OK, DRAG OK, SPRING OK, BUOANCY OK
    float listP1[12] = { 1,0,10,5,0,-2,5,0,0,0,0.9,2 };
    float listP2[12] = { 1,0,15,-5,0,0,-5,0,0,0,0.9,2 };
    //BUOANCY
    float list2[9] = { 1,100,10,0.1,0,0,0,0,0 };
    //GRAVITE
    float list3[9] = { 0,0,0,0,0,0,-5,0,0 };
    //DRAG
    float list4[9] = { 0,0,0,0,5,5,0,0,0 };
    //SPRING
    float list5[9] = { 0,0,0,0,0,0,0,0.1,10 };
    physicWorld->InstancierParticule(listP1);
    //physicWorld->InstancierParticule(listP2);
    //physicWorld->CreerGenerateurForce(2, physicWorld->listeParticules[0], list3);
    //physicWorld->CreerGenerateurForce(0, physicWorld->listeParticules[0], list2);
    //physicWorld->CreerGenerateurForce(1, physicWorld->listeParticules[0], list4);
    //physicWorld->CreerGenerateurForce(3, physicWorld->listeParticules[0], list5, physicWorld->listeParticules[1]);
    
    //--------------------------------------------------------------------------------------------------------------------------TEST MURS CONTACT OK
    //posXMurA,posYMurA,posZMurA,posXMurB,posYMurB,posZMurB, restitution
    float listM1[7] = { 0,0,15,0,10,15,0.8};
    Vector3D normalPlan = Vector3D(0, 0, 1);
    physicWorld->InstancierMur(normalPlan, listM1);

    //--------------------------------------------------------------------------------------------------------------------------TEST CONTACT
    //physicWorld->CreerTypeContactParticules(typeContact, particule1, particule2, listeParamsContacts);


    //Boucle while jusqu'a une fermeture de fenetre de la part de l'utilisateur.
    while (!glfwWindowShouldClose(window))
    {

        //startTime = std::chrono::system_clock::now();
        //std::chrono::duration<double, std::milli> work_time = startTime - endTime;

        //On peut rendre des elements dans cette boucle.
        glClear(GL_COLOR_BUFFER_BIT);

        //Dire a OpenGL que une nouvelle image va devoir etre affichee.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Création menu IMGUI pour particules et murs.
        IMGUI_ParticulesMursParameters();

        //Création menu IMGUI pour ajouter des générateurs de forces aux particules.
        IMGUI_AjoutForceGenerator();

        //Création menu IMGUI pour ajouter des types de contacts entre nos particules.
        IMGUI_AjoutTypeContacts();

        //Liste des particules instanciées afin de pouvoir leur appliquer generateur et force
        IMGUI_ChoixParticleUnique_Binome();

        //Permet de choisir si nous instantion une particule, un mur, un contact, un generateur de force
        IMGUI_ChoixInstanciation();

        //-----------------------------------------------Recuperer les interactions clavier/souris de l'utilisateur.----------------------------------------------
        Particle* particule1 = new Particle();
        Particle* particule2 = new Particle();
        if (physicWorld->listeParticules.size() > 0)
        {
            particule1 = physicWorld->listeParticules[first_currentParticuleSelected];
            particule2 = physicWorld->listeParticules[second_currentParticuleSelected];
        }
        float listParamsParticule[12] = { masseObj, posXObj,posYObj,posZObj,vitXObj,vitYObj,vitZObj,accXObj,accYObj,accZObj,dampingObj, radius};
        float listeParamsMur[7] = { posXMurA,posYMurA,posZMurA,posXMurB,posYMurB,posZMurB, restitution };
        float listeParamsGenerator[9] = {m_maxDepth, m_volume, m_waterHeight, m_liquidDensity, m_k1Drag, m_k2Drag, posYGravity, m_k, m_restLength };
        float listeParamsContacts[3] = {maxLength,restitutionContacts,length };
        Vector3D plan = Vector3D(planXMur, planYMur, planZMur);
        GestionSouris(listParamsParticule, listeParamsMur, listeParamsGenerator, listeParamsContacts, typeGenerateurForce, typeContact , particule1, particule2, plan,instancierParticule, instancierMur);
        //----------------------------Actualisation des positions des particules + gestion des contacts entre nos particules, et ceux des murs--------------------------------------------------------
        TimingData::update();
        physicWorld->UpdateVariousFrameRate(pause);//getLastFrameDuration(startTime, endTime));
        //------------------------------------------------------------Dessin de notre repere XYZ.------------------------------------------------------------------
        DessineRepereOrthonorme(posCamX, posCamY, posCamZ);
        //--------------------------------------------------------------Rendre nos particules et nos murs.--------------------------------------------------------------------
        physicWorld->DisplayOpenGL();



        //Affichage des elements de IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Forcer l'actualisation
        glFlush();
        // Swap front and back buffers //
        glfwSwapBuffers(window);
        // Poll for and process events //
        glfwPollEvents();

        //endTime = std::chrono::system_clock::now();
    }

    //arret du timer.
    TimingData::deinit();

    //Si nous quitter la boucle, on déinitialise les elements de OpenGL et de IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}
