---

# Web Radio Project

This project demonstrates how to create a simple web radio streaming application using an **ESP32** that connects to a Wi-Fi network and plays MP3 audio streams. It uses the **MAX98357A** I2S audio amplifier module to output audio. The ESP32 is used to stream audio from an internet radio station and send it to the MAX98357A via I2S protocol.

## Features

- **Wi-Fi Connectivity**: Connects to a Wi-Fi network for internet access.
- **MP3 Streaming**: Streams MP3 audio from an internet radio station.
- **Audio Output**: Outputs audio to a speaker using the **MAX98357A** I2S audio amplifier module.
- **Mono Output**: Audio is output in mono by default for simplicity.

## Requirements

- **Hardware**:  
  - **ESP32** or compatible board
  - **MAX98357A** I2S audio amplifier module
  - Speaker (compatible with MAX98357A)
  - Wi-Fi network for internet access

- **Software**:  
  - **Arduino IDE** (or compatible environment)
  - Libraries:
    - `WiFi` library for connecting to the network
    - `AudioGeneratorMP3` library for MP3 decoding
    - `AudioFileSourceHTTPStream` library for streaming audio over HTTP
    - `AudioOutputI2S` library for sending audio data to an I2S output device

## MAX98357A Module

The **MAX98357A** is a low-power, high-quality I2S audio DAC (Digital to Analog Converter) with integrated amplification, which makes it perfect for driving speakers directly from your ESP32.

### Key Features:
- **I2S Interface**: The MAX98357A communicates with the ESP32 over I2S, which is an industry-standard audio protocol.
- **Built-in Amplifier**: The MAX98357A includes a built-in class D amplifier, so you can drive speakers directly without needing an external amplifier.
- **Mono or Stereo Output**: The module is configured for mono output, but you can modify it for stereo output if needed.
- **Power Supply**: Typically powered by 5V DC (ensure your ESP32 and the MAX98357A module are powered properly).

### Wiring:
- The **MAX98357A** connects to the ESP32 via I2S pins (Bit Clock, Left-Right Clock, and Data Out), along with a 5V power supply.
- This module has a **mono output** and works well with small to medium speakers.

## Installation

1. **Install the required libraries** in the Arduino IDE:
   - `Audio`
   - `WiFi`
   You can install them through the Arduino Library Manager (`Sketch` -> `Include Library` -> `Manage Libraries`).

2. **Upload the code** to your ESP32:
   - Open the Arduino IDE.
   - Select your ESP32 board and the correct port.
   - Copy the code provided below into a new Arduino sketch.
   - Click **Upload**.

3. **Modify your Wi-Fi credentials**:
   - Replace `SSID` and `PASSWORD` with your own Wi-Fi network credentials in the code.

4. **Connect your audio hardware**:
   - Connect the **MAX98357A** to your ESP32 using the I2S pins.
   - Ensure proper power supply connections (5V to VCC, GND to ground).

## Wiring for MAX98357A and ESP32

| **ESP32 Pin** | **MAX98357A Pin** |
|---------------|-------------------|
| GPIO 26       | BCLK              |
| GPIO 25       | LRC               |
| GPIO 22       | DOUT              |
| 3.3V          | VCC               |
| GND           | GND               |

Note: These are the default pins used in the code. You can adjust them if your setup requires different pins.

## Code

```cpp
#include <WiFi.h>
#include <AudioGeneratorMP3.h>
#include <AudioFileSourceHTTPStream.h>
#include <AudioOutputI2S.h>

const char* ssid = "SSID";    // Replace with your WiFi SSID
const char* password = "PASSWORD";  // Replace with your WiFi password

AudioGeneratorMP3 *mp3;
AudioFileSourceHTTPStream *file;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Initialize I2S
  out = new AudioOutputI2S();
  out->SetPinout(26, 25, 22);  // BCLK, LRC, DOUT
  out->SetOutputModeMono(true); // Set to mono by default

  // Start MP3 stream from internet radio
  file = new AudioFileSourceHTTPStream("http://vis.media-ice.musicradio.com/CapitalMP3");
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);
}

void loop() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.println("MP3 playback stopped");
    delay(1000);
  }
}
```
## Customization

- **Change the radio station**: Modify the URL in the `AudioFileSourceHTTPStream` constructor to point to a different MP3 stream.
  - Example: `"http://stream-url.com/your-radio-stream.mp3"`

- **Adjust Output Mode**: By default, the audio is output in mono mode. If you'd like to change it to stereo, you can modify the line `out->SetOutputModeMono(true);` to `out->SetOutputModeMono(false);`.

- **Error Handling**: Add additional error handling or recovery mechanisms for network disconnections or audio issues, depending on your use case.

## Troubleshooting

- **Audio Not Playing**:  
  - Check your audio connections (I2S) and ensure the **MAX98357A** is correctly wired and powered.
  - Make sure the MP3 stream URL is correct and reachable from your ESP32.
  - Verify that the speaker is connected to the MAX98357A and is working.

- **Wi-Fi Connection Issues**:  
  - Double-check your SSID and password.
  - Ensure your ESP32 is within range of the Wi-Fi network.

- **No Sound or Low Volume**:  
  - Check the volume settings of your speaker and make sure it's properly connected to the **MAX98357A**.
  - Verify that the speaker is compatible with the output power of the **MAX98357A**.

## License

This project is licensed under the MIT License.

---
