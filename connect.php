
<?php  
 $hostname_localhost ="localhost";  
 $database_localhost ="webcontroler";  
 $username_localhost ="root";  
 $password_localhost ="";  
 $conn = mysqli_connect($hostname_localhost, $username_localhost, $password_localhost, $database_localhost);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
 ?>