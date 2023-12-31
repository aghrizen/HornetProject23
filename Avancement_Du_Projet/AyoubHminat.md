## Semaine 1: 20/09/23
### (Travail en groupe)
Dans la première semaine du travail dans le projet, 
nous avons commencé par comprendre ce que l'ancien groupe a fait.


  Tout d'abord, nous avons essayé de tester le code qui permet 
  de manipuler la caméra qui prends les photos des frelons:                                                                                       
- Il s'agit d'un code sur Arduino. Nous avons pu le compilé sans problème.

- Puis, nous l'avons testé sur les deux cartes en notre possession : une fonctionne parfaitement mais l'autre nous sort une erreur avec le lecteur de carte SD (les 2 cartes ont été testées avec la même carte sd).                                                                                                                                                                            
-  Nous avons essayé de refaire le soudage de quelques fils de la 
 carte défectueuse sans succés.


  Par la suite, avec la carte fonctionnelle, nous avons testé le code "testmoteur" qui permet de manipuler le moteur:                                                                           
-  Problèmes observés :
    - Voltage 3.3V (max uc) au lieu de 4.8V - 6V. Toutefois, le moteur fonctionne même à ce voltage. Le seul problème est que les valeurs données par le constructeur, comme par ex la vitesse de rotation en °/s ont été mesuré à ces valeurs. Nous devrons donc le recalculer avec 3.3V. Deplus, le code fournit utilise des pwn avec des fréquences incorrectes pour faire tourner le moteur. Résultat le moteur bloqué à 180° force pour continuer. 
    Pour le fonctionnement voulu, nous n'avons pas besoin de PWN car la rotation est un événément inopiné et variable donc nous devrions avoir la possibilité de controler sa durée à l'état haut à tout moment. Remplacement par une simple pin DigitalOut. Nous calculerons la durée d'attente entre l'état haut et l'état bas en fonction de la distance avec la cible.

    Le défaut de cette méthode est que nous "bloquons le proccess" pendant la rotation. Mais ce temps est négligeage car il s'agit de 0.1 - 0.3s. Les frelons volent en stationnaire, nous n'avons pas besoin d'une réponse rapide mais bien d'une réponse précise.


## Semaine 2: 17/10/2023
### (Travail en groupe)

Dans la deuxième semaine, nous avons tester une nouvelle carte qui prend les photos des frelons. 

-  En fait, celle-ci est mieux que l'autre que nous avons tester la dernière fois, car, elle permet de détecter les mouvements grace à un capteur intégré: en fonction des mouvements, elle prend les photos. Pour faire fonctionner le code, nous avons installer la bibliothèque EloquentSurveillance de Arduino, version 13, pour éviter toute erreur de la compilation.

-  Par la suite, avec la carte fonctionnelle, nous avons testé le code "testmoteur" qui permet de manipuler le moteur:                                                                           
-  Problèmes observés :
   
    - Voltage 3.3V (max uc) au lieu de 4.8V - 6V. Toutefois, le moteur fonctionne même à ce voltage. Le seul problème est que les valeurs données par le constructeur, comme par ex la vitesse de rotation en °/s ont été mesuré à ces valeurs. Nous devrons donc le recalculer avec 3.3V. 

    Le défaut de cette méthode est que nous "bloquons le proccess" pendant la rotation. Mais ce temps est négligeage car il s'agit de 0.1 - 0.3s. Les frelons volent en stationnaire, nous n'avons pas besoin d'une réponse rapide mais bien d'une réponse précise.


-  En fait, celle-ci est mieux que l'autre que nous avons tester la dernière fois, car, elle permet de détecter les mouvements grace à un capteur intégré: en fonction des mouvements, elle prend les photos. Pour faire fonctionner le code, nous avons installer la bibliothèque EloquentSurveillance de Arduino, version 13, pour éviter toute erreur de la compilation.

-  Deuxième chose que nous avons fait, c'était d'essayer de résoudre le problème que nous avons observé la dernière fois dans le code du moteur.

-  Nous avons rencontrer un problème qui empêchait le bon fonctionnement du moteur et qui le bloquait: le courant était insuffisant pour alimenter le moteur, il refait chaque fois la fonction setup() sans entrer dans la boucle. Donc, il faut utiliser une alimentation pour lui alimenter et éviter son bloquage.
Objectifs pour la semaine prochaine: 
- Utiliser une alimentation pour alimenter le moteur et le faire fonctionner avec les bonnes valeurs des angles.
- Fixer la carte caméra de détection dans la boite.



## Semaine 3: 27/10/2023
### (Travail en groupe)

- Dans cette semaine, nous avons alimenté le moteur avec une alimentation externe 5V pour résoudre le problème que nous avions la dernière fois (courant inssufisant), et nous avons pu confirmer que les constantes présentes dans le code pour les angles du positionnement (0°, 90°, 180°).
- Nous avons teste avec des valeurs d'angles aléatoire pour etre sûr que c'est proportionnel. 
- Par suite, nous avons positionné la carte qui détécte le mouvement dans notre boite: le positionnement a été fait après avoir tester tout endroit de la boite dans lequel nous pouvons prendre assez des photos qui couvrent toute la boite un peu près avec des bons fonctionnement et détéction du capteur.
- Nous avons tenté de comprendre les outils utilisés dans la partie de reconnaissance d'image afin de déterminer si la photo prise par la caméra contient un frelon ou une abeille, puis de transmettre l'information, en particulier la position, dans le cas où il s'agit d'un frelon.
- L'outil utilisé est un site web appelé " Edge Impulse ", qui constitue une plateforme de développement pour l'apprentissage automatique sur des appareils embarqués. Cette plateforme facilite le processus de construction, de déploiement et de gestion des modèles d'apprentissage automatique sur des appareils embarqués, le rendant ainsi accessible et simple.
- Dans notre cas, l'objectif est de prendre un maximum de photos de frelons et d'abeilles sous différents angles, positions et éclairages, afin de fournir cette base de données sur le site web pour entraîner le modèle à reconnaître la cible (le frelon, dans notre cas). Enfin, le modèle nous fournira un code final qui sera compatible avec la carte ESP32..



## Semaine 5: 20/11/2023
### (Travail en groupe)

- Dans cette séance, nous avons essayé de tester les deux codes générés la dernière fois par l'outil Edge Impule. Mais, nous avons rencontré quelques problèmes lors de la comilation:
     - En fait, l'outil de l'IA *Edge Impulse* ne génère des codes que pour deux modèles des cartes: nous pouvons pas utilisé le code pour la carte du modèle ESP32 Wrover-dev, par contre, pour la carte qui détècte le mouvement des frelons du modèle AI Thinker, ça fonctionne bien et ça arrive de détécter les frelons ( nous avons essayé de placer l'un des frelons qui se trouvent dans la boite à côté du caméra et de le faire bouger), ça affiche également les dimensions (x, y) du position de frelon.
     - Nous avons essayé de définir beaucoup des types des modèles dans l'en-tête de code généré mais ça marché pas du tout.

####  Pourquoi le choix du modèle ESP32 Wrover-dev?
 -> Parce que, cette, carte, permet d'alimenter en même temps le moteur contrairement à l'autre. Donc l'objectif est de trouver une solution:
 
  - Soit de trouver un autre outil similaire à *Edge Impulse* qui peut être un peu complexe parce qu'il faut entraîner notre modèle, de configurer ou/et d'adapter le modèle pour gérer les opérations d'inférence sur l'ESP32... ce qui va prendre du temps et des efforts.
    
  - Soit de trouver un moyen de communication entre les deux modèles de carte.


   - Nous avons également commencer de souder des pins dans l'autre carte du modèle ESP32 Wrover-dev pour alimenter le moteur ave celle-ci qui fonctionne bien au niveau des images (parce que dans la première séance il y'avait deux carte de ce modèle et une ne fonctionne pas pour prendre des photos: elle alimente le moteur uniquement).
   - Nous avons récupéré d'autres DataBase dans notre projet pour re-générer un autre code plus efficace: plus la database est grande, plus la probabilité de détécter le frelon est élevée. 
