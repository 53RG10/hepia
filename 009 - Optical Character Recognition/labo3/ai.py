#!/usr/bin/env python3

import os

os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"  # ignoring TensorFlow CUDA errors

import numpy as np
from PIL import Image
import tensorflow as tf
from tensorflow import keras
from keras.models import Sequential, load_model
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPooling2D
from typing import *

# Converting array to PIL Image
def pilImg(array: np.ndarray) -> np.ndarray:
    temp_img = np.transpose(array.astype(np.uint8))
    img = Image.fromarray(temp_img)
    return img


# Saving drawed image to folder specified by number entered
def save(img: np.ndarray, num: int) -> None:
    save_path = "dataset/" + str(num)
    if not os.path.exists(save_path):
        os.makedirs(save_path)

    files = len(os.listdir(save_path))  # number of files in folder
    im = pilImg(img)
    im.save(save_path + "/" + str(files) + ".jpeg")

    print("Image saved.")


def initDataset() -> np.ndarray:
    # Import images for dataset
    dataset = keras.preprocessing.image_dataset_from_directory(
        "dataset", color_mode="grayscale", batch_size=128, image_size=(20, 20)
    )

    for data, labels in dataset:
        print(str(data.shape[0]) + " images loaded.")

    return dataset


# Training model
def train(dataset: np.ndarray) -> None:

    for d, l in dataset:
        data = d
        labels = l

    # Image preprocessing
    model = Sequential()
    model.add(
        Conv2D(
            filters=8, kernel_size=(3, 3), activation="relu", input_shape=(20, 20, 1)
        )
    )
    model.add(Conv2D(filters=16, kernel_size=(3, 3), activation="relu"))
    model.add(MaxPooling2D(pool_size=(2, 2)))
    model.add(Flatten())

    # Layers
    model.add(Dense(32, activation="relu"))  # Hidden Layer 1
    model.add(Dense(256, activation="relu"))  # Hidden Layer 2
    model.add(Dense(10, activation="softmax"))  # Output layer

    # Training
    model.compile(
        loss="sparse_categorical_crossentropy", optimizer="adam", metrics=["accuracy"]
    )
    model.fit(data, labels, batch_size=128, epochs=1000, verbose=1)

    # Saving model so no need to train it everytime
    model.save("labo3/trained_network.h5")
    print("Trained model saved in labo3 directory.")


def predict(img: np.ndarray) -> np.ndarray:
    model = load_model("labo3/trained_network.h5")
    im = pilImg(img)
    img_data = tf.keras.preprocessing.image.img_to_array(im)
    test_img = np.array([img_data])
    tf_img = tf.convert_to_tensor(
        test_img
    )  # to avoid warning after submitting 5 images, but still getting it

    prediction = model.predict(tf_img)
    prediction *= 100  # To obtain values in percentage

    return np.round(prediction, 5)
