char fistpage[] PROGMEM = R"====(



<?php
                header('Access-Control-Allow-Origin: *');
                $servername = "localhost";
                $username = "root";
                $password = "";
                $dbname = "Capstone2023";

               

 
$conn =  mysqli_connect($servername, $username, $password, $dbname);  
$sql="SELECT * FROM Module ORDER BY Module.Time DESC LIMIT 1"; 
$result= mysqli_query($conn,$sql); 
//  echo "HERE"; 
 
$row=mysqli_fetch_assoc($result); 
 
$Ultrasonic=$row['Ultrasonic']; 
$LDR=$row['LDR']; 
$Temperature=$row['Temperature']; 
$Humidity=$row['Humidity'];
$ID = $row['ID'];


 
// Query database for soil moisture data 
$sql="SELECT ID,LDR FROM Module"; 
$result = mysqli_query($conn, $sql); 

// Create array to hold data for soil moisture graph 
$LDR_data = array(); 
while($row = mysqli_fetch_assoc($result)) { 
    $LDR_data[] = $row; 
} 
$LDR_data = array_slice($LDR_data, -50);
 
// Convert soil moisture data to JSON format 
$json_LDR_data = json_encode($LDR_data); 
 
// Query database for temperature data 
$sql = "SELECT ID, Temperature FROM Module"; 
$result = mysqli_query($conn, $sql); 
 
// Create array to hold data for temperature graph 
$Temperature_data = array(); 
while($row = mysqli_fetch_assoc($result)) { 
    $Temperature_data[] = $row; 
} 
$Temperature_data = array_slice($Temperature_data, -50);
 
// Convert temperature data to JSON format 
$json_Temperature_data = json_encode($Temperature_data); 
 
// Query database for water level data 
$sql = "SELECT ID, Ultrasonic FROM Module"; 
$result = mysqli_query($conn, $sql); 
 
// Create array to hold data for water level graph 
$Ultrasonic_data = array(); 
while($row = mysqli_fetch_assoc($result)) { 
    $Ultrasonic_data[] = $row; 
} 
$Ultrasonic_data = array_slice($Ultrasonic_data, -50);
 
// Convert water level data to JSON format 
$json_Ultrasonic_data = json_encode($Ultrasonic_data); 
 
// Query database for humidity data 
$sql = "SELECT ID, Humidity FROM Module"; 
$result = mysqli_query($conn, $sql); 
 
// Create array to hold data for humidity graph 
$Humidity_data = array(); 
while($row = mysqli_fetch_assoc($result)) { 
    $Humidity_data[] = $row; 
} 
$Humidity_data = array_slice($Humidity_data, -50); 

// Convert humidity data to JSON format 
$json_Humidity_data = json_encode($Humidity_data); 
 
// Close database connection 
mysqli_close($conn); 
 

?> 
 

                
                
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://cdn.tailwindcss.com"></script>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <title>Document</title>
    <style>
        .v_13 {
            width: 250px;
            height: 820px;
            background: rgb(34, 34, 36);
            opacity: 1;
            position: absolute;
            top: 60px;
            left: 0px;
            border-top-left-radius: 0px;
            border-top-right-radius: 70px;
            border-bottom-left-radius: 0px;
            border-bottom-right-radius: 0px;
            overflow: hidden;
            box-shadow: 15px 25px 25px rgb(231, 231, 231);
        }
    </style>
        
</head>
<body onload="createCharts()">
    <h1 class="flex space-x-1 font-montserrat w-44 font-semibold text-sky-900 text-2xl text-left absolute top-3 left-4 drop-shadow-lg">
        <span>
            Hydropontiac
        </span>
        <svg class="w-8 h-8 dark:text-sky-900" fill="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
            <path clip-rule="evenodd" fill-rule="evenodd" d="M14.615 1.595a.75.75 0 01.359.852L12.982 9.75h7.268a.75.75 0 01.548 1.262l-10.5 11.25a.75.75 0 01-1.272-.71l1.992-7.302H3.75a.75.75 0 01-.548-1.262l10.5-11.25a.75.75 0 01.913-.143z"></path>
          </svg>
    </h1>
    <div class="v_13">  
        <div class="absolute top-8 left-6">
        <div class="flex flex-col space-y-2 place-items-start">
            <button class="flex space-x-2 hover:bg-neutral-700 text-slate-300 font-normal  pl-4 pr-11 pt-2 pb-2 rounded-lg ">
                <svg class="w-5 h-5 dark:text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="M12 14l9-5-9-5-9 5 9 5z"></path><path d="M12 14l6.16-3.422a12.083 12.083 0 01.665 6.479A11.952 11.952 0 0012 20.055a11.952 11.952 0 00-6.824-2.998 12.078 12.078 0 01.665-6.479L12 14z"></path><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 14l9-5-9-5-9 5 9 5zm0 0l6.16-3.422a12.083 12.083 0 01.665 6.479A11.952 11.952 0 0012 20.055a11.952 11.952 0 00-6.824-2.998 12.078 12.078 0 01.665-6.479L12 14zm-4 6v-7.5l4-2.222"></path></svg>
                <span>
                    Dashboard
                </span>
                
            </button>
            <button class="flex space-x-2  hover:bg-neutral-700 text-neutral-600 font-normal  pl-4 pr-4 pt-2 pb-2 rounded-lg " onclick="window.location.href='second'">
                <svg class="w-5 h-5 dark:text-neutral-600" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4"></path></svg>
                <span>
                    Control Centre
                </span>
            </button>
            <button class="flex space-x-2 hover:bg-neutral-700 text-neutral-600 font-normal  pl-4 pr-14 pt-2 pb-2 rounded-lg " onclick="window.location.href='third'">
                <svg class="w-5 h-5 dark:text-neutral-600" fill="none" stroke="currentColor" stroke-width="1.5" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
                    <path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6A2.25 2.25 0 016 3.75h2.25A2.25 2.25 0 0110.5 6v2.25a2.25 2.25 0 01-2.25 2.25H6a2.25 2.25 0 01-2.25-2.25V6zM3.75 15.75A2.25 2.25 0 016 13.5h2.25a2.25 2.25 0 012.25 2.25V18a2.25 2.25 0 01-2.25 2.25H6A2.25 2.25 0 013.75 18v-2.25zM13.5 6a2.25 2.25 0 012.25-2.25H18A2.25 2.25 0 0120.25 6v2.25A2.25 2.25 0 0118 10.5h-2.25a2.25 2.25 0 01-2.25-2.25V6zM13.5 15.75a2.25 2.25 0 012.25-2.25H18a2.25 2.25 0 012.25 2.25V18A2.25 2.25 0 0118 20.25h-2.25A2.25 2.25 0 0113.5 18v-2.25z"></path>
                </svg>
                <span>
                    Statistics
                </span>
            </button>
            
        </div>
        </div>  
    </div>
    <h1 class="font-montserrat w-44 font-bold text-sky-900 text-3xl text-left absolute top-3 left-72 drop-shadow-lg">
            Dashboard
    </h1>
    <div class="flex space-x-10 box-border border-gray-100 h-1/4 w-1/2 p-8 border-2  absolute left-72 top-16 rounded-3xl">
        <div class="bg-gray-100 h-32 w-56 p-2 rounded-lg drop-shadow relative">
        
            <div class="font-semibold text-neutral-500 left-0 top-0 absolute p-1">
                Light
            </div>
            <svg class="w-5 h-5 dark:text-neutral-600 top-0 right-0 absolute p-1" fill="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true"> 
                <path d="M12 2.25a.75.75 0 01.75.75v2.25a.75.75 0 01-1.5 0V3a.75.75 0 01.75-.75zM7.5 12a4.5 4.5 0 119 0 4.5 4.5 0 01-9 0zM18.894 6.166a.75.75 0 00-1.06-1.06l-1.591 1.59a.75.75 0 101.06 1.061l1.591-1.59zM21.75 12a.75.75 0 01-.75.75h-2.25a.75.75 0 010-1.5H21a.75.75 0 01.75.75zM17.834 18.894a.75.75 0 001.06-1.06l-1.59-1.591a.75.75 0 10-1.061 1.06l1.59 1.591zM12 18a.75.75 0 01.75.75V21a.75.75 0 01-1.5 0v-2.25A.75.75 0 0112 18zM7.758 17.303a.75.75 0 00-1.061-1.06l-1.591 1.59a.75.75 0 001.06 1.061l1.591-1.59zM6 12a.75.75 0 01-.75.75H3a.75.75 0 010-1.5h2.25A.75.75 0 016 12zM6.697 7.757a.75.75 0 001.06-1.06l-1.59-1.591a.75.75 0 00-1.061 1.06l1.59 1.591z"></path>
            </svg>
        
            
      
            <div class="font-semibold text-6xl text-neutral-600 inset-y-10 left-0 absolute p-1">
                <p id="LDR"></p>
            </div>
       
            <div class="font-semibold text-sm text-neutral-600 bottom-0 left-0 absolute p-2">
            Ω
            </div>
            <div id="onsign37" class="font-semibold text-green-400 text-sm bottom-0 right-0 absolute p-2">
                
                +0.00%
                
                
            </div>
        
        </div>
        <div class="bg-gray-100 h-32 w-56 p-2 rounded-lg drop-shadow relative">
        
            <div class="font-semibold text-neutral-500 left-0 top-0 absolute p-1">
                Solution
            </div>
            <svg class="w-5 h-5 dark:text-neutral-600 top-0 right-0 absolute p-1" fill="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
                <path clip-rule="evenodd" fill-rule="evenodd" d="M10.5 3.798v5.02a3 3 0 01-.879 2.121l-2.377 2.377a9.845 9.845 0 015.091 1.013 8.315 8.315 0 005.713.636l.285-.071-3.954-3.955a3 3 0 01-.879-2.121v-5.02a23.614 23.614 0 00-3 0zm4.5.138a.75.75 0 00.093-1.495A24.837 24.837 0 0012 2.25a25.048 25.048 0 00-3.093.191A.75.75 0 009 3.936v4.882a1.5 1.5 0 01-.44 1.06l-6.293 6.294c-1.62 1.621-.903 4.475 1.471 4.88 2.686.46 5.447.698 8.262.698 2.816 0 5.576-.239 8.262-.697 2.373-.406 3.092-3.26 1.47-4.881L15.44 9.879A1.5 1.5 0 0115 8.818V3.936z"></path>
            </svg>
            <div class="font-semibold text-6xl text-neutral-600 inset-y-10 left-0 absolute p-1">
                <p id="Ultrasonic"></p>
            </div>
       
            <div class="font-semibold text-sm text-neutral-600 bottom-0 left-0 absolute p-2">
                cm
            </div>
            <div id="onsign371" class="font-semibold text-green-400 text-sm bottom-0 right-0 absolute p-2">
                +0.00%
            </div>
        
        </div>
        <div class="bg-gray-100 h-32 w-56 p-2 rounded-lg drop-shadow relative">
        
            <div class="font-semibold text-neutral-500 left-0 top-0 absolute p-1">
                Temperature
            </div>
            <svg class="w-5 h-5 dark:text-neutral-600 top-0 right-0 absolute p-1" fill="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
                <path clip-rule="evenodd" fill-rule="evenodd" d="M16.098 2.598a3.75 3.75 0 113.622 6.275l-1.72.46V12a.75.75 0 01-.22.53l-.75.75a.75.75 0 01-1.06 0l-.97-.97-7.94 7.94a2.56 2.56 0 01-1.81.75 1.06 1.06 0 00-.75.31l-.97.97a.75.75 0 01-1.06 0l-.75-.75a.75.75 0 010-1.06l.97-.97a1.06 1.06 0 00.31-.75c0-.68.27-1.33.75-1.81L11.69 9l-.97-.97a.75.75 0 010-1.06l.75-.75A.75.75 0 0112 6h2.666l.461-1.72c.165-.617.49-1.2.971-1.682zm-3.348 7.463L4.81 18a1.06 1.06 0 00-.31.75c0 .318-.06.63-.172.922a2.56 2.56 0 01.922-.172c.281 0 .551-.112.75-.31l7.94-7.94-1.19-1.19z"></path>
            </svg>
            <div class="font-semibold text-6xl text-neutral-600 inset-y-10 left-0 absolute p-1">
                <p id="Temperature"></p>
            </div>
       
            <div class="font-semibold text-sm text-neutral-600 bottom-0 left-0 absolute p-2">
            °C
            </div>
            <div id="onsign372" class="font-semibold text-green-400 text-sm bottom-0 right-0 absolute p-2">
                +0.00%
            </div>
            
        
        </div>
        
    </div>
    <div class="box-border border-gray-100 h-3/5 w-1/2 p-8 border-2  absolute left-72 bottom-8 rounded-3xl overflow-y-scroll">
            <div class=" top-0 left-0">
                <canvas id="ldrChart"></canvas>
                <canvas id="ultrasonicChart"></canvas>
                <canvas id="temperatureChart"></canvas>
                <canvas id="humidityChart"></canvas>
            </div>
            </div>
    
    <div class=" space-y-2 box-border bg-white drop-shadow-lg border-white h-1/2 w-1/6 p-4 border-2  absolute right-6 top-16 rounded-lg ">
        <div class="flex space-x-1 text-black-300 font-bold ">
            
                Alerts
              
            
            <svg class="w-3 h-3 text-red-600" fill="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
                <path clip-rule="evenodd" fill-rule="evenodd" d="M5.25 9a6.75 6.75 0 0113.5 0v.75c0 2.123.8 4.057 2.118 5.52a.75.75 0 01-.297 1.206c-1.544.57-3.16.99-4.831 1.243a3.75 3.75 0 11-7.48 0 24.585 24.585 0 01-4.831-1.244.75.75 0 01-.298-1.205A8.217 8.217 0 005.25 9.75V9zm4.502 8.9a2.25 2.25 0 104.496 0 25.057 25.057 0 01-4.496 0z"></path>
            </svg>
            
            
        </div>
        <div id="wnotif" class="bg-red-100 border border-red-400 text-red-700 px-3 py-2 rounded relative" role="alert" >
            <strong class="font-bold">Solution Level is low!</strong>
            <span class="block sm:inline text-sm">System needs a refill</span>
        </div>
        <div id="lnotif" class="bg-red-100 border border-red-400 text-red-700 px-4 py-2 rounded relative" role="alert" >
            <strong class="font-bold">It's Getting Dark!</strong>
            <span class="block sm:inline text-sm">Lights may be faulty</span>
        </div>
        <div id="tnotif" class="bg-red-100 border border-red-400 text-red-700 px-3 py-2 rounded relative" role="alert" >
            <strong class="font-bold">It's getting too hot!</strong>
            <span class="block sm:inline text-sm">Turn-on the fans</span>
        </div>
    
    </div>
    <script>
        var closebtns = document.getElementsByClassName("close");
        var i;
        for (i = 0; i < closebtns.length; i++) {
          closebtns[i].addEventListener("click", function() {
            this.parentElement.style.display = 'none';
          });
        }
    </script>
        <script> 
        setInterval(function() {LDR();PercLDR();Ultrasonic();PercSol();Humidity();Temperature();PercTemp();Light_Alert();Water_Alert();Temp_Alert();},1000);
        var notif;
        var notif2;
        var notif3;
        function LDR(){
        var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById("LDR").innerHTML = this.responseText;
            };
            xhr.open('GET', "LDR", true);
            xhr.send();
        }
        function Ultrasonic(){
        var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById("Ultrasonic").innerHTML = this.responseText;
            };
            xhr.open('GET', "Ultrasonic", true);
            xhr.send();
        }
        function Humidity(){
        var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById("Humidity").innerHTML = this.responseText;
            };
            xhr.open('GET', "Humidity", true);
            xhr.send();
        }
        function Temperature(){
        var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById("Temperature").innerHTML = this.responseText;
            };
            xhr.open('GET', "Temperature", true);
            xhr.send();
        }
        function PercLDR(){
            var numb = document.getElementById("LDR").innerHTML;
            var yout = ((numb-1000)/1000)*100;
            document.getElementById("onsign37").innerHTML = yout.toFixed(2)+"%";
            if(yout>60 ||yout< -60){
                document.getElementById("onsign37").style.color = "rgb(239 68 68)";
            }
        
            else{
                document.getElementById("onsign37").style.color = "rgb(74 222 128)";
                document.getElementById("onsign37").innerHTML = yout.toFixed(2)+"%";
            }
        }
        function PercSol(){
            var numb1 = document.getElementById("Ultrasonic").innerHTML;
            var yout1 = ((numb1-100)/100)*100;
            document.getElementById("onsign371").innerHTML = yout1.toFixed(2)+"%";
            if(yout1>60 ||yout1< -60){
                document.getElementById("onsign371").style.color = "rgb(239 68 68)";
            }
        
            else{
                document.getElementById("onsign371").style.color = "rgb(74 222 128)";
                document.getElementById("onsign371").innerHTML = yout1.toFixed(2)+"%";
            }
        }
        function PercTemp(){
            var numb2 = document.getElementById("Temperature").innerHTML;
            var yout2 = ((numb2-23)/23)*100;
            document.getElementById("onsign372").innerHTML = yout2.toFixed(2)+"%";
            if(yout2>30 ||yout2< -30){
                document.getElementById("onsign372").style.color = "rgb(239 68 68)";
            }
        
            else{
                document.getElementById("onsign372").style.color = "rgb(74 222 128)";
                document.getElementById("onsign372").innerHTML = yout2.toFixed(2)+"%";
            }
        }

        function Light_Alert(){
        
        var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200)
                    notif = parseInt(this.responseText);
            };
            xhr.open('GET', "LightN", true);
            xhr.send();
           
            if(notif == 1){
              document.getElementById("lnotif").hidden = false;
            }
            else{
                document.getElementById("lnotif").hidden = true;
            }
        }

        function Water_Alert(){
           
           var xhr = new XMLHttpRequest();
               xhr.onreadystatechange = function (butn) {
                   if (this.readyState == 4 && this.status == 200)
                       notif2 = parseInt(this.responseText);
               };
               xhr.open('GET', "WaterN", true);
               xhr.send();
              
               if(notif2 == 1){
                 document.getElementById("wnotif").hidden = false;
               }
               else{
                   document.getElementById("wnotif").hidden = true;
               }
           }

           function Temp_Alert(){
        
           var xhr = new XMLHttpRequest();
               xhr.onreadystatechange = function (butn) {
                   if (this.readyState == 4 && this.status == 200)
                       notif3 = parseInt(this.responseText);
               };
               xhr.open('GET', "TempN", true);
               xhr.send();
              
               if(notif3 == 1){
                 document.getElementById("tnotif").hidden = false;
               }
               else{
                   document.getElementById("tnotif").hidden = true;
               }
           }

        </script>

<script src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"></script>
<script>
function createCharts() {
  // Get JSON data from PHP script
  var temperatureData = <?php echo $json_Temperature_data; ?>;
  var humidityData = <?php echo $json_Humidity_data; ?>;
  var ldrData = <?php echo $json_LDR_data; ?>;
  var ultrasonicData = <?php echo $json_Ultrasonic_data; ?>;
  
  // temperature chart
  var temperatureChart = new Chart(document.getElementById("temperatureChart"), {
    type: 'line',
    data: {
      labels: temperatureData.map(function(e) { return e.ID; }),
      datasets: [{
        label: 'Temperature',
        data: temperatureData.map(function(e) { return e.Temperature; }),
        borderColor: 'red',
        fill: false
      }]
    },
    options: {
      title: {
        display: true,
        text: 'Temperature'
      }
    }
  });
  
  // humidity chart
  var humidityChart = new Chart(document.getElementById("humidityChart"), {
    type: 'line',
    data: {
      labels: humidityData.map(function(e) { return e.ID; }),
      datasets: [{
        label: 'Humidity',
        data: humidityData.map(function(e) { return e.Humidity; }),
        borderColor: 'blue',
        fill: false
      }]
    },
    options: {
      title: {
        display: true,
        text: 'Humidity'
      }
    }
  });
  
  // LDR chart
  var ldrChart = new Chart(document.getElementById("ldrChart"), {
    type: 'line',
    data: {
      labels: ldrData.map(function(e) { return e.ID; }),
      datasets: [{
        label: 'Light Intensity',
        data: ldrData.map(function(e) { return e.LDR; }),
        borderColor: 'green',
        fill: false
      }]
    },
    options: {
      title: {
        display: true,
        text: 'LDR'
      }
    }
  });
  
  // ultrasonic chart
  var ultrasonicChart = new Chart(document.getElementById("ultrasonicChart"), {
    type: 'line',
    data: {
      labels: ultrasonicData.map(function(e) { return e.ID; }),
      datasets: [{
        label: 'Solution Level',
        data: ultrasonicData.map(function(e) { return e.Ultrasonic; }),
        borderColor: 'orange',
        fill: false
      }]
    },
    options: {
      title: {
        display: true,
        text: 'Ultrasonic'
      }
    }
  });
}
</script>

    
</body>
</html>




)====";
