#!usr/bin/env python3

'''
    Projet d'orientation
    21/06/2021
    
    Code principal pour la récupération des données GPS et du microphone pour envoi au réseau LoRaWAN. 

    Axel Ava
    Sergio Guarino
    Marc Savioz
'''

import micro
import gps
import lora
import numpy as np


def microphoneData():
	raw = micro.getRawData()
	max_value = np.max(raw)
	min_value = np.min(raw)
	data, avg = micro.processData(raw)
	
	sound = max_value - min_value
	# print(sound)
	# print(max_value)
	# print(min_value)
	
	if (sound < 1000):
		noise = "low"
	elif (sound < 5000):
		noise = "medium"
	else:
		noise = "high"

	# value = max_value - avg
	max_dB = micro.getdB(max_value)
    min_dB = micro.getdB(min_value)
	avg_dB = micro.getdB(avg)
    
	return max_dB, min_dB, avg_dB



if __name__ == "__main__":
    
	max_dB, min_dB, avg_dB = microphoneData()
    sound = [max_dB, min_dB, avg_dB]
	lat, lon, position = gps.getCoordinates()
	data_sent = False
    count = 0
	
	while not data_sent:
		if lora.ready():
            if count == 0:
                lora.send(str(sound))
                count = 1
                
            elif count == 1:
                lora.send(str(lat))
                count = 2
                
            elif count == 2:
                lora.send(str(lon))
                count = 0
                data_sent = True
                
        # check if device has been moved more than 100 meters   
        lat, lon, new_pos = gps.getCoordinates()
        if getDistance(position, new_pos) > 100:
            lora.send("Alarm.")