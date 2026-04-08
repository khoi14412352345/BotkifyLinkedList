#include "Playlist.h"

void printDivider()
{
    cout << "----------------------------------------" << endl;
}

void seedDemoPlaylist(Playlist& playlist)
{
    playlist.addSong(new Song(1, "City Lights", "Nova Lane", "Night Drive", 198, 8, "demo://city-lights"));
    playlist.addSong(new Song(2, "Ocean Echo", "Blue Static", "Coastline", 214, 7, "demo://ocean-echo"));
    playlist.addSong(new Song(3, "Sunrise Code", "Pixel Bloom", "Morning Build", 186, 9, "demo://sunrise-code"));
    playlist.addSong(new Song(4, "Neon Rain", "Echo Harbor", "Midnight Signals", 221, 6, "demo://neon-rain"));
    playlist.addSong(new Song(5, "Golden Hour Loop", "Paper Skies", "Weekend Mix", 203, 8, "demo://golden-hour-loop"));
}

void showPlaylist(const Playlist& playlist)
{
    printDivider();
    cout << "Playlist contains " << playlist.size() << " songs:" << endl;
    for (int i = 0; i < playlist.size(); i++)
    {
        Song* song = playlist.getSong(i);
        cout << i + 1 << ". " << song->toString()
             << " | duration: " << song->getDuration() << "s"
             << " | score: " << song->getScore() << endl;
    }
}

void playSeveralSongs(Playlist& playlist, int count)
{
    printDivider();
    for (int i = 0; i < count; i++)
    {
        Song* song = playlist.playNext();
        cout << "Now playing: " << song->toString()
             << " (" << song->getDuration() << "s)" << endl;
    }
}

void showMenu()
{
    printDivider();
    cout << "Botkify Demo Menu" << endl;
    cout << "1. Show playlist" << endl;
    cout << "2. Play 3 songs" << endl;
    cout << "3. Play next song" << endl;
    cout << "4. Play previous song" << endl;
    cout << "5. Show playlist score" << endl;
    cout << "6. Play random chain from song 1" << endl;
    cout << "7. Show approximate jump score (step = 2)" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose: ";
}

int main()
{
    Playlist playlist("Botkify Demo Mix");
    seedDemoPlaylist(playlist);

    cout << "Botkify Demo App" << endl;
    cout << "Loaded a sample playlist and ready to play." << endl;
    showPlaylist(playlist);
    playSeveralSongs(playlist, 3);

    bool running = true;
    while (running)
    {
        showMenu();

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 0 to 7." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            showPlaylist(playlist);
            break;
        case 2:
            playSeveralSongs(playlist, 3);
            break;
        case 3:
            printDivider();
            cout << "Now playing: " << playlist.playNext()->toString() << endl;
            break;
        case 4:
            printDivider();
            cout << "Now playing: " << playlist.playPrevious()->toString() << endl;
            break;
        case 5:
            printDivider();
            cout << "Playlist total score: " << playlist.getTotalScore() << endl;
            break;
        case 6:
            printDivider();
            cout << "Random playback chain:" << endl;
            playlist.playRandom(0);
            break;
        case 7:
            printDivider();
            cout << "Minimum duration difference with step 2: "
                 << playlist.playApproximate(2) << endl;
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "Please choose a number from 0 to 7." << endl;
            break;
        }
    }

    playlist.clear();
    cout << "Botkify demo closed." << endl;
    return 0;
}