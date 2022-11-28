#!/usr/bin/env python3

'''
    Projet d'orientation
    21/06/2021
    
    Code de communication avec la carte GPS/LoRa HAT connectée au Raspberry Pi. 
    Vérifier que le port série ci-dessous est correct et le changer si nécessaire.

    Axel Ava
    Sergio Guarino
    Marc Savioz
'''

import time, serial, math

ser = serial.Serial(
    port="/dev/ttyS0",
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

# Retrieving coordinates from GPS
def getCoordinates():
    data_ok = False
    while not data_ok:
        x=ser.readline()
        raw_data = x.decode("utf-8")
        if "GPGGA" in raw_data:
            data_ok = True
            data = raw_data.split(",")
            time = data[1]
            lat = data[2]
            lat_dir = data[3]
            lon = data[4]
            lon_dir = data[5]
            alt = data[9]
            
            coordinates = data[2:6]
            latitude = data[2:4]
            longitude = data[4:6]
            
            return latitude, longitude, coordinates

# calculating distance between two points on the Earth. Using haversine formula
def getDistance(coord1, coord2):
    R = 6372800  # Earth radius in meters
    lat1, lon1 = coord1
    lat2, lon2 = coord2

    phi1, phi2 = math.radians(lat1), math.radians(lat2) 
    dphi       = math.radians(lat2 - lat1)
    dlambda    = math.radians(lon2 - lon1)

    a = math.sin(dphi/2)**2 + math.cos(phi1)*math.cos(phi2)*math.sin(dlambda/2)**2
        
    distance = 2*R*math.atan2(math.sqrt(a), math.sqrt(1 - a))

    return distance
