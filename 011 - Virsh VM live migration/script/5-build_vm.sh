#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script to build VM to be hosted by Hypervisor.
# The VM is stored in the shared folder on the NFS server.
# This script is to be executed on the STORAGE VM.

. ./library.sh

build_vm () {
  echo "Building VM for Hypervisor on Storage LVM"
  virt-builder debian-11 -o /mnt/lvm/vm.qcow2 \
  --root-password password:$PASS \
  --edit "/etc/network/interfaces: s/ens2/enp1s0/g" \
  --firstboot-command "ip link set enp1s0 up" \
  --firstboot-command "dpkg-reconfigure openssh-server" \
  --hostname vm \
  --timezone Europe/Zurich
}

# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 14: Prepare next steps
echo "Copying script to Storage VM."
chmod +x *.sh
scp 5-build_vm.sh $STORAGE:/home/$USER
scp library.sh $STORAGE:/home/$USER

# STEP 15: Building VM
ansible -i hosts storage -m command -a '/home/debian/5-build_vm.sh'
