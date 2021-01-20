# Readme  Hardware Code

## Diagrams

>**Note**
>
> The diagrams shown here, are made using the [C4 model](https://c4model.com/).
> 
> Also, the code diagrams will not be shown. We will provide you directly with the code.

### (C1) Context Diagram
![Context diagram for the ESP32 driven dartboard](./images/ContextDiagram.jpg)
>**Note**
>
>These diagrams are written in Dutch. I will do my best to translate them to English correctly.

#### Context overview
In the middle we see our "ESP32 drive electronical dartboard". To the left of the "ESP32 drive electronical dartboard" we see "Players". To the right, wee see "External code libraries." To the top, we see "OpenRemote web application".

*Players interact with the dartboard, throwing darts. No technologies are used for this.
*The ESP32 driven dartboard, will use external code libraries, to make use of the TTGO-T-Display(mounted on the ESP32), the MCP23017 I/O Extender and the Bluetooth Antenne (mounted on the ESP32).
*The Esp32 driven dartboard will also send hit-scan data of darts thrown to OpenRemote. (Using Bluetooth Low Energy)
*OpenRemote will also send data to the ESP32 driven dartboard when needed. (Using Bluetooth Low Energy)

### (C2) Container Diagram Esp32 Driven Dartboard
![Container diagram for the ESP32 Driven Dartboard](./images/ContainerDiagramEsp32.jpg)