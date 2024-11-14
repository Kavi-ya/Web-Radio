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
