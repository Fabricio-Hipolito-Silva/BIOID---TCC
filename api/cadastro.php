<?php
require "conecta.php";
$nome = $_POST['nome'] ?? null;
$id = $_POST['id'] ?? null;

if ($nome !== null && $id !== null) {
    $sql = 'REPLACE INTO usuarios (id, nome) VALUES (:id, :nome)';
    $replace = $conn->prepare($sql);
    $replace->bindParam(":id", $id);
    $replace->bindParam(":nome", $nome);

    try {
        $replace->execute();
        echo "Cadastrado com Sucesso";
    } catch (PDOException $pe) {
        echo "Falha no Cadastro".$pe->getMessage();
    };
}else{
    echo "Algum Valor Nulo, tente denovo.";
}
