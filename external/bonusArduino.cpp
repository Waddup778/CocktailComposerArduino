#include <Arduino.h>
#include <FastLED.h>

// SETUP PIN CONNECTIONS TO THE ARDUINO
const int ledPin = 10;
const int pingPin = 11;

// Define FastLED Class object
#define NUM_LEDS 21
CRGB leds[NUM_LEDS];

// CREATE GLOBAL VARIABLES FOR THE LED ANIMATION FUNCTION TO USE
unsigned long lastAnimationTime = 0;
// SET THE ANIMATION TIME HERE *********************************
unsigned long animationInterval = 1000;
// *************************************************************

// void fadeAnimation(int red, int green, int blue) {
//     unsigned long animationStartTime = millis();
//     float r, g, b;
//     int elapsedTime = 0;

//     while (elapsedTime < 1024) {
//         elapsedTime = millis() - animationStartTime;
//         // Compact if-else statement using ?: notation
//         int brightness = (elapsedTime < 512) ? map(elapsedTime, 0, 512, 0, 255) : map(elapsedTime - 512, 0, 512, 255, 0);
//         r = (brightness / 255) * red;
//         g = (brightness / 255) * green;
//         b = (brightness / 255) * blue;
//         fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
//         FastLED.show();
//     }
// }

void fadeAnimation(int red, int green, int blue) {
    unsigned long animationStartTime = millis();
    float r, g, b;
    int elapsedTime = 0;

    // Fade in and out combined
    while (elapsedTime < 1024) { // Total duration of 512 + 512 milliseconds
        elapsedTime = millis() - animationStartTime;
        int brightness = (elapsedTime < 512) ? map(elapsedTime, 0, 512, 0, 255) : map(elapsedTime - 512, 0, 512, 255, 0);
        r = (brightness / 255.0) * red;
        g = (brightness / 255.0) * green;
        b = (brightness / 255.0) * blue;
        fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
        FastLED.show();
    }
}

long microsecondsToInches(long microseconds) {
    return microseconds / 74 / 2;
}

// void handleLeds(int usPin) {
//     unsigned long currentMillis = millis();
//     long duration, inches;

//     pinMode(usPin, OUTPUT);
//     digitalWrite(usPin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(usPin, HIGH);
//     delayMicroseconds(5);
//     digitalWrite(usPin, LOW);

//     duration = pulseIn(usPin, HIGH);

//     inches = microsecondsToInches(duration);

//     if (inches < 2 && currentMillis - lastAnimationTime >= animationInterval) {
//         lastAnimationTime = currentMillis;
//         fadeAnimation(255, 255, 255);
//     }   else if (inches >= 2) {
//         fill_solid(leds, NUM_LEDS, CRGB::Black);
//         FastLED.show();
//         lastAnimationTime = currentMillis;
//     }
// }
void handleLeds(int usPin) {
    unsigned long currentMillis = millis();
    long duration, inches;

    pinMode(usPin, OUTPUT);
    digitalWrite(usPin, LOW);
    delayMicroseconds(2);
    digitalWrite(usPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(usPin, LOW);

    pinMode(usPin, INPUT);

    duration = pulseIn(usPin, HIGH);

    inches = microsecondsToInches(duration);
    //Serial.println(inches);

    if (inches < 2 && currentMillis - lastAnimationTime >= animationInterval) {
        lastAnimationTime = currentMillis;
        Serial.println("Object Detected.");
        fadeAnimation(255, 255, 255);
    } else if (inches >= 2) {
        Serial.println("No object detected.");
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        lastAnimationTime = currentMillis;
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(ledPin, OUTPUT);

    Serial.println("Started!");
    FastLED.setBrightness(50);
    FastLED.addLeds<WS2812, ledPin, GRB>(leds, NUM_LEDS);

    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    FastLED.show();
}

void loop() {
    handleLeds(pingPin);
}
