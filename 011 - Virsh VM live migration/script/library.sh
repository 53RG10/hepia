# TP Virtualisation
# 12/01/2022
# Sergio Guarino

# Library files for scripts.
# Contains useful functions and variables.

# -------- VARIABLES -------- #

STORAGE="storage-sergio"
HYP1="hypervisor1-sergio"
HYP2="hypervisor2-sergio"
PASS="hepia"
USER="debian"
NET="mynet"

VM_ARRAY=($STORAGE $HYP1 $HYP2)


# -------- FUNCTIONS -------- #

# Function to pause execution.
next () {
  echo "Done. Press enter to continue."
  read
}

# Getting IP address of VM passed in parameter
get_ip () {
  virsh domifaddr $1 | awk 'NR==3 {print substr( $4, 1, length($4)-3 )}'
}

# Getting MAC address of VM passed in parameter
get_mac () {
  virsh domiflist $1 | awk 'NR==3 {print $5}'
}

# Function to restart all VMs.
restart () {
  for vm in ${VM_ARRAY[@]}; do virsh shutdown $vm; done
  sleep 15
  for vm in ${VM_ARRAY[@]}; do virsh start $vm; done
}
