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
    public function createPlaylist($userId, $name, $description) {
        $stmt = $this->conn->prepare("INSERT INTO playlists (user_id, name, description) VALUES (?, ?, ?)");
        $stmt->bind_param("iss", $userId, $name, $description);
        return $stmt->execute();
    }

    // Search Songs
    public function searchSongs($query) {
        $searchTerm = "%{$query}%";
        $stmt = $this->conn->prepare("
            SELECT song_id, title, artist, album 
            FROM songs 
            WHERE title LIKE ? OR artist LIKE ? 
            LIMIT 20
        ");
        $stmt->bind_param("ss", $searchTerm, $searchTerm);
        $stmt->execute();
        $result = $stmt->get_result();
        return $result->fetch_all(MYSQLI_ASSOC);
    }

    // Get User Playlists
    public function getUserPlaylists($userId) {
        $stmt = $this->conn->prepare("
            SELECT playlist_id, name, description, created_at 
            FROM playlists 
            WHERE user_id = ?
        ");
        $stmt->bind_param("i", $userId);
        $stmt->execute();
        $result = $stmt->get_result();
        return $result->fetch_all(MYSQLI_ASSOC);
    }

    // Add Song to Playlist
    public function addSongToPlaylist($playlistId, $songId, $userId) {
        $stmt = $this->conn->prepare("
            INSERT INTO playlist_songs (playlist_id, song_id, added_by_user_id) 
            VALUES (?, ?, ?)
        ");
        $stmt->bind_param("iii", $playlistId, $songId, $userId);
        return $stmt->execute();
    }

    // Close connection
    public function __destruct() {
        $this->conn->close();
    }
}

// Handle AJAX Requests
header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $db = new DatabaseManager();
    $action = $_POST['action'] ?? '';

    switch($action) {
        case 'create_playlist':
            $result = $db->createPlaylist($_POST['user_id'], $_POST['name'], $_POST['description']);
            echo json_encode(['success' => $result]);
            break;

        case 'search_songs':
            $songs = $db->searchSongs($_POST['query']);
            echo json_encode($songs);
            break;

        case 'get_playlists':
            $playlists = $db->getUserPlaylists($_POST['user_id']);
            echo json_encode($playlists);
            break;

        case 'add_song_to_playlist':
            $result = $db->addSongToPlaylist(
                $_POST['playlist_id'], 
                $_POST['song_id'], 
                $_POST['user_id']
            );
            echo json_encode(['success' => $result]);
            break;
    }
}
