# Botkify Demo App

This folder contains a simple C++ demo app for a small music player called Botkify. The project uses a custom singly linked list to store songs inside a playlist and provides a console menu to simulate playback.

## Files

- `BotkifyLinkedList.h`: templated linked list used by the playlist
- `Playlist.h`, `Playlist.cpp`: `Song` and `Playlist` classes
- `main.cpp`: demo application entry point
- `main.h`, `utils.h`: shared includes and utility declarations

## Features

- Create a playlist with sample songs
- Show all songs in the playlist
- Play the next song
- Play the previous song
- Auto-play 3 songs in sequence
- Calculate playlist total score
- Play a random duration-based chain
- Compute approximate playback cost with a configurable step

## Build

Open a terminal in this folder and compile with `g++`:

```bash
g++ -std=c++17 main.cpp Playlist.cpp -o botkify_demo.exe
```

## Run

After building, run:

```bash
./botkify_demo.exe
```

On Windows PowerShell, this is usually:

```powershell
.\botkify_demo.exe
```

## Demo Flow

When the app starts, it:

1. Creates a playlist named `Botkify Demo Mix`
2. Loads 5 sample songs
3. Prints the playlist
4. Plays the first 3 songs
5. Opens an interactive menu

Menu options:

- `1`: Show playlist
- `2`: Play 3 songs
- `3`: Play next song
- `4`: Play previous song
- `5`: Show playlist score
- `6`: Play random chain starting from the first song
- `7`: Show approximate jump score with step `2`
- `0`: Exit

## Core Classes

### Song

Represents one track in the playlist.

Stored information:

- song ID
- title
- artist
- album
- duration
- score
- URL

### Playlist

Manages a list of `Song*` values using `BotkifyLinkedList<Song*>`.

Important operations:

- `addSong`
- `removeSong`
- `getSong`
- `playNext`
- `playPrevious`
- `getTotalScore`
- `compareTo`
- `playRandom`
- `playApproximate`

### BotkifyLinkedList

A generic linked list implementation that supports:

- append
- insert by index
- remove by index
- remove by value
- random access by index
- clear
- convert to string

## Notes

- This demo simulates playback by printing `Now playing:` messages in the console.
- The project currently does not play real audio files.
- Songs are dynamically allocated and cleaned up by `Playlist::clear()` and `removeSong()`.
