/*
 * Name: Drink Composer - Backend
 *
 * Written By: C. Abbey
 * Course: ME379
 *
 * Date: FEB 18, 2024
 *
 * Description:
 *  This code is meant to run on a NodeMCU module. The code instructs
 *  the NodeMCU to generate a WiFi network with the given name and password
 *  It then establishes basic protocols like IP, gateway, and subnet.
 *
 *  The program hosts an http webserver that allows http requests to be processed
 *  by the NodeMCU to accomplish tasks. It does this by accepting pre-determined
 *  URLs which are handled by the ClientHandler function. The correct method is
 *  called for the matching url, and a subroutine is initialized.
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>      //Import the ESP8266WiFi library
#include <ESP8266WebServer.h> //Import the ESP8266WebServer library
#include <ArduinoJson.h>      //Import the json library for arduino
#include <ArduinoJson.hpp>    //Import the json library supplemental for the json library
#include <SoftwareSerial.h>   //Enable the software serial library

//Put your SSID & Password here
const char* ssid = "Cocktail Composer";  // Enter SSID here (Network name)
const char* password = "12345678";       //Enter Password here (Network password)

// Put IP Address details
IPAddress local_ip(192,168,0,10);    //Define the IP Address of the Access Point
IPAddress gateway(192,168,0,10);     //Define the Gateway address of the Access Point
IPAddress subnet(255,255,255,0);    //Define the subnet mask Identity

ESP8266WebServer server(80);     //Create a server object on port 80 (for SSH communication)

//=================================================================================================

//================================================================================================

void setup() {

    WiFi.softAP(ssid, password);    //Start an access point (AP) with the entered SSID and password
    WiFi.softAPConfig(local_ip, gateway, subnet);   //Configure the network proxies
    delay(100);   //Wait 100 milliseconds

    server.on("/order", handle_order); //when the app sends a url '/order', the handler will call handle_order()

    server.begin();   //initialize the server
    Serial.begin(9600);
    Serial.println();
    Serial.println("HTTP server started");  //verify the server has initialized
    Serial.println("*********************************************************");

    Serial1.begin(9600);

}
//=========== END SET UP FUNCTION ==========================================

void loop() {
    server.handleClient();    //Look for URLs, address handler defined in void setup()

}

//===================== ORDER HANDLING FUNCTION ============================

void handle_order() {

    delay(2000);  //wait 2 seconds (fool the user, add wait time)

    String orderId = server.arg("orderId");   //parse the incoming Json file for the argument 'orderId'
    String drink = server.arg("drink");       //parse the incoming Json file for the argument 'drink'

    Serial.println("Order request: " + drink + " recieved!");    // print a confirmation message to the console
    Serial.println(" ");
    delay(500);
    Serial.println("Order ID: " + orderId);
    Serial.println("Drink Name: " + drink);
    Serial.println(" ");

    delay(500);

    int responseCode = 200;   // create integer variable for the status response code
    JsonDocument response;    // initialize Jsondocument class object response
    String responseString;    // create a string variable named responseString

    // no order ID passed in Json, reply with error code and message:
    if (orderId == NULL) {                                  // if the orderId is null, do the following:
        responseCode = 400;                                   // send the error response code (not found 400)
        response["message"] = "Please pass in an order ID";   // send response message body
    }
        // no drink type passed in Json, reply with error code and message:
    else if (drink == NULL) {                               // if the drink is null, do the following:
        responseCode = 400;                                   // send the error response code (not found 400)
        response["message"] = "Please pass in an drink";      // send response message body
    }

        // All order criteria met, send a confirmation back to the app and stop loading icon
    else {                                                                                          // otherwise, do the followin:
        responseCode = 200;                                                                           // send a good request response
        response["message"] = "Order " + orderId + " was placed successfully for a " + drink + "!";   // construct a new response confirmation body to send back to the app
        inProgress = true;
    }

    serializeJson(response, responseString);    // construct a serialized json response with the response message and string

    Serial.println();
    Serial.println("Sending confirmation response....");
    server.send(responseCode, "application/json", responseString);    // send the constructed response as a Json (post)
    Serial.println("Confirmation Sent!");
    Serial.println();
    processOrder(drink);    // process the request and actually do something
}

//================== ORDER PROCESSING ============================

void processOrder(String drink) {
    if (drink == "Vodka Lemonade") {
        //vodkaLemonade();
        Serial1.print(1);
    }
    else if (drink == "Madras") {
        //madras();
        Serial1.print(2);
    }
    else if (drink == "Cape Cod") {
        Serial1.print(3);
    }
    else if (drink == "Screwdriver")  {
        Serial1.print(4);
    }
}

