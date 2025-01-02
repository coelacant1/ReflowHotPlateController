# ReflowHotPlateController

An Arduino-based reflow hot plate controller that leverages a **MAX31850K** or MAX31856 thermocouple sensor, an **AC Solid-State Relay (SSR)**, and a 16×2 I2C display. This controller monitors temperature using a K-type thermocouple and applies or cuts power to a hot plate according to predefined reflow curves. It is useful for low-cost, DIY reflow soldering or for controlling solder reflow temperature profiles on a hot plate.

## Features

- **Temperature Sensing**: Monitors real-time temperature with the MAX31856 or MAX31850K chip and a K-type thermocouple.
- **AC SSR Control**: Activates and deactivates the SSR to regulate hot plate temperature.
- **Multiple Reflow Profiles**: Includes built-in reflow curves (e.g., SMD291AX, SMD291SNL, SMDLTLFP) for different solder paste requirements.
- **16×2 I2C Display**: Displays current status, selected profile, and run-time temperature data.
- **User Interface**: 
  - A **potentiometer** to select the reflow curve.
  - A **push-button** to navigate through the controller's menu.

## Hardware Requirements

1. **Arduino Board** (e.g., Arduino UNO)
2. **MAX31856 or MAX31850K** thermocouple amplifier
3. **K-Type Thermocouple** (suitable for reflow temperatures up to ~300°C)
4. **AC Solid State Relay (SSR)** with a corresponding load capacity
5. **16×2 I2C LCD Display** (optional, but recommended for stand-alone use)
6. **Potentiometer** and **Button** (for user input)
7. **Power Supply** and wiring appropriate for the hot plate

## Wiring Overview

- **Thermocouple Amplifier**  
  - Connect the thermocouple to the MAX31856 / MAX31850K.  
  - SPI lines (MISO, MOSI, SCK) go to Arduino digital pins (11, 12, 13 by default).  
  - Chip select pin on the amplifier goes to Arduino digital pin 10.

- **AC SSR**  
  - Control pin from Arduino digital pin 3 to the SSR input.  
  - SSR output connected to the hot plate AC line in accordance with SSR specifications.

- **Potentiometer**  
  - Middle pin to Arduino analog input A0.  
  - Outer pins to 5V and GND.

- **Button**  
  - Digital input pin (e.g., pin 2).  
  - Typically configured with an internal pull-up or external resistor.

- **LCD (16×2 I2C)**  
  - Connect SDA and SCL to Arduino SDA/SCL pins (A4/A5 on an Uno, or dedicated SDA/SCL pins on newer boards).  
  - Provide 5V (or 3.3V, depending on the display) and GND.

## Usage
1. Set Up PlatformIO Project
  - Create or open a PlatformIO project for your microcontroller (e.g., Arduino-based board).
  - In your project’s platformio.ini file, specify the board, framework, and any additional library dependencies.
2. Add Required Libraries
  - Place custom libraries (e.g., ButtonHandler, HeaterHandler, TemperatureHandler, etc.) in a lib folder under your PlatformIO project.
  - Confirm external libraries (such as MAX31856 support) are referenced either in platformio.ini (under [env:your_board] → lib_deps) or directly in the lib folder.
3. Build and Upload
  - Open a terminal in your project directory.
  - Run: ''' pio run ''' to build the code.
  - Connect your board and upload the firmware using: ''' pio run --target upload '''
4. Monitor the Controller
  - After uploading, you can start the serial monitor to see debugging information (baud rate: 38400) with: ''' pio device monitor '''
  - Adjust the potentiometer to select a reflow curve.
  - Use the button to navigate between screens and begin the reflow process.
5. Hot Plate Operation
  - The SSR (connected to digital pin 3 by default) controls power to the hot plate, switching on/off to follow your chosen reflow profile.

## Contributing

1. **Fork** this repository.  
2. **Create** a feature branch (e.g. `feature/my-new-feature`).  
3. **Commit** your changes and open a **pull request**.

## License

This project is provided as-is with no specific license. If you use or modify the code, please retain appropriate credit.
