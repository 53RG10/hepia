#!/usr/bin/python
# -*- coding: utf-8 -*-

# Copyright: (c) 2022, Sergio Guarino <sergio.guarino@etu.hesge.ch>
# GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)

from curses import keyname
from ansible.module_utils.basic import *


def enable(module):
    filename = module.params["file"]
    sig_file = module.params["signed"]
    signature = "--signature=" + sig_file
    rc, out, err = module.run_command(["fsverity", "enable", filename, signature])
    response = {"rc": rc, "out": out, "err": err}
    return response

def signature(module):
    hash = module.params["hash"]
    filename = module.params["file"]
    key = "--key=" + module.params["key"]
    cert = "--cert=" + module.params["cert"]
    signed_file = module.params["signed"]
    rc, out, err = module.run_command(["fsverity", "sign", hash, signed_file, key, cert])
    response = {"rc": rc, "out": out, "err": err}
    return response

def disable(module):
    original = module.params["file"]
    backup = original + ".copy"
    rc, out, err = module.run_command(["cp", original, backup])
    # add exceptions
    rc, out, err = module.run_command(["rm", original])
    # add exceptions
    rc, out, err = module.run_command(["mv", backup, original])
    response = {"rc": rc, "out": out, "err": err}
    return response

def digest(module):
    filename = module.params["file"]
    rc, out, err = module.run_command(["fsverity", "digest", "--compact", filename])
    out = out[:-1] # Removing \n from output
    response = {"rc": rc, "out": out, "err": err}
    return response

def verify(module):
    filename = module.params["file"]
    rc, out, err = module.run_command(["lsattr", filename])
    if "V" in out[:22]:
        response = {"out": "This is a verity file"}
    else:
        response = {"out": "Not a verity file"}
    return response

def main():
    fields = {
        "signature": {"default": False, "required": False, "type": "bool"},
        "enable": {"default": False, "required": False, "type": "bool"},
        "disable": {"default": False, "required": False, "type": "bool"},
        "digest": {"default": False, "required": False, "type": "bool"},
        "verify": {"default": False, "required": False, "type": "bool"},
        "file": {"required": True, "type": "str"},
        "signed": {"required": False, "type": "str"},
        "hash": {"required": False, "type": "str"},
        "key": {"required": False, "type": "str"},
        "cert": {"required": False, "type": "str"},
    }
    module = AnsibleModule(
        argument_spec=fields, supports_check_mode=True
    )  # check_mode sert à pouvoir faire des essais sans rien modifier. pourrait être utilisé pour voir si fs-verity peut être activé.

    if module.params["enable"] == True:
        response = enable(module)

    if module.params["disable"] == True:
        response = disable(module)

    if module.params["signature"] == True:
        response = signature(module)

    if module.params["digest"] == True:
        response = digest(module)
    
    if module.params["verify"] == True:
        response = verify(module)

    result = dict(changed=True, message=response)
    if module.check_mode:
        module.exit_json(**result)

    module.exit_json(**result)


if __name__ == "__main__":
    main()
