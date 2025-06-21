<?php
$hostname = "localhost";
$dbname = "bio_id";
$username = "root";
$password = "";

try {
    $conn = new PDO("mysql:host=$hostname;dbname=$dbname", $username, $password);
} catch (PDOException $pe) {
    echo "Falha" . $pe -> get_message();
}