<?php
require_once('connect.php'); 

$quary="SELECT * FROM `sensors`";
 $result = mysqli_query($conn, $quary);
if (mysqli_num_rows($result) > 0) {
	
 while($row = mysqli_fetch_assoc($result)) {
	 
        $etat=$row["motor"].','.$row["message"];
        echo($etat);
    }}
    else{
    	echo("no");
    }
?>
