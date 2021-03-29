# hovercraft
simple hovercraft controlled by a 433MHz radio module pair

the controller reads from a potentiometer and a button, latches the button, then converts them both into a numerical array that subsequently gets sent through the radio module using manchester encoding library

the hovercraft reads the numbers, tweaks the potentiometer value a bit, then controlls the two fans accordingly.
