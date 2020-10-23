#include <Servo.h> 
#include <DS3231.h>
#include <Wire.h>

char *horas[]={ // PARA LA HORA EN LA QUE SE MUEVE EL SERVO
    "21:05",
    "21:08",
    "21:10",
    "21:12",
    "21:15",
    "21:18",
    "21:20",
};

long nhoras = (sizeof(horas)/sizeof(char *));
bool h12;
bool PM;
DS3231 Clock;
Servo servoMotor;
byte year, month, date, DoW, hour, minute, second;

void setup() { // Mensajes que apareceran en LCD
  Wire.begin();
  Serial.begin(9600);
}

void loop() { 
    delay(1000);
    Clock.getTime(year, month, date, DoW, hour, minute, second);
    if(deboGirar()==1)
      girar();
}

void girar(){ // Para hacer girar el servo
    servoMotor.attach(9);// PIN 9 de arduino
    int i;
  for (i=0;i<4;i++){ //i <4
    servoMotor.write(0);// posicion cero a la que se encuentra y regresara
    delay(500);
    servoMotor.write(180);// se mueve a 360 grados
    delay(1000);
    //nueva funcion
    servoMotor.write(0);
    delay(1000);
    //otra funcion
    servoMotor.write(180);// se mueve a 360 grados
    delay(1000);
  }
  servoMotor.detach();
}

int deboGirar(){// valua el momento indicado en el que girara 
  String h = "";
  String m = "";
  for(int i=0;i<nhoras;i++){
    h= getValue(horas[i], ':', 0);
    m= getValue(horas[i], ':', 1);
    hour = Clock.getHour(h12, PM);
    if(int(hour)==atoi(h.c_str()) && int(minute)==atoi(m.c_str()) && int(second)==0)
      return 1;
  }
  return 0;  
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
