#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Script to build and install VMs

. ./library.sh

build () {
  echo "Building image file $1"
  virt-builder debian-11 -o $1.qcow2 \
  --root-password password:$PASS \
  --install "sudo" \
  --edit "/etc/network/interfaces: s/ens2/enp1s0/g" \
  --firstboot-command "ip link set enp1s0 up" \
  --firstboot-command "useradd -m -p $(echo $PASS | openssl passwd -stdin) -s /bin/bash $USER" \
  --firstboot-command "usermod -aG sudo $USER" \
  --firstboot-command "sed '/root/a $USER  ALL=(ALL) NOPASSWD:ALL' /etc/sudoers" \
  --firstboot-command "dpkg-reconfigure openssh-server" \
  --hostname $1 \
  --timezone Europe/Zurich
}

install_storage () {
  echo "Installing storage VM."
  virt-install \
  --name $1 \
  --ram 8192 \
  --vcpus 2 \
  --disk path=$1.qcow2,format=qcow2,size=6 \
  --disk path=disk1.qcow2,format=qcow2,size=10 \
  --disk path=disk2.qcow2,format=qcow2,size=10 \
  --os-variant debian10 \
  --network network=$NET \
  --cloud-init ssh-key=/home/debian/.ssh/id_rsa.pub \
  --graphics none \
  --noautoconsole \
  --import
}

install_hypervisor () {
  echo "Installing $1"
  virt-install \
  --name $1 \
  --ram 8192 \
  --vcpus 4 \
  --disk path=$1.qcow2,format=qcow2,size=8 \
  --os-variant debian10 \
  --network network=$NET \
  --cloud-init ssh-key=/home/debian/.ssh/id_rsa.pub \
  --graphics none \
  --noautoconsole \
  --import
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 1: Downloading and preparing image.
for vm in ${VM_ARRAY[@]}; do build $vm; done
next

# STEP 2: Installing VMs
install_storage $STORAGE
install_hypervisor $HYP1
install_hypervisor $HYP2
echo "Pausing a few seconds to let VMs boot"
sleep 30
echo "Done."
