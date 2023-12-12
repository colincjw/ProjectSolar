# ProjectSolar – A Sunlight Measurement Device to Promote Healthy Sun Exposure
### Inspired by the film and robot WALL-E, #ProjectSolar is a wearable sunlight-measurement device that reminds its wearer to spend a minimum of 30 minutes in the natural light within a 24-hour period.



## Overview
Exposure to sunlight is a natural and biological source of serotonin and vitamin D, contributors to mood-boosting hormones and bone-building nutrients for the body. With limited mechanisms to measure and keep track of UV exposure (even through the latest technologies), many people do not spend sufficient time outdoors, let alone recognizing the benefits of doing so.

**#ProjectSolar** is a small, portable device operated by an internal power source (battery) that detects, records and centrally keeps track of total time spent in the sun (UV) and otherwise within a 24-hour period. The core component of the internal build is the UV detection module, specifically designed in manufacturing to detect spectrums of UV light naturally emitted by the sun. The data from the reading is transmitted to a self-sustaining program on an Arduino microcontroller, which adds to an arbitrary “solar value” during active exposure and depletes conversely.

Communicating to the user is a series of visual modules – LED light cues – to indicate the “charge level” from zero (minimum exposure) to a full charge (min. 30-min exposure). A secondary blink animation indicates a low-charge warning visually.

While seemingly technical, the objective is to provide a mechanic to measure this element but in a fun, interactive and nostalgic manner to many who grew up with the animated film. Building it as a portable device ensures the user need not be confined to a fixed location and power source, which defeats the purpose of getting them outdoors.

![IMG_0526](https://github.com/colincjw/ProjectSolar/assets/20199609/e0f1ac03-3be7-4d4e-b80b-585f399af0b4)
![IMG_0534](https://github.com/colincjw/ProjectSolar/assets/20199609/e8f4ab34-113c-408d-8248-a306e9c9be98)
![IMG_0535](https://github.com/colincjw/ProjectSolar/assets/20199609/7754315f-c4aa-4a7e-90f9-4f9751a5958d)

## 🔧 Required Hardware

[Functional Components]
 - Nano/Micro-sized microcontroller board (Arduino or equivalent featherboard)
 - 1x micro-JST compatible Lithium-ion Polymer Battery
 - 1x UV Light Sensor Breakout ([recommended](https://www.adafruit.com/product/1918))
 - WS2812 LED Strips or NeoPixel-compatible Strips
	 > 	 *Define quantity accordingly to build*

 
 [Build Components]
 - Outer frame (~ 5" x 5" x 2")
	 > 	 *Recommended materials: Acrylic, PLA*
- Yellow acrylic LED diffusers
 - Rope lace (for wearable lanyard)


## Instructions (for Code)

Load the .ino file onto your code editor or development environment and install the related libraries **including FastLED**.

Change the following code lines:

> #define  NUM_LEDS  **25** --> Adjust according to the number of LEDs in your build

> #define  DATA_PIN  **11** --> Adjust according to the **digital** pin port on your microcontroller

> const int uvSensorPin = **A5**;  --> Adjust according to the **analog** pin port on your microcontroller

> const float uvChargeTime = **0.5** * 60;      --> Adjust according to your desired duration (hours) to charge from 0% to 100%

> const float uvDischargeTime = **23.5** * 60;  --> Adjust according to your desired duration (hours) to discharge from 100% to 0%
