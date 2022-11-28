# Lab Virsh Advanced Sergio

## Prérequis
- Le rendu de ce Labo est composé de plusieurs fichiers.
- Tous les fichiers doivent se trouver dans le même dossier.
- La liste des packages nécessaires pour exécuter les scripts sur une machine autre que `vmhostsoir` se trouve dans le fichier `3-hypervisor_conf.sh`.
- Un réseau appelé `mynet` doit exister sur la machine dans laquelle on exécute le script. Pour modifier le nom du réseau, éditer le fichier `library.sh`.
- Le mot de passe par défaut est `hepia`. Pour le modifier, éditer le fichier `library.sh`.

## Exécution des scripts
Après avoir copié tous les fichiers sur la VM depuis laquelle les exécuter, lancer la commande suivante:
```
./make.sh
```
Les scripts seront exécutés l'un après l'autre.

Si besoin, rendre les fichiers exécutables avec la commande: 
```
chmod +x *.sh
```

Certaines étapes demandent de rentrer un mot de passe (voir prérequis pour le modifier).


## Notes
- Les explications concernantes les fonctions utilisées se trouvent dans chaque fichier.
- L'étape qui manque est la clonation de la VM installée sur l'hyperviseur.
- Les scripts 5 et 6 devraient être optimisés ultérieurement.
