#!usr/bin/env python3

'''
    Projet d'orientation
    21/06/2021
    
    Code de communication avec le microphone connecté via un ADC en I2C au Raspberry Pi.
    Changer le nombre de SAMPLES et le RATE pour plus de précision ou des enregistrements de durée différente.

    Axel Ava
    Sergio Guarino
    Marc Savioz
'''


import time, board, busio
import adafruit_ads1x15.ads1015 as ADS
from adafruit_ads1x15.ads1x15 import Mode
from adafruit_ads1x15.analog_in import AnalogIn
import numpy as np


# Function to get microphone values
def getRawData():
    print("Setting up ADC and microphone...")
    # I2C setup
    i2c = busio.I2C(board.SCL, board.SDA, frequency=1000000)
    ads = ADS.ADS1015(i2c)

    # ADC Configuration
    RATE = 250 # 4ms
    SAMPLES = 15000 # 1 minute
    chan0 = AnalogIn(ads, ADS.P0) # channel A0
    ads.mode = Mode.CONTINUOUS
    ads.data_rate = RATE


    _ = chan0.value

    sample_interval = 1.0 / ads.data_rate # 4 ms

    data = np.empty(SAMPLES) # Output array

    start = time.monotonic()
    time_next_sample = start + sample_interval

    print("Set up done. Listening...")
    # Read the same channel over and over
    for i in range(SAMPLES):
        # Wait for expected conversion finish time
        while time.monotonic() < time_next_sample:
            pass

        # Read conversion value for ADC channel
        data[i] = chan0.value
        # print(chan0.value)
        
        # Loop timing
        time_last_sample = time.monotonic()
        time_next_sample = time_next_sample + sample_interval
        if time_last_sample > (time_next_sample + sample_interval):
            time_next_sample = time.monotonic() + sample_interval
    print("Sampling finished. Returning data.")
    saveData(data, "raw.txt")
    return data


# Function to save data to file
def saveData(data, filename):
    print("Saving data to file " + filename + ".")
    with open(filename,"w") as f:
        for v in data:
            f.write(str(v)+"\n")


# Filtering raw data
def processData(raw_data):
    print("Processing raw data...")
    # Step 1: calculating average
    avg = np.average(raw_data)
    
    # Step 2: calculating RMS
    RMS = np.sqrt(np.square(raw_data - avg))
    RMS = np.round(RMS, 8) # rounding values
    saveData(RMS, "rms.txt")
    
    print("Processing done.")
    return RMS, avg

# Converting data to dB
def getdB(value):    
    return round(value * 0.01 + 40, 3) # formula extracted from calibration
