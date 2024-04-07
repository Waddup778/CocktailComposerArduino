#include <Arduino.h>
#include <FastLED.h>

// Constants for pin numbers
const int mixer0 = 2;
const int mixer1 = 3;
const int mixer2 = 4;
const int b0 = 8;
const int b1 = 9;
const int b2 = 10;
const int b4 = 7;
const int pingPin = 11;
const int ledPin = 5;

#define NUM_LEDS 21
CRGB leds[NUM_LEDS];

char appOrderState = ' ';

bool inProgress = false;
bool b0State = false;
bool b1State = false;
bool b2State = false;
bool b4State = false;

unsigned long lastAnimationTime = 0;
unsigned long animationInterval = 1500;

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

void vodkaLemonade()  {
    //Serial.write("Arduino Starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a vodka Lemonade...");

        fill_solid(leds, NUM_LEDS, CRGB::Blue);
        FastLED.show();

        Serial.println("Dispensing mixer A...");
        digitalWrite(mixer0, HIGH);
        delay(1000);
        digitalWrite(mixer0, LOW);

        Serial.println("Dispensing mixer B...");
        digitalWrite(mixer1, HIGH);
        delay(1000);
        digitalWrite(mixer1, LOW);

        inProgress = false;
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

void madras() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a madras...");

        Serial.println("Dispensing mixer A...");
        digitalWrite(mixer0, HIGH);
        delay(2000);
        digitalWrite(mixer0, LOW);

        Serial.println("Dispensing mixer B...");
        digitalWrite(mixer1, HIGH);
        delay(2000);
        digitalWrite(mixer1, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

void capeCod() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a Cape Cod...");

        Serial.println("Dispensing mixer A...");
        digitalWrite(mixer0, HIGH);
        delay(1000);
        digitalWrite(mixer0, LOW);

        Serial.println("Dispensing mixer B...");
        digitalWrite(mixer1, HIGH);
        delay(1000);
        digitalWrite(mixer1, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

void screwdriver() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a screwdriver...");

        Serial.println("Dispensing mixer A...");
        digitalWrite(mixer2, HIGH);
        digitalWrite(mixer1, HIGH);
        delay(3000);
        digitalWrite(mixer2, LOW);
        digitalWrite(mixer1, LOW);

        Serial.println("Dispensing mixer B...");
        digitalWrite(mixer1, HIGH);
        delay(3000);
        digitalWrite(mixer1, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

long microsecondsToInches(long microseconds)  {
    return microseconds / 74 / 2;
}

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
        fadeAnimation(255, 255, 255);
    } else if (inches >= 2) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        lastAnimationTime = currentMillis;
    }
}

void setup() {
    //Open serial communications and wait for port to open:
    Serial.begin(9600);
    pinMode(mixer0, OUTPUT);
    pinMode(mixer1, OUTPUT);
    pinMode(mixer2, OUTPUT);

    pinMode(b0, INPUT_PULLUP);
    pinMode(b1, INPUT_PULLUP);
    pinMode(b2, INPUT_PULLUP);
    pinMode(b4, INPUT_PULLUP);

    pinMode(ledPin, OUTPUT);

    Serial.print("Started!");
    FastLED.setBrightness(50);
    FastLED.addLeds<WS2812, ledPin, GRB>(leds, NUM_LEDS);
}

void loop() {
    if (Serial.available() > 0){
        Serial.println("Online order detected.");
        //uncomment line 208 for diagnostics
        //Serial.write(Serial.read());
        char appOrderState = Serial.read();
        switch (appOrderState) {
            case '1':
                inProgress = true;
                vodkaLemonade();
                break;
            case '2':
                inProgress = true;
                madras();
                break;
            case '3':
                inProgress = true;
                capeCod();
                break;
            case '4':
                inProgress = true;
                screwdriver();
                break;
            default:
                break;
        }

        b0State = digitalRead(b0);
        b1State = digitalRead(b1);
        b2State = digitalRead(b2);
        b4State = digitalRead(b4);

        if (!b0State){
            inProgress = true;
            vodkaLemonade();
        }
        if (!b1State){
            inProgress = true;
            madras();
        }
        if (!b2State){
            inProgress = true;
            capeCod();
        }
        if (!b4State){
            inProgress = true;
            screwdriver();
        }
    }
    handleLeds(pingPin);
}
