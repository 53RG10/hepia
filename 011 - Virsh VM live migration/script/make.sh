#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Makefile to execute all scripts one after the other.

# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

./0-install.sh
./1-ip_conf.sh
./2-storage_conf.sh
./3-hypervisor_conf.sh
./4-nfs.sh
./5-build_vm.sh
./6-install_vm.sh

echo "Program finished. Run ./clean.sh to clean up files and VMs."
