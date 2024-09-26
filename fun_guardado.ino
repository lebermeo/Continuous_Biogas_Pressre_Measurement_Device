

#include <SoftwareSerial.h> //libreria para emular puertos seriales
SoftwareSerial SerialBLE(5,6); // RX, TX

#include "guardar.h" //almacena las variables y funciones para la escritura/lectura en la SD
#include "set_get.h" //almacena las diferentes funciones de envio/recepcion de datos

const int sp1= A0,sp2= A1,sp3= A2, sp4= A3, in_led = 4; 
float presion1=0,presion2=0,presion3=0,presion4=0;
byte sensor_act= 1; // Led indicador de actividad del dispositivo
int hora=0, minutos=0,segundos=0 ;
String fechahora ;
//variable del filtro
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
  inicializacion(); //inicializacion modulos RTC y SD
}

void loop()
{
  //Esta fumcion se activa cuando recibe valores a travez del Serial
  // por parte del Es-01
  if(SerialBLE.available()> 0){
    serial();
   }
  
    //escalamiento de la señal de voltage a presion (mbar)
    presion1 = lectura(analogRead(sp1),0);
    presion2 = lectura(analogRead(sp2),1);
    presion3 = lectura(analogRead(sp3),2);
    presion4 = lectura(analogRead(sp4),3);

  //Serial.println(presion1);
  //Serial.print(",");
  //Serial.print((analogRead(sp1)/10));
  //Serial.println(",");

  /*Verifica estado de funcionamiento y conexion de los modulos */
  /*if(!(segundos == obtener_segundos())){
    segundos = obtener_segundos();
    
    if(chek_rtc_sd == false){             // Establece el led indicador en bajo en caso de
      digitalWrite(in_led,LOW);           // error en la tarjeta SD o el modulo RTC    
    }else{
       if(sensor_act == 0){ //Condicion para la realizacion del guradado de datos
         Serial.println("Se detuvo");
         Serial.println(sensor_act);
         digitalWrite(in_led,HIGH); //indica que el muestreado de los datos se ha detenido
       }else{
          
          // Control de led indicador de actividad de tarjeta SD
          digitalWrite(in_led, 1-digitalRead(in_led));   // toggle LED pin 
       }
    }
     //Envio de datos al ESP- 01
     set_data(presion1,presion2,presion3,presion4); 
  }*/

  /*Esta funcion obtiene la hora y fecha cada minuto y se envia por 
  comunicacion serial al EsP-01 para mostrar en el panel de control*/
  if(!(minutos == obtener_minutos())){
    fechahora = fecha_hora();
    minutos =obtener_minutos();
    set_fechahora(fechahora);  
    Serial.println("hora y fecha enviada");
  }
  /*Verifica si la opcion de muestreo del equipo esta activa y 
   * registra el valor de cada sensor cada hora
   */
  if((chek_rtc_sd == true)){
    //LLamado a la funcion registrar para el registro de datos en la tarjeta SD
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

 /*Serial(): Recibe los datos entrantes por comunicacion serial y llama la funcion
   segun el caso el cual es indicado por la variable flag(--> bandera)
   caracter identificado del tipo de informacion que llega a traves de la 
   comunicacion serial*/
    
void serial(){
  /*Esta funcion recibe los datos que llegan al puerto serial y de acuerdo a la variable flag
   * realiza las funciones necesarias dependiendo el tipo de informacion que llegue, el cual 
   * esta determinado por el valor que reciba "flag"
   */
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
    if(chek_rtc_sd == false){             // Establece el led indicador en bajo en caso de
      digitalWrite(in_led,LOW);           // error en la tarjeta SD o el modulo RTC    
    }else{
       if(sensor_act == 0){ //Condicion para la realizacion del guradado de datos
         Serial.println("Se detuvo");
         Serial.println(sensor_act);
         digitalWrite(in_led,HIGH); //indica que el muestreado de los datos se ha detenido
       }else{
          
          // Control de led indicador de actividad de tarjeta SD
          digitalWrite(in_led, 1-digitalRead(in_led));   // toggle LED pin 
       } 
  }
  //Envio de datos al ESP- 01
   set_data(presion1,presion2,presion3,presion4); 
}

/*Funcion de lectura: Procesa las señales de 
  voltaje y las escala a mbar */
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

//Funcion de filtro 
float filtro(float pr,byte j){
  float presfil;

  presfil= (alpha*pr)+ ((1-alpha)*pres_anterior[j]);
  pres_anterior[j]= presfil;
  return presfil;
}

//Funcion de calibracion
float calibracion(float pres){
  float prescal;
  
  return prescal;
}
