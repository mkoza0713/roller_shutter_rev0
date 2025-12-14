<?php
// Włącz debugowanie błędów
ini_set('display_errors', 1);
error_reporting(E_ALL);

// Odbieranie danych z ESP32
$rawData = file_get_contents("php://input");
$data = json_decode($rawData, true);

if ($data === null) {
    echo "Błąd: JSON nie został poprawnie odczytany";
    exit;
}

// Plik, w którym przechowujemy wszystkie urządzenia
$jsonFile = __DIR__ . "/devices.json";

// Wczytanie istniejącego pliku, jeśli istnieje
if (file_exists($jsonFile)) {
    $allDevices = json_decode(file_get_contents($jsonFile), true);
    if (!is_array($allDevices)) $allDevices = [];
} else {
    $allDevices = [];
}

// Iterujemy po wszystkich urządzeniach w przesłanym JSON
foreach ($data as $deviceID => $deviceData) {
    $allDevices[$deviceID] = $deviceData; // aktualizacja lub dopisanie nowego urządzenia
}

// Zapis zaktualizowanego pliku JSON
file_put_contents($jsonFile, json_encode($allDevices, JSON_PRETTY_PRINT));

echo "OK";
?>
