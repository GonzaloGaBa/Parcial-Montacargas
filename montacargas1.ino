// C++ code
// Configuración de los pines para el visualizador de 7 segmentos
#define PIN_A 10
#define PIN_B 11
#define PIN_C 5
#define PIN_D 6
#define PIN_E 7
#define PIN_F 9
#define PIN_G 8

// Configuración de los pines para los botones y LEDs
#define PIN_BOTON_SUBIR 2
#define PIN_BOTON_BAJAR 3
#define PIN_BOTON_PAUSAR 4
#define PIN_LED_VERDE 13
#define PIN_LED_ROJO 12

// Variables para el control del montacargas
int pisoActual = 0; // El montacargas comienza en el piso 1
int pisoAnterior = 1; // Variable para almacenar el piso anterior
bool enMovimiento = false;
bool enPausa = false;
bool mostrarMensaje = false; // Variable para controlar la visualización del mensaje

void setup() {
  // Configuración de los pines
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);

  pinMode(PIN_BOTON_SUBIR, INPUT_PULLUP);
  pinMode(PIN_BOTON_BAJAR, INPUT_PULLUP);
  pinMode(PIN_BOTON_PAUSAR, INPUT_PULLUP);

  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);

  // Inicialización del monitor serial
  Serial.begin(9600);
  Serial.println("El montacargas esta listo para su uso.");
  mostrarMensaje = true;
}

void loop() {
  // Actualizar el display de 7 segmentos
  actualizarDisplay();

  // Comprobar el estado de los botones
  bool botonSubirPresionado = digitalRead(PIN_BOTON_SUBIR) == LOW;
  bool botonBajarPresionado = digitalRead(PIN_BOTON_BAJAR) == LOW;
  bool botonPausarPresionado = digitalRead(PIN_BOTON_PAUSAR) == LOW;

  if (botonSubirPresionado) 
  {
    if (pisoActual < 10) {
      pisoActual++;
      iniciarMovimiento();
    }
  }

  if (botonBajarPresionado) 
  {
    if (pisoActual > 0) {
      pisoActual--;
      iniciarMovimiento();
    }
  }

  if (botonPausarPresionado ) {
    pausarMovimiento();
  }

 

  // Detener el montacargas si ha llegado al piso deseado (piso 10 en este caso)
  if (pisoActual == 10) {
    detenerMontacargas();
  }
  // Mostrar el piso actual por el monitor serial solo si ha cambiado
  if (pisoActual != pisoAnterior && mostrarMensaje) {
    Serial.print("Piso actual: ");
    Serial.println(pisoActual);
    pisoAnterior = pisoActual;
    mostrarMensaje = false; // Reiniciar la variable para evitar repeticiones
  }
}

// Función para actualizar el display de 7 segmentos con el piso actual
void actualizarDisplay() {
  // Lógica para mostrar el piso actual en el display de 7 segmentos
  switch (pisoActual) {
    case 0:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, HIGH);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, LOW);
      break;
    case 1:
      digitalWrite(PIN_A, LOW);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, LOW);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, LOW);
      digitalWrite(PIN_G, LOW);
      break;
    case 2:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, LOW);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, HIGH);
      digitalWrite(PIN_F, LOW);
      digitalWrite(PIN_G, HIGH);
      break;
    case 3:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, LOW);
      digitalWrite(PIN_G, HIGH);
      break;
    case 4:
      digitalWrite(PIN_A, LOW);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, LOW);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
    case 5:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, LOW);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
    case 6:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, LOW);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, HIGH);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
    case 7:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, LOW);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, LOW);
      digitalWrite(PIN_G, LOW);
      break;
    case 8:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, HIGH);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
    case 9:
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, HIGH);
      digitalWrite(PIN_E, LOW);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
    default:
      // Mostrar un guion "-" si el piso actual está fuera del rango de 0 a 9
      digitalWrite(PIN_A, HIGH);
      digitalWrite(PIN_B, HIGH);
      digitalWrite(PIN_C, HIGH);
      digitalWrite(PIN_D, LOW);
      digitalWrite(PIN_E, HIGH);
      digitalWrite(PIN_F, HIGH);
      digitalWrite(PIN_G, HIGH);
      break;
  }
}

// Función para iniciar el movimiento del montacargas
void iniciarMovimiento() {
  enMovimiento = true;
  digitalWrite(PIN_LED_VERDE, HIGH);
  digitalWrite(PIN_LED_ROJO, LOW);
  
  delay(3000); // Tiempo de trayecto entre pisos (3 segundos)
  
  mostrarMensaje = true; // Activar la visualización del mensaje
}

// Función para pausar el movimiento del montacargas
void pausarMovimiento() {
  if (enMovimiento) {
    enMovimiento = false;
    enPausa = true;
    digitalWrite(PIN_LED_VERDE, LOW);
    digitalWrite(PIN_LED_ROJO, HIGH);
  } else if (enPausa) {
    enMovimiento = true;
    enPausa = false;
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(PIN_LED_ROJO, LOW);
  }
}

// Función para detener el montacargas
void detenerMontacargas() {
  enMovimiento = false;
  enPausa = false;
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_ROJO, HIGH);
  Serial.println("El montacargas ha llegado al piso deseado.");
  Serial.println(pisoActual);
}
