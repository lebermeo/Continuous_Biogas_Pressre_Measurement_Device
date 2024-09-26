#include "c_serial.h"
#include <Arduino.h>
// Import required libraries
#include <DNSServer.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include "ESPAsyncWebServer.h" //Genera un servidor Asincronico
#include "config_page.h"//Libreia que almacena las varibles String de las paginas HTML
#include "FS.h"


void openFS(void){
 //Abre el sistema de archivos
 if(!SPIFFS.begin()){
  Serial.println("\nError al abrir el sistema de archivos");
 } else {
  Serial.println("\nSistema de archivos abierto con éxito!");
  if(!SPIFFS.exists("/reporte.txt")){
    File rFile = SPIFFS.open("/reporte.txt","w+");
     if(!rFile){
      Serial.println("Error al abrir archivo!");
     } else {
      rFile.print("Fecha");
      rFile.print(";");
      rFile.print("sensor1");
      rFile.print(";");
      rFile.print("sensor2");
      rFile.print(";");
      rFile.print("sensor3");
      rFile.print(";");
      rFile.println("sensor4");
     }
     rFile.close();
  }
 }
 
}
void borrarReporte(void){
  if(SPIFFS.remove("/reporte.txt")){
    File rFile = SPIFFS.open("/reporte.txt","w+");
     if(!rFile){
      Serial.println("Error al abrir archivo!");
     } else {
      rFile.print("Fecha");
      rFile.print(";");
      rFile.print("sensor1");
      rFile.print(";");
      rFile.print("sensor2");
      rFile.print(";");
      rFile.print("sensor3");
      rFile.print(";");
      rFile.println("sensor4");
     }
     rFile.close();
  }
}

void writereport(float data1,float data2,float data3,float data4,String fechah){
  File rFile = SPIFFS.open("/reporte.txt","a+");
 if(!rFile){
  Serial.println("Error al abrir archivo!");
 } else {
  rFile.print(fechah);
  rFile.print(";");
  rFile.print(data1);
  rFile.print(";");
  rFile.print(data2);
  rFile.print(";");
  rFile.print(data3);
  rFile.print(";");
  rFile.println(data4);
  Serial.println("Datos guardados");
 }
 rFile.close();
}

void writecredencials(String ssid, String pass) {
 //Abre el archivo para escribir ("w" write))
 //Sobreescribe el contenido del archivo
 File rFile = SPIFFS.open("/credenciales.txt","w+");
 if(!rFile){
  Serial.println("Error al abrir archivo!");
 } else {
  rFile.print(ssid);
  rFile.print(",");
  rFile.println(pass);
 }
 rFile.close();
}




// credenciales del punto de acceso
#ifndef APSSID
#define APSSID "SIPBI_3"
#define APPSK  "presion1234"
#endif

//Credenciales del punto de acceso del ESP01
const char *ssid = APSSID;
const char *password = APPSK;
bool est=false;
bool conexion= false;
bool a_sensor= true,
     a_sensor1= true,
     a_sensor2= true,
     a_sensor3= true,
     a_sensor4= true;
float ser_presion1=0,ser_presion2=0,ser_presion3=0,ser_presion4=0;
String fechahora;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void handleRoot(String sid_sta,String pass_sta) {
  
  byte cont=0;
  
  if(!(sid_sta == "")){
    Serial.print("SSID: ");
    Serial.println(sid_sta);
    Serial.print("PASS: ");
    Serial.println(pass_sta);
    if(!(pass_sta == "")){
      WiFi.begin(sid_sta,pass_sta);
    }else{
      WiFi.begin(sid_sta);
    }
    while ((WiFi.status() != WL_CONNECTED) && (cont< 50)){
      delay(200);
      Serial.print(".");
      cont++;
    }
    Serial.println(".");
  }else{
   
  }
}

void credenciales() {
 File rFile = SPIFFS.open("/credenciales.txt","r");
 if (!rFile) {
  Serial.println("Error al abrir archivo!");
 }
 String content = rFile.readStringUntil('\r'); 
 Serial.print("lectura de credenciales: ");
 Serial.println(content);
 rFile.close();
 String SID= content.substring(0,content.indexOf(','));
 String pass= content.substring(content.lastIndexOf(',')+1);
 handleRoot(SID,pass); 
}

String processor(const String& var){
  //Serial.println(var);
  if(var == "s1"){
    int valor= int(ser_presion1);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor1== true){
      return bufer;
    }else{
      return "--";  
    }
  }
  if(var == "s2"){
    int valor= int(ser_presion2);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor2== true){
      return bufer;
    }else{
      return "--";  
    }
  }
    if(var == "s3"){
    int valor= int(ser_presion3);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor3== true){
      return bufer;
    }else{
      return "--";  
    }
  }
  if(var == "s4"){
    int valor= int(ser_presion4);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor4== true){
      return bufer;
    }else{
      return "--";  
    }
  }
  if(var == "bs1"){
    if(a_sensor1== true){
        return "ON";
      }else{
        return "OFF";
      }
  }   
  if(var == "bs2"){
    if(a_sensor2== true){
        return "ON";
      }else{
        return "OFF";
      }
  }   
  if(var == "bs3"){
    if(a_sensor3== true){
        return "ON";
      }else{
        return "OFF";
      }
  }   
  if(var == "bs4"){
    if(a_sensor4== true){
        return "ON";
      }else{
        return "OFF";
      }
  }   
  if(var == "conect"){
    if(conexion== true){
       return "Conectado";
    }else{
      return "Desconectado";
    }  
  }
  if(var == "fh"){
     return fechahora;
  }
  return String();
}

bool verificacion(){
  byte cont=0;
  //WiFi.setAutoConnect(true);
 
  WiFi.begin();
  est= false;
  Serial.println("Conectando");
  while ((WiFi.status() != WL_CONNECTED) && (cont< 50))  {
      delay(200);
      Serial.print(".");
      cont++;
    }
  if(WiFi.status() != WL_CONNECTED){
      Serial.print("");
      Serial.println("No se pudo conectar");
      WiFi.setAutoReconnect(true);
      conexion= false;
      return false;
    }else
    {
      Serial.print("");
      Serial.println("Ya estas conectado");
      conexion= true;
      return true;
    }
     
}
bool confirmacion;

void serv_inicio()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");

  server.on("/borrar_reporte", HTTP_POST, [](AsyncWebServerRequest *request){
    borrarReporte();
    request->send_P(200, "text/html",sensorpage,processor);
  });
  server.on("/btn_reporte", HTTP_POST, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/reporte.txt", String(), true);
  });
  
  // Route for root / web page
  server.on("/CONF_WIFI", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html",webpage);
  });
  
  server.on("/Conect", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebParameter* s = request->getParam(0);
    String ssid_s= s->value();
    AsyncWebParameter* p = request->getParam(1);
    String pass_s= p->value();
    handleRoot(ssid_s,pass_s); 
    writecredencials(ssid_s, pass_s);
    est= true;
    request->send_P(200, "text/html",sensorpage,processor);
  });

  server.on("/CONF_HF", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebParameter* s = request->getParam(0);
    String fecha= s->value();
    AsyncWebParameter* p = request->getParam(1);
    String hora= p->value();
    Serial.println(fecha);
    Serial.println(hora);
    setData_fechahora(fecha,hora);
    request->send_P(200, "text/html",sensorpage,processor);
  });

  server.on("/fechahora", HTTP_GET, [](AsyncWebServerRequest *request){
    String fechah = fechahora;
    char Buf[50];
    fechah.toCharArray(Buf, 50);
     request->send_P(200, "text/plain",Buf);
  });

  server.on("/estado", HTTP_GET, [](AsyncWebServerRequest *request){
     if(conexion== true){
       request->send_P(200, "text/plain","Conectado");
    }else{
      request->send_P(200, "text/plain","Desconectado");
    }   
  });

  // Route for root / sensorpage 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html",sensorpage,processor);
  });
  
  server.on("/btn_opcion", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebParameter* s = request->getParam(0);
    String value= s->value();
    if(value=="1"){
      a_sensor= true;
      set_data(1);
    }else{
      a_sensor= false;
      set_data(0);
    }
    request->send_P(200, "text/html",sensorpage,processor);
  });

  server.on("/btn_sensor", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebParameter* s = request->getParam(0);
    String value= s->value();
    if(value=="1"){
      a_sensor1=!(a_sensor1);
      setData_sensores(a_sensor1);
      Serial.println(a_sensor1);
    }else if(value=="2"){
       a_sensor2=!(a_sensor2);
       setData_sensores(a_sensor2);
       Serial.println(a_sensor2);
    }else if(value=="3"){
       a_sensor3=!(a_sensor3);
       setData_sensores(a_sensor3);
      Serial.println(a_sensor3);
    }else if(value=="4"){
       a_sensor4=!(a_sensor4);
       setData_sensores(a_sensor4);
       Serial.println(a_sensor4);
    }
      
    request->send_P(200, "text/html",sensorpage,processor);
  });

  /*server.on("/estado_boton1", HTTP_GET, [](AsyncWebServerRequest *request){
     if(a_sensor1== true){
       request->send_P(200, "text/plain","ON");
    }else{
      request->send_P(200, "text/plain","OFF");
    }   
  });
  server.on("/estado_boton2", HTTP_GET, [](AsyncWebServerRequest *request){
     if(a_sensor2== true){
       request->send_P(200, "text/plain","ON");
    }else{
      request->send_P(200, "text/plain","OFF");
    }   
  });
  server.on("/estado_boton3", HTTP_GET, [](AsyncWebServerRequest *request){
     if(a_sensor3== true){
       request->send_P(200, "text/plain","ON");
    }else{
      request->send_P(200, "text/plain","OFF");
    }   
  });
  server.on("/estado_boton4", HTTP_GET, [](AsyncWebServerRequest *request){
     if(a_sensor4== true){
       request->send_P(200, "text/plain","ON");
    }else{
      request->send_P(200, "text/plain","OFF");
    }   
  });*/

  server.on("/sensor_1", HTTP_GET, [](AsyncWebServerRequest *request){
    int valor= int(ser_presion1);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor1== true){
      request->send_P(200, "text/plain",bufer);
    }else{
      request->send_P(200, "text/plain","--");  
    }   
 
  });
  server.on("/sensor_2", HTTP_GET, [](AsyncWebServerRequest *request){
    int valor= int(ser_presion2);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor2== true){
      request->send_P(200, "text/plain",bufer);
    }else{
      request->send_P(200, "text/plain","--");  
    }   
  });
  server.on("/sensor_3", HTTP_GET, [](AsyncWebServerRequest *request){
    int valor= int(ser_presion3);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor3== true){
      request->send_P(200, "text/plain",bufer);
    }else{
      request->send_P(200, "text/plain","--");  
    }   
  });
  server.on("/sensor_4", HTTP_GET, [](AsyncWebServerRequest *request){
    int valor= int(ser_presion4);
    char bufer[10]= " ";
    char*formato ="%i";
    sprintf(bufer,formato,valor);
    if(a_sensor4== true){
      request->send_P(200, "text/plain",bufer);
    }else{
      request->send_P(200, "text/plain","--");  
    }    
  });
  
  server.begin();
}
