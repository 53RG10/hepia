#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script to install virsh on VMs using Ansible.

. ./library.sh

create_hypervisor_playbook () {
  echo "---
- name: install virsh
  hosts: all
  become: yes
  tasks:
  - name: install vmhost libvirt packages
    apt:
      install_recommends: no
      pkg:
        - qemu-kvm
        - libvirt-daemon-system
        - libvirt-clients
        - bridge-utils
        - virtinst
        - libguestfs-tools
        - virt-viewer
        - gpg
        - dnsmasq
        - ncat
        - gpg-agent

  - name: install optional package
    apt:
      install_recommends: no
      pkg:
        - screen
        - htop

  - name: add user debian to libvirt groups
    user:
     name: debian
     groups:
        - libvirt
        - libvirt-qemu
        - kvm
     append: yes

  - name: configure hypervisor URL
    lineinfile:
      path: '/home/debian/.bashrc'
      line: export LIBVIRT_DEFAULT_URI='qemu:///system?socket=/var/run/libvirt/libvirt-sock'
      insertbefore: EOF" > hypervisor-playbook.yml
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 11: create and execute hypervisor playbook
create_hypervisor_playbook
ansible-playbook -i hosts hypervisor-playbook.yml
