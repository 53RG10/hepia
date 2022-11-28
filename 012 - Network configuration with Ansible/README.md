# Virtualisation - TP3 & TP4

## Tag 1.0 - TP3

Ce TP a pour but d'utiliser Ansible pour:
- configurer l'interface eth1 de H1 et H2;
- ajouter des ip routes à H1 et H2;
- installer curl sur H1 et nginx sur H2;
- configurer R1 en tant que router;
- tester depuis H1 un curl sur H2.

Les informations IP se trouvent sous forme de texte dans le schéma gns3: 
[lien du projet](https://gns3.hepiapp.ch/static/web-ui/server/1/project/4a340c72-f20e-45d1-914c-df4f40e258e0)

H1, H2 et R1 doivent être aprovisionnés avant de lancer le playbook Ansible. Notamment:
- récupérer l'adresse IP de H1, H2, R1 (par ex. avec `ip a`);
- modifier les hostnames de H1, H2, R1 (par ex. en modifiant `/etc/hostname` );
- ajouter H1, H2, R1 dans les hôtes de AG1 (Ansible Gateway) (`nano /etc/hosts`);
- générer des clés ssh sur AG1 (`ssh-keygen`)
- envoyer les clés ssh aux hôtes (pour H1: `ssh-copy-id H1`);
- essayer de se connecter en ssh sur les hôtes: aucun mot de passe ne devrait être demandé.

## Tag 2.0 - TP4
