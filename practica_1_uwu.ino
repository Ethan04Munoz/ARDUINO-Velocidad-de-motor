#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
const byte filas = 4; 
const byte columnas = 4;

// Pin donde esta conectado el MOSFET
#define GPIO_MOTOR 10

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,16,2);  //


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
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");
  delay(1000);
  lcd.clear();
  pinMode(GPIO_MOTOR, OUTPUT);
}
void loop(){
  lcd.print("Ingrese el tiempo");
  char key = teclado1.getKey();
  while(key != '#')
  {
    key = teclado1.getKey();
    if(key != NO_KEY and key != '#')
    {
      lcd.print(key);
      res += key; 
    }
    delay(100); 
  }
  lcd.print("");
  tiempo = res.toInt();
  equivalencia = 255/tiempo;
  porcentaje = 100/tiempo;
  p = porcentaje;
  e = equivalencia;
  analogWrite(GPIO_MOTOR, 0);
  for(int i = 1; i <= tiempo; i++){
    lcd.print("");
    lcd.print(i);
    lcd.print(" Segundo(s)");
    lcd.print("");
    lcd.print(p);
    lcd.print(" %");
    lcd.print("");
    analogWrite(GPIO_MOTOR, e);
    p += porcentaje;
    e += equivalencia;
    delay(1000);
  }
  for(int i = 1; i <= tiempo; i++){
    p -= porcentaje;
    e -= equivalencia;
    lcd.print("");
    lcd.print(i);
    lcd.print(" Segundo(s)");
    lcd.print("");
    lcd.print(p);
    lcd.print(" %");
    lcd.print("");
    analogWrite(GPIO_MOTOR, e);
    delay(1000);
  }
  analogWrite(GPIO_MOTOR, 0);
}
