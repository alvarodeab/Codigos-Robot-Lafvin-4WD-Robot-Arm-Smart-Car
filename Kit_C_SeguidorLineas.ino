 int sensor_izquierdo;
 int sensor_central;
 int sensor_derecho;
//Pines controlador de motores
int DIR_A = 2;
int DIR_B = 4;
int PWM_A = 5;
int PWM_B = 6;
 
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
void escanear_sensores(){
sensor_izquierdo = digitalRead(7);
sensor_central = digitalRead(8);
sensor_derecho = digitalRead(A1);
  }
void setup(){
  pinMode(7, INPUT); //Sensor Izquierdo
  pinMode(8, INPUT); //Sensor Central
  pinMode(A1, INPUT); // Sensor Derecho
   pinMode(DIR_A,OUTPUT);
  pinMode(DIR_B,OUTPUT);
  pinMode(PWM_A,OUTPUT);
  pinMode(PWM_B,OUTPUT);
}
void loop(){
  escanear_sensores();
  if(sensor_central == 1){
      if( sensor_izquierdo == 1 && sensor_derecho == 0){
        girar_izquierda(80) ; //Corregir girando a la izquierda
     } else if ( sensor_izquierdo == 0 && sensor_derecho == 1){
        girar_derecha(80) ; //Corregir girando a la derecha
     } else { //Ambos sensores sobre linea negra o blanca
        avanzar(120) ; 
      }
 } else { //Sensor central sobre linea blanca
   if( sensor_izquierdo == 1 && sensor_derecho == 0){
        girar_izquierda(120) ; //Corregir girando a la izquierda
     } else if ( sensor_izquierdo == 0 && sensor_derecho == 1){
        girar_derecha(120) ; //Corregir girando a la derecha
     } else { //Robot fuera de línea negra
        retroceder(120) ;
        delay (100) ;
        detener() ;
        delay(100) ;
      }
 }
}