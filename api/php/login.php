<?php

$servername = "Localhost";
$username = "root";
$pass = "aryanshr";
$db_name = "verse";

$conn = mysqli_connect($servername, $username, $pass, $db_name);

if(!$conn){
    die("Failed". mysqli_connect_error());
}

$error = ""; // Variable to store error messages

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user_id = trim($_POST["user_id"]);
    $name = trim($_POST["name"]);
    $email = trim($_POST["email"]);
    $password = trim($_POST["password"]);
    
    // Input validation
    if (empty($user_id) || !is_numeric($user_id)) {
        $error = "User ID must be a valid number.";
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $error = "Invalid email format.";
    } elseif (strlen($password) < 6) {
        $error = "Password must be at least 6 characters long.";
    } else {
        // Hash the password for security
        $hashed_password = password_hash($password, PASSWORD_BCRYPT);
        
        // Insert into database
        $stmt = $conn->prepare("INSERT INTO users (user_id, username, email, pass) VALUES (?, ?, ?, ?)");
        $stmt->bind_param("isss", $user_id, $name, $email, $hashed_password);
        
        if ($stmt->execute()) {
            // Redirect to the main page
            header("Location: http://localhost:5500/frontend/public/verse.html");
            exit;
        } else {
            if ($conn->errno === 1062) { // Error code for duplicate entry
                $error = "User ID or email already exists.";
            } else {
                $error = "Error: " . $stmt->error;
            }
        }
        
        $stmt->close();
    }
}

$conn->close();
?>
