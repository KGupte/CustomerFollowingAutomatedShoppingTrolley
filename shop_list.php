/*
*	This code updates the shopping list of the customer as the products are added to the trolley.
*/

<?php
				$server = "localhost";
				$username = "root";
				$password = "";
				$dbname = "insert";
				
				$conn = mysqli_connect($server, $username, $password,$dbname);
?>
<!doctype html>
<html>
	<head>
		<title>
			Shoping List
		</title>
	</head>
	<body>
		<form action="" method="POST" >
			<label> Product ID:</label><input type="text" name="pid"><br><br>
			<button type="submit" name="Add">ADD</button>
			<button type="submit" name="Done">DONE</button>
		</form>
		
		<table align="center" border="1px" style="width:600px; line-height:40px">
			<tr>
				<th colspan="3"><h2>Shopping List</h2></th>
			</tr>
			<t>
				<th> Product Name </th>
				<th> Cost (RS.) </th>
			</t>
			
			
			<?php
				
				if(isset($_POST['Add']))
				{
					$pid = $_POST['pid'];
					
					$query = "insert into shoping_list(pname,cost) (select pname,cost from product_list where pid='$pid')";
					$run = mysqli_query($conn,$query);
					$query_1="select * from shoping_list";
					$run_1 = mysqli_query($conn,$query_1);
					
					while($rows = mysqli_fetch_array($run_1))
					{
			?>
			
			<tr>
				<td align="center"><?php echo $rows['pname'];?></td>
				<td align="center"><?php echo $rows['cost'];?></td>
				
			</tr>
			<?php
				}
				
			}
		?>
		
		<?php
				
				if(isset($_POST['Done']))
				{
					
					$query_2 = "insert into shoping_list(pname,cost) (select 'TOTAL',sum(cost) from shoping_list)";
					$run = mysqli_query($conn,$query_2);
					$query_3="select * from shoping_list";
					$run_2 = mysqli_query($conn,$query_3);
					
					$query_4="truncate table shoping_list";
					$run_3 = mysqli_query($conn,$query_4);
					
					$query_5="alter table shopping_list auto_increment = 1";
					$run_4 = mysqli_query($conn,$query_5);
					
					while($row = mysqli_fetch_array($run_2))
					{
			?>
			<tr>
				<td align="center"><?php echo $row['pname'];?></td>
				<td align="center"><?php echo $row['cost'];?></td>
				
			</tr>
			<?php
				}
				
			}
		?>
		
	</body>
</html>