#!/usr/bin/env python3

import cv2 as cv
import numpy as np
import sys, os
import matplotlib, matplotlib.pyplot as plt
from typing import *


# video_path = "data/wheel_racing.avi"
output_file = "data/angles.txt"

# Deleting previously generated file
if os.path.exists(output_file):
    os.remove(output_file)

# HSV values for inRange function
yellow_hsv_low = (15, 50, 0)
yellow_hsv_high = (36, 255, 255)
red_hsv_low = (160, 100, 0)
red_hsv_high = (180, 220, 255)

# Colors
white = (255, 255, 255)

# For imshow function
matplotlib.use("tkagg")

# Function that returns an 2D array of ones of the size defined in input
def kernel(size: int) -> np.ndarray:
    return np.ones((size, size), np.uint8)


# function to extract a specific color from an image.
def extract_color(
    img: np.ndarray, low: Tuple[int, int, int], high: Tuple[int, int, int]
) -> np.ndarray:
    mask = cv.inRange(img, low, high)

    # test_kernel = np.array([
    # [0, 0, 1, 0, 0],
    # [0, 1, 1, 1, 0],
    # [1, 1, 1, 1, 1],
    # [0, 1, 1, 1, 0],
    # [0, 0, 1, 0, 0]]
    # ).astype('uint8')

    # Using different kernels in case we want to test with different kernel sizes and shapes

    eroding_kernel = kernel(5)
    eroded_mask = cv.erode(mask, eroding_kernel, iterations=1)

    closing_kernel = kernel(5)
    closed_mask = cv.morphologyEx(eroded_mask, cv.MORPH_CLOSE, closing_kernel)

    opening_kernel = kernel(5)
    open_mask = np.array(0).astype("uint8")
    open_mask = cv.morphologyEx(closed_mask, cv.MORPH_OPEN, opening_kernel)

    return open_mask


# Function to get center of mass of the biggest object in an image
def get_center_of_mass(img: np.ndarray) -> Tuple[int, int]:

    contours, hierarchy = cv.findContours(img, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    try:
        contours = max(contours, key=cv.contourArea)
    except ValueError:
        return (1, 1)

    M = cv.moments(contours)
    x = int(M["m10"] / M["m00"])
    y = int(M["m01"] / M["m00"])

    return (x, y)


# Saving data to a file
def save(data: int) -> None:
    with open(output_file, "a") as f:
        f.write(str(data) + "\n")


# Extrapolating angle of line in relation to the horizon.
# Input: two points belonging to the line
def angle(p1: Tuple[int, int], p2: Tuple[int, int]) -> int:

    x1, y1 = p1
    x2, y2 = p2

    if x2 != x1:
        alpha = int(np.arctan((y1 - y2) / (x2 - x1)) * 180 / np.pi)
    else:
        alpha = 0

    return alpha


def draw_plot() -> None:
    plt.ion()  # to close plot automatically
    print("Plotting data. The plot will close automatically after 10 seconds. Or press q to quit.")
    y_data = []
    x_max = 0
    with open(output_file, "r") as f:
        print()
        for lines in f:
            y_data.append(int(lines))
            x_max += 1

    x_data = np.arange(0, x_max, 1)

    plt.ylim([-90, 90])
    plt.xlim([0, x_max])

    xticks = np.arange(0, x_max + 1, 150)
    yticks = np.arange(-90, 91, 15)
    plt.yticks(yticks)
    plt.xticks(xticks)

    plt.title("Angles plot")
    plt.xlabel("Frame number")
    plt.ylabel("Angle [°]")

    plt.plot(x_data, y_data)
    plt.show()
    plt.pause(10)
    plt.close()


# Main function
def run(vid_fn: str, interval: int) -> None:
    print(
        "Showing video. The plot with the angles will be shown at the end.\nPress q to stop the video at any moment."
    )
    video = cv.VideoCapture(vid_fn)

    while True:
        ret, bgr_img = video.read()
        if not ret:
            break

        # Converting image to HSV color space
        hsv_img = cv.cvtColor(bgr_img, cv.COLOR_BGR2HSV)

        # Extracting shapes of specific color from frame
        yellow_mask = extract_color(hsv_img, yellow_hsv_low, yellow_hsv_high)
        red_mask = extract_color(hsv_img, red_hsv_low, red_hsv_high)

        # Applying result of extraction on video
        mask = cv.bitwise_or(yellow_mask, red_mask)
        masked_img = cv.bitwise_and(bgr_img, bgr_img, mask=mask)

        line_img = masked_img.copy()

        # Calculating center of mass and drawing result
        red_center = get_center_of_mass(red_mask)
        yellow_center = get_center_of_mass(yellow_mask)
        cv.circle(line_img, red_center, 4, white, -1)
        cv.circle(line_img, yellow_center, 4, white, -1)
        cv.line(line_img, red_center, yellow_center, white, 2)

        # Calculating angle and saving to file
        a = angle(red_center, yellow_center)
        save(a)

        # Showing videos
        # cv.imshow("Mask video", np.hstack((yellow_mask, red_mask)))
        cv.imshow("Output video", np.hstack((bgr_img, line_img)))

        # Showing a frame each 20 milliseconds
        # Press q to quit
        if cv.waitKey(interval) & 0xFF == ord("q"):
            break

    video.release()
    cv.destroyAllWindows()
    draw_plot()
    print("Simulation ended.")


if __name__ == "__main__":
    try:
        video_path = sys.argv[1]
    except IndexError:
        print(
            "Missing argument. Usage:\npoetry run labo2/gamepad.py data/wheel_racing.avi"
        )
        exit(1)

    try:
        interval = sys.argv[2]
        try:
            t = int(interval)
        except ValueError:
            print("Error with interval. Using default at 10ms.")
            t = 10
    except IndexError:
        print("Interval not set. Using default at 10ms.")
        t = 10

    if os.path.exists(video_path):
        root, ext = os.path.splitext(video_path)
        if ext == ".avi" or ext == ".mp4":
            run(video_path, t)
        else:
            print("Only .avi or .mp4 videos are accepted. Please choose another file.")
    else:
        print(
            "Video not found. Please don't forget to upload a video in the data folder.\nAccepted formats: .avi, .mp4"
        )
        exit(1)

    exit(0)
