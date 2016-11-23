<?php
require_once('connect.php');

$temp=$_GET['temp'];
$ip=$_GET['ip'];

$sql = "INSERT INTO watering ( id,temp, ip) VALUES ('1', '$temp','$ip')
 ON DUPLICATE KEY UPDATE
         temp='" . $temp . "',
         ip='" . $ip . "'" ;
		 
$msg="Too hot ";	
$msg2="ok : ".$temp." Celcius";		 

$sql2 = "INSERT INTO sensors (id,motor,message) VALUES ('1','170','$msg')
 ON DUPLICATE KEY UPDATE
         message='" . $msg . "',
         motor='" . "170" . "'" ;
		 
$sql3 = "INSERT INTO sensors (id,motor,message) VALUES ('1','0','$msg2')
 ON DUPLICATE KEY UPDATE
         message='" . $msg2 . "',
         motor='" . "0" . "'" ;
		 
				
if( $temp>30) 	{
	if (mysqli_query($conn, $sql2))     echo " sensorOKHOT ";
}else{
		if (mysqli_query($conn, $sql3))     echo " sensorOKCool";
}	
		
if (mysqli_query($conn, $sql)) {
    echo "success";
} else {
    echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}

mysqli_close($conn);
?>