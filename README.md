Here's a `README.md` file for your web radio project using the provided code:

---

# Web Radio Project

This project demonstrates how to create a simple web radio streaming application using an ESP32 (or compatible board) that connects to a Wi-Fi network and plays MP3 audio streams. The ESP32 is used to stream audio from an internet radio station and output it via I2S audio hardware.

## Features

- **Wi-Fi Connectivity**: Connects to a Wi-Fi network for internet access.
- **MP3 Streaming**: Streams MP3 audio from an internet radio station.
- **Audio Output**: Outputs audio using I2S protocol to an audio device (such as an amplifier or speaker).
- **Mono Output**: Audio is output in mono by default for simplicity.

## Requirements

- **Hardware**:  
  - ESP32 or compatible board
  - I2S-compatible audio output device (e.g., an external DAC, speaker, or amplifier)
  - Wi-Fi network for internet access

- **Software**:  
  - Arduino IDE (or compatible environment)
  - Libraries:
    - `WiFi` library for connecting to the network
    - `AudioGeneratorMP3` library for MP3 decoding
    - `AudioFileSourceHTTPStream` library for streaming audio over HTTP
    - `AudioOutputI2S` library for sending audio data to an I2S output device

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
   - Connect your I2S DAC or audio amplifier to the ESP32.
   - Ensure proper pin connections for the I2S protocol.

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
  out->SetOutputModeMono(true);

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

## Pin Configuration

Ensure you connect your I2S DAC or audio hardware as follows:

| ESP32 Pin  | I2S Pin      |
|------------|--------------|
| GPIO 26    | BCLK         |
| GPIO 25    | LRC          |
| GPIO 22    | DOUT         |

These are the default pins used in the code. You can adjust them if your setup requires different pins.

## Customization

- **Change the radio station**: Modify the URL in the `AudioFileSourceHTTPStream` constructor to point to a different MP3 stream.
  - Example: `"http://stream-url.com/your-radio-stream.mp3"`

- **Adjust Output Mode**: By default, the audio is output in mono mode. If you'd like to change it to stereo, you can modify the line `out->SetOutputModeMono(true);` to `out->SetOutputModeMono(false);`.

- **Error Handling**: Add additional error handling or recovery mechanisms for network disconnections or audio issues, depending on your use case.

## Troubleshooting

- **Audio Not Playing**:  
  - Check your audio connections (I2S) and ensure the DAC or amplifier is correctly wired and powered.
  - Make sure the MP3 stream URL is correct and reachable from your ESP32.

- **Wi-Fi Connection Issues**:  
  - Double-check your SSID and password.
  - Ensure your ESP32 is within range of the Wi-Fi network.

## License

This project is licensed under the MIT License.

---

Let me know if you'd like any other adjustments or additional sections to the README!
