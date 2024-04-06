/*
*This code is used to insert new products to the Product List of the shop.
*/

<?php
	$server = "localhost";
	$username = "root";
	$password = "";
	$dbname = "insert";
	
	$conn = mysqli_connect($server, $username, $password,$dbname);
	
	if(isset($_POST['submit'])){
		
		if(!empty($_POST['pid']) && !empty($_POST['pname']) && !empty($_POST['weight']) && !empty($_POST['cost']))
		{
			
			$pid = $_POST['pid'];
			$pname = $_POST['pname'];
			$weight = $_POST['weight'];
			$cost = $_POST['cost'];
			
			$query = "insert into product_list(pid,pname,weight,cost) 
					  VALUES ('$pid','$pname','$weight','$cost')";
			
			$run = mysqli_query($conn,$query) or die(mysqli_error());
			
			if($run){
				echo "Form Submitted succesfully";
			}
			
			else{
				echo "Form not submitted";
			}
				
			}
		else{
			echo "All fields compulsory";
		}
	}
?>