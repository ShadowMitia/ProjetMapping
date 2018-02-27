# ProjetMapping
Projet Mapping Interactif avec des apoiliens

# Installation


## Windows

Télécharger openFrameworks 0.9.8 ici: http://openframeworks.cc/download/
Installer visual studio 2015: http://openframeworks.cc/setup/vs/ (l'addon VS est optionel)

Installer git.

L'interface graphique: https://desktop.github.com/
ET les outils (obligatoire pour les scripts): https://github.com/git-for-windows/git/releases/download/v2.16.1.windows.1/Git-2.16.1-64-bit.exe

Dans git cloner le dépot https://github.com/ShadowMitia/ProjetMapping.git et le placer dans racineopenframeworks/apps/myApps


Il faut ensuite télécharger (ou cloner) les addons suivant et les mettres dans racineopenframeoworks/addons
Il y a le script "installAddons.bat" pour installer ça sous windows une fois que le projet est installé.
- https://github.com/kylemcdonald/ofxCv (prendre la branch stable pour la version 0.9.8)
- https://github.com/armadillu/ofxGLFWJoystick
- https://github.com/ShadowMitia/ofxLiquidFun
- https://github.com/kr15h/ofxPiMapper
- https://github.com/thomasgeissl/ofxWiiuse (optionel si pas de wiimote à porter de main)
Attention! Les addons doivent avoir le nom exact (pas de -master à la fin), et les dossier doivent contenir les fichiers de l'addon directement (on ne pas peut avoir par exemple ofxCv/ofxcv/"les fichiers ofxcv", mais directement "ofxCv/fichiers ofxcv")

Pour installer les wiimotes, il faut:
- installer cmake https://cmake.org/download/
- installer wiiuse https://github.com/rpavlik/wiiuse en suivant les instructions
- rajouter "ofxWiiuse" dans addons.make


Pour désactiver le code pour les wiimotes il faut commenter "#define USE_WIIMOTE" dans src/ofApp.h



## Linux

Télécharger openFrameworks 0.9.8 ici: http://openframeworks.cc/download/
On peut installer un des IDE proposer, mais on peut s'en passer et utiliser la commande `make` dans le terminal.

Une fois openFrameworks installer, il faut aller installer les dépendances nécessaires.

Dans un terminal:
- `cd chemin_racine_of/scripts/linux/<distribution>/` (remplacer distribution par le nom approprié)
- `sudo ./install_codecs.sh; sudo ./install_dependencies.sh`, appuyer sur 'y' quand demandé. Si un message parlant de Poco apparait faire `Ctrl-C`
- `cd ../../apothecary`
- `./apothecary -g -s poco-1.8.1-release update poco`

Installer git. S'installe via le gestionnaire de paquet. (Exemple: sudo apt-get install git (debian/ubuntu) ou sudo dnf install git (fedora))
TODO: Git avec un GUI.

Instructions dans un terminal:

- `cd chemin_racine_of/apps/myApps`
- `git clone  https://github.com/ShadowMitia/ProjetMapping.git`
- `cd ProjetMapping/scripts`
- `chmod +x installAddons.bat`
- `./installAddons.bat`
- `cd ..`
- [pour les programmeurs] `make Debug` ou `make Debug -jN` avec `N` le nombre de processeurs que vous voulez utiliser
- [pour les autres ou pour utiliserw en publique]`make Release` ou `make Release -jN` avec `N` le nombre de processeurs que vous voulez utiliser
- pour lancer le programme `make RunDebug` ou `make RunRelease` ou `./bin/ProjetMapping` ou `./ProjetMapping_debug` ou aller dans le dossier `bin` dans le dossier du projet et cliquer sur l'exécutable voulu.


Pour installer les wiimotes, il faut:
- installer wiiuse (dans le dépôts: sudo apt-get install wiiuse ou sudo dnf install wiiuse)
- rajouter "ofxWiiuse" dans addons.make

Pour désactiver le code pour les wiimotes il faut commenter "#define USE_WIIMOTE" dans src/ofApp.h
