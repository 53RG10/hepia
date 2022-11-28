#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script that creates Ansible playbooks for VMs and executes them.

. ./library.sh

create_hosts_file () {
  echo "[storage]
$STORAGE

[hypervisor]
$HYP1
$HYP2" > ./hosts
}

create_sudo_playbook () {
  echo "---
- hosts: all
  tasks:
    - name: edit sudoers for passwordless login
      lineinfile:
        path: /etc/sudoers
        state: present
        regexp: '^%sudo'
        line: '%sudo ALL=(ALL) NOPASSWD: ALL'
        validate: 'visudo -cf %s'

    - name: edit sudoers to add debian user
      lineinfile:
        path: /etc/sudoers
        line: 'debian  ALL=(ALL) NOPASSWD:ALL'
        insertafter: '%sudo'" > sudo.yml
}


create_storage_playbook () {
  echo "---
- name: storage playbook
  hosts: storage
  become: yes
  tasks:
  - name: install LVM and NFS tools
    apt:
      install_recommends: no
      pkg:
        - lvm2
        - nfs-kernel-server

  - name: create LVM group
    command: sudo vgcreate storage /dev/vdb /dev/vdc

  - name: create LVM disk
    command: sudo lvcreate -L 19.99GB -n LVStorage storage

  - name: show result
    register: output
    command: sudo lvdisplay

  - debug:
      msg:
       - '{{output.stdout_lines}}'

  - name: creating filesystem
    command: sudo mkfs.ext4 /dev/storage/LVStorage

  - name: create mount directory
    file:
      path: /mnt/lvm
      state: directory

  - name: mount at startup
    lineinfile:
      path: /etc/fstab
      line: '/dev/storage/LVStorage /mnt/lvm ext4 defaults 0 0'
      insertbefore: EOF

  - name: Mounting LVM
    mount:
      path: /mnt/lvm
      src: /dev/storage/LVStorage
      fstype: ext4
      state: present" > storage-playbook.yml
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 6: Create hosts file
create_hosts_file

# STEP 7: create sudo playbook
create_sudo_playbook

# STEP 8: execute sudo playbook with ansible.
# -b to execute as root, -K to ask for password
ansible-playbook -i hosts sudo.yml -b -K
next

# STEP 9: install and setup LVM on storage VM
create_storage_playbook
ansible-playbook -i hosts storage-playbook.yml
next

# STEP 10: create and mount filesystem on storage VM
#mount_LVM
# Skipped. Created playbook instead.
