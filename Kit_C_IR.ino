#include "IR_remote.h"
#include "keymap.h"
IRremote ir(3);
#include <Servo.h>
int angulo_base;
int angulo_brazo;
int angulo_garra;
Servo servo_garra;
Servo servo_brazo;
Servo servo_base;
int DIR_A = 2 ;
int DIR_B = 4;
int PWM_A = 5 ;
int PWM_B = 6;
int speedmax = 255 ;
int speed = speedmax ;
void avanzar(int speed) {
  digitalWrite(DIR_A,HIGH);
  analogWrite(PWM_A,speed);
  digitalWrite(DIR_B,LOW);
  analogWrite(PWM_B,speed);
}
void retroceder(int speed) {
  digitalWrite(DIR_A,LOW);
  analogWrite(PWM_A,speed);
  digitalWrite(DIR_B,HIGH);
  analogWrite(PWM_B,speed);
}
void girar_derecha(int speed) {
 digitalWrite(DIR_A,HIGH);
  analogWrite(PWM_A,speed);
  digitalWrite(DIR_B,HIGH);
  analogWrite(PWM_B,speed);
}
void girar_izquierda(int speed) {
 digitalWrite(DIR_A,LOW);
  analogWrite(PWM_A,speed);
  digitalWrite(DIR_B,LOW);
  analogWrite(PWM_B,speed);
}
void detener() {
   digitalWrite(DIR_A,HIGH);
  analogWrite(PWM_A,0);
  digitalWrite(DIR_B,LOW);
  analogWrite(PWM_B,0);
}
void abrir_garra() {
angulo_garra = angulo_garra - 1;
    if (angulo_garra <= 50) {
      angulo_garra = 50;
    }
    servo_garra.write(angulo_garra);
    delay(2);
}
void cerrar_garra() {
angulo_garra = angulo_garra + 1;
    if (angulo_garra >= 180) {
      angulo_garra = 180;
    }
    servo_garra.write(angulo_garra);
    delay(2);
}
void subir_brazo() {
angulo_brazo = angulo_brazo + 1;
    if (angulo_brazo >= 180) {
      angulo_brazo = 180;
    }
    servo_brazo.write(angulo_brazo);
    delay(2);
}
void bajar_brazo() {
 angulo_brazo = angulo_brazo - 1;
    if (angulo_brazo <= 0) {
      angulo_brazo = 0;
    }
    servo_brazo.write(angulo_brazo);
    delay(2);
}
void rotar_base_horario() {
 angulo_base =  angulo_base - 1;
    if (angulo_base <= 0) {
      angulo_base = 0;

    }
    servo_base.write(angulo_base);
    delay(2);
}
void rotar_base_antihorario() {
angulo_base =  angulo_base + 1;
    if  (angulo_base >= 180) {
      angulo_base = 180;
    }
    servo_base.write(angulo_base);
    delay(2);
}

void setup()
{
  IRremote ir(3);
  angulo_base = 90;
  angulo_brazo = 90;
  angulo_garra = 90;
  servo_garra.attach(9);
  servo_brazo.attach(10);
  servo_base.attach(11);
  servo_garra.write(angulo_garra);
  delay(500);
  servo_brazo.write(angulo_brazo);
  delay(500);
  servo_base.write(angulo_base);
  delay(500);
  detener();
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
}
void loop(){
  if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_UP) {
    avanzar(speed);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_DOWN) {
    retroceder(speed);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_LEFT) {
    girar_izquierda(speed);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_RIGHT) {
    girar_derecha(speed);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_OK) {
    detener();
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_9) {
    abrir_garra() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_7) {
    cerrar_garra() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_2) {
    subir_brazo() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_8) {
   bajar_brazo() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_4) {
    rotar_base_antihorario() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_6) {
   rotar_base_horario() ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_3) {
   speed = 0.33 * speedmax ;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_5) {
   speed = 0.66 * speedmax ;
  }else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_1) {
   speed = speedmax ;
  }
}