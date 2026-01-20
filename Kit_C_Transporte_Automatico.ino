#include <Servo.h>
//Declaración de variables
//Pines controlador de motores
int DIR_A = 2;
int DIR_B = 4;
int PWM_A = 5;
int PWM_B = 6;
char dato = 'k' ; //variablem que almacena un caracter
int pin_servo_garra = 9 ;
int pin_servo_brazo= 10 ;
int pin_servo_base = 11 ;
// Ángulos 
int angulo_garra ;
int angulo_brazo ;
int angulo_base ;
//Banderas para funciones de los servos
bool bandera_garra_abierta = false ;
bool bandera_garra_cerrada = false  ;
bool bandera_brazo_subir = false  ;
bool bandera_brazo_bajar = false  ;
bool bandera_rotar_horario = false  ;
bool bandera_rotar_antihorario = false  ;
bool bandera_memoria_accion = false ;
int speedmax = 255; //PWM max
int speed = 0; 
int actions_count;
 int auto_count;
//Creamos 3 objetos de la clase Servo
Servo servo_garra ;
Servo servo_brazo ;
Servo servo_base ;
int angulos_garra[20]={0,0,0};
int angulos_brazo[20]={0,0,0};
int angulos_base[20]={0,0,0};
void avanzar(int speed){
  digitalWrite(DIR_A,1);
  digitalWrite(DIR_B,0);
  analogWrite(PWM_A,speed);
  analogWrite(PWM_B,speed);
}
void retroceder(int speed){
  digitalWrite(DIR_A,0);
  digitalWrite(DIR_B,1);
  analogWrite(PWM_A,speed);
  analogWrite(PWM_B,speed);
}
void girar_derecha(int speed){
  digitalWrite(DIR_A,1);
  digitalWrite(DIR_B,1);
  analogWrite(PWM_A,speed);
  analogWrite(PWM_B,speed);
}
void girar_izquierda(int speed){
  digitalWrite(DIR_A,0);
  digitalWrite(DIR_B,0);
  analogWrite(PWM_A,speed);
  analogWrite(PWM_B,speed);
}
void detener(){
 digitalWrite(DIR_A,1);
  digitalWrite(DIR_B,1);
  analogWrite(PWM_A,0);
  analogWrite(PWM_B,0);
}
void abrir_garra() {
  bandera_garra_abierta = true;
  while (bandera_garra_abierta ) {
    angulo_garra = angulo_garra - 1;
   servo_garra.write(angulo_garra);
    delay(10);
    if (angulo_garra <= 50) {
      angulo_garra = 50;
    }
    if (Serial.read() == 's') {
       bandera_garra_abierta= false;
    }
  }
}
void cerrar_garra() {
  bandera_garra_cerrada = true;
  while (bandera_garra_cerrada ) {
    angulo_garra = angulo_garra + 1;
   servo_garra.write(angulo_garra);
    delay(10);
    if (angulo_garra >= 180) {
      angulo_garra = 180;
    }
    if (Serial.read() == 's') {
       bandera_garra_cerrada= false;
    }
  }
}
void subir_brazo() {
  bandera_brazo_subir = true;
  while (bandera_brazo_subir) {
   angulo_brazo= angulo_brazo + 1;
    servo_brazo.write(angulo_brazo);
    delay(10);
    if (angulo_brazo >= 180) {
      angulo_brazo = 180;
    }
    if (Serial.read() == 's') {
      bandera_brazo_subir = false;
    }
  }
}
void bajar_brazo() {
  bandera_brazo_bajar = true;
  while (bandera_brazo_bajar) {
   angulo_brazo = angulo_brazo - 1;
    servo_brazo.write(angulo_brazo);
    delay(10);
    if (angulo_brazo <= 0) {
      angulo_brazo = 0;
    }
    if (Serial.read() == 's') {
      bandera_brazo_bajar = false;
    }
  }
}
void rotar_base_horario() {
  bandera_rotar_horario = true;
  while (bandera_rotar_horario) {
    angulo_base = angulo_base  - 1;
    servo_base.write(angulo_base );
    delay(10);
    if (angulo_base  <= 0) {
      angulo_base  = 0;
    }
    if (Serial.read() == 's') {
      bandera_rotar_horario= false;
    }
  }
}
void rotar_base_antihorario() {
  bandera_rotar_antihorario = true;
  while ( bandera_rotar_antihorario) {
    angulo_base = angulo_base  +1;
    servo_base.write(angulo_base );
    delay(10);
    if (angulo_base  >= 180) {
      angulo_base  = 180 ;
    }
    if (Serial.read() == 's') {
       bandera_rotar_antihorario= false;
    }
  }
}
void encender_rojo(){
  digitalWrite(A0, HIGH) ;
  digitalWrite(A2, LOW) ;
  digitalWrite(A3, LOW) ;
  }
  void encender_verde(){
  digitalWrite(A0, LOW) ;
  digitalWrite(A2, HIGH) ;
  digitalWrite(A3, LOW) ;
  }
  void encender_azul(){
  digitalWrite(A0, LOW) ;
  digitalWrite(A2, LOW) ;
  digitalWrite(A3, HIGH) ;
  }
void guardar_angulos(){
  detener() ;
  encender_verde() ;
  delay(500) ; //Espera de 0.5s para que se aprecie el led en verde.
if (actions_count <= 19) {
    angulos_garra[actions_count] = servo_garra.read() ;
    delay(50);
    angulos_brazo[actions_count] = servo_brazo.read() ;
    delay(50);
    angulos_base[actions_count] = servo_base.read() ;
    delay(50);
    actions_count = actions_count + 1;
    auto_count = actions_count;
  }
  encender_azul() ;
  }
void transporte_automatico(){
  detener() ;
  encender_rojo() ;
  if (0 != auto_count) {
    bandera_memoria_accion = true;
  }
  actions_count = 0;
  angulo_garra = servo_garra.read();
  angulo_brazo = servo_brazo.read();
  angulo_base = servo_base.read();
  while (bandera_memoria_accion) {
    for (int i = (1); i <= (auto_count); i = i + (1)) {
      if (Serial.read() == 's') {
        bandera_memoria_accion = false;
        break;
      }
      if (angulo_garra < angulos_garra[(int)(i - 1)]) {
        while (angulo_garra < angulos_garra[(int)(i - 1)]) {
          angulo_garra = angulo_garra + 1;
          servo_garra.write(angulo_garra);
          delay(15);
        }
      } else {
        while (angulo_garra > angulos_garra[(int)(i - 1)]) {
          angulo_garra = angulo_garra - 1;
          servo_garra.write(angulo_garra);
          delay(15);
        }
      }
      if (Serial.read() == 's') {
        bandera_memoria_accion = false;
        break;
      }
      if (angulo_brazo < angulos_brazo[(int)(i - 1)]) {
        while (angulo_brazo < angulos_brazo[(int)(i - 1)]) {
          angulo_brazo = angulo_brazo + 1;
          servo_brazo.write(angulo_brazo);
          delay(15);
        }
      } else {
        while (angulo_brazo > angulos_brazo[(int)(i - 1)]) {
          angulo_brazo = angulo_brazo - 1;
          servo_brazo.write(angulo_brazo);
          delay(15);
        }
      }
      if (Serial.read() == 's') {
        bandera_memoria_accion = false;
        break;
      }
      if (angulo_base < angulos_base[(int)(i - 1)]) {
        while (angulo_base < angulos_base[(int)(i - 1)]) {
          angulo_base = angulo_base + 1;
          servo_base.write(angulo_base);
          delay(15);
        }
      } else {
        while (angulo_base > angulos_base[(int)(i - 1)]) {
          angulo_base = angulo_base - 1;
          servo_base.write(angulo_base);
          delay(15);
        }
      }
      if (Serial.read() == 's') {
        bandera_memoria_accion = false;
        break;
      }
    }
  }
  encender_azul();
}
void setup() {
  //Definimos pines de los motores como salidas.
  pinMode(DIR_A,OUTPUT);
  pinMode(DIR_B,OUTPUT);
  pinMode(PWM_A,OUTPUT);
  pinMode(PWM_B,OUTPUT);
  angulo_garra = 90 ;
  angulo_brazo = 90 ;
  angulo_base = 90 ;
  servo_garra.attach(pin_servo_garra) ;
  servo_brazo.attach(pin_servo_brazo) ;
  servo_base.attach(pin_servo_base) ;
  servo_garra.write(angulo_garra) ;
  servo_brazo.write(angulo_brazo) ;
  servo_base.write(angulo_base) ;
  Serial.begin(9600) ; //Iniciamos comunicación serie
}
void programa_principal()    {
if(Serial.available() > 0){
  encender_azul() ;
    dato = Serial.read() ;
      if (dato == 'F') {
        avanzar(speed) ;
        }
      else if (dato == 'B'){
        retroceder(speed) ;
    }
     else if (dato == 'R'){
        girar_derecha(speed) ;
    }
    else if (dato == 'L'){
        girar_izquierda(speed) ;
    }
    else if (dato == 'o'){
        abrir_garra() ;
    }
    else if (dato == 'c'){
        cerrar_garra() ;
    }
    else if (dato == 'u'){
        subir_brazo() ;
    }
    else if (dato == 'd'){
        bajar_brazo() ;
    }
    else if (dato == 'r'){
        rotar_base_horario() ;
    }
    else if (dato == 'l'){
        rotar_base_antihorario() ;
    }
    else if (dato == 'X'){
        speed = 0.33 * speedmax ;
    }
    else if (dato == 'Y'){
        speed = 0.66* speedmax ;
    }
    else if (dato == 'Z'){
        speed = speedmax ;
    }
    else if (dato == 'm'){
        guardar_angulos();
    }
    else if (dato == 'a'){
        transporte_automatico();
    }
    else{
      detener() ;
      }
 }
                                 }
void loop() {
  programa_principal() ;
          }