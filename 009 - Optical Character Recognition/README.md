# Labo 3: OCR

Pour lancer le programme, utiliser la commande suivante:
```bash
poetry run labo3/server.py 0
```

Où ```0``` est un paramètre pour indiquer au programme s'il faut effectuer le processus d'entrainement du réseaux de néurones.
Le ```0``` correspond à **non**, ```1``` correspond à **oui**.
Ce paramètre est optionnel et par défaut est à ```0```. Un modèle pre-entrainé est déjà présent dans le dossier **Labo3**.


Après lancement, aller à l'adresse http://127.0.0.1:8000 pour accéder à l'interface.

Pour tester un chiffre, le dessiner sur le tableau et cliquer sur **Send**.
Après quelques secondes le résultat va apparaître au dessous du bouton Send.
Les probabilités sont affichées en pourcentage.


## Autres infos

- Pour l'entrainement, 11 images pour chaque chiffre ont été utilisées.
- Si vous souhaitez ajouter des images au dataset d'entrainement, il suffit de dessiner le chiffre et rentrer dans la case de quel chiffre il s'agit. Ensuite cliquez sur **Send**. L'image sera ajouté au dataset dans le dossier correspondant au chiffre choisi.
- Pour la partie réseaux de néurones, je me suis inspiré de cet article: https://www.sitepoint.com/keras-digit-recognition-tutorial/
- Je n'ai pas eu le temps de rendre le design de la page web un peu plus attractif, mais tout fonctionne correctement.
- Il y a un Warning TensorFlow qui s'affiche après avoir soumis 5 images, mais je n'ai pas réussi à le résoudre, même après avoir essayé les différentes solutions proposées par le message.
```
WARNING:tensorflow:5 out of the last 5 calls to <function Model.make_predict_function.<locals>.predict_function at 0x7f06b44a3c10> triggered tf.function retracing. Tracing is expensive and the excessive number of tracings could be due to (1) creating @tf.function repeatedly in a loop, (2) passing tensors with different shapes, (3) passing Python objects instead of tensors. For (1), please define your @tf.function outside of the loop. For (2), @tf.function has experimental_relax_shapes=True option that relaxes argument shapes that can avoid unnecessary retracing. For (3), please refer to https://www.tensorflow.org/guide/function#controlling_retracing and https://www.tensorflow.org/api_docs/python/tf/function for  more details.
```




## Note personnelle

Personnellement, j'ai passé beaucoup plus de temps sur la partie Javascript que celle Python. J'aurais préféré approfondir la partie machine learning plutôt que celle web development / web design.
