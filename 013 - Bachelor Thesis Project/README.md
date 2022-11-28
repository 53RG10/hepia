# Travail de Bachelor - Guarino Sergio

## Description
Le présent dépôt contient les fichiers sources utilisés et développés dans le cadre du travail de Bachelor en Informatique et Systèmes de Communication à l'HEPIA (Genève). Le dépôt est un complément au memoire de Bachelor. 

## Structure
Le dépôt est composé des dossiers suivants:
 - **ansible**, qui contient le module dévéloppé pour ce projet et un playbook de test
 - **disable**, avec le script à utiliser pour désactiver fs-verity d'un fichier
 - **fsverity**, qui contient un programme originellement partie d'un autre projet et qui a été modifié pour l'adapter à nos besoins
 - **service**, un service de monitoring des fichiers fs-verity

## Utilisation
### ansible
Le répertoire contient une structure de fichiers pour le déploiement de fs-verity sur des hôtes définis dans le fichier `inventory`.<br>


Le fichier `roles/demo/vars/main.yml` doit être adapté avec l'emplacement correct des fichiers tel que certificat, clé privé et index de fichiers à protéger. Il en vaut de même pour `roles/setup/vars/main.yml`. Ou on peut créer un fichier de variables globales à tous les rôles pour regrouper certaines variables.

Commande d'exemple pour l'exécution du playbook : `ansible-playbook play.yml -i inventory`

### disable
Script de désactivation de fs-verity sur un fichier. <br>
Le script efface le fichier passer en paramètre de l'index contenant la liste des fichiers qui sont monitorés par le service. Pour pouvoir utiliser cette fonctionnalité, modifier le script pour inclure le chemin du fichier d'index.

Pour simplifier son exécution, on peut copier le script dans `/usr/bin/` <br>
Exemple d'utilisation: `disable file.txt`


### fsverity 
Pour l'utilisation du script contenu dans le répertoire fsverity:
 - télécharger le [dépôt git du projet original](https://git.kernel.org/pub/scm/linux/kernel/git/ebiggers/fsverity-utils.git/tree/) : `git clone https://git.kernel.org/pub/scm/linux/kernel/git/ebiggers/fsverity-utils.git`
 - remplacer `cmd_sign.c` dans le répertoire `programs` avec celui de notre projet
 - exécuter la commande `make` pour compiler l'exécutable
 - copier l'exécutable `fsverity` dans `/usr/bin/`

Ces opérations sont à effectuer sur la machine à partir de laquelle on crée les fichiers de signature.<br>
Les client sur lesquels on a activé fs-verity dans le kernel ne nécessitent pas cet exécutable modifié. <br>

### service
Pour l'installation du service de monitoring, 3 fichiers sont nécessaires:
 - **fsverity.service**, à copier dans `/etc/systemd/system/`
 - **fsverity_service.py**, à placer dans le répertoire indiqué dans fsverity.service (ligne ExecStart)
 - un fichier d'index. Son chemin on peut le définir dans fsverity_service.py. 
