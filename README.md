# TBE UI redesign spike

This code was created to showcase the use of QML to make a new, rich UI for 
the open source physics puzzle game "The Butterfly Effect"
    http://the-butterfly-effect.org .
It is prototype code, meant to express and validate concepts. Integrating
into the existing TBE project will probably take significant time.

The goals of this "spike":
 * prototype a new, simpler UI
   * using concepts closer to 'Powerpoint' and 'Inkscape'
   * less clicking, more intuitive
 * validate ease-of-use with a few users
 * learn how to use QT's QML
   * learn all about the new declarative approach
   * figure out the minimum Qt version needed
   * learn how to integrate C++ code and QML
   * use as little Javascript as possible
   * learn what's missing in QML and needs to be written in C++
     * undo/redo
     * collision detection
     * coordinate conversions
 * integrate QQuickView into Qt's standard MainWindow layout
 * scale with size of window
 * coordinate conversions
   * introduce DPI singleton that communicates with view
   * enhance Position class
 * conditionals: only show horizontal arrows when hor resizing is allowed
 * collision detection, and how to visualize issues with that
   * collisions with the borders of the view
   * collisions with other objects (note that moves of objects are not taken 
     into account yet)
 * undo/redo
   * should take care of updating the AO and VI for move/resize/rotate

I'll leave it up to you to judge if the above succeeded.

Note that there's another architecture spike, 
https://github.com/kaa-ching/tbe-qml-toolbox-spike , showcasing the new toolbox
and how we want to improve gameplay in the toolbox.

Still to be implemented:
 * delete undo
 * polymorphism
   * butterfly, colamintbottle and penguin require animations
   * postit requires different clicking behavior
   * detonatorbox has a handle that needs to be addressed
 * tooltips
 * segfault when exiting with something selected

kaa-ching, a.k.a. Klaas van Gend

