//Declaración de variables
//Pines controlador de motores
int DIR_A = 2;
int DIR_B = 4;
int PWM_A = 5;
int PWM_B = 6;
//Pines Echo y Trigger del Sensor Ultrasónico
int pin_echo = 13;
int pin_trigger = 12;
float distancia ;
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
float medirDistancia(int pin_echo, int pin_trigger){  //Función que devuelve la distancia medida por el sensor del ultrasonidos
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
 
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(pin_trigger, LOW);
  
  t = pulseIn(pin_echo, HIGH); //obtenemos el ancho del pulso
  d = t/59.0;             //escalamos el tiempo a una distancia en cm
  return d ;

  }

void setup() {
  //Definimos pines de los motores como salidas.
  pinMode(DIR_A,OUTPUT);
  pinMode(DIR_B,OUTPUT);
  pinMode(PWM_A,OUTPUT);
  pinMode(PWM_B,OUTPUT);
  pinMode(pin_trigger, OUTPUT) ;
  pinMode(pin_echo,INPUT) ;
}

void loop() {
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
        } 
          }
    