# Labo 2: VISNU WHEEL!

Pour lancer le programme, utiliser la commande suivante: 
```bash
poetry run labo2/gamepad.py data/wheel_racing.avi 10
```

Où ```data/wheel_racing.avi``` correspond à la vidéo et ```10``` c'est le temps en millisecondes entre deux frames. Cette dernière valeur est optionnelle.

## Important ! 
Pour une question d'efficience, il n'y a pas de vidéo dans le dossier ```data```. 
Merci de l'ajouter avant de lancer le programme. 


## Autres infos

- Le fichier texte contenant les angles calculés est sauvegardé dans le dossier ```data```.
- Il y a un délai de **10ms** entre deux frames de la vidéo configuré dans la variable ```interval``` en debut du fichier ```gamepad.py```
- Après avoir cherché pendant longtemps, je n'ai pas trouvé de moyen pour afficher le graphique en temps réel. Pour cela on serait obligé de traiter d'abord toute la vidéo, ce qui demanderait trop de temps et de mémoire avant de pouvoir faire l'affichage.
- Je n'affiche pas l'image binaire avec les deux formes extraites. Pour cela décommenter la ligne 168 : ```cv.imshow("Mask video", np.hstack((yellow_mask, red_mask)))```
