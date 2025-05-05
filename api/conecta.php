<?php
$hostname = "localhost";
$dbname = "bio_id";
$username = "root";
$password = "";

try {
    $conn = new PDO("mysql:host=$hostname;dbname=$dbname", $username, $password);
    echo "Esp 32 conectado bem sucedida.";
} catch (PDOException $pe) {
    echo "Falha" . $pe -> get_message();
}