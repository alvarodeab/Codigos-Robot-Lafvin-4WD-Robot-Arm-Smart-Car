#include <Servo.h>
//Declaración de variables
//Pines controlador de motores
int DIR_A = 2; int DIR_B = 4;
int PWM_A = 5; int PWM_B = 6;
char datoBT = 'k' ; //variable que almacena un caracter
int pin_servo_garra = 9 ; //
int pin_servo_brazo= 10 ; //Pines de los servos
int pin_servo_base = 11 ; //
//Pines Echo y Trigger del Sensor Ultrasónico
int pin_echo = 13;
int pin_trigger = 12;
 int angulo_base;  //
 int angulo_brazo; // Ángulos de los tres servos.
 int angulo_garra; //
 //Banderas para funciones de los servos
 bool bandera_garra_cerrada = false;
 bool bandera_garra_abierta = false;
 bool bandera_brazo_subir = false;
 bool bandera_brazo_bajar = false;
 bool bandera_rotar_antihorario = false;
 bool bandera_rotar_horario = false;
 //Banderas para modos de operación
 bool action_memory = false ;
 bool bandera_modo_evasor_obstaculos ;
 bool bandera_modo_seguidor ;
 bool bandera_modo_anticaidas ;
 bool bandera_modo_seguidor_lineas ;
 bool bandera = false ;
 int sensor_izq ;     
 int sensor_central ; //Señales de sensores infrarrojos
 int sensor_der ;  
 float distancia ;
 int contador_posiciones;
 int contador_automatico;
 int speedmax ;
 int speed ;
int angulos_garra[20]={0,0,0};
int angulos_brazo[20]={0,0,0}; //Arreglos para guardar angulos
int angulos_base[20]={0,0,0};
Servo servo_garra; //
Servo servo_brazo; // Objetos de la clase servo
Servo servo_base; //+
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
float medirDistancia(int pin_echo, int pin_trigger){  //Función que devuelve la distancia medida por el sensor del ultrasonidos
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(pin_trigger, LOW);
  t = pulseIn(pin_echo, HIGH); //obtenemos el ancho del pulso
  d = t/59.0;             
  return d ;
  }
void escanear_sensores(){
sensor_izq = digitalRead(7);
sensor_central = digitalRead(8);
sensor_der = digitalRead(A1);
  }
void encender_rojo(){
    digitalWrite(A0, 1) ;
    digitalWrite(A2, 0) ;
    digitalWrite(A3, 0) ;
    }
  void encender_verde(){
    digitalWrite(A0, 0) ;
    digitalWrite(A2, 1) ;
    digitalWrite(A3, 0) ;
    }
    void encender_azul(){
    digitalWrite(A0, 0) ;
    digitalWrite(A2, 0) ;
    digitalWrite(A3, 1) ;
    }
    void encender_amarillo(){
    digitalWrite(A0, 1) ;
    digitalWrite(A2, 1) ;
    digitalWrite(A3, 0) ;
    }
    void encender_morado(){
    digitalWrite(A0, 1) ;
    digitalWrite(A2, 0) ;
    digitalWrite(A3, 1) ;
    }
   void encender_celeste(){
    digitalWrite(A0, 0) ;
    digitalWrite(A2, 1) ;
    digitalWrite(A3, 1) ;
    }
  void encender_blanco(){
    digitalWrite(A0, 0) ;
    digitalWrite(A2, 1) ;
    digitalWrite(A3, 1) ;
    }
void f_evasor_obstaculos() { //MODO 2
  bandera_modo_evasor_obstaculos = true ;
  while (bandera_modo_evasor_obstaculos) {
    distancia = medirDistancia(pin_echo,pin_trigger) ;
  if( distancia > 25 ){
    avanzar(70) ;
} else {
  if( distancia  < 15 ){
   detener() ;
   delay(100) ;
   retroceder(100) ;
   delay(600) ;
  } else { //La distancia se encuentra entre 15 y 25 cm
    detener() ;
    delay(100) ;
    girar_izquierda(100) ;
    delay(600) ;
       } if( Serial.read() == 'S'){
    bandera_modo_evasor_obstaculos = false ;
     detener() ;
    encender_azul() ;
  }
        } 
  }
}
void f_seguidor() { //MODO 3
  bandera_modo_seguidor = true ;
  detener() ;
  encender_amarillo() ;
  while (bandera_modo_seguidor ) {
    distancia = medirDistancia(pin_echo,pin_trigger) ;
  if( distancia > 30 ){
    detener() ;
} else {
  if( distancia > 25 && distancia < 30 ){
   avanzar(100);
  } else { //La distancia se encuentra entre 15 y 25 cm
if( distancia > 20 && distancia < 25 ){
   avanzar(80);
  } 
  else { 
if( distancia > 15 && distancia < 20 ){
   detener() ;
  } else {
      retroceder(80) ;
    } 
      } 
       } 
        } if( Serial.read() == 'S'){
    bandera_modo_seguidor = false ;
     detener() ;
    encender_azul() ;
  }
  }
}
void f_seguidor_lineas() { //MODO 4
  bandera_modo_seguidor_lineas = true;
  encender_morado() ;
  while (bandera_modo_seguidor_lineas) {
     escanear_sensores();
  if(sensor_central == 1){
      if(sensor_izq == 1 && sensor_der == 0){
        girar_izquierda(80) ; //Corregir girando a la izquierda
     } else if (sensor_izq  == 0 && sensor_der == 1){
        girar_derecha(80) ; //Corregir girando a la derecha
     } else { //Ambos sensores sobre linea negra o blanca
        avanzar(120) ; 
      }
 } else { //Sensor central sobre linea blanca
   if( sensor_izq  == 1 && sensor_der == 0){
        girar_izquierda(120) ; //Corregir girando a la izquierda
     } else if ( sensor_izq  == 0 && sensor_der== 1){
        girar_derecha(120) ; //Corregir girando a la derecha
         } else { //Robot fuera de línea negra
        retroceder(120) ;
        delay (100) ;
        detener() ;
        delay(100) ;
      }
 } if( Serial.read() == 'S'){
    bandera_modo_seguidor_lineas = false ;
     detener() ;
    encender_azul() ;
  }
  }
}
void f_anticaidas() { //MODO 5
  bandera_modo_anticaidas = true;
  detener() ;
  encender_blanco() ;
  while (bandera_modo_anticaidas) {
  escanear_sensores();
  if (sensor_izq == 0 && sensor_central == 0 && sensor_der == 0  ) {  
    avanzar(60) ;
} else {
    retroceder(60) ;
    delay(600) ;
    girar_izquierda(60) ;
    delay(500) ;
  }
  if( Serial.read() == 'S'){
    bandera_modo_anticaidas = false ;
    detener() ;
    encender_azul() ;
  }
}
}
void f_guardar_angulos() { //MODO 6
  detener() ;
  encender_verde() ;
  delay(500) ; // Espera para poder observar el color verde
  if (contador_posiciones <= 19) {
    angulos_garra[(int)((contador_posiciones + 1) - 1)] = servo_garra.read();
    delay(50);
    angulos_brazo[(int)((contador_posiciones + 1) - 1)] = servo_brazo.read();
    delay(50);
    angulos_base[(int)((contador_posiciones + 1) - 1)] = servo_base.read();
    delay(50);
    contador_posiciones = contador_posiciones + 1;
    contador_automatico = contador_posiciones;
}
encender_azul() ;
  }
void f_transporte_automatico() { //MODO 7
  detener() ;
  encender_celeste() ;
  if (0 != contador_automatico) {
    action_memory = true;
  }
  contador_posiciones = 0;
  angulo_garra = servo_garra.read();
  angulo_brazo = servo_brazo.read();
  angulo_base = servo_base.read();
  while (action_memory) {
    for (int i = (1); i <= (contador_automatico); i = i + (1)) {
      if (Serial.read() == 's') {
        action_memory = false;
        encender_azul() ;
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
        action_memory = false;
        encender_azul() ;
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
        action_memory = false;
        encender_azul() ;
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
        action_memory = false;
        encender_azul() ;
        break;
      }
    }
  }
encender_azul() ;
}
  void programa_principal() {
    if(Serial.available() > 0){
    datoBT = Serial.read() ;
    if(bandera == false ){
      while( !( Serial.read() == 'S') ){
            delay(5) ;
         }
         encender_azul() ;
         datoBT = Serial.read() ;
         bandera = true ;
      }
      if (datoBT == 'F') {
        avanzar(speed) ;
        }
      else if (datoBT == 'B'){
        retroceder(speed) ;
    }
     else if (datoBT == 'R'){
        girar_derecha(speed) ;
    }
    else if (datoBT == 'L'){
        girar_izquierda(speed) ;
    }
    else if (datoBT == 'o'){
        abrir_garra() ;
    }
    else if (datoBT == 'c'){
        cerrar_garra() ;
    }
    else if (datoBT == 'u'){
        subir_brazo() ;
    }
    else if (datoBT == 'd'){
        bajar_brazo() ;
    }
    else if (datoBT == 'r'){
        rotar_base_horario() ;
    }
    else if (datoBT == 'l'){
        rotar_base_antihorario() ;
    }
    else if (datoBT == 'X'){
        speed = 0.33 * speedmax ;
    }
    else if (datoBT == 'Y'){
        speed = 0.66* speedmax ;
    }
    else if (datoBT == 'Z'){
        speed = speedmax ;
    }
    else if (datoBT == 'A'){
        f_evasor_obstaculos() ;
    }
     else if (datoBT == 'W'){
        f_seguidor();
    }
    else if (datoBT == 'T'){
        f_seguidor_lineas() ;
    }
     else if (datoBT == 'D'){
        f_anticaidas() ;
    }
     else if (datoBT == 'm'){
        f_guardar_angulos() ;
    }
     else if (datoBT == 'a'){
        f_transporte_automatico() ;
    }
    else{
      detener() ;
      }
 }
                }
void setup(){
  bandera = false ;
  angulo_base = 90;
  angulo_brazo = 90;
  angulo_garra = 90;
  action_memory = false;
  distancia = 0;
  contador_posiciones = 0;
  contador_automatico = 0;
  speedmax = 255 ;
  speed = speedmax ;
  servo_garra.attach(pin_servo_garra);
  servo_brazo.attach(pin_servo_brazo);
  servo_base.attach(pin_servo_base);
  servo_garra.write(angulo_garra);
  delay(500);
  servo_brazo.write(angulo_brazo);
  delay(500);
  servo_base.write(angulo_base);
  delay(500);
  detener();
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(A1, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  pinMode(A0, OUTPUT) ;
  pinMode(A2, OUTPUT) ;
  pinMode(A3, OUTPUT) ;
  Serial.begin(9600); //Iniciar comunicacion serie a 9600 bds
}
void loop(){
  programa_principal() ;
  }