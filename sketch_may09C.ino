// Codigo basado en ej_03_perilla_mapeo x montoyamoraga (v0.0.1 abril 2022)
// Hecho con Arduino Uno y IDE 1.8.19

// Recursos adicionales: ej_02_pulsador_luz_intermitente_delay
//                       ej_03_pulsador_luz_intermitente        x montoyamoraga
//                       https://forum.arduino.cc/

// Arduino Uno x Potenciometro
// 5V conectado a pin1 potenciometro (fila 1)
// A0 conectado a pin2 potenciometro (fila 3)
// GND conectado a pin3 potenciometro (fila 5)

// LED VERDE conectado a digital 6
// LED ROJO conectado a digital 4
// LED AZUL conectado a digital 2


int pinEntrada = A1;
int pinBoton = 8;


int pinVER = 6;
int pinRED = 4;
int pinBLU = 2;

int estadoLED = 0;
int estadoLED2 = 0;


// Potenciometro
int valorSensor = 0;

int valorMin = 0;
int valorMax = 1024;

int rangoMin = 0;
int rangoMax = 255;

int valorMapeado = 0;

// variable para almacenar estado pulsador
int estadoBoton = 0;

// variable para pausa de intermitencia
const long intervalo = 100;
const long intervalo2 = 200;

unsigned long tiempoAnterior = 0;
unsigned long tiempoActual = 0;



void setup() {

  // definir pin como salida digital
  pinMode(pinVER, OUTPUT);
  pinMode(pinRED, OUTPUT);
  pinMode(pinBLU, OUTPUT);

  pinMode(pinBoton, INPUT);




  // abrir comunicacion serial
  Serial.begin(9600);
}

void loop() {

  // actualizar tiempo actual
  tiempoActual = millis();

  // actualizar valor sensor
  valorSensor = analogRead(pinEntrada);

  // actualizar valor minimo
  if (valorSensor < valorMin) {
    valorMin = valorSensor;
  }

  if (valorSensor > valorMax) {
    valorMax = valorSensor;
  }

  // mapear valor
  valorMapeado = map(valorSensor, valorMin, valorMax, rangoMin, rangoMax);

  // leer pin y actualizar variable interna
  estadoBoton = digitalRead(pinBoton);


  // imprimir valores min y max
  Serial.print("actual, min, max, mapeado: ");
  Serial.print(valorSensor);
  Serial.print(", ");
  Serial.print(valorMin);
  Serial.print(", ");
  Serial.print(valorMax);
  Serial.print(", ");
  Serial.print(valorMapeado);
  Serial.print(", ");
  Serial.print(estadoBoton);
  Serial.println("");

  // prender LED VERDE segun brillo
  analogWrite(pinVER, valorMapeado);

  // prender LED ROJO cuando potenciometro llega a la mitad
  if (valorSensor > 512) {
    analogWrite(pinRED, valorMapeado);
  }

  else {
    digitalWrite(pinRED, LOW);

    // LED ROJO apagado con potenciometro a menos de la mitad
    //if (valorSensor < 512) {
    //  digitalWrite(pinRED, LOW);
  }

  // LED VERDE intermitente y prender LED AZUL cuando potenciometro llega al maximo
  if (valorSensor > 1020) {
    analogWrite(pinBLU, valorMapeado);

    // actualizar tiempo actual
    // tiempoActual = millis();

    // comprobar si tiempo transcurrido es mayor que intervalo
    if (tiempoActual - tiempoAnterior >= intervalo) {

      // actualizar tiempo previo
      tiempoAnterior = tiempoActual;

      estadoLED = !estadoLED;
      digitalWrite(pinVER, estadoLED);

    }

    if (estadoBoton == HIGH) {
      digitalWrite(pinVER, HIGH);

      // comprobar si tiempo transcurrido es mayor que intervalo
      if (tiempoActual - tiempoAnterior >= intervalo2) {

        // actualizar tiempo previo
        tiempoAnterior = tiempoActual;

        estadoLED2 = !estadoLED2;
        digitalWrite(pinRED, estadoLED2);

      }

    }

    //digitalWrite(pinVER, LOW);
    //delay(100);
    //digitalWrite(pinVER, HIGH);
    //delay(100);
  }

  else {
    digitalWrite(pinBLU, LOW);

    // LED AZUL apagado con potenciometro a menos de la mitad
    //if (valorSensor < 1020) {
    //  digitalWrite(pinBLU, LOW);
  }

  // if (valorSensor > 1020 && estadoBoton == HIGH) {
  //   digitalWrite(pinVER, HIGH);
  //   digitalWrite(pinBLU, LOW);
  //   delay(100);
  //   digitalWrite (pinBLU, HIGH);
  //   delay(100);
  // }

}
