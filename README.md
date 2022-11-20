# UQAC Projet moteur physique

## Comment utiliser l'application

-Dès la compilation effectuée, le lancement de notre démonstration est possible sans besoin d’apporter des changements. Vous pouvez observer un cube se déplaçant sur écran blanc. 

-Vous pouvez observer plusieurs configurations, pour cela il suffit de changer la valeur de la variable APPLICATION_WANTED, sa valeur peut être mise entre 0 et 4 pour tester chacun des fonctionnements. La fonction d’initialisation est ChooseWitchApplicationIsWanted(), elle se situe dans “Main_rendu3.cpp”.

-Vous pouvez changer manuellement les valeurs des vecteurs 3D passés en paramètres du constructeur de demoCube appelé dans le switch case de ChooseWitchApplicationIsWanted(). Comme expliqué ci-dessous dans la rubrique “Les problèmes rencontrés” nous n’avons pas réussi à utiliser IMGUI pour ce rendu, ainsi nous ne pouvons pas faire varier les paramètres lors de l'exécution, ça aurait été un atout non négligeable.

-Si la compilation recontre un problème (normalement non, le projet est testé sur machine vierge), un exécutable est a votre disposition dans le répertoire source.
