const menuOpen = document.getElementById('menu-open');
const menuClose = document.getElementById('menu-close');
const sidebar = document.querySelector('.container .sidebar');

menuOpen.addEventListener('click', () => sidebar.style.left = '0');
menuClose.addEventListener('click', () => sidebar.style.left = '-100%');

var audio = document.getElementById("audio");
var playPauseBTN = document.getElementById("playPauseBTN");
var progressBar = document.getElementById("progressBar");
var progress = document.getElementById("progress");
var currentTimeDisplay = document.getElementById("currentTime");
var durationDisplay = document.getElementById("duration");
var isPlaying = false;

// Play/Pause functionality
function playPause() {
    if (!isPlaying) {
        audio.play();
        isPlaying = true;
        playPauseBTN.classList.remove('bxs-right-arrow');
        playPauseBTN.classList.add('bx-pause');
    } else {
        audio.pause();
        isPlaying = false;
        playPauseBTN.classList.remove('bx-pause');
        playPauseBTN.classList.add('bxs-right-arrow');
    }
}

audio.addEventListener("ended", function () {
    isPlaying = false;
    playPauseBTN.classList.remove('bx-pause');
    playPauseBTN.classList.add('bx bxs-right-arrow play-button');
    progress.style.width = "0%";
    currentTimeDisplay.textContent = "0:00";
});

function toggleLyrics() {
    const lyricsSection = document.querySelector('.lyrics');
    lyricsSection.classList.toggle('open');
}

// Select all play buttons
const playButtons = document.querySelectorAll(".play-button");

// Track the currently playing audio and its button
let currentAudio = null;
let currentButton = null;

playButtons.forEach(button => {
    button.addEventListener("click", function () {

        const parentItem = this.closest(".item");

        const audioPath = parentItem.getAttribute("data-audio");

        // Check if the clicked button corresponds to the currently playing audio
        if (currentAudio && currentButton === button) {
            // Toggle between play and pause
            if (currentAudio.paused) {
                currentAudio.play();
                this.innerHTML = `<i class='bx bx-pause'></i>`; // Change to pause icon
            } else {
                currentAudio.pause();
                this.innerHTML = `<i class='bx bxs-right-arrow'></i>`; // Change back to play icon
            }
        } else {
            // If a new song is clicked, stop the currently playing audio
            if (currentAudio) {
                currentAudio.pause();
                currentAudio.currentTime = 0;
                currentButton.innerHTML = `<i class='bx bxs-right-arrow'></i>`;
            }

            currentAudio = new Audio(audioPath);
            currentAudio.play();

            this.innerHTML = `<i class='bx bx-pause'></i>`;

            currentButton = this;
        }

        currentAudio.addEventListener("ended", () => {
            currentAudio = null;
            currentButton.innerHTML = `<i class='bx bxs-right-arrow'></i>`;
        });
    });
});













