import cv2
import numpy as np

# Define the lower and upper bounds for the red and green colors
red_lower = np.array([0, 50, 50])
red_upper = np.array([10, 255, 255])
green_lower = np.array([30, 50, 80])
green_upper = np.array([70, 255, 255])

# Initialize the video capture device
cap = cv2.VideoCapture(0)

while True:
    # Read a frame from the video capture device
    ret, frame = cap.read()

    # Convert the frame from the BGR color space to the HSV color space
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create binary images by thresholding the HSV frame using the lower and upper bounds for the red and green colors
    red_mask = cv2.inRange(hsv_frame, red_lower, red_upper)
    green_mask = cv2.inRange(hsv_frame, green_lower, green_upper)

    # Find the contours in the binary images
    red_contours, red_hierarchy = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    green_contours, green_hierarchy = cv2.findContours(green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Find the contour with the largest area for each color
    max_red_area = 0
    max_red_contour = None
    max_green_area = 0
    max_green_contour = None

    for contour in red_contours:
        area = cv2.contourArea(contour)
        if area > max_red_area:
            max_red_area = area
            max_red_contour = contour

    for contour in green_contours:
        area = cv2.contourArea(contour)
        if area > max_green_area:
            max_green_area = area
            max_green_contour = contour

    # Draw the contour with the largest area for each color on the frame and calculate the center coordinate of the contour
    if max_red_contour is not None:
        cv2.drawContours(frame, [max_red_contour], -1, (0, 0, 255), 2)
        red_moments = cv2.moments(max_red_contour)
        red_cx = int(red_moments['m10'] / red_moments['m00'])
        red_cy = int(red_moments['m01'] / red_moments['m00'])
        cv2.circle(frame, (red_cx, red_cy), 5, (0, 0, 255), -1)
        print("Red Contour Midpoint: ({}, {})".format(red_cx, red_cy))
        if red_cx < int(frame.shape[1] / 2):
            print("Red Contour Midpoint is on the Left")
        else:
            print("Red Contour Midpoint is on the Right")

    if max_green_contour is not None:
        cv2.drawContours(frame, [max_green_contour], -1, (0, 255, 0), 2)
        green_moments = cv2.moments(max_green_contour)
        green_cx = int(green_moments['m10'] / green_moments['m00'])
        green_cy = int(green_moments['m01'] / green_moments['m00'])
        cv2.circle(frame, (green_cx, green_cy), 5, (0, 255, 0), -1)
        print("Green Contour Midpoint: ({}, {})".format(green_cx, green_cy))
        if green_cx< int(frame.shape[1] / 2):
            print("Green Contour Midpoint is on the Left")
        else:
            print("Green Contour Midpoint is on the Right")

    # Display the frame with the contours and the center coordinates
    cv2.imshow('frame', frame)

    # Wait for a key press to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the video capture device and close all windows
cap.release()
cv2.destroyAllWindows()