//Date de création : 16/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 18/09/22
//Modifié par : Victor GUIRAUD

#include "Ballistic.h"
#include <SFML/Window/Keyboard.hpp>

void Ballistic::Shoot(float listParamsObj[] = {}, bool initialValues = true) {

	//Le projectile que nous allons lancer, avoir acces a son initialisation en fonction de son type
	AmmoRound* shot;

	//Nous avons la liste de munition ammo qui contient les objets a initialiser, nous chercons le premier non utilise.
	for (shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type == ShotType::UNUSED) break;
	}
	//Si les ammoRounds (16) munitions sont deja en train d'evoluer dans l'espace, nous ne pouvons pas en tirer une supplementaire.
	if (shot >= ammo + ammoRounds) return;

	//Nous affectons a notre objet ses attributs initiaux en fonction du type de projectile souhaite.
	if (initialValues)
	{
		switch (currentType) {
		case ShotType::PISTOL:
			shot->particle.setMass(2.0f); //2KG
			shot->particle.setVelocity(0.0f, 0.0f, 35.0f); //35m/s ou 110m/s 
			shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);//-1.0f ou -9.81f 
			shot->particle.setDamping(0.99f);
			break;
		case ShotType::ARTILLERY:
			shot->particle.setMass(200.0f); // 200KG
			shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s 
			shot->particle.setAcceleration(0.0f, -9.81f, 0.0f);//g force gravitationnelle
			shot->particle.setDamping(0.99f);
			break;
		case ShotType::FIREBALL:
			shot->particle.setMass(1.0f); // 1KG											  
			shot->particle.setVelocity(0.0f, 0.0f, 10.0f); //10m/s 
			shot->particle.setAcceleration(0.0f, 0.6f, 0.0f);
			shot->particle.setDamping(0.9f);
			break;
		case ShotType::LASER:
			shot->particle.setMass(0.1f); //0.1KG
			shot->particle.setVelocity(0.0f, 0.0f, 100.0f); // 100m/s 
			shot->particle.setAcceleration(0.0f, 0.0f, 0.0f); //Un laser est un rayon lumineux, nous ne pouvons pas lui donner une masse = 0 pour des raisons de calculs.
			//Ainsi nous ne mettons pas d'acceleration, force gravitationnelle par exemple car ce rayon lumineux peut evoluer a l'infini.
			shot->particle.setDamping(0.99f);
			break;
		case ShotType::ARROW:
			shot->particle.setMass(0.5f); // 1KG											  
			shot->particle.setVelocity(0.0f, 0.0f, 70.0f); //70m/s 
			shot->particle.setAcceleration(0.0f, -9.81f, 0.0f);
			shot->particle.setDamping(0.9f);
			break;
		default: return;
			break;
		}

		//Appliquer la position initiale
		shot->particle.setPosition(0.0f, 1.5f, 0.0f);//1,5m hauteur de lancement pour une personne lambda si nous devions lancer un de ces projectiles.
	}
	else
	{
		shot->particle.setPosition(listParamsObj[1], listParamsObj[2], listParamsObj[3]);
		shot->particle.setMass(listParamsObj[0]);
		shot->particle.setVelocity(listParamsObj[4], listParamsObj[5], listParamsObj[6]);
		shot->particle.setAcceleration(listParamsObj[7], listParamsObj[8], listParamsObj[9]);
		shot->particle.setDamping(listParamsObj[10]);
	}

	shot->startTime = TimingData::get().lastFrameTimestamp;
	shot->type = currentType;
	shot->alreadyPrinted = false;
}

//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
void Ballistic::UpdateVariousFrameRate()
{
	//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
	//Nous prenons donc volontairement une unite de retard pour la simulation.
	float duration = (float)TimingData::get().lastFrameDuration * 0.001f;//on discretise plus que la normale
	if (duration <= 0.0f) return;

	//Actualisation de la vitesse et de l'acceleration de notre particule avec l'integration en fonction du temps (temps de la frame n-1).
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != ShotType::UNUSED) {
			shot->particle.integrate(duration);
		}

		//Ici nous detectons si notre particule sort des limites de simultations et/ou des limites realistes.
		//En dessous du sol pour l'axe Y et au dessus de 300m pour la simulation sur Z et X.
		if (shot->particle.getPosition().y < 0.0f  || shot->particle.getPosition().z > 300.0f || shot->particle.getPosition().x > 300.0f || shot->startTime + 5000 < TimingData::get().lastFrameTimestamp)
		{
			//Pour les tests sur console, nous voulons un affichage de la fin de la simulation, nous detectons si la particule a deja ete affiche comme etant morte ou non.
			//Oblige de conditionner car nous passons tout le temps dans cette boucle meme en UNUSED car nous balayons la liste de munitions.
			//Les UNUSED restent a une position y = 0f par exemple.
			if (!shot->alreadyPrinted)
			{
				double LivingTime = (TimingData::get().lastFrameTimestamp - shot->startTime) / 1000;
				if (shot->particle.getPosition().y < 0.0f)
				{
					std::cout << "La particule " + shot->getType() + " vient de toucher le sol en : " + std::to_string(LivingTime) + " secondes.\n";
				}
				else if (shot->particle.getPosition().z > 200.0f)
				{
					std::cout << "La particule " + shot->getType() + " a dépassé les limites du terrain (300m) en : " + std::to_string(LivingTime) + " secondes.\n";
				}
				else if(shot->startTime + 5000 < TimingData::get().lastFrameTimestamp)
				{
					std::cout << "La temps de deplacement de la particule a depasse le temps maximum alloue a la simulation.\n";
				}
				shot->alreadyPrinted = true;
			}
			//Un fois que la particule est considere comme non utilisable, on la repasse en inactive pour que plus tard, lors d'un tir, une autre particule puisse prendre sa place
			//et etre tiree.
			shot->type = ShotType::UNUSED;

		}
	}
}

//Rafraichissement des valeurs de position et de vitesse a valeur de temps fixe, nous actualisons a la duree voulu par l'utilisateur.
void Ballistic::UpdateFixedFrameRate(double frameRateMS)
{
	float duration = frameRateMS * 0.001f;//on discretise plus que la normale
	if (duration <= 0.0f) return;

	//Actualisation de la vitesse et de l'acceleration de notre particule avec l'integration en fonction du temps voulu de rafraichissement.
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != ShotType::UNUSED) {
			shot->particle.integrate(duration);
		}

		//Ici nous detectons si notre particule sort des limites de simultations et/ou des limites realistes.
		//En dessous du sol pour l'axe Y et au dessus de 300m pour la simulation sur Z et X.
		if (shot->particle.getPosition().y < 0.0f || shot->particle.getPosition().z > 300.0f || shot->particle.getPosition().x > 300.0f || shot->startTime + 5000 < TimingData::get().lastFrameTimestamp)
		{
			//Pour les tests sur console, nous voulons un affichage de la fin de la simulation, nous detectons si la particule a deja ete affiche comme etant morte ou non.
			//Oblige de conditionner car nous passons tout le temps dans cette boucle meme en UNUSED car nous balayons la liste de munitions.
			//Les UNUSED restent a une position y = 0f par exemple.
			if (!shot->alreadyPrinted)
			{
				double LivingTime = (TimingData::get().lastFrameTimestamp - shot->startTime) / 1000;
				if (shot->particle.getPosition().y < 0.0f)
				{
					std::cout << "La particule " + shot->getType() + " vient de toucher le sol en : " + std::to_string(LivingTime) + " secondes.\n";
				}
				else if (shot->particle.getPosition().z > 200.0f)
				{
					std::cout << "La particule " + shot->getType() + " a dépassé les limites du terrain (300m) en : " + std::to_string(LivingTime) + " secondes.\n";
				}
				else if(shot->startTime + 5000 < TimingData::get().lastFrameTimestamp)
				{
					std::cout << "La temps de deplacement de la particule a depasse le temps maximum alloue a la simulation.\n";
				}
				shot->alreadyPrinted = true;
			}
			//Un fois que la particule est considere comme non utilisable, on la repasse en inactive pour que plus tard, lors d'un tir, une autre particule puisse prendre sa place
			//et etre tiree.
			shot->type = ShotType::UNUSED;

		}
	}
}

//Fonction display affichage console, pour toutes les particules lancees a l'instant t, nous affichons son type, son ordre de liste pour les differencier
//et sa position.
void Ballistic::DisplayConsole()
{
	int cpt = 0;
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		cpt++;
		if (shot->type != ShotType::UNUSED)
		{
			shot->particle.getPosition().display("Position particle " + shot->getType() + " : " + std::to_string(cpt));
		} 
	}
}

//Fonction display d'affichage sur OpenGL de nos projectiles. Vu que nos particule possede dans leur structure un attribut les affichants,
//cette methode est appelee pour chacun a chaque appel de displayOpenGL()
void Ballistic::DisplayOpenGL()
{
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
	{
		if (shot->type != ShotType::UNUSED)
		{
			AfficherProjectile(shot);
		}
	}

	//Rendu du texte du projectile actuelle
	glColor3f(1.0, 0.0, 0.0);//Couleur du text
	glRasterPos2f(-240, 120);//Position sur l'écran
	const char* string = getCurrentType();//Retourne le type de projectile selectionne.
	while (*string) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *string++);
	}
}

//Lors d'un appui sur le bouton gauche de la souris une particle du type actuel pourra etre lancee.
void Ballistic::MouseInput(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		Shoot();
	}
}

//Lors d'un appui sur une de ces touches (A,Z,E,R) du clavier, nous pourrons changer de type de projectile respectivemetn entre PISTOL, ARTILLERY, FIREBALL et LASER.
void Ballistic::KeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentType = ShotType::PISTOL;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		currentType = ShotType::ARTILLERY;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		currentType = ShotType::FIREBALL;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		currentType = ShotType::LASER;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		currentType = ShotType::ARROW;
	}
	//switch (key)
	//{
	//case 'A': currentType = ShotType::PISTOL; break;
	//case 'Z': currentType = ShotType::ARTILLERY; break;
	//case 'E': currentType = ShotType::FIREBALL; break;
	//case 'R': currentType = ShotType::LASER; break;
	//}
}

//Setter du type courant tant que l'interaction clavier ne fonctionne pas.
void Ballistic::setCurrentType(ShotType myType)
{
	currentType = myType;
}

//Permet au projectile de s'afficher sur OpenGL en fonction de sa position.
void Ballistic::AfficherProjectile(AmmoRound *amo)
{
	//ajouter des differentes couleurs en fonciton des types de projectiles.
	Vector3D position;
	position = amo->particle.getPosition();

	std::vector<int> couleurs = amo->getDisplayedColor();

	//affichage de notre sphere. Notre projectile.
	glColor3f(couleurs[0], couleurs[1], couleurs[2]);
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glutSolidSphere(2, 2, 2);
	glPopMatrix();
}

const char* Ballistic::getCurrentType()
{
	switch (currentType) {
	case ShotType::UNUSED:
		return "ERROR";
	case ShotType::ARTILLERY:
		return "ARTILLERY";
	case ShotType::FIREBALL:
		return "FIREBALL";
	case ShotType::LASER:
		return "LASER";
	case ShotType::PISTOL:
		return "PISTOL";
	case ShotType::ARROW:
		return "ARROW";
	}
}