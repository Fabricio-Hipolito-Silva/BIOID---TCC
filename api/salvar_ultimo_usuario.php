<?php
require 'conecta.php';

$id = $_POST['id'] ?? null;

if ($id !== null) {
    file_put_contents('ultimo_usuario.txt', $id);
    echo "Salvo com sucesso";
} else {
    echo "ID ausente";
}
?>
