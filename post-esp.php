/*
* This code searches the database based on product ID (which it receives frm Arduino Mega)
* and then it send that PID's weight back to arduino for further processing.
*/

<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "insert";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

$api_key= $pname = $cost = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
		$pid = $_POST['pid'];
		$counter = $_POST['counter'];
		
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
		
		if ($pid == 'done'){
			$query_2 = "insert into shoping_list(pname,cost) (select 'TOTAL',sum(cost) from shoping_list)";
			$run = mysqli_query($conn,$query_2);
			$query_3="select * from shoping_list";
			$run_2 = mysqli_query($conn,$query_3);
		}
		else{
			$sql1 = "SELECT weight FROM product_list WHERE pid = '$pid'";
			$result = mysqli_query($conn,$sql1);
			while($row = mysqli_fetch_array($result)) 
			{
				echo $row['weight']; 
			}
        	
			if ($counter == "Proceed"){
				$sql = "INSERT INTO shoping_list (pname, cost)
				(select pname,cost from product_list where pid='$pid')";
				$result = mysqli_query($conn,$sql);
			}
        }    
        $conn->close();
    }
 	
    else {
        echo "Wrong API Key provided.";
    }
}
else {
    echo "No data posted with HTTP POST.";
}
function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}