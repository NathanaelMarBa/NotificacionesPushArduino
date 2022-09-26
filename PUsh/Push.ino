#include <HTTPClient.h>
#include <WiFi.h>
#include <SPI.h>

/*Credenciales de red*/
const char* ssid = "Saray";
const char* pass = "123456789";

void setup() {
  /*Iniciamos el terminal Serial para la escritura de algunos parámetros */
  Serial.begin(115200);
  /*Iniciamos la conexión a la red WiFi definida*/
  WiFi.begin(ssid, pass);
  delay(2000);
  /*Indicamos que se está realizando la conexión*/
  Serial.print("Se está conectando a la red WiFi denominada ");
  Serial.println(ssid);
  /*Mientras se realiza la conexión a la red, aparecerán puntos, hasta que se realice la conexión*/
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  /*Con la conexión ya realizada, se pasa a imprimir algunos datos importantes, como la dirección IP asignada a nuestro dispositivo*/
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {


  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin("https://fcm.googleapis.com/fcm/send");
    Serial.println("Inicio el programa");
    String data = "{";
    data = data + "\"to\":\"/topics/Kevin\",";
    data = data + "\"notification\": {";
    data = data + "\"body\": \"Mensaje de prueba\",";
    data = data + "\"title\":\"CCAI\"";
    data = data + "} }";
    Serial.println(data);

    Serial.println("Antes");
    http.addHeader("Authorization", "key=AAAAFVcJKjw:APA91bHQn0Jrv4rBnEmya-UCptEmtn8F78V_Og6H3s094qWGjSsqmXeAJEMtGqwZNrASwGpEeVc8b2fzahHVzT2DTV3fE2cPGLpKg0s-1XrwT4xIC0Mc6G0yp7748-GfwPwA3u50eOco");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Content-Length", (String)data.length());
    
    int httpResponseCode = http.POST(data);
    Serial.println("Despues");
    Serial.println(httpResponseCode);

    Serial.println("Se esta entrando");

    if (httpResponseCode > 0) {

      String response = http.getString();  //Get the response to the request

      Serial.println("Se envio la notificacion");   //Print return code
      Serial.println(response);           //Print request answer

    } else {

      Serial.println("Error on sending POST: ");
      Serial.println(httpResponseCode);

    }

  }
}
