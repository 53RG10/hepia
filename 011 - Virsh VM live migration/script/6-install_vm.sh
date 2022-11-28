#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script to install VM to be hosted by Hypervisor.
# The VM image is stored in the shared folder on the NFS server.
# This script is to be executed on the HYPERVISOR VM.

. ./library.sh

install_vm () {
  echo "Installing VM"
  virt-install \
  --name vm \
  --ram 4096 \
  --vcpus 2 \
  --disk path=/mnt/nfs/vm.qcow2,format=qcow2,size=6 \
  --os-variant debian10 \
  --network network=$NET \
  --graphics none \
  --noautoconsole \
  --import
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 16: Coyping script to Hypervisor 1
echo "Copying script to Hypervisor 1."
chmod +x *.sh
scp 6-install_vm.sh $HYP1:/home/$USER
scp library.sh $HYP2:/home/$USER

# STEP 17: Installing VM
ansible -i hosts storage -m command -a '/home/debian/6-install_vm.sh'
