#!/usr/bin/env python3

'''
    Projet d'orientation
    21/06/2021
    
    Code de communication avec la carte Waspmote pour la transmission LoRa. 
    La carte est connectée en USB à un Raspberry Pi.
    Vérifier que le port série ci-dessous est correct et le changer si nécessaire.

    Axel Ava
    Sergio Guarino
    Marc Savioz
'''


import time, serial

ser = serial.Serial(
    port="/dev/ttyUSB0",
    baudrate = 115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)


def ready():
    data_ok = False
    
    while not data_ok:
        x=ser.readline()
        raw_data = x.decode("utf-8")
        print(raw_data)
        if "Waiting for message" in raw_data:
            data_ok = True
            return True
        else:
            return False

def send(data):
    time.sleep(2)
    ser.write(data.encode())
    print("Message sent: " + data)
    
def read():
    while True:
        x=ser.readline()
        raw_data = x.decode("utf-8")
        print(raw_data)
