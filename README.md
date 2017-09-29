# OSG_Qt5

This is an integration of OpenSceneGraph and Qt5, 
good for getting them to work easily together. 
At least how I do it, to have a panel to control the scene 
with Qt signal-slot mechanism, and separating my scene 
completely to extend it as desired.
This is a simple framework which lacks so many functionalities,
but can be easily extended. 
For example, one should probably add menu bar, status bar, icons, etc.
And obviously change the scene.

I am using Qt 5.9, osg 3.4.1, and cmake 3.9. Probably you need to change 
CMakeLists.txt file according to your needs, as I wrote it very specific 
to my system. E.g. one most likely change the cmake version I've put in the first line!

Please share your suggestions. 
