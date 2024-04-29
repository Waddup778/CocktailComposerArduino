/*
 * This header file houses the custom functions used
 * in the cocktail composer project. This custom library
 *
 */
#ifndef cocktailComposer
#define cocktailComposer.h

#include <Arduino.h>

class ManageLED {
    //constructor
    ManageLED();

    //deconstructor
    ~ManageLED();

    //public methods
public:
    void LedAnimation(int red, int green, int blue);
    void handleLeds(int usPin);
    long microsecondsToInches(long microseconds);


    //private variables
private:
    int red;
    int green;
    int blue;

    int usPin;
    long microseconds;
};

class Ultrasonic {
    Ultrasonic();

    ~Ultrasonic();

public:
    long microsecondsToInches(long microseconds);
    long microseconds;
};

class Drinks {
    Drinks();
    ~Drinks();

public:
    void vodkaLemonade();
    void madras();
    void capeCod();
    void screwdriver();

    bool inProgress;
    int NUM_LEDS;
    CRGB leds[NUM_LEDS];

    int relayVodka;
    int relayLemonade;
    int relayCranberry;
    int relayOJ;
};

#endif