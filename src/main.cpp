#include <Arduino.h>
#include <FastLED.h>

// 2.56 Oz/min - dispensing capability of pumps
// 23.5 sec per oz

const int ounce = 23500;

// Constants for pin numbers
const int relayVodka = 7;   //VODKA         create constant integer for pin named relayVodka, attached to pin 2
const int relayLemonade = 6;   //LEMONADE      create constant integer for pin named relayLemonade, attached to pin 3
const int relayOJ = 5;   //ORANGE JUICE  create constant integer for pin named relayOJ, attached to pin 4
const int relayCranberry = 4;   //CRAN JUICE

const int b0 = 8;       //create constant integer for pin named b0, attached to pin 8
const int b1 = 9;       //create constant integer for pin named b1, attached to pin 9
const int b2 = 12;      //create constant integer for pin named b2, attached to pin 10
const int b4 = 13;       //create constant integer for pin named b3, attached to pin 7

const int pingPin = 11; //create constant integer for pin named pingPin, attached to pin 11
const int ledPin = 10;   //create constant integer for pin named ledPin, attached to pin 5

#define NUM_LEDS 21     //define the number of LEDs in the led array
CRGB leds[NUM_LEDS];    //create FastLED CRGB class object array called leds[No. Leds in array]

char appOrderState = ' ';   //create empty character appOrderState and store blank space

bool inProgress = false;    //set inProcess flag to false globally
bool b0State = true;       //set b0State to false globally
bool b1State = false;       //set b1State to false globally
bool b2State = false;       //set b2State to false globally
bool b4State = false;       //set b3State to false globally

unsigned long lastAnimationTime = 0;        //store zero to lastAnimationTime
unsigned long animationInterval = 1000;     //set the led animation interval time

//create a custom function to manage led strips to relay feedback to the user
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

//======================= Drink Making Routines =========================
//Each function structured similarly, comments can be found in the function vodkaLemonade.
/*
 * Create function for Vodka Lemonade
 *
 * Return type: Void
 *
 * Args: None
 *
 * Purpose:
 * Handle the drink making process for the vodka lemonade selection
 *
 * Recipe:
 * 2 Oz vodka
 * 6 Oz Lemonade
 */
void vodkaLemonade()  {
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

/*
 * Create function for madras drink
 *
 * Return type: Void
 *
 * Purpose:
 * Hand the drink making process for the madras drink selection
 *
 * Recipe:
 * 1.5 Oz vodka
 * 3 Oz Cranberry Juice
 * 1 Oz Orange Juice
 */
void madras() {
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

/*
 * Create function for cape cod drink
 *
 * Return type: Void
 *
 * Purpose:
 * Handle the drink making process for the cape cod drink selection
 *
 * Recipe:
 * 1.5 Oz vodka
 * 4 Oz Cranberry Juice
 */
void capeCod() {
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

/*
 * Create function for the screwdriver drink
 *
 * Return type: Void
 *
 * Purpose:
 * Handle the drink making process for the Screwdriver drink selection
 *
 * Recipe:
 * 1.5 Oz vodka
 * 6 Oz Orange Juice
 */
void screwdriver() {
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

//=======================================================================

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

    pinMode(relayVodka, OUTPUT);    //set pin as output
    pinMode(relayLemonade, OUTPUT);    //set pin as output
    pinMode(relayOJ, OUTPUT);    //set pin as output
    pinMode(relayCranberry, OUTPUT);

    pinMode(b0, INPUT_PULLUP);  //button 0, use software debounce as input
    pinMode(b1, INPUT_PULLUP);  //button 1, use software debounce as input
    pinMode(b2, INPUT_PULLUP);  //button 2, use software debounce as input
    pinMode(b4, INPUT_PULLUP);  //button 3, use software debounce as input

    pinMode(ledPin, OUTPUT);    //set ledPin as an output

    Serial.println("Started!");       //print confirmation to the monitor to confirm setup has run
    FastLED.setBrightness(50);      //contro the maximum brightness of the LED indicators
    FastLED.addLeds<WS2812, ledPin, GRB>(leds, NUM_LEDS);   //add LEDs to FastLED, include LED type, pin, and color order, apply to led array

    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 255));
    FastLED.show();
}

void loop() {
    //Need to monitor the serial connection for commands sent from the NodeMCU
    // if the serial communication is available and is greater than zero, run the following code:
    if (Serial.available() > 0){
        Serial.println("Online order detected.");   //print online order confirmation to the monitor
        //uncomment line 208 for diagnostics
        //Serial.write(Serial.read());
        char appOrderState = Serial.read();     //read the serial port and save any data as
        //Serial.println(appOrderState);
        if (appOrderState == '1') {
            inProgress = true;
            vodkaLemonade();
        }
        if (appOrderState == '2') {
            inProgress = true;
            madras();
        }
        if (appOrderState == '3') {
            inProgress = true;
            capeCod();
        }
        if (appOrderState == '4') {
            inProgress = true;
            screwdriver();
        }
    }

    //Read all button states to determine presses
    b0State = digitalRead(b0);
    b1State = digitalRead(b1);
    b2State = digitalRead(b2);
    b4State = digitalRead(b4);

    //handle button presses:
    //All processes are the same for each button, each calls a specific function to make a drink
    //if b0State is false:
    if (!b0State){
        inProgress = true;  //set the inProgress flag to true
        vodkaLemonade();    //call the function vodkaLemonade to make a drink
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
    //handleLeds(pingPin);
}
