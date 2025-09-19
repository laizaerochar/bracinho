#include <Servo.h>

// --- Joystick 1 : Base (X) + Cotovelo 1 (Y) ---
const int joyBase_X = A0;    
const int joyCotovelo1_Y = A1;  

// --- Joystick 2 : Cotovelo 2 (X) + Botão (Z) ---
const int joyCotovelo2_X = A2;    
const int joyGarraBotao = 2;  
     
     // --- Pinos dos Servos ---
Servo servoBase;       
Servo servoCotovelo1;  
Servo servoCotovelo2;  
Servo servoGarra;      

// --- Limites de ângulo ---
const int minBase = 30, maxBase = 150;
const int minCotovelo1 = 0, maxCotovelo1 = 180;
const int minCotovelo2 = 0, maxCotovelo2 = 180;
const int minGarra =      


0, maxGarra = 80;

// --- Variáveis para controle da garra ---
bool garraAberta = false;
bool ultimoEstadoBotao = HIGH;

void setup() {
  servoBase.attach(9);
  servoCotovelo1.attach(10);
  servoCotovelo2.attach(11);
  servoGarra.attach(6);

  pinMode(joyGarraBotao, INPUT_PULLUP); 

  Serial.begin(9600);
}

void loop() {
  // --- Leitura dos Joysticks ---
  int leituraBase = analogRead(joyBase_X);
  int leituraCotovelo1 = analogRead(joyCotovelo1_Y);
  int leituraCotovelo2 = analogRead(joyCotovelo2_X);

  // --- Conversão para ângulos ---
  int angleBase = map(leituraBase, 0, 1023, minBase, maxBase);
  int angleCotovelo1 = map(leituraCotovelo1, 0, 1023, minCotovelo1, maxCotovelo1);
  int angleCotovelo2 = map(leituraCotovelo2, 0, 1023, minCotovelo2, maxCotovelo2);

  // --- Controle da garra com botão (abre/fecha) ---
  bool estadoBotao = digitalRead(joyGarraBotao);
  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    garraAberta = !garraAberta; // alterna estado
  }
  ultimoEstadoBotao = estadoBotao;

  int angleGarra = garraAberta ? maxGarra : minGarra;

  // --- Movimento dos Servos ---
  servoBase.write(angleBase);          
  servoCotovelo1.write(angleCotovelo1); 
  servoCotovelo2.write(angleCotovelo2); 
  servoGarra.write(angleGarra);        

  // --- Monitor Serial ---
  Serial.print("Base: "); Serial.print(angleBase);
  Serial.print(" | Cotovelo1: "); Serial.print(angleCotovelo1);
  Serial.print(" | Cotovelo2: "); Serial.print(angleCotovelo2);
  Serial.print(" | Garra: "); Serial.println(angleGarra);

  delay(100); 
}