
<?php
//Kod od odbierania danych z ESP32 i zapisywania ich do pliku rollers.json
//Dane można podejrzec pod adresem https://srv97872.seohost.com.pl/rollers.json
//Dane można podejrzec pod adresem https://srv97872.seohost.com.pl/job_todo.json
//zapisa jako id - klucz
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

// JSON zawsze ma DEVICE_ID jako klucz nadrzędny
// Iterujemy po wszystkich urządzeniach (choć w Twoim przypadku zwykle jedno)
foreach ($data as $deviceID => $deviceData) {

    // Zapis pliku rollers.json
    if (isset($deviceData["rollers"])) {
        $rollersFile = __DIR__ . "/rollers.json";
        // Odczyt istniejącego pliku, jeśli chcemy zachować dane innych urządzeń
        if (file_exists($rollersFile)) {
            $allRollers = json_decode(file_get_contents($rollersFile), true);
            if (!is_array($allRollers)) $allRollers = [];
        } else {
            $allRollers = [];
        }

        // Aktualizacja danych dla tego urządzenia
        $allRollers[$deviceID] = $deviceData["rollers"];
        file_put_contents($rollersFile, json_encode($allRollers, JSON_PRETTY_PRINT));
    }

    // Zapis pliku job_todo.json
    if (isset($deviceData["job_todo"])) {
        $jobFile = __DIR__ . "/job_todo.json";
        if (file_exists($jobFile)) {
            $allJobs = json_decode(file_get_contents($jobFile), true);
            if (!is_array($allJobs)) $allJobs = [];
        } else {
            $allJobs = [];
        }

        // Aktualizacja danych dla tego urządzenia
        $allJobs[$deviceID] = $deviceData["job_todo"];
        file_put_contents($jobFile, json_encode($allJobs, JSON_PRETTY_PRINT));
    }
}

echo "OK";
?>