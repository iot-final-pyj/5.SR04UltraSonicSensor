#include <Arduino.h>
#include <TFT_eSPI.h>
// HC-SR04 needs 5V, so its VCC should be connected to 5V

const int   trigPin = 43;
const int   echoPin = 44;
long        duration;
float       distance;
char        buffer[30];

TFT_eSPI tft = TFT_eSPI();

void setup() {
    Serial.begin(115200); 
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("UltraSonic Sensor", 60, 20, 4);
    Serial.println();
    Serial.println("starting...");
} 

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.017;            // distance = duration / 29 / 2;

    Serial.printf("Duration = %6ld, Distance = %6.2fcm\n", duration, distance);
    sprintf(buffer, "time : %6ld, distance %6.2f", duration, distance);
    tft.fillRect(65, 80, 200, 20, TFT_BLACK);
    tft.drawString(buffer, 68, 80, 2);

    delay(1000);
}