// Definição dos pinos dos sensores
const int sensor1Pin = 8; // Primeiro sensor
const int sensor2Pin = 9; // Segundo sensor

unsigned long startTime;
unsigned long endTime;
float deltaTime; // Tempo entre os sensores
float distance = 0.10; // Distância entre os sensores em metros
float velocity; // Velocidade da bolinha entre os sensores

void setup() {
  Serial.begin(9600); // Inicia comunicação serial para ver os resultados
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
}

void loop() {
 
  if (digitalRead(sensor1Pin) == HIGH) {
    startTime = micros(); 
  }
  
  
  if (digitalRead(sensor2Pin) == HIGH) {
    endTime = micros();
    deltaTime = (endTime - startTime) / 1000000.0; 

    velocity = distance / deltaTime;
    
 
    Serial.print("Velocidade entre os sensores: ");
    Serial.print(velocity);
    Serial.println(" m/s");//Imprime o valor que sera usado para medir a precisao do calculo de velocidade de acordo com a distancia entre o inicio da queda livre e o sensor de velocidade
    
    delay(1000); 
  }
}
