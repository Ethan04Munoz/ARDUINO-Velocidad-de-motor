#include <Keypad.h>
const byte filas = 4; 
const byte columnas = 4;

// Pin donde esta conectado el MOSFET
#define GPIO_MOTOR 10

byte pinesFilas[]  = {9,8,7,6};
byte pinesColumnas[] = {5,4,3,2};
char teclas[4][4] = {{'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};
Keypad teclado1 = Keypad( makeKeymap(teclas), pinesFilas, pinesColumnas, filas, columnas); 


int equivalencia, porcentaje, e, p, duty, tiempo;
String res = "";

void setup(){  
  Serial.begin(9600);
  Serial.println("Teclado 4x4 con Biblioteca Keypad");
  Serial.println();
  pinMode(GPIO_MOTOR, OUTPUT);
}
void loop(){
  Serial.println("Ingrese el tiempo");
  char key = teclado1.getKey();
  while(key != '#')
  {
    key = teclado1.getKey();
    if(key != NO_KEY and key != '#')
    {
      Serial.print(key);
      res += key; 
    }
    delay(100); 
  }
  Serial.println("");
  tiempo = res.toInt();
  equivalencia = 255/tiempo;
  porcentaje = 100/tiempo;
  p = porcentaje;
  e = equivalencia;
  analogWrite(GPIO_MOTOR, 0);
  for(int i = 1; i <= tiempo; i++){
    Serial.println("");
    Serial.print(i);
    Serial.print(" Segundo(s)");
    Serial.println("");
    Serial.print(p);
    Serial.print(" %");
    Serial.println("");
    analogWrite(GPIO_MOTOR, e);
    p += porcentaje;
    e += equivalencia;
    delay(1000);
  }
  for(int i = 1; i <= tiempo; i++){
    p -= porcentaje;
    e -= equivalencia;
    Serial.println("");
    Serial.print(i);
    Serial.print(" Segundo(s)");
    Serial.println("");
    Serial.print(p);
    Serial.print(" %");
    Serial.println("");
    analogWrite(GPIO_MOTOR, e);
    delay(1000);
  }
  analogWrite(GPIO_MOTOR, 0);
}
