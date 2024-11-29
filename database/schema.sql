-- Step 1: Create the database (if not already created)
CREATE DATABASE IF NOT EXISTS verse;

-- Step 2: Use the created database
USE verse;

-- Step 3: Create the users table
CREATE TABLE users (
    user_id INT PRIMARY KEY,
    username VARCHAR(70) UNIQUE,
    email VARCHAR(70),
    pass VARCHAR(70) UNIQUE NOT NULL,
    profile_picture VARCHAR(70),
    account_type ENUM('free', 'premium') DEFAULT 'free',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Step 4: Create the playlists table
CREATE TABLE playlists (
    playlist_id INT PRIMARY KEY,
    user_id INT,
    name VARCHAR(70),
    description VARCHAR(70),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    genre VARCHAR(70),
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

-- Step 5: Create the songs table
CREATE TABLE songs (
    song_id INT PRIMARY KEY,
    spotify_id VARCHAR(70) UNIQUE,
    title VARCHAR(70),
    artist VARCHAR(70),
    album VARCHAR(70),
    duration INT
);

-- Step 6: Create the playlist_songs table
CREATE TABLE playlist_songs (
    playlist_id INT,
    song_id INT,
    position INT,
    added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (playlist_id, song_id),
    FOREIGN KEY (playlist_id) REFERENCES playlists(playlist_id),
    FOREIGN KEY (song_id) REFERENCES songs(song_id)
);
