#include <Servo.h>
//Declaración de variables
//Pines controlador de motores
int DIR_A = 2;
int DIR_B = 4;
int PWM_A = 5;
int PWM_B = 6;
char dato = 'a' ; //variablem que almacena un caracter
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
int speedmax = 255; //PWM max
int speed = speedmax; 
//Creamos 3 objetos de la clase Servo
Servo servo_garra ;
Servo servo_brazo ;
Servo servo_base ;
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
void loop() {
  if(Serial.available() > 0){
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
    else{
      detener() ;
      }
 }
            }