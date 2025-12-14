Importatnt variables:


DEVICE_ID "ESP32_xxxxx"//device serial. Edit while new device

//WIFI connection
const char ssid[] = "";
const char password[] = "";

//Server data
String HOST_NAME = "https://srv97872.seohost.com.pl";  // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME = "/connectEspRollerShutter.php";         //REPLACE WITH YOUR PHP FILE NAME
String JSON_FILE_1 = "/rollers.json";
String JSON_FILE_2 = "/job_todo.json";
String server = "";