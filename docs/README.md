# Open hardware centrifuge project
## Towards Polyfuge V2.0
  ::: Git repository

Clone, or download [our repo](https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab) with all the source files.

  :::

A laboratory centrifuge is a piece of laboratory equipment, driven by a motor, which spins liquid samples at high speed. There are various types of centrifuges, depending on the size and the sample capacity. Like all other centrifuges, laboratory centrifuges work by the sedimentation principle, where the centripetal acceleration is used to separate substances of greater and lesser density.
To know more about centrifuges [read here](/SubContent/AboutCentrifuges.md).

## Current design based on Polyfuge V1.0
There are many OH centrifuge designs. For this project we decided to focus on one available open hardware design that was quite comprehensive and complete. This is why we decided to go for [the polyfuge](http://doublegene.com/), developed by doublegene. Find the [repo of Polyfuge V1.0 here](https://github.com/jasonwu2153/Polyfuge-A-DIY-Open-Source-Microcentrifuge-for-Everyone)

## Roadmap for improvements:
- **Design based on Arduino UNO**. We have faced difficulties with the Arduino NANO board specifically
- **Temperature control**. We are adding temperature control with a peltier module and a temperature sensor.
- **Increased speeds**. The current motor is limited in performance with regard to relative centrifuge force.
