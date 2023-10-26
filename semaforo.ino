#include <Servo.h>

int servo = 6; // Porta Digital 6 PWM
Servo s; // Variável Servo
int pos; // Posição Servo

int ledverde = 8;
int ledvermelho = 9;

int trigPin = 3;
int echoPin = 2;
long duration;
int distance;

int bzr = 10;

void iniciar() {
  Serial.begin(9600);

  Serial.print("Iniciando...");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  s.attach(servo);
  s.write(0); // Inicia motor posição zero

  pinMode(ledverde, OUTPUT);
  pinMode(ledvermelho, OUTPUT);

  pinMode(bzr, OUTPUT); // Buzzer

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledvermelho, HIGH);
    digitalWrite(ledverde, HIGH);
    delay(500);
    digitalWrite(ledvermelho, LOW);
    digitalWrite(ledverde, LOW);
    delay(500);
  }
}

void fecharVia() {
  digitalWrite(ledvermelho, HIGH);
  digitalWrite(ledverde, LOW);
  for (pos = 0; pos < 180; pos++)
  {
    s.write(pos);
    delay(15);
  }
  delay(3000);
}

void abrirVia() {
  for (pos = 180; pos >= 0; pos--)
  {
    s.write(pos);
    delay(15);

  }
  digitalWrite(ledverde, HIGH);
  digitalWrite(ledvermelho, LOW);
  delay(3000);
}

void somMulta() {
  for (int i = 0; i < 3; i++) {
    tone(bzr, 500);
    delay(250);
    noTone(bzr);
    delay(250);
  }
}

void lerDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void setup ()
{
  iniciar();
}
void loop()
{
  fecharVia();
  lerDistancia();
  if (distance < 20 && distance > 0) {
    somMulta();
  }
  abrirVia();
}
