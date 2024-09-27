#define BLYNK_TEMPLATE_ID           "TMPLUXu0rgO7"
#define BLYNK_DEVICE_NAME           "SIPBI 3"

//#define BLYNK_PRINT Serial

#include "serv.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//#include <WiFiClient.h>
//include <ESP8266WebServer.h >

// Authentication Codes for each devices on BLYNK app
//char auth[] = "xWlOcjiKAlA6Dm_fANZJELx9245M-_JR"; //SIPBI_1
//char auth[] = "es5e073chuWMNetzMLdN4_vnqsvrU0R7"; //SIPBI_2
char auth[] = "1Hj-1-2arabelCSn-pdlIUD5AmQs-FHq"; //SIPBI_3
//char auth[] = "0XGtPW1QdTZjJRw_7qnmgdNnrqQ3d1bY"; //SIPBI_4
//char auth[] = "zOApKi6rJrjzndiYGcQbV0g1iG5fQrbU"; //SIPBI_5
//char auth[] = "u0WOXBhZLSzPYbinCeoCXOgxss90R5oL"; //SIPBI_6
float presion1=0,presion2=0,presion3=0,presion4=0; 
String hora;

BlynkTimer timer; // inicializacion del timer de Blynk

void myTimerEvent()
{
  // Precaution: Don't send  than 10 data per second.
  // send data to Blynk Server
    Blynk.virtualWrite(V1, presion1);
    Blynk.virtualWrite(V2, presion2);
    Blynk.virtualWrite(V3, presion3);
    Blynk.virtualWrite(V4, presion4);
    
}

void setup() {
  //delay(500);
  Serial.begin(9600);
  openFS();
  serv_inicio();
  //writecredencials("Lemos", "021"); //credentials
  credenciales(); 
  verificacion(); 
  Blynk.config(auth); 
  timer.setInterval(1000L, myTimerEvent); 
  
}

void loop() {
/* only run BLYNK if there is WIFI conection */
if(WiFi.status() == WL_CONNECTED){
 Blynk.run(); 
 timer.run(); 
}
 if(est==true){
  verificacion();
 }
 
}


//Function that receive data obtained by arduino nano
void get_data(String cmd){

  String cmd1="", cmd2="", cmd3="", cmd4="";
  
    //Serial.println(cmd);
    //Serial.println(cmd.substring(cmd.indexOf('g'),cmd.indexOf('g')+1));
 if (cmd.substring(cmd.indexOf('g'),cmd.indexOf('g')+1)== "g"){
    if ((cmd.substring(cmd.lastIndexOf('g'),cmd.lastIndexOf('g')+1)=="g")){
      
      cmd= cmd.substring(cmd.indexOf("g/")+2,cmd.lastIndexOf("/g"));
      cmd1= cmd.substring(0,cmd.indexOf(','));
      
      cmd2= cmd.substring(cmd.indexOf(',')+1,cmd.lastIndexOf(','));
      cmd3 = cmd2.substring(cmd2.indexOf(',')+1);
      cmd2 = cmd2.substring(0,cmd2.indexOf(','));
      cmd4 = cmd.substring(cmd.lastIndexOf(',')+1);
      
      /*Serial.println(cmd1);
      Serial.println(cmd2);
      Serial.println(cmd3);
      Serial.println(cmd4);  */

      presion1= cmd1.toFloat();
      presion2= cmd2.toFloat();
      presion3= cmd3.toFloat();
      presion4= cmd4.toFloat();

      //Copy the pressure values to variables of the library serv.h
      ser_presion1= presion1;
      ser_presion2= presion2;
      ser_presion3= presion3;
      ser_presion4= presion4;
    }
  }
 }

 void serialEvent(){
  
  String cmd="",flag="";
  cmd=Serial.readStringUntil('\n');   
  flag= cmd.substring(0,1);

  if (flag== "g"){
    get_data(cmd);
  }
  if (flag== "h"){
    get_fecha_hora(cmd);
  }
}

void get_fecha_hora(String cmd){
    Serial.println(cmd); 
 if ((cmd.substring(cmd.indexOf('h'),cmd.indexOf('h')+1)== "h") && (cmd.lastIndexOf('h')>cmd.indexOf('h'))){
    if ((cmd.substring(cmd.lastIndexOf('h'),cmd.lastIndexOf('h')+1)=="h")){
      
      cmd= cmd.substring(cmd.indexOf("h/")+2,cmd.lastIndexOf("/h"));
      fechahora= cmd ;
      cmd= cmd.substring(cmd.indexOf(" ")+1,cmd.lastIndexOf(":"));
      horaguardado(cmd);
    }
  }
 }

 void horaguardado(String cmd){
  if (!(hora== cmd)){
     hora = cmd;
     writereport(presion1,presion2,presion3, presion4,fechahora);
  }
 }
