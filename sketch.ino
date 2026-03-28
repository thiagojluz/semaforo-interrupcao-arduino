/* * Universidade Federal do Paraná (UFPR) - DELT 
 * Disciplina: Sistemas Operacionais Embarcados
 * Prática 1: Interrupções de Hardware e Troca de Contexto Manual
 * Professor: Thiago José da Luz, PhD
 * Data: 20/03/2025
 * * OBJETIVO DIDÁTICO:
 * Demonstrar o uso de ISR (Interrupt Service Routine) para tratamento de eventos 
 * assíncronos (botão de pedestre) em um sistema sem RTOS. O código evidencia a 
 * complexidade de gerenciar estados e tempos (delay) sem um scheduler (escalonador).
 */

// Definição de Hardware - Via A
#define  pinVerde_A 8
#define  pinAmarelo_A 9
#define  pinVermelho_A 10

// Definição de Hardware - Via B
#define  pinVerde_B 11
#define  pinAmarelo_B 12
#define  pinVermelho_B 13

// Interface de Pedestre
#define  pinBotao 2  // Pino com suporte a interrupção externa
#define  pinVerde_P 4
#define  pinVermelho_P 5

unsigned long delay1; // Variável para controle de debounce por software


void setup() {
  pinMode(pinVerde_A, OUTPUT);
  pinMode(pinAmarelo_A, OUTPUT);
  pinMode(pinVermelho_A, OUTPUT);
  pinMode(pinVerde_B, OUTPUT);
  pinMode(pinAmarelo_B, OUTPUT);
  pinMode(pinVermelho_B, OUTPUT); 

  pinMode(pinBotao, INPUT_PULLUP);
  pinMode(pinVerde_P, OUTPUT);
  pinMode(pinVermelho_P, OUTPUT); 

  // Estado Inicial: Pedestre em espera
  digitalWrite(pinVerde_P, LOW);
  digitalWrite(pinVermelho_P, HIGH);

  // Configuração da Interrupção: Acionada na borda de descida (FALLING)
  attachInterrupt(digitalPinToInterrupt(pinBotao), pedestre, FALLING);

  Serial.begin(9600);

}

void loop() {
  
  /* Ciclo Principal: Demonstra o uso de delays bloqueantes, 
     que seriam evitados em uma implementação com FreeRTOS */
  
  // Verde para A / Vermelho para B (15s)
  // Semáforo A
  digitalWrite(pinVerde_A, HIGH);
  digitalWrite(pinAmarelo_A, LOW);
  digitalWrite(pinVermelho_A, LOW);

  // Semáforo B
  digitalWrite(pinVerde_B, LOW);
  digitalWrite(pinAmarelo_B, LOW);
  digitalWrite(pinVermelho_B, HIGH);
  
  delay(15000);

  // Amarelo para A (5s)
  // Semáforo A
  digitalWrite(pinVerde_A, LOW);
  digitalWrite(pinAmarelo_A, HIGH);
  digitalWrite(pinVermelho_A, LOW);

  // Semáforo B
  digitalWrite(pinVerde_B, LOW);
  digitalWrite(pinAmarelo_B, LOW);
  digitalWrite(pinVermelho_B, HIGH);

  delay(5000);

  // Vermelho para A / Verde para B (15s)
  // Semáforo A
  digitalWrite(pinVerde_A, LOW);
  digitalWrite(pinAmarelo_A, LOW);
  digitalWrite(pinVermelho_A, HIGH);

  // Semáforo B
  digitalWrite(pinVerde_B, HIGH);
  digitalWrite(pinAmarelo_B, LOW);
  digitalWrite(pinVermelho_B, LOW);

  delay(15000);

  // Amarelo para B (5s)
  // Semáforo A
  digitalWrite(pinVerde_A, LOW);
  digitalWrite(pinAmarelo_A, LOW);
  digitalWrite(pinVermelho_A, HIGH);

  // Semáforo B
  digitalWrite(pinVerde_B, LOW);
  digitalWrite(pinAmarelo_B, HIGH);
  digitalWrite(pinVermelho_B, LOW);

  delay(5000);
}

/* ISR (Interrupt Service Routine): Rotina de tratamento do pedestre.
   Aqui ocorre uma 'troca de contexto' manual para salvar e restaurar estados. */
void pedestre(){
  // Salvando contexto atual dos LEDs para retomada pós-interrupção
  int ledVerde_A = digitalRead(pinVerde_A);
  int ledAmarelo_A = digitalRead(pinAmarelo_A);
  int ledVermelho_A = digitalRead(pinVermelho_A);
  int ledVerde_B = digitalRead(pinVerde_B);
  int ledAmarelo_B = digitalRead(pinAmarelo_B);
  int ledVermelho_B = digitalRead(pinVermelho_B);

  // Lógica de Debounce e execução da prioridade
  if ((millis() - delay1) > 1000){
    Serial.println("Interrupção Detectada: Pedestre solicitou travessia.");
    delay1 = millis();

    amarelo(ledVermelho_B, ledAmarelo_A); // Gerencia transição segura
    vermelho(); // Bloqueia tráfego e libera pedestre
    pisca();   // Alerta de fim de tempo de pedestre

    digitalWrite(pinVermelho_P, HIGH);
   
    // RESTAURAÇÃO DE CONTEXTO: O sistema retoma exatamente onde o loop parou
    if (ledAmarelo_A){
      digitalWrite(pinVermelho_A, HIGH);
    }else{
       digitalWrite(pinVermelho_A, ledVermelho_A);
    }

    if (ledAmarelo_B){
      digitalWrite(pinVermelho_B, HIGH);
    }else{
      digitalWrite(pinVermelho_B, ledVermelho_B);
    }

    digitalWrite(pinVerde_A, ledVerde_A);  
    digitalWrite(pinVerde_B, ledVerde_B);

  }
}

// Sub-rotinas de controle com loops de micro-atrasos 
// (Necessário pois delay() não funciona dentro de ISRs no Arduino)

void amarelo(int VB, int AA){
  Serial.println("amarelo");

  if (VB||AA) {
// Semáforo A
  digitalWrite(pinVerde_A, LOW);
  digitalWrite(pinAmarelo_A, HIGH);
  digitalWrite(pinVermelho_A, LOW);
  }
  else{
  // Semáforo B
  digitalWrite(pinVerde_B, LOW);
  digitalWrite(pinAmarelo_B, HIGH);
  digitalWrite(pinVermelho_B, LOW);
  }

  int i = 0;
  while(i < 5000){
    i++;
    delayMicroseconds(1000);

  }
  
}

void vermelho(){
  
    Serial.println("Vermelho");
    // Semáforo A
    digitalWrite(pinVerde_A, LOW);
    digitalWrite(pinAmarelo_A, LOW);
    digitalWrite(pinVermelho_A, HIGH);

    // Semáforo B
    digitalWrite(pinVerde_B, LOW);
    digitalWrite(pinAmarelo_B, LOW);
    digitalWrite(pinVermelho_B, HIGH);

    // Pedestre
    digitalWrite(pinVerde_P, HIGH);
    digitalWrite(pinVermelho_P, LOW);
 
    int i = 0;
    while(i < 10000){
    i++;
    delayMicroseconds(1000);
    }
    digitalWrite(pinVerde_P, LOW);
  
}

void pisca(){
    for(int a = 0; a < 5 ; a++){
      digitalWrite(pinVermelho_P, HIGH);
      int i = 0;
      while(i < 500){
        i++;
        delayMicroseconds(1000);
      }
    
      digitalWrite(pinVermelho_P, LOW);
      i = 0;
      while(i < 500){
        i++;
        delayMicroseconds(1000);
      }
    }

}

