#pragma once

#include <stdio.h>
#include <string>
#include <windows.h>
#include <gl/GL.h>
#include "GL/glut.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "Particle.h"
#include "Timing.h"
#include "Vector3D.h"
#include <vector>

using namespace moteurJeux;

class Ballistic {

public:

	//----------------------------------------------------------------ATTRIBUTES-----------------------------------------------------------------------------------

	//pour differencier chacun de nos projectiles, pour leur assigner des comportements differents.
	enum class ShotType
	{
		UNUSED = 0,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER,
		ARROW
	};

	//la structure de l'objet que nous tirerons.
	struct AmmoRound {

		//Un type de projectile associe a la structure et ses attributs
		ShotType type = ShotType::UNUSED;

		//Correspond au moment auquel nous le lancons
		double startTime = 0;

		//Cet objet reste une particule avec position, vitesse, acceleration...
		Particle particle;

		//Savoir si notre vecteur vient de depasser les limites de simulation et afficher un retour utilisateur en consequence. (affichage console)
		bool alreadyPrinted = false;

		std::string getType()
		{
			switch (type) {
				case ShotType::UNUSED :
					return "UNUSED ";
				case ShotType::ARTILLERY :
					return "ARTILLERY ";
				case ShotType::FIREBALL :
					return "FIREBALL ";
				case ShotType::LASER :
					return "LASER ";
				case ShotType::PISTOL :
					return "PISTOL ";
				case ShotType::ARROW :
						return "ARROW";
			}
		}

		std::vector<int> getDisplayedColor()
		{
			switch (type) {
			case ShotType::UNUSED:
				return {255,87,51};//rouge
			case ShotType::ARTILLERY:
				return { 51,191,255 };//bleu
			case ShotType::FIREBALL:
				return { 238,51,255 };//rose
			case ShotType::LASER:
				return { 79,255,51 };//vert
			case ShotType::PISTOL:
				return { 255,169,47 };//orange
			case ShotType::ARROW:
				return { 255,246,51 };//jaune
			}
		}

	};

	//le maximum de munition/d'object que nous pouvons avoir en meme temps dans l'espace virtuel
	const static unsigned ammoRounds = 10;

	//la liste des munitions/des objets instancies en ce moment dans l'espace, pour les garder accessible et les faire evoluer.
	AmmoRound ammo[ammoRounds];

	//le type de munition que nous voulons lancer ? l'instant t.
	ShotType currentType;

	//-----------------------------------------------------------------------------CONSTRUCTOR----------------------------------------------------------------------

	//Constructeur par defaut.
	Ballistic() : currentType(ShotType::PISTOL)
	{
		for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
		{
			shot->type = ShotType::UNUSED;
		}
	}

	//---------------------------------------------------------------------------VARIOUS METHODS--------------------------------------------------------------------

	void Shoot(float listParamsObj[], bool initialValues);
	
	void UpdateVariousFrameRate();

	void UpdateFixedFrameRate(double frameRate);

	void DisplayConsole();

	void DisplayOpenGL();

	void MouseInput(int button, int state, int x, int y);

	//void KeyboardInput(unsigned char key);
	void KeyboardInput();


	void AfficherProjectile(AmmoRound* amo);

	//tant que le clavier ne fonctionne pas
	void setCurrentType(ShotType myType);

	const char* getCurrentType();

};
		