<?php
require 'conecta.php';
$id = $_GET['id'] ?? null;

if ($id !== null) {
    $sql = 'SELECT nome FROM usuarios WHERE id = :id';
    $select = $conn->prepare($sql);
    $select->bindParam(":id", $id);

    try {
        $select->execute();
        $resultado = $select->fetch(PDO::FETCH_ASSOC);
        if ($resultado) { //Se tem algo ai dentro
            echo $resultado['nome']; //Ele printa o valor .nome que o bgl retornou
        } else {
            echo "ID não encontrado";
        }
    } catch (PDOException $pe) {
        echo "Falha na Consulta: " . $pe->getMessage();
    }
} else {
    echo "Valor Nulo";
}
?>


