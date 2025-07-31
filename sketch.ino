#include <DHT.h>
#include <WiFi.h>

DHT dht(13,DHT22);
WiFiServer server(80);
void setup() { 
  Serial.begin(115200);
  WiFi.softAP("ESP Sensor","12345678");
  delay(1000);
  Serial.println("Started network");
  Serial.println(WiFi.softAPIP());
  dht.begin();
  server.begin();
}

void loop() {
    WiFiClient client = server.available();
  if (client) {
    while (client.connected() && !client.available()) {
      delay(10);
    }
    Serial.println("Client connected");
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.read();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close"); 
    client.println();
    client.println(F(
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "<meta charset=\"UTF-8\">\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "<title>Temperatur</title>\n"
    "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">\n"
    "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>\n"
    "<link href=\"https://fonts.googleapis.com/css2?family=Roboto:wght@411&display=swap\" rel=\"stylesheet\">\n"
    "<style>\n"
    ".col{display:flex;flex-direction:column;padding:10px;align-items:center;justify-items:center;}\n"
    ".row{display:flex;flex-direction:row;align-items:center;justify-content:center;}\n"
    ".val{font-size:48px;padding:0px;margin:3px;}\n"
    ".border{border-radius:0.5rem;border-color:white;border-width:1px;background:rgba(255,255,255,0.07);box-shadow:0 4px 30px rgba(0,0,0,0.1);backdrop-filter:blur(6px);padding:10px;margin:10px;}\n"
    "p{margin:3px;}\n"
    "html{background-image:url('https://lutzemburg.de/bg.png');color:azure;background-position:center center;min-height:100vh;font-family:'Roboto',sans-serif;font-optical-sizing:auto;font-weight:411;font-style:normal;font-variation-settings:'wdth' 100;}\n"
    "a{color:azure;}\n"
    "</style>\n"
    "</head>\n"
    "<body>\n"
    "<div class=\"col\" style=\"padding: 0px;\">\n"
    "<h1 class=\"border\">ESP Sensor by <a target=\"_blank\" href=\"https://github.com/TKX10\">TKX10</a></h1>\n"
    "<div class=\"row\" style=\"flex-wrap: wrap;\">\n"
    "<div class=\"col border\">\n"
    "<div class=\"row\">\n"
    ));
    client.println("<p class=\"val\">"+String(dht.readTemperature())+"°C</p>");
    client.println("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"currentColor\" class=\"bi bi-thermometer\" viewBox=\"0 0 16 16\">");
    client.println("<path d=\"M8 14a1.5 1.5 0 1 0 0-3 1.5 1.5 0 0 0 0 3\"/>");
    client.println("<path d=\"M8 0a2.5 2.5 0 0 0-2.5 2.5v7.55a3.5 3.5 0 1 0 5 0V2.5A2.5 2.5 0 0 0 8 0M6.5 2.5a1.5 1.5 0 1 1 3 0v7.987l.167.15a2.5 2.5 0 1 1-3.333 0l.166-.15z\"/>");
    client.println("</svg>");
    client.println("</div>");
    client.println("<p style=\"font-size: 22px;\">Temperature</p>");
    client.println("</div>");

    client.println("<div class=\"col border\">");
    client.println("<div class=\"row\">");
    client.println("<p class=\"val\">"+String(dht.readHumidity())+"%</p>");
    client.println("<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"currentColor\" class=\"bi bi-moisture\" viewBox=\"0 0 16 16\">");
    client.println("<path d=\"M13.5 0a.5.5 0 0 0 0 1H15v2.75h-.5a.5.5 0 0 0 0 1h.5V7.5h-1.5a.5.5 0 0 0 0 1H15v2.75h-.5a.5.5 0 0 0 0 1h.5V15h-1.5a.5.5 0 0 0 0 1h2a.5.5 0 0 0 .5-.5V.5a.5.5 0 0 0-.5-.5zM7 1.5l.364-.343a.5.5 0 0 0-.728 0l-.002.002-.006.007-.022.023-.08.088a29 29 0 0 0-1.274 1.517c-.769.983-1.714 2.325-2.385 3.727C2.368 7.564 2 8.682 2 9.733 2 12.614 4.212 15 7 15s5-2.386 5-5.267c0-1.05-.368-2.169-.867-3.212-.671-1.402-1.616-2.744-2.385-3.727a29 29 0 0 0-1.354-1.605l-.022-.023-.006-.007-.002-.001zm0 0-.364-.343zm-.016.766L7 2.247l.016.019c.24.274.572.667.944 1.144.611.781 1.32 1.776 1.901 2.827H4.14c.58-1.051 1.29-2.046 1.9-2.827.373-.477.706-.87.945-1.144zM3 9.733c0-.755.244-1.612.638-2.496h6.724c.395.884.638 1.741.638 2.496C11 12.117 9.182 14 7 14s-4-1.883-4-4.267\"/>");
    client.println("</svg>");
    client.println("</div>");
    client.println("<p style=\"font-size: 22px;\">Humidity</p>");
    client.println("</div>");

    client.println("</div>");
    client.println("<div class=\"col border\">");
    client.println("<p style=\"font-size: 22px;\">Sensor: DHT22</p>");
    client.println("<p style=\"font-size: 22px;\">Chip: ESP32</p>");
    client.println("</div>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");

    delay(80);
    client.stop();
    Serial.println(String(dht.readTemperature()));
  }
}