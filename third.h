char thirdpage[] PROGMEM = R"====(
<?php
  header('Access-Control-Allow-Origin: *');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://cdn.tailwindcss.com"></script>
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
<body>
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
            <button class="flex space-x-2 hover:bg-neutral-700 text-neutral-600 font-normal  pl-4 pr-11 pt-2 pb-2 rounded-lg " onclick="window.location.href='first'">
                <svg class="w-5 h-5 dark:text-neutral-600" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="M12 14l9-5-9-5-9 5 9 5z"></path><path d="M12 14l6.16-3.422a12.083 12.083 0 01.665 6.479A11.952 11.952 0 0012 20.055a11.952 11.952 0 00-6.824-2.998 12.078 12.078 0 01.665-6.479L12 14z"></path><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 14l9-5-9-5-9 5 9 5zm0 0l6.16-3.422a12.083 12.083 0 01.665 6.479A11.952 11.952 0 0012 20.055a11.952 11.952 0 00-6.824-2.998 12.078 12.078 0 01.665-6.479L12 14zm-4 6v-7.5l4-2.222"></path></svg>
                <span>
                    Dashboard
                </span>
                
            </button>
            <button class="flex space-x-2  hover:bg-neutral-700 text-neutral-600 font-normal  pl-4 pr-4 pt-2 pb-2 rounded-lg "  onclick="window.location.href='second'">
                <svg class="w-5 h-5 dark:text-neutral-600" fill="none" stroke="currentColor" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M12 6V4m0 2a2 2 0 100 4m0-4a2 2 0 110 4m-6 8a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4m6 6v10m6-2a2 2 0 100-4m0 4a2 2 0 110-4m0 4v2m0-6V4"></path></svg>
                <span>
                    Control Centre
                </span>
            </button>
            <button class="flex space-x-2 hover:bg-neutral-700 text-slate-300 font-normal  pl-4 pr-14 pt-2 pb-2 rounded-lg ">
                <svg class="w-5 h-5 dark:text-white" fill="none" stroke="currentColor" stroke-width="1.5" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg" aria-hidden="true">
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
            Statistics
    </h1>
    <div class="flex flex-col overflow-y-scroll space-x-10 box-border border-gray-100 h-3/5 w-1/2 border-2 absolute left-72 top-16 rounded-lg">
    <table type="table" class="min-w-full text-left text-sm font-light">
        <thead class="w-full font-medium dark:border-gray-100 border-gray-500 border-2 absolute bg-gray-100 dark:bg-gray-700 dark:text-gray-400 sticky top-0" >
            <tr>
                <th class="pr-12 pl-4 py-2">ID</th>
                <th class="px-10 py-2">Sensor ID</th>
                <th class="px-4 py-2">Sensor Value</th>
                <th class="px-16 py-2">Time</th>
            </tr>
        </thead>
        <tbody>
            <?php
            // connect to database
          
            $con = mysqli_connect("localhost", "root", "", "FinalCapstone");
                    // check connection
        if (mysqli_connect_errno()) {
            echo "Failed to connect to MySQL: " . mysqli_connect_error();
            exit();
        }
    
            $sql = "SELECT * FROM `Stats` ORDER BY `Time` DESC LIMIT 200";
            $result = mysqli_query($con, $sql);
            if(mysqli_num_rows($result) > 0){
            }else{
                $msg = "No Record found";
            }
            ?>
 
<?php
        // output data of each row
        while ($row = mysqli_fetch_assoc($result)) {?>
            <tr>
            <td class='border px-4 py-2'><?php echo $row["ID"];?></td>
            <td class='border px-4 py-2'><?php echo $row["Sensor_ID"]; ?></td>
            <td class='border px-4 py-2'><?php echo number_format($row["Sensor_Value"], 2); ?></td>
            <td class='border px-4 py-2'><?php echo $row["Time"]; ?></td>
            </tr>
        <?}
        ?>

        <?php

        mysqli_close($con);
    
        ?>
    </tbody>
</table>
</div>

            
            <div class="border-2 border-black pl-4 pr-16 pt-2 pb-2 flex space-x-2 absolute bottom-40 left-72 rounded-lg drop-shadow-lg bg-gray-100 hover:bg-neutral-200 text-neutral-600 font-normal">
            <a href="/loginIndex">Update Sketch</a>
            </div>
            <div class=" space-y-4 box-border bg-white drop-shadow-lg border-white h-1/2 w-1/6 p-4 border-2  absolute right-6 top-16 rounded-lg ">

  <form>
  <div>
    <label class="font-bold p-4" for="typeText">Interval Configuration</label>
  </div>
  <br>
  <div class="form-outline">
    <div>
      <label class="form-label" for="tempInput">ID 1: Temp(°C)</label>
    </div>
    <input type="text" id="tempInput" class="form-control border-2 border-slate-100" />
  </div>
  <div class="form-outline">
    <div>
      <label class="form-label" for="humidityInput">ID 2: Humidity(%)</label>
    </div>
    <input type="text" id="humidityInput" class="form-control border-2 border-slate-100" />
  </div>
  <div class="form-outline">
    <div>
      <label class="form-label" for="ldrInput">ID 3: LDR(Ω)</label>
    </div>
    <input type="text" id="ldrInput" class="form-control border-2 border-slate-100" />
  </div>
  <div class="form-outline">
    <div>
      <label class="form-label" for="ultrasonicInput">ID 4: Ultrasonic(cm)</label>
    </div>
    <input type="text" id="ultrasonicInput" class="form-control border-2 border-slate-100" />
  </div>
 
  <button id="changeIntervalsBtn" class="bg-slate-500 hover:bg-slate-700 text-white font-bold py-2 px-4 rounded-full absolute bottom-4 left-8">
    Change Intervals
  </button>
</form>

</div>
    
    
</body>
</html>

<script>

  const changeIntervalsBtn = document.getElementById("changeIntervalsBtn");
  changeIntervalsBtn.addEventListener("click", function(event) {
    event.preventDefault();
    const tempInputValue = document.getElementById("tempInput").value;
    const humidityInputValue = document.getElementById("humidityInput").value;
    const ldrInputValue = document.getElementById("ldrInput").value;
    const ultrasonicInputValue = document.getElementById("ultrasonicInput").value;



    var xhr = new XMLHttpRequest();
    const URL = "handle_input.php";
    const method = "POST";
    const data = new FormData();
    data.append("tempInputValue", tempInputValue);
    data.append("humidityInputValue", humidityInputValue);
    data.append("ldrInputValue", ldrInputValue);
    data.append("ultrasonicInputValue", ultrasonicInputValue);

    xhr.open(method, URL, true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send();

  });
</script>




)====";
