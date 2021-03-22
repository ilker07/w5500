#include <SPI.h>
#include <Ethernet2.h>
int led = 4;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 1,50);

EthernetServer server(80);
String readString;
void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server IP adres: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  
 
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Random Nerd Tutorials Project</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Random Nerd Tutorials Project</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Turn On LED</a>");
           client.println("<a href=\"/?button1off\"\">Turn Off LED</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/?button2on\"\">Rotate Left</a>");
           client.println("<a href=\"/?button2off\"\">Rotate Right</a><br />"); 
           client.println("<p>Created by Rui Santos. Visit http://randomnerdtutorials.com for more projects!</p>");  
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, LOW);
           }
          
          
            //clearing string for next read
            readString="";  
           
         }
       }
    }
}
}
