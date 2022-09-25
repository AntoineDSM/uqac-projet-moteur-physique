# UQAC Projet moteur physique

## Comment utiliser l'application

Le tire c’est clic droit
Vous pouvez changer les arme avec les touches AZERT
Changer la caméra avec les 3 première réglette
Changer la masse
Changer la vitesse
Changer l’accélération
l'amortissement
la position initiale
<<<<<<< refs/remotes/origin/Victor

## Comment utiliser la version 2

-Pour la génération de l'amat de particule / de blob :
  
  -Un fichier release blob contient le Release_blob.exe correspond si un problème subvenait.
  -Lorsque vous lancez la solution, de nombreuses fonctions sont presentes avant le main, une d'entre elle s'appelle Blob(), il vous faudra décommenter son appel dans le main et commenter celui de TestEachFonctionnalities().
  
  Lorsque l'application aura compilée, plusieurs particules seront présentes, une dizaine. Pour simuler l'ensemble il est nécessaire d'appuyer sur le booléen "Pause" dans une des fenêtre IMGUI.
  
-Pour le test de chacune des fonctionnalités (Buoancy, drag, gravity.....)

  -Il vous faudra commenter l'appel de blob() dans le main et decommenter TestEachFonctionnalities().
  -TestEachFonctionnalities() récupère un entier par défaut à 0 en paramètre, il faut changer cet entier soit dans l'appel dans le main soit directement dans la déclaration de la fonction. Il est possible de le mettre de 0 à 7 pour aller de Buancy à Contact Rod.
  -Il faudra donc build pour tester une à une les foncitonnalités, n'oubliez pas d'appuyer sur le booléen "pause" du menu IMGUI pour lancer la simulation.
  
-L'utilisation des menus IMGUI :

  -Le booléen "Pause" permet le lancement/l'arret de la simulation. Vous pouvez vous deplacer dans le repère avec les 3 premiers sliders de la fenêtre particle/mur.
  -Un menu permet d'instancier une particule/un mur. Les paramètres sont à rentrer aux emplacements adéquates, ensuite, si vous voulez instancier une particule, mettre le booléen correspondant "InstancierParticule" à true et faite clic droit. De même pour l'instanciation d'un mur.
  -L'ajout des forces et des contacts via les menus IMGUI n'ont pas été assez testé et ne sont pas fonctionnelles.
  
  -Pour les soucis de compilation sur machine vierge subvenus lors du premier rendu :
  
    -Les problèmes ont normalement été résolus, cependant pour tester le précédant rendu, un release à été déposé également. Son nom est "Release_demoBallisitc.exe".

=======
>>>>>>> Modif Read me + Add document

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://git.enib.fr/a8desain/uqac-projet-moteur-physique.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://git.enib.fr/a8desain/uqac-projet-moteur-physique/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Automatically merge when pipeline succeeds](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing(SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!). Thank you to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
