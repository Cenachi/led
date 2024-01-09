// Definindo os pinos
const int triggerPin = 4;  // Pino de trigger do sensor ultrassônico
const int echoPin = 2;     // Pino de echo do sensor ultrassônico
const int ledPin = 13;     // Pino do LED

// Definindo as variáveis
long duration;
int distance;

// Inicializando a porta serial
#define SERIAL_ARDUINO Serial

void setup() {
  // Inicializando a comunicação serial
  SERIAL_ARDUINO.begin(9600);
  
  // Configurando os pinos como entrada ou saída
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Inicializando o LED desligado
  digitalWrite(ledPin, LOW);
}

void blinkLED(int duration) {
  digitalWrite(ledPin, HIGH);
  delay(duration);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Acionando o pulso no pino de trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Medindo a duração do pulso no pino de echo
  duration = pulseIn(echoPin, HIGH);

  // Convertendo a duração em centímetros
  distance = duration * 0.034 / 2;

  // Imprimindo a distância na porta serial da Arduino IDE
  SERIAL_ARDUINO.print(distance);
  SERIAL_ARDUINO.println(" cm");

  // Verificando se há dados disponíveis na porta serial da Arduino IDE
  if (SERIAL_ARDUINO.available() > 0) {
    // Lendo o comando da porta serial da Arduino IDE
    char command = SERIAL_ARDUINO.read();

    // Executando a ação correspondente ao comando
    if (command == 'A') {
      // Comando para acender o LED
      if (distance >= 1187) {
        digitalWrite(ledPin, HIGH);
      } else if (distance < 5) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    } else if (command == 'B') {
      // Comando para apagar o LED
      digitalWrite(ledPin, LOW);
    }
  }

  // Aguarda 500 milissegundos antes da próxima leitura
  delay(500);
}
