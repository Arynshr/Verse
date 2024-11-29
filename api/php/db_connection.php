<?php

class databaseManager
{

    private $conn;

    public function __construct()
    {
        $servername = "Localhost";
        $username = "root";
        $pass = "aryanshr";
        $db_name = "verse";

        $conn = mysqli_connect($servername, $username, $pass, $db_name);

        if(!$conn){
            die("Failed". mysqli_connect_error());
        }
        echo "Connection established";
    }
}
