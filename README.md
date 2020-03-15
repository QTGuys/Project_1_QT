# Project 1 QT
### Authors
- [Max García](https://github.com/MaxitoSama)
- [Lorién Portella](https://github.com/Witiza)

## Features
# Creating New Shapes
- Select the type of shape that you want to create, can be changed later.
![](https://imgur.com/wo36gvX.png)
# Selecting Shapes
- Press any shape in the hierarchy window, or in the scene window, to select it and display it in the inspector.
![](https://i.imgur.com/yqlJdKG.png)
# General Inspector
- **Name:** Displays the name of the shape selected. Can also be changed.
- **Deleting Shapes:** Press the button to completely delete the selected shape
![](https://i.imgur.com/Of4g89n.png)
# Transform
- **Changing Position:** Use the arrows, the middle button or write another number to change the position. Position can also be changed by dragging the gameobject in the scene.
- **Changing Scale:** Use the arrows, the middle button or write another number to change the components of the scale.
![](https://i.imgur.com/QxyKbJT.png)
# Shape
- **Type:** Switches between the shape types instantly.
- **Colors:** Use both the sliders or the numbers to change the RGB components of the stroke or fill of the shape.
- **Thickness:** Vary the thickness of the stroke of the selected shape.
- **Stroke Style:** Change the type of stroke the selected shape has, or deactivate it.
![](https://i.imgur.com/Mste0ji.png)
# Saving Scenes
- Press the icon or the action from the Scene menu. You can specify the name and place of the 
# Loading Scenes
- Press the icon or the action from the Scene menu. You will be asked if you want to save the current scene before.
![](https://i.imgur.com/E7bCgnU.png)

## Qt Tools
- **Signals and Slots**: To comunicate all the UI with the application, and to comunicate between UI elements, for example, between inspector and scene.
- **Qt XML System**: To save and load scene.
- **Qt Colors and Brushes**: To draw shapes, where each component of the brush can be customized.
- **Qt Sliders and Color Picker**: To change the color. The color display next to the sliders is made with an empty widget with its background color changed
- **Mouse events**: Detecting mouse events and using them to mousepick shapes and to drag them around the scene
