/*______Copy Message Functions*/
const copyButton = document.getElementById("copy_button");
const variableText = document.getElementById("variable_text");
copyButton.addEventListener("click", function() {
  variableText.select();
  document.execCommand("copy");
});

/*______Download Functions*/
  /*
    This functions allows to download the data of the different measurements done by the Arduino.
    The data is downloaded in a .txt file and the name of the file is the name of the measurement.
    Finaly, we call this functions via each button with same name as the measurement.
  */


//Reseau
function Grid_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Reseau Current Data";
      document.getElementById('variable_text').innerHTML = "Voici les courants mesurees de votre réseau. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'reseau_current.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_grid_current", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}

//Panneau photovoltaique
function PV_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "PV Current Data";
      document.getElementById('variable_text').innerHTML = "Voici les courants mesurees de votre system de Pannaux Photovoltaique. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'pv_current.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_pv_current", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}

//Battery
function Battery_Temperature(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Temperature Data";
      document.getElementById('variable_text').innerHTML = "Voici les temperature mesurés de votre system de batteries. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_temperature.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_temperature", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_Pack_Voltage(){  
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Pack Voltage Data";
      document.getElementById('variable_text').innerHTML = "Voici les tensions mesurees de votre pack de batteries. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_pack_voltage.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_pack_voltage", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}


function Battery_Voltage_1(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage 1 Data";
      document.getElementById('variable_text').innerHTML = "Voici la tension mesuree de la 1ere batterie. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_voltage_1.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_voltage_1", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_Voltage_2(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage 2 Data";
      document.getElementById('variable_text').innerHTML = "Voici la tension mesuree de la 2eme batterie. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_voltage_2.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_voltage_2", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_Voltage_3(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage 3 Data";
      document.getElementById('variable_text').innerHTML = "Voici la tension mesuree de la 3eme batterie. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_voltage_3.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_voltage_3", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_Voltage_4(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage 4 Data";
      document.getElementById('variable_text').innerHTML = "Voici la tension mesuree de la 4eme batterie. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_voltage_4.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_voltage_4", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}


function Battery_Pack_Current(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Pack Current Data";
      document.getElementById('variable_text').innerHTML = "Voici les courants mesurees de votre system de batteries. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_pack_current.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_pack_current", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_SOC(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery SOC Data";
      document.getElementById('variable_text').innerHTML = "Voici les SOC mesurés de votre system de batteries. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_soc.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_soc", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}
function Battery_SOH(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery SOH Data";
      document.getElementById('variable_text').innerHTML = "Voici les SOH mesurés de votre system de batteries. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'battery_soh.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_battery_soh", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}

//Reporting data
function Reporting(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Ecriture d'un rapport...";
      document.getElementById('variable_text').innerHTML = "Veuillez patienter, le rapport est en cours de generation. Cela risque de prendre du temps. Merci de votre patience.";
      var a = document.createElement('a');
      var url = window.URL.createObjectURL(this.response);
      a.href = url;
      a.download = 'rapport_complet.txt';
      document.body.appendChild(a);
      a.click();
      document.body.removeChild(a);
      window.URL.revokeObjectURL(url);
    }
  };
  
  xhttp.open("GET", "download_report", true);
  xhttp.responseType = 'blob';
  xhttp.send();
}

/*______Display Functions*/
  /*
    This function arent't used anymore, but they can be used to display the data on the screen.
  */
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
function PV_Voltage_bis(){
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
function PV_Current_bis(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "PV Current Data";
      //document.getElementById('variable_text').innerHTML = this.responseText;
      document.getElementById('variable_text').innerHTML = "Voici les tensions mesurees de votre system de Pannaux Photovoltaique. Si vous voulez plus d'autres informations, veuillez cliquer sur les autre boutons sur l'ecran.";
    }
  };
  
  xhttp.open("GET", "get_pv_current", true);
  xhttp.send();
}
function Battery_Voltage_bis(){
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
function Battery_Current_bis(){
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
function Battery_SOC_bis(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Voltage Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_battery_SOC", true);
  xhttp.send();
}
function Battery_SOH_bis(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Battery Current Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_battery_SOH", true);
  xhttp.send();
}
function Charge_Current_bis(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      document.getElementById('variable_name').innerHTML = "Charge_Current Data";
      document.getElementById('variable_text').innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "get_charge_current", true);
  xhttp.send();
}

/*______Test Functions*/
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

}, 300000); // end of setInterval function with 5000ms period