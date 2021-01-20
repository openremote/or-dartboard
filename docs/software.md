# Software

The software stack is based on three main components

* BLE client protocol support (PoC) for OpenRemote
* Game logic server
* ESP32 BLE server

### OpenRemote BLE client support

Because OpenRemote v3, as of [release v1.0.4](https://github.com/openremote/openremote/releases/tag/v1.0.4), does not have support for Bluetooth communication, we also worked on developing a proof of concept for adding Bluetooth Low Energy support to OpenRemote.

The new Bluetooth Low Energy protocol can be setup by creating a protocol configuration on an Agent asset, like most other protocols. In the BLE protocol configuration, you can configure the Bluetooth Hardware address to connect to. Once this is configured, OpenRemote will start scanning for this hardware address and connect to the device once it is detected.

Much like other protocols in OpenRemote, to read/write data to and from the Bluetooth device you can setup a new asset, add attributes and link the attributes to the device using an agent protocol link. As the BLE-equivalent of OpenRemote attributes are BLE characteristics, you can configure the UUID of the BLE service & characteristic to link the attribute to. Once this is configured, the OpenRemote attribute should be updated with the latest value of the Bluetooth characteristic and any writes to the attribute should also be written to the characteristic of the Bluetooth device.

The changes made to OpenRemote to add BLE support can be found in [this OpenRemote fork](https://github.com/raqbit/openremote).

### Game logic server

The game logic "server" (which is actually a client of sorts) is an external application connected to the same instance of OpenRemote as the dartboards. With MQTT the application listens for updates on the assets of the dartboard units and will write back changes to the dartboards' displays. This way all logic is separate from the dartboards which means the dartboards are themselves "dumb" and can be used for different things alongside games of darts.

The code for the game logic server can be found [here](../gamelogic).

### ESP32 BLE server

The ESP32 on the TTGO T-Display is responsible for handling bluetooth communication with the hardware, like sending updates for dart hits and updating scores on the display. We designed the underlying protocol to be as generic as possible, to make it easy to add other games or (ab)use the dartboard for non-game automations, like for example turning the lights on when someone throws a bulls-eye.

All code which runs on the ESP32 can be found [here](../esp32).