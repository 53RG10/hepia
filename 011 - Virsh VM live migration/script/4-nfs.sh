#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script to configure NFS server-side and client-side, using Ansible.

. ./library.sh

create_nfs_playbook () {
  IP_H1=$(get_ip $HYP1)
  IP_H2=$(get_ip $HYP1)
  echo "---
- name: NFS server configuration
  hosts: storage
  become: yes
  tasks:
   - name: add NFS path
     lineinfile:
       path: /etc/exports
       line: /mnt/lvm   192.168.122.0/24(rw,sync,no_subtree_check)
       insertbefore: EOF

   - name: enable fileshare
     command: exportfs -a

   - name: restart NFS service
     service:
       name: nfs-kernel-server
       state: restarted
       enabled: yes

   - name: change directory permissions
     file:
      path: /mnt/lvm
      state: directory
      owner: root
      group: root
      mode: 0777" > nfs-playbook.yml
}


create_nfs_client_playbook () {
  IP=$(get_ip $STORAGE)
  echo "---
- name: NFS client configuration
  hosts: hypervisor
  become: yes
  tasks:
   - name: install NFS clients
     apt:
       install_recommends: no
       pkg:
        - nfs-common

   - name: create mount directory
     file:
       path: /mnt/nfs
       state: directory

   - name: mount at startup
     lineinfile:
       path: /etc/fstab
       line: '$IP:/mnt/lvm /mnt/nfs nfs defaults 0 0'
       insertbefore: EOF

   - name: mount NFS directory
     mount:
      path: /mnt/nfs
      src: $IP:/mnt/lvm
      fstype: nfs
      state: present" > nfs-client-playbook.yml
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 12: Setup NFS on server
create_nfs_playbook
ansible-playbook -i hosts nfs-playbook.yml

# STEP 13: Setup NFS on clients
create_nfs_client_playbook
ansible-playbook -i hosts nfs-client-playbook.yml
