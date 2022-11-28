#!/usr/bin/env bash

# TP Virtualisation
# 12/01/2022
# Sergio Guarino

. ./library.sh

# Function to fix IP address of VM in dhcp range of network interface
set_ip () {
  IP=$(get_ip $1)
  MAC=$(get_mac $1)
  virsh net-update $NET add ip-dhcp-host "<host mac='$MAC' name='$1' ip='$IP'/>" --live --config
  echo "$1 IP: $IP"
}

# Shutdown network interface of specific VM
if_down () {
  MAC=$(get_mac $1)
  virsh domif-setlink $1 $MAC down
}

# Start network interface of specific VM
if_up () {
  MAC=$(get_mac $1)
  virsh domif-setlink $1 $MAC up
}

# Copying public ssh key into VMs.
ssh_config () {
  IP=$(get_ip $1)
  #echo -e "\n$IP $1" >> /etc/hosts
  echo "Host $1
  Hostname $IP
  User $USER
  Port 22" >> /home/debian/.ssh/config

  ssh-copy-id -i /home/debian/.ssh/id_rsa $1
}


# ------------------------------------------------------
# Program starts here.
# ------------------------------------------------------

# STEP 3: Adding VMs to virt host file
echo "Setting IPs."
for vm in ${VM_ARRAY[@]}; do set_ip $vm; done
echo "Restarting network interfaces."
for vm in ${VM_ARRAY[@]}; do if_down $vm; done
sleep 5
for vm in ${VM_ARRAY[@]}; do if_up $vm; done
next

# STEP 4: Verify xml (optional)
virsh net-dumpxml $NET | grep sergio

# STEP 5: SSH config
echo "Configuring ssh access."
# Copy existing configuration if needed. 
# Better way: add lines and remove them in clean.sh script.
mv /home/debian/.ssh/config /home/debian/.ssh/config.old
for vm in ${VM_ARRAY[@]}; do ssh_config $vm; done
next
