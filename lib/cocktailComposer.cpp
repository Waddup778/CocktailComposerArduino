#include "cocktailComposer.h"
#include "FastLED.h"
#include "Arduino.h"

ManageLED::ManageLED() {
    //init variables and perform setup here
}
void ManageLED::handleLeds(int usPin) {
    //define function code here
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

void ManageLED::LedAnimation(int red, int green, int blue) {
    //define function code here
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

ManageLED::~ManageLED() {

}

Ultrasonic::Ultrasonic() {

}

long Ultrasonic::microsecondsToInches(long microseconds) {
    return microseconds / 74 / 2;
}

Drinks::Drinks() {
}

void Drinks::vodkaLemonade() {
    //Serial.write("Arduino Starting order");
    delay(1000);    //wait for 1 second

    while (inProgress)  {
        Serial.println("Processing order for a vodka Lemonade...");     //Print a confirmation that the order has started
        fill_solid(leds, NUM_LEDS, CRGB::Blue);     //Interrupt the current LED animation and change to a solid color
        FastLED.show();     //show the new LED animation, light the LEDs

        Serial.println("Dispensing Vodka...");    //Print a confirmation that Mixer A has started
        digitalWrite(relayVodka, HIGH);         //activate the correct relay to turn on pump A
        delay(47000);                            //wait 1 second, allow motor to dispense
        digitalWrite(relayVodka, LOW);          //deactivate the relay to turn off the pump

        Serial.println("Dispensing Lemonade...");    //Print a confirmation that mixer B has started
        digitalWrite(relayLemonade, HIGH);         //activate the correct relay to turn on pump B
        delay(141000);                            //wait X seconds, allow motor to dispense
        digitalWrite(relayLemonade, LOW);          //deactivate the correct relay to turn off pump B

        inProgress = false;     //set the inProgress flag back to false to exit the loop (allows function to return completion status)
    }
    fill_solid(leds, NUM_LEDS, CRGB::Black);    //turn off the leds (setting color to black makes LEDs turn off)
    FastLED.show();     //send the new color command to the LEDs

    delay(500);     //wait half a second
    Serial.println("Order processing complete!");       //Print a completion confirmation to the monitor
    Serial.println("*******************************************");      //print a divider to the monitor to separate commands
    Serial.println();   //print a blank line
}

void Drinks::madras() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a Madras...");

        Serial.println("Dispensing Vodka...");
        digitalWrite(relayVodka, HIGH);
        delay(35250);   //dispense for 35.25 seconds
        digitalWrite(relayVodka, LOW);

        Serial.println("Dispensing Cranberry Juice...");
        digitalWrite(relayCranberry, HIGH);
        delay(70500);       //dispense cranberry juice for 70.5 seconds
        digitalWrite(relayCranberry, LOW);

        Serial.println("Dispensing Orange Juice...");
        digitalWrite(relayOJ, HIGH);
        delay(23500);
        digitalWrite(relayOJ, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

void Drinks::capeCod() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a Cape Cod...");

        Serial.println("Dispensing Vodka...");
        digitalWrite(relayVodka, HIGH);
        delay(35250);       //dispense for 35.25 seconds
        digitalWrite(relayVodka, LOW);

        Serial.println("Dispensing Cranberry Juice...");
        digitalWrite(relayCranberry, HIGH);
        delay(94000);   //dispense for 94 seconds
        digitalWrite(relayCranberry, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}

void Drinks::screwdriver() {
    //Serial.write("Arduino starting order");
    delay(1000);

    while (inProgress)  {
        Serial.println("Processing order for a Screwdriver...");

        Serial.println("Dispensing Vodka...");
        digitalWrite(relayVodka, HIGH);
        delay(35250);       //dispense for 35.25 seconds
        digitalWrite(relayVodka, LOW);

        Serial.println("Dispensing Orange Juice...");
        digitalWrite(relayOJ, HIGH);
        delay(141000);  //dispense for 141 seconds
        digitalWrite(relayOJ, LOW);

        inProgress = false;
    }
    delay(500);
    Serial.println("Order processing complete!");
    Serial.println("*******************************************");
    Serial.println();
}
