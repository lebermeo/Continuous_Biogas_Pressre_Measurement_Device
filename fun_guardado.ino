

#include <SoftwareSerial.h> //library to emulate serial ports
SoftwareSerial SerialBLE(5,6); // RX, TX

#include "guardar.h" //stores the variables and functions for writing/reading to SD
#include "set_get.h" //stores the different send/receive data functions

const int sp1= A0,sp2= A1,sp3= A2, sp4= A3, in_led = 4; 
float presion1=0,presion2=0,presion3=0,presion4=0;
byte sensor_act= 1; // Led indicator of activity of the devices
int hora=0, minutos=0,segundos=0 ;
String fechahora ;

  float pres_anterior[4], alpha = 0.005;

void in_temp()
{
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  //OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  OCR1A = 62500;          // compare match register 16MHz/256/1Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  
}

void setup()
{
  in_temp();
  Serial.begin(9600);
  SerialBLE.begin(9600);
  pinMode(in_led,OUTPUT);
  digitalWrite(in_led,HIGH);//declaracion del led indicador del SD
  inicializacion(); //initialization of RTC and SD modules
}

void loop()
{
  //This function is activated when it receives values through the serial port from the Esp-01
  
  if(SerialBLE.available()> 0){
    serial();
   }
  
    presion1 = lectura(analogRead(sp1),0);
    presion2 = lectura(analogRead(sp2),1);
    presion3 = lectura(analogRead(sp3),2);
    presion4 = lectura(analogRead(sp4),3);

  //Serial.println(presion1);
  //Serial.print(",");
  //Serial.print((analogRead(sp1)/10));
  //Serial.println(",");

  /*Verify the operating and connection status of the modules */
  /*if(!(segundos == obtener_segundos())){
    segundos = obtener_segundos();
    
    if(chek_rtc_sd == false){             
      digitalWrite(in_led,LOW);             
    }else{
       if(sensor_act == 0){ 
         Serial.println("Se detuvo");
         Serial.println(sensor_act);
         digitalWrite(in_led,HIGH); 
       }else{
          digitalWrite(in_led, 1-digitalRead(in_led));   // toggle LED pin 
       }
    }
     set_data(presion1,presion2,presion3,presion4); 
  }*/

  /*This function obtains the time and date every minute and sends it via serial communication to the EsP-01 for display on the control panel*/
  if(!(minutos == obtener_minutos())){
    fechahora = fecha_hora();
    minutos =obtener_minutos();
    set_fechahora(fechahora);  
    Serial.println("hora y fecha enviada");
  }
  /*Verify whether the sampling option of the device is active and 
   * record the value of each sensor every hour
   */
  if((chek_rtc_sd == true)){
    if(!(hora == obtener_hora())){
        hora= obtener_hora();
        if(a_sensor1== true){
          registrar("sensor_1",presion1);
        }
        if(a_sensor2== true){
           registrar("sensor_2",presion2);
        }
        if(a_sensor3== true){
          registrar("sensor_3",presion3);
        }
        if(a_sensor4== true){
          registrar("sensor_4",presion4);
        }   
    }
  }
  
}
    
void serial(){
  String cmd="",flag="";
  cmd=SerialBLE.readStringUntil('\n');   
  flag= cmd.substring(0,1);
  
  if (flag== "b"){
    sensor_act=get_data(cmd);
  }
  if (flag== "/"){
    get_datasensores(cmd);
  }
  if (flag== "f"){
    get_fecha(cmd);
    delay(100);
    set_fechahora(fechahora); 
  }
}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{ 
  //Serial.println(sensor_act);
    if(chek_rtc_sd == false){             
      digitalWrite(in_led,LOW);              
    }else{
       if(sensor_act == 0){ 
         Serial.println("Se detuvo");
         Serial.println(sensor_act);
         digitalWrite(in_led,HIGH); 
       }else{
          digitalWrite(in_led, 1-digitalRead(in_led));   // toggle LED pin 
       } 
  }
   set_data(presion1,presion2,presion3,presion4); 
}

/*Read Function */
float lectura(float lect,byte i){ 
  float pres;
  int lectpres;
    
    pres = ((lect/1023)*5)*1000; // volts
    pres = map(pres, 0, 3800 , 0, 6000);
    pres= pres/10; //mbar
    pres= filtro(pres,i);
    lectpres = map(pres, 0, 600 , 0, 600);
    
  return lectpres;
}

//Filter Function
float filtro(float pr,byte j){
  float presfil;

  presfil= (alpha*pr)+ ((1-alpha)*pres_anterior[j]);
  pres_anterior[j]= presfil;
  return presfil;
}

//Calibration Function
float calibracion(float pres){
  float prescal;
  
  return prescal;
}
