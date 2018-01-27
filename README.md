# ProjetMapping
Projet Mapping Interactif avec des apoiliens

# Installation


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

TODO: instructions pour wiimotes et lib wiiuse

Pour désactiver le code pour les wiimotes il faut commenter "#define USE_WIIMOTE" dans src/ofApp.h

