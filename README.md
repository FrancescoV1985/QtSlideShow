# QtSlideShow


## Introduction

A GUI application is to be created that reads images from a directory, processes them and then displays
them on the GUI in a “slide show”.

## Functional requirements

### RQ_1
The GUI of the application shall include the following elements:
- The main window is resizable
- A title for the application
- Controls for “Minimize”, “Maximize” and “Close”
- The actual image of the “slide show”
- A button “Define image folder”, which allows the user to define a folder for the images
- Button(s) “Start”/”Stop” which allows the user to start stop the slide show.
It is possible to combine the start/stop functionality in one button
- A combo box for selecting the mirror mode, following modes shall be available:
o “none”
o “horizontal”
o “vertical”
o “both”

### RQ_2
If the user defines a file folder by using the “Define image folder” button, application
automatically scans for supported image files in the defined folder.
### RQ_3
The following image file formats shall be supported:
- .jpg
- .tiff
- .bmp

### RQ_4
The application shall load, process and display a new image every 2 seconds.
Optional: The update time is selectable by the user.

### RQ_5
The image processing task shall mirror the loaded image data.
The following modes shall be supported:
- “none” - no image processing
- “horizontal” – mirroring of the image on the horizontal
- “vertical” – mirroring of the image on the vertical
- “both” – mirroring of the image in both directions

### RQ_6
The image processing/mirroring mode shall be selectable by the user.

## Non-functional requirements

### RQ_1
The application shall be compatible with Windows 10 and Linux (Ubuntu).

### RQ_2
The application shall be written with C++ and QT. C++17 or higher shall be use.

### RQ_3
CMake shall be used for the build configuration of the project.

### RQ_4
To prevent the GUI from blocking, the images shall be read and processed in a separate
(background) thread.
