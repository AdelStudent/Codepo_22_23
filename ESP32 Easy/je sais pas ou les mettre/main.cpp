#include<WiFi.h>
#include<WebServer.h>

/*
    When the user clicks the button in the HTML file, the onclick="onButton()" function in the 
        JavaScript code will be executed. This function sends a GET request to the server at the "/on" 
        path.

    When the server receives the GET request at the "/on" path, the server.on() function in the Arduino 
        sketch will call the lambda function that's defined. This lambda function can then perform any 
        actions we want on the ESP32, such as turning on an LED or performing some other task.

    So, when the user clicks the button in the HTML file, it triggers a chain of events that ultimately
        results in the ESP32 performing a specific action.
*/

const char *ssid = "Galaxy_A5247AB";
const char *password = "imuy8402";
const int led = 2;
const capteur_luminausite = A0;


void handle_not_found(){
    server.send(404, "text/plain", "404 : Not found");
}
void handle_root(){
    String my_page = "";
    my_page+= "<!DOCTYPE html>";
    my_page+= "<html>";
    my_page+= "  <head>";
    my_page+= "    <title>Welcome!</title>";
    my_page+= "  </head>";
    my_page+= "  <body>";
    my_page+= "    <h1>Welcome to our website!</h1>";
    my_page+= "    <p>Thank you for visiting us. We hope you find what you're looking for.</p>";
    my_page+= "  </body>";
    my_page+= "</html>";

    server.send(200, "text/html", my_page);

}

void setup(){
    Serial.begin(115200); // Start the Serial communication to send messages to the computer
    Serial1.begin(115200); // Start the Serial1 communication to send messages to the computer
    
    pinMode(led, OUTPUT); // Initialize the LED_BUILTIN pin as an output
    digitalWrite(led, HIGH);

    //-----------------WIFI-------------------
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.print("local ip: ");
    Serial.println(WiFi.localIP());
    
    //-----------------SERVER-----------------
    server.on("/",handle_root); // Call the handle_root function when a client requests the root path
    server.onNotFound(handle_not_found); // When a client requests an unknown path or page, call the function "handle_not_found"

    server.begin(); // Start the server
    Serial("Server started!!");

    setup_website();
}
void loop(){
    //Since we are using AsyncWebServer, we don't need to use the loop function
    //receive_message();
    server.handleClient();
}   