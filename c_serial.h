
    Serial.print("b");
    Serial.print(n);
    Serial.println("b");
}

void setData_sensores( bool n){
    Serial.print("/");
    Serial.print(n);
    Serial.println("/");
}

void setData_fechahora( String fecha,String hora){
    Serial.print("fecha/");
    Serial.print(fecha);
    Serial.print(",");
    Serial.print(hora);
    Serial.println("f");
}
