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


## Semaine 4: 01/11/2023
### (Travail individuel)

- Dans cette séance, nous avons vu les images des frelons qui ont été prises dernièrement. Il y'avait des photos avec le flash et sans flash (elles ont été prises par la carte qui détécte le mouvement). Le problème c'était la qualité des images: en fait c'était presque impossible de distinguer entre les frelons et les abeilles qui se trouvent dans les photos.
- Pour avancer, j'ai pris les images de base qui se retrouvent dans le projet des ancient étudiants de l'année dernière (les images qu'ils ont pris en fixant le frelon et l'abeille). Et j'ai essayé de regénérer le code sur *Edge Impulse* en séléctionnant de nouveau le frelon et/ou l'abeille qui apparaient sur les photos. Comme ça, je peux également arriver à comprendre comment ça marche le logiciel en ligne, pour travailler sur ce dernier facilement pour la prochaîne séance quand nous allons avoir les nouvelles images qui sont plus claires.
- En fin, j'ai générée le code, il reste uniquement de le tester sur la carte pour la séance prochaîne: en effet, la compilation prend un long temps, à cause des multiples librairies et fichier *.h qui ont été générés par *Edge Impulse*. 


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


## Semaine 6: 04/12/2023
### (Travail en groupe)

- Dans cette séance, nous avons arrivé de faire fonctionner le code génerer par l'outil d'I.A Edge Impulse avec la carte électronique du modèle WROVER.
- Pour faire fonctionner le code, nous avons modifié les pins de la carte dans le code, et nous avons effectué d'autres modifications auniveau des libraries générées.
- Maintenant, il faut trouver une solution pour contrôler la puissance du laser qui se trouve sur le moteur pas-à-pas: parce que sans contrôleur, ça reste dangereux de l'utiliser. Il faut voir si on doit utiliser une carte particulière pour le contôle ou un générateur de 12V.


## Semaine 7: 22/12/2023
### (Travail en groupe)
- Dans cette semaine, nous avons essayé de trouver une méthode pour faire contrôler le laser. Parce que, qu'on on charge le code pour faire fonctionner le moteur, le laser reste allumé ce qui est dangereux puisqu'il chauffe. Il fallait donc, trouver un moyen pour qu'il s'allume uniquement le moement ou un frelon est détécter.
- Après avoir faire une recherche, nous avons trouvé un schématic en pdf qui explique comment le laser a été contrôlé:
    - Il suffit d'utiliser deux transistors pour contrôler le laser.
    - Le pin 8 n'est utilisé que pour le laser.
    - Le signal est soit 1 ou 0: 1 est la durée pour laquelle le laser reste allumé.
- Il faut maintenant chercher comment peut on intégrer ce protocole qui fait contrôler le laser dans PCB.


## Semaine 8: 13/02/2024
### (Soutenance du projet et travail en groupe)
- Dans cette séance là, nous avons fait la soutenance du projet pour présenter au prof les avancements que nous avons fait par rapport à ce que les autres avaient fat l'année dernière.
- Le code que nous avons généré par l'outil Edge Impulse doit être regénérer pour que le caméra détècte le vide.
- Pour cet outil de l'I.A Edge Impulse, nous avons deux modèles d'entraînement que nous pouvons utiliser:
    - Le modèle classique qui est déjà choisit par défaut et qui va fournir une librairie avec le nom du projet créer sur Edge Impulse. Donc pour faire fonctionner la carte avec celui-là, nous allons prendre tout simplement dans esp32 le code esp32_camera puis on l'intégre sur notre carte.
    - Le deuxième est le modèle FOMO (First Object Most Object). Celui-là à pour but de générer un code plus condensé donc plus facile à comprendre par rapport au modèle de base. C'est parce qu'il génére de plus, une autre librairie qui contient les détails du programme. Dans ce code condensé, nous allons voir sur le moniteur, le 'label' qui reprèsente 'frelon' ou 'abeille', et les cordonnées x et y pour détécter le position du frelon dans l'espace.
- Dans le code généré, il faut chaque fois le modifier en fonction du modèle de la carte que nous allons utiliser (AI Thinker où Wrover).
- Le board à choisir sur Arduino qui va faire marcher n'importe quelle carte esp32, est le board: 'Esp32 Dev Module'.
- Concernant le contrôle de laser, et comme ce que nous avons vu la dernière fois, il faut tester la solution avec les deux transistors MOSFET pour voir si ça va fonctionner où pas. Il faut, également, trouver une solution pour que le laser ne chauffe pas lors de notre processus, et qu'on contrôle sa puissance.

Donc les objectifs à faire après cette soutenance là:
- Re-génère le code avec Edge Impule pour que la caméra détècte le vide.
- Tester la solution avec les deux transistors pour contrôler le laser.

### (Travail Individuel)
- Après la présentation, j'ai commencé à re-génèrer le code avec l'outil Edge Impulse.


### Semaine 8: 14/02/2024
### (Travail Individuel)
- Dans cette séance là, j'ai travaillé sur l'outil Edge Impulse, ça m'a pris toute la séance parce que j'ai choisi une database qui est énormément grande pour augmenter la précision. En prenant dans cette fois là, en considération, la saisie de background pour que, le programme généré, n'affiche pas 'hornet' ou 'bee' quand il y'a rien qui tourne en face du caméra.
- Dans l'utilisation de l'outil, J'ai augmenté le nombre des cycles de training, ce qui m'a permet d'obtenir une détéction de 100% pour le frelon et pour l'abeille et aussi pour le background (regardez sur le répértoire rapport_en_pdf, edge_ipmulse_precised_version.pdf).


### Semaine 8: 16/02/2024
### (Travail en Groupe)
- Nous avons passé, cette séance là, en faisant des modifications sur la nouvelle version du code regénéré par Edge Impulse, la dernière fois.
### (Travail Individuel)
- J'ai testé ce modèle sur la carte, et le problème de la détéction du vide n'était pas une bonne solution. Celui-là, a diminué la probabilité de la détction du frelon et de l'abeille. Ce qui affiche, par suite, 'Object not found' même si qu'il y'a le frelon juste en face de la caméra.
- Donc pour résoudre ce problème, j'ai réduit la base des données dans même version du projet sur Edge Impulse. J'ai gardé que des photos net (regarder même rapport edge_impulse_precised_version). Et j'ai gardé que deux classes: 'bee' et 'hornet'. Parce que, dans les exemples en lignes normalement, l'outil de l'IA qu'on utilise cherche par lui même le background donc ça sert a rien de le préciser sur les images.



### Semaine 9: 27/02/2024
### (Travail en Groupe)
- Dans cette séance, nous avons essayé de commencer de faire tester la solution que les autres ont proposé l'année dernière et qu'ils l'ont pas testé: c'était l'utilisation de deux transistors FET pour contrôler le laser.
- Pour ceci, nous allons utilisé un laser du modèle qui a une puissance faible déjà, pour ne pas endommager quelque chose lors du test.
- Il fallait pour ça, tester sur la carte Wrover directement. Donc, nous avons soudé des pins pour utilisé Vin.
### (Travail Individuel)
- Dans cette séance là, j'ai travaillée encore sur l'outil de Edge Impulse pour bien améliorer la précision. J'ai appris plein de choses sur le modèle de FOMO (regarder le rapport en PDF: edge_impulse_fomo_modele.pdf).
- Comme rappel, il faut chaque fois, dans le code généré, ajouter le define et les pins du modèle Wrover de la carte.



### Semaine 9: 28/02/2024
### (Travail Individuel)
- Le problème que nous avons remarqué dans les séances précédentes, c'est que, le laser chauffe quand il est allumé. La solution c'était de ne le pas faire chauffer parce que c'est risqué lors du processus de la détéction.
- La solution c'est d'utiliser un fan ventilateur qui est collé sur le laser. La fan est du modèle 'LD3010HS laser brushless DC fan', il fonctionne sous 12V, de puissance 168Watt.
- Nous avons déjà, à notre disposition, ce fan. Le problème c'est que il y'avait un fil décracher du fan, il fallait le souder alors.
- Puisque le fan fonctionne sous 12V, il faut trouver l'alimenter.
- J'ai essayé d'intégrer le code du moteur sur le code généré par Edge Impulse: ça fonctionne. Il faut juste alimenté le moteur parce que il travaille sous 12V, l'alimentation par carte n'est pas suffisante.
### (Travail en groupe)
- Nous avons essayé de souder le fil du fan pour le faire fonctioner.
- Nous avons réussi hier, à faire clignoter le petit laser à l'aide du code généré par Edge Impulse directement avec la carte Wrover aliménté.


### Semaine 10: 13/03/2024
### (Travail en groupe)
- La dernière fois, nous avons arrivé à faire fonctionner le petit Laser et à le contrôler à l'aide de PWM.
- Nous avons intégré le code de contrôle et de fonctionnement du moteur dans le code qui était généré par Edge Impulse. Donc nous avons bien modifié ce dernier même aussi des fonctions définies.
- Nous avons alimenté le fan ventilateur, et ça a fonctioné parfaitement. Donc on est sûr qu'on va pas envisager le problème du chauffement de laser quand il est allumé.


  ### Semaine : 19/03/2024
  ### (Travail 
