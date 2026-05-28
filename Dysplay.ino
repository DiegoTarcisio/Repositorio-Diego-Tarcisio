#include <Wire.h> //Inclusão da biblioteca wire
#include <Adafruit_SSD1306.h> //Inclusão da biblioteca Adafruit_SSD1306.h

Adafruit_SSD1306 displayLED; //Criação do objeto displayLED, que será chamado para realizar as intruções da biblioteca Adafruit_SSD1306.h

void setup() {
  Wire.begin(); //Inicia a biblioteca Wire
  displayLED.begin(); //Inicia o display OLED
  displayLED.clearDisplay(); //Limpa as mensagens do display
}

void loop() {
  displayLED.setTextColor(WHITE); //Define a cor das letras, mas no nosso exemplo o display é Azul, então independente da cor que for colocada neste campo as letras ficarão azul. Por padrão deixe WHITE.
  displayLED.setTextSize(1); //Define o tamanho da letra
  displayLED.setCursor(10, 12); //Define o local(Horizontal e vertical), de onde irá aparecer a mensagem no display.
  displayLED.print("O cara bom");//Envia mensagem para o display
  displayLED.display();//Confirma a escrita no display
  
  delay(5); //Tempo de espera de 1500 milissegundos
  
  displayLED.clearDisplay(); //Limpa a mensagem do display
  displayLED.setCursor(7, 12); //Define um novo local para a próxima mensagem do display
  displayLED.print("Diego Tarcisio"); //Envia mensagem para o display
  displayLED.display(); //Confirma a escrita no display
  
  delay(1500); //Tempo de espera de 1500 milissegundos
  
  displayLED.clearDisplay(); //Limpa a mensagem do display