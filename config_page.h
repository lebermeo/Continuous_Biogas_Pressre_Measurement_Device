

const char webpage[] PROGMEM =  R"rawliteral(<!DOCTYPE html>
<!-- Adapting of Coding By CodingNepal - youtube.com/codingnepal -->
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>WIFI_Confiuraciónl</title>
  <style>
      @import url('https://fonts.googleapis.com/css2?family=Noto+Sans:wght@700&family=Poppins:wght@400;500;600&display=swap');
    *{
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    font-family: "Poppins", sans-serif;
    }
    body{
    margin: 0;
    padding: 0;
    background: linear-gradient(120deg,#379fe4, #4a2ba0);
    height: 100vh;
    overflow: hidden;
    }
    .center{
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    width: 400px;
    background: white;
    border-radius: 10px;
    box-shadow: 10px 10px 15px rgba(0,0,0,0.05);
    }
    .center h1{
    text-align: center;
    padding: 20px 0;
    border-bottom: 1px solid silver;
    }
    .center form{
    padding: 0 40px;
    box-sizing: border-box;
    }
    form .txt_field{
    position: relative;
    border-bottom: 2px solid #adadad;
    margin: 30px 0;
    }
    .txt_field input{
    width: 100%;
    padding: 0 5px;
    height: 40px;
    font-size: 16px;
    border: none;
    background: none;
    outline: none;
    }
    .txt_field label{
    position: absolute;
    top: 50%;
    left: 5px;
    color: #adadad;
    transform: translateY(-50%);
    font-size: 16px;
    pointer-events: none;
    transition: .5s;
    }
    .txt_field span::before{
    content: '';
    position: absolute;
    top: 40px;
    left: 0;
    width: 0%;
    height: 2px;
    background: #2691d9;
    transition: .5s;
    }
    .txt_field input:focus ~ label,
    .txt_field input:valid ~ label{
    top: -5px;
    color: #2691d9;
    }
    .txt_field input:focus ~ span::before,
    .txt_field input:valid ~ span::before{
    width: 100%;
    }
    .pass{
    margin: -5px 0 20px 5px;
    color: #a6a6a6;
    cursor: pointer;
    }
    .pass:hover{
    text-decoration: underline;
    }
    input[type="submit"]{
    width: 100%;
    height: 50px;
    border: 1px solid;
    background: #2691d9;
    border-radius: 25px;
    font-size: 18px;
    color: #e9f4fb;
    font-weight: 700;
    cursor: pointer;
    outline: none;
    }
    input[type="submit"]:hover{
    border-color: #2691d9;
    transition: .5s;
    }
    .signup_link{
    margin: 30px 0;
    text-align: center;
    font-size: 16px;
    color: #666666;
    }
    .signup_link a{
    color: #2691d9;
    text-decoration: none;
    }
    .signup_link a:hover{
    text-decoration: underline;
    }

  </style>
  </head>
  <body>
    <div class="center">
      <h1>WIFI</h1>
      <form method="get" action="Conect">
        <div class="txt_field">
          <input type="text" name="SSID" required>
          <span></span>
          <label>SSID</label>
        </div>
        <div class="txt_field">
          <input type="password" name="PASS">
          <span></span>
          <label>Password</label>
        </div>
        <input type="submit" value="Conectar">
        <div class="signup_link">
      <span id="estado">Estado: %Conexion:% </span>
        </div>
      </form>
    </div>

  </body>
  <script>
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("estado").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/estado", true);
      xhttp.send();
    }, 1000 ) ;
 </script>
</html>)rawliteral";



char cambiar(String indx,byte ver){
  
  long len= indx.length()+1;
  char cadena[len];
  if (ver == 0){
    indx.replace("<span> </span>","<span>Conexión exitosa</span>");
  }else{
    if( ver== 1){
      indx.replace("<span> </span>","<span>Conexión fallida</span>");
    }   
  }
   
   indx.toCharArray(cadena,len);
  
}

const char sensorpage[] PROGMEM =  R"rawliteral(
<!DOCTYPE HTML><html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title> Sensores </title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
   <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    
  <style>
    body{
        margin-top: 6rem;
    }
    html {
     font-family: Arial;
     display:inline-block;
     margin: 0px auto;
     text-align: center;
    }
    header { font-size: 1.2rem; background-color: rgba(16, 236, 90, 0.671);
    
             padding:0rem;
             margin: 0rem;
             left: 0;
             top: 0;
             position:absolute;
             width: 100%;
             height: 4.5rem;
             color: white;
    }
    p { font-size: 1.60rem; 
        
        display:inline-block
    }
    .units { font-size: 1.0rem; }
    .dht-labels{
      font-size: 1.2rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
        .btn_form{
            padding-left: 3rem;
            display:inline-block;
            width: 5rem;
            
        }
    button{
        width: 4rem;
        vertical-align:middle;
        height: 2rem;
        border-radius: 0.25rem;
        border-width: 0.1rem;
        border-color: white;
        background-color: white;
        
    }
    .btn_opcion,
    .btn_opcion1 {
        width: 10rem;
        height: 3rem;
        border-radius: 0.3rem;
        background-color: rgba(16, 236, 90, 0.671);
        color: white;
        font-size: 1rem
    }   
    .btn_reporte,.btn_reporte1 {
        width: 20rem;
        height: 3rem;
        border-radius: 0.3rem;
        background-color: rgba(16, 236, 90, 0.671);
        color: white;
        font-size: 1.2rem
    }  
   
    .btn_opcion1,.btn_reporte1{
      background-color: white;
      color: rgba(16, 236, 89, 0.788);
      border-width: 0.1rem;
      border-color: rgba(16, 236, 89, 0.788);
    }
    .btn_wifi{
      height: 2rem;
      width: 8rem;
      margin-bottom: 1.2rem;
      background-color: white;
      border-width: 0.1rem;
      border-color: white;
      
    }
    
/* */
.show-btn{
  background: #fff;
  padding: 20px 20px;
  font-size: 15px;
  font-weight: 500;
  color: rgba(16, 236, 89, 0.788);
  cursor: pointer;
}
.container{
  position: absolute;
  top: 40vh;  
  left: 40vw; 
  transform: translate(-25vmin, -10vh);
}

input[type="checkbox"]{
  display: none;
}
.container{
  display: none;
  background: #fff;
  width: 18rem;
  padding: 30px;
  box-shadow: 0 0 10px rgba(0,0,0,0.1);
  height: 15rem;
}
#show:checked ~ .container{
  display: block;
}
.container .close-btn{
  position: absolute;
  right: 20px;
  top: 15px;
  font-size: 18px;
  cursor: pointer;
}
.container .close-btn:hover{
  color: rgba(16, 236, 89, 0.788);
}
.container .text{
  font-size: 20px;
  font-weight: 600;
  text-align: center;
}
.container form{
  margin-top: -20px;
}
.container form {
  height: 45px;
  width: 20rem; 
  margin: 40px 0;
}
form  label{
  font-size: 18px;
}
form  input{
  height: 3rem; 
  width: 3rem; 
  padding-left: 10px;
  font-size: 17px;
  border: 1px solid silver;
}
form input:focus{
  border-color: rgba(16, 236, 89, 0.788);
  border-bottom-width: 2px;
}
form .forgot-pass{
  margin-top: -8px;
}
form .forgot-pass a{
  color: #3498db;
  text-decoration: none;
}
form .forgot-pass a:hover{
  text-decoration: underline;
}


form .btn:hover .inner{
  left: 0;
}

form .signup-link{
  text-align: center;
}
form .signup-link a{
  color: #3498db;
  text-decoration: none;
}
form .signup-link a:hover{
  text-decoration: underline;
}

.data{
  position: center;
  width: 12rem;
  margin-bottom: 1rem;
}
  </style>
  </head>
  <body>
    <header>
        <h2><i class="far fa-chart-bar" style="color:#575a5a54;"></i>  Panel de sensores</h2>
        
    </header>
    <div class="center">
      <input type="checkbox" id="show">
      <label for="show" class="show-btn" id="fechahora">%fh%</label>
      
      <div class="container">
         <label for="show" class="close-btn" title="close">X</label>
         <div class="text">
            Configuracion Fecha/Hora
         </div>
         <form method="get" action="CONF_HF">
                
          <input  required class ="data" type= "date" placeholder="YYYY" name="fecha">
          <input required class ="data" type= "time" placeholder="M" name="hora" >
          <button type="submit" class="btn_opcion" id="btn_FH" > Guardar </button>
         </form>
      </div>
   </div>
   <br>
    <form action="/CONF_WIFI" method="">
      <button type="submit" class="btn_wifi" id="btn_w" >
        <i class="fas fa-wifi" style="color:#12be93;"></i> %conect%</button>
  </form>
    <form action="/btn_opcion" method="">
        <button type="submit" class="btn_opcion" id="btn_I" name="valor" value="1">Iniciar</button>
        <button type="submit" class="btn_opcion1" id="btn_D" name="valor" value="0">Detener</button>
    </form>
    
    <p>
    <i class="fab fa-cloudscale" style="color:#12be93;"></i> 
    <span class="dht-labels">Sensor 1:  </span> 
    <span id="sensor_1">%s1%</span>
    <sup class="units"> mb</sup>
        <form action="/btn_sensor" class="btn_form">
            <button type="submit" id="btn_sensor1" name="n_boton" value="1">%bs1%</button>
        </form>
        <br>
    </p>
      <p>
    <i class="fab fa-cloudscale" style="color:#0eb5df;"></i> 
    <span class="dht-labels">Sensor 2:  </span> 
    <span id="sensor_2">%s2%</span>
    <sup class="units"> mb</sup>
        <form action="/btn_sensor" class="btn_form">
            <button type="submit" id="btn_sensor2" name="n_boton" value="2">%bs2%</button>
        </form>
        <br>
    </p>
      <p>
    <i class="fab fa-cloudscale" style="color:#f8c210;"></i> 
    <span class="dht-labels">Sensor 3:  </span> 
    <span id="sensor_3">%s3%</span>
    <sup class="units"> mb</sup>
        <form action="/btn_sensor" class="btn_form">
            <button type="submit" id="btn_sensor3" name="n_boton" value="3">%bs3%</button>
        </form>
        <br>
    </p>
      <p>
    <i class="fab fa-cloudscale" style="color:#fa6023ec;"></i> 
    <span class="dht-labels">Sensor 4:  </span> 
    <span id="sensor_4">%s4%</span>
    <sup class="units"> mb</sup>
        <form action="/btn_sensor" class="btn_form"> 
            <button type="submit" id="btn_sensor4" name="n_boton" value="4">%bs4%</button>
        </form>
    </p>

    <form action="/btn_reporte" method="post">
      <button type="submit" class="btn_reporte" id="btn_R" >Reporte</button>
  </form>
  <form action="/borrar_reporte" method="post">
    <button type="submit" class="btn_reporte1" id="btn_R" >Borrar datos</button>
</form>

  </body>

  <script>

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor_1").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/sensor_1", true);
      xhttp.send();
    }, 3000 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor_2").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/sensor_2", true);
      xhttp.send();
    }, 3000 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor_3").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/sensor_3", true);
      xhttp.send();
    }, 3100 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor_4").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/sensor_4", true);
      xhttp.send();
    }, 3100 ) ;

    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("fechahora").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "/fechahora", true);
      xhttp.send();
    }, 10000 ) ;
    
</script>

</html>


)rawliteral";
