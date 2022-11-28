#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Clean up script to remove all VMs, reset network configuration, remove Ansible playbooks and restore ssh config file.

. ./library.sh

# Function to delete VM from network
delete_host () {
  IP=$(get_ip $1)
  MAC=$(get_mac $1)
  virsh net-update $NET delete ip-dhcp-host "<host mac='$MAC' name='$1' ip='$IP'/>" --live --config
}

# Function to delete VM and their storage.
delete_VM () {
  virsh destroy $1
  virsh undefine $1 --remove-all-storage
}

# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

for vm in ${VM_ARRAY[@]}; do
  delete_host $vm;
  delete_VM $vm;
done

rm /home/debian/.ssh/config
mv /home/debian/.ssh/config.old /home/debian/.ssh/config

rm -f *.yml
rm hosts

echo "All files and VMs have been deleted."
