# Halloween2017
Dev Repo for my Halloween costume in 2017

The costume is a cyberpunk get-up.
The main technological aspect of the costume is a hal-face mask. The mask contains a piezoelectric transducer mounted in front of the mouth, which detects the volume of my speech. Two columns of LEDs are lit front bottom to top as a function of the volume, much like an EQ visualization. Other LEDs will also light up the mask but will remain static. The logic is powered by an Arduino.

On the hardware side, the analog output of the Piezo requires amplification, in this case an LM358 in a constant gain configuration. This is necessary to increase the resolution of the sensor.

On the software side, the primary goal is to make the eq rise and fall gracefully as I speak into the mask. Thus, the LED columns should light up when I speak, but not fall down immediately, but rather come down one by one (a "waterfall" effect).

## Completed:
* Proof of concept:
** Piezo circuit generates voltage, arduino can read analog data
** LEDs can be lit in response to piezo voltage level

## To do:
* Implement amplifier for piezo to increase resolution
* Implement smoothing of LED output in software; either:
** Running average filter; or
** Some count-based decay function.
** Tradeoff: running average filter increases simplicity of code structure, but introduces delay in the actual ouput; count-based decay allows for instantaneous output with a decaying output (superseded by any greater input), but makes the code much more difficult to implement. The way I imagine doing it would require creating wrapper classes for the LED columns, implementing some form of persistent knowledge of which is the top-most lit LED. 
* Make schematic
* Solder protoboard
* Assemble costume
