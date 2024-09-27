//include "guardar.h"

bool a_sensor1= true,
     a_sensor2= true,
     a_sensor3= true,
     a_sensor4= true;

void set_data(float val, float val2, float val3, float val4){
  String cd = String("g/" + String(val) + "," + String(val2) + "," + String(val3) + "," + String(val4) + "/g");
 
  SerialBLE.println(cd);
  //Serial.println(cd);  
}

void set_fechahora(String fechahora){
  String cd = String("h/" + String(fechahora)  + "/h");
  SerialBLE.println(cd);
  
}

byte get_data(String cmd){

  /*static*/ byte dato;
  String cmd2="";
   Serial.println(cmd);
  if (cmd.substring(cmd.indexOf('b'),cmd.indexOf('b')+1)=="b"){
    if ((cmd.substring(cmd.lastIndexOf('b'),cmd.lastIndexOf('b')+1)=="b") && (cmd.lastIndexOf('b')>cmd.indexOf('b'))){
      cmd2= cmd.substring(cmd.indexOf('b')+1,cmd.lastIndexOf('b'));
      dato= cmd2.toInt();
      if (dato== 0){
        dato = dato;
      }else{
        dato=1;
      }
      Serial.println(dato);
      return dato;
    }
  }
 
}

void get_datasensores(String cmd){
  
  /*static*/ byte dato;
  String cmd2="";

  if (cmd.substring(cmd.indexOf('/'),cmd.indexOf('/')+1)=="/"){
    if ((cmd.substring(cmd.lastIndexOf('/'),cmd.lastIndexOf('/')+1)=="/") && (cmd.lastIndexOf('/')>cmd.indexOf('/'))){
      cmd2= cmd.substring(cmd.indexOf('/')+1,cmd.lastIndexOf('/'));;
      dato= cmd2.toInt();
      Serial.println(dato);
      if(dato==1){
        a_sensor1=!(a_sensor1);
      }else if(dato==2){
        a_sensor2=!(a_sensor2);
      }else if(dato==3){
        a_sensor3=!(a_sensor3);
      }else if(dato==4){
        a_sensor4=!(a_sensor4);
      }
    }
  }
}

void get_fecha(String cmd){
  
  Serial.print("PUERTO SERIE: ");
  Serial.println(cmd);
  
  String fecha="",hora="";
  String a,m,d,h,mn;

  if (cmd.substring(cmd.indexOf("fecha/"),cmd.indexOf("fecha/")+6)=="fecha/"){
    if ((cmd.substring(cmd.lastIndexOf('f'),cmd.lastIndexOf('f')+1)=="f") && (cmd.lastIndexOf('f')>cmd.indexOf('f'))){
      
      cmd= cmd.substring(cmd.indexOf("fecha/")+6,cmd.lastIndexOf('f'));
      fecha= cmd.substring(0,cmd.indexOf(','));
      hora = cmd.substring(cmd.lastIndexOf(',')+1);
      Serial.println(fecha);
      Serial.println(hora);
      a= fecha.substring(0,fecha.indexOf('-'));
      m= fecha.substring(fecha.indexOf('-')+1,fecha.lastIndexOf('-'));
      d= fecha.substring(fecha.lastIndexOf('-')+1);
      
      h= hora.substring(0,hora.indexOf(':'));
      mn= hora.substring(hora.lastIndexOf(':')+1);
      Serial.println(h);
      Serial.println(mn);
      if((a.toInt()>0)&&(m.toInt()>0) && (d.toInt()>0)){
        rtc.adjust(DateTime(a.toInt(),m.toInt(),d.toInt(),h.toInt(),mn.toInt(),0)); 
        Serial.println("Fecha establecida");
      }   
    }
  }
}
