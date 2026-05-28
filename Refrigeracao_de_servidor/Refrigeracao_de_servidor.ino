#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "NOME_DO_SEU_WIFI_AQUI";
const char* password = "SENHA_DO_SEU_WIFI_AQUI";

IPAddress local_IP(192, 168, 5, 150);  
IPAddress gateway(192, 168, 5, 1);    
IPAddress subnet(255, 255, 255, 0);   


#define DHTPIN 4      // Pino  de Entrada 
#define DHTTYPE DHT22 // Tipo do sensor
DHT dht(DHTPIN, DHTTYPE);

// Pinos físicos de Saída 
const int cooler1 = 26;
const int cooler2 = 27;
const int cooler3 = 32;
const int cooler4 = 33;

WebServer server(80); // Servidor web na porta 80

float temperatura = 0.0;
int coolersAtivos = 0;


void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\">";
  html += "<meta http-equiv=\"refresh\" content=\"5\">"; 
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Controle Termico Servidor</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; text-align: center; background-color: #1a1a1a; color: #f1f1f1; margin-top: 50px; }";
  html += ".card { background: #333; padding: 30px; border-radius: 15px; display: inline-block; box-shadow: 0 8px 16px rgba(0,0,0,0.5); border: 1px solid #444; }";
  html += "h1 { color: #00a8ff; margin-bottom: 5px; }";
  html += "h3 { color: #7f8fa6; margin-top: 0; }";
  html += ".temp { font-size: 60px; font-weight: bold; color: #ff4757; text-shadow: 2px 2px 4px rgba(0,0,0,0.3); }";
  html += ".status { font-size: 26px; margin-top: 25px; color: #2ed573; background: #2f3640; padding: 10px; border-radius: 8px; }";
  html += "</style></head><body>";
  
  html += "<div class=\"card\">";
  html += "<h1>Painel de Refrigeração</h1>";
  html += "<h3>Monitoramento do Servidor</h3>";
  
  if (isnan(temperatura)) {
    html += "<div class=\"temp\">Falha no Leitor</div>";
  } else {
    html += "<div class=\"temp\">" + String(temperatura, 1) + " &deg;C</div>";
  }
  
  html += "<div class=\"status\">Coolers Ligados: <b>" + String(coolersAtivos) + " / 4</b></div>";
  html += "<p style='margin-top:20px; font-size:14px; color:#7f8fa6;'>Atualizando ao vivo no IP: http://" + WiFi.localIP().toString() + "</p>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}


void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(cooler1, OUTPUT);
  pinMode(cooler2, OUTPUT);
  pinMode(cooler3, OUTPUT);
  pinMode(cooler4, OUTPUT);


  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Falha ao aplicar IP Estatico");
  }

  Serial.print("Conectando ao Wi-Fi... ");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWi-Fi Conectado!");
  Serial.println("Acesse o painel digitando no seu navegador: ");
  Serial.println("http://192.168.5.150");

  server.on("/", handleRoot);
  server.begin();
}


void loop() {
  server.handleClient(); 

  temperatura = dht.readTemperature();

  if (!isnan(temperatura)) {
    if (temperatura < 30.0) {
      digitalWrite(cooler1, LOW);
      digitalWrite(cooler2, LOW);
      digitalWrite(cooler3, LOW);
      digitalWrite(cooler4, LOW);
      coolersAtivos = 0;
    } 
    else if (temperatura >= 30.0 && temperatura < 35.0) {
      digitalWrite(cooler1, HIGH);
      digitalWrite(cooler2, LOW);
      digitalWrite(cooler3, LOW);
      digitalWrite(cooler4, LOW);
      coolersAtivos = 1;
    } 
    else if (temperatura >= 35.0 && temperatura < 40.0) {
      digitalWrite(cooler1, HIGH);
      digitalWrite(cooler2, HIGH);
      digitalWrite(cooler3, LOW);
      digitalWrite(cooler4, LOW);
      coolersAtivos = 2;
    } 
    else if (temperatura >= 40.0 && temperatura < 45.0) {
      digitalWrite(cooler1, HIGH);
      digitalWrite(cooler2, HIGH);
      digitalWrite(cooler3, HIGH);
      digitalWrite(cooler4, LOW);
      coolersAtivos = 3;
    } 
    else if (temperatura >= 45.0) {
      digitalWrite(cooler1, HIGH);
      digitalWrite(cooler2, HIGH);
      digitalWrite(cooler3, HIGH);
      digitalWrite(cooler4, HIGH);
      coolersAtivos = 4;
    }
  }
  delay(2000); 
}