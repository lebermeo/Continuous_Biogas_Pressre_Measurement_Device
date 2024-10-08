#include <SPI.h>
#include <SD.h>
//#include <Wire.h>
#include <RTClib.h>

#define SSpin 10
File archivo; //Objet file type
RTC_DS3231 rtc; //objet RTC

bool chek_rtc_sd= true; 

void inicializacion(){
   chek_rtc_sd= true;
  // inicialization of the RTC module
   if (!rtc.begin()){
    Serial.println(F("Modulo RTC no encontrado"));
    chek_rtc_sd= false;
  }
   
  //Inicialization of SD module
    Serial.println(F("inicializacion.."));
  if(!SD.begin(SSpin)){
    Serial.println(F("Fallo en inicializacion"));
    chek_rtc_sd= false;
  }
  
}



void registrar (String directorio,float presion)
{
 DateTime fecha = rtc.now(); 

 String fec = String(String(fecha.day()) + "-" + String(fecha.month()) + "-" + String(fecha.year()).substring(2,4) +  ".txt");
 //String fech = String(String(fecha.day()) + "/" + String(fecha.month()) + "/" + String(fecha.year()));
 
  Serial.println("inicio correcto");
  archivo = SD.open(String(directorio) , FILE_WRITE);

  if (archivo){
    archivo.print(fecha.day());
    archivo.print("/");
    archivo.print(fecha.month());
    archivo.print("/");
    archivo.print(fecha.year());
    archivo.print(" ");
    archivo.print(fecha.hour());
    archivo.print(":");
    archivo.print(fecha.minute());
    archivo.print(":");
    archivo.print(fecha.second());
    archivo.print(";");
    archivo.println(presion);
    Serial.println("Escribiendo en archivo");
    archivo.close();
    Serial.println("Escritura correcta");

  }else {
    Serial.println("error en apertura");
  }

}

void lectura (String directorio){

  archivo = SD.open(String(directorio));
  if(archivo){
    Serial.println("Contenido:");
    while(archivo.available()){
      Serial.write(archivo.read());
    }
    archivo.close();
  }else{
    Serial.println(F("error en la apertura del documento"));
  }
}

int obtener_hora(){
  int hor;
  DateTime fecha = rtc.now();
  hor= fecha.hour();
  return hor;
}
int obtener_minutos(){
  int minu;
  DateTime fecha = rtc.now();
  minu= fecha.minute();
  return minu;
}
int obtener_segundos(){
  int seg;
  DateTime fecha = rtc.now();
  seg= fecha.second();
  return seg;
}

String fecha_hora(){
  DateTime fecha = rtc.now();
  String fec = String(String(fecha.year()) + "/" + String(fecha.month()) + "/" + String(fecha.day())
                + " " + String(fecha.hour())+ ":" + String(fecha.minute()));
  return fec;
}
