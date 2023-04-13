function PV_Voltage(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "PV Voltage Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_pv_voltage", true);
  xhttp.send();
}
function PV_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "PV Current Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_pv_current", true);
  xhttp.send();
}

function Battery_Voltage(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_battery_voltage", true);
  xhttp.send();
}
function Battery_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Current Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_battery_current", true);
  xhttp.send();
}

function Charge_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Charge_Current Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_battery_current", true);
  xhttp.send();
}
function Clean_Screen(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      valeur_mesure
      document.getElementById('valeur_mesure').innerHTML = "0";
      document.getElementById('variable_name').innerHTML = "____";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "clean_screen", true);
  xhttp.send();
}

function onButton(){
  //The behaviour of this function is to send a request to the path "on" in the main.cpp file
    //Once the request is sent, the ESP32 will execute the function that is triggered by the path "on"
  var xhttp = new XMLHttpRequest(); // create a new XMLHttpRequest object wich is used to send and receive data from a server
                                      //It allows the main thread to send and receive data from a server without blocking the main thread
  xhttp.open("GET", "on", true); // true for asynchronous = non-blocking request
                                  // on is the path to the on function in the main.cpp file
                                  // Get is the method = how the data is sent
  
  xhttp.send(); // send the request
}
function offButton(){
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "off", true); // true for asynchronous = non-blocking request
                                    // off is the path to the off function in the main.cpp file
  xhttp.send(); // send the request
}

setInterval(function getData(){
  var xhttp = new XMLHttpRequest();

  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      //When the request is ready (4) and the status is OK (200)
        //then, the responseText is the data sent from the ESP32 to the server
        
      //this.responseText is the data sent from the ESP32 to the server                                                                     
        //and it gonna change the value with the id valeur_mesure
      document.getElementById('valeur_mesure').innerHTML = this.responseText;
    }
  }; // end of onreadystatechange function
  xhttp.open("GET", "get_periodic_data", true); // true for asynchronous = non-blocking request
  xhttp.send(); // send the request

}, 30000); // end of setInterval function with 5000ms period