<?php
require_once('connect.php'); 

$temp=$_GET['temp'];
$lum=$_GET['lum'];
$quary="UPDATE `watering` SET `temp`='$temp',`lum`='$lum'  WHERE id=1";
 $result = mysqli_query($conn, $quary);
	echo $result;
//$quary2="UPDATE `webcontroler` SET `ETATLUM`='0' WHERE 1";
// $result = mysqli_query($conn, $quary2);
?>