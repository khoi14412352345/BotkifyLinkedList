#include "Playlist.h"
#include "BotkifyLinkedList.h"

void testBotkifyLinkedList() {
    cout << "===== Testing BotkifyLinkedList =====" << endl;
    
    BotkifyLinkedList<int> list;
    
    // Test empty and size
    cout << "Empty list: " << (list.empty() ? "true" : "false") << endl;
    cout << "Size: " << list.size() << endl;
    
    // Test add
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    cout << "After adding 1,2,3,4,5: " << list.toString() << endl;
    cout << "Size: " << list.size() << endl;
    
    // Test add at index
    list.add(2, 10);
    cout << "After adding 10 at index 2: " << list.toString() << endl;
    
    // Test get
    cout << "Element at index 2: " << list.get(2) << endl;
    
    // Test removeAt
    int removed = list.removeAt(2);
    cout << "Removed element at index 2: " << removed << endl;
    cout << "After removal: " << list.toString() << endl;
    
    // Test removeItem
    bool found = list.removeItem(3);
    cout << "Removed item 3: " << (found ? "true" : "false") << endl;
    cout << "After removal: " << list.toString() << endl;
    
    cout << endl;
}

void testSong() {
    cout << "===== Testing Song =====" << endl;
    
    Song song1(1, "BabyShark", "Pinkfong", "Baby Shark Single", 180, 800, "http://example.com/song1");
    Song song2(2, "HelloWorld", "TestArtist", "Test Album", 240, 750, "http://example.com/song2");
    
    cout << "Song 1 ID: " << song1.getID() << endl;
    cout << "Song 1 Duration: " << song1.getDuration() << endl;
    cout << "Song 1 Score: " << song1.getScore() << endl;
    cout << "Song 1 toString: " << song1.toString() << endl;
    
    cout << "Song 2 toString: " << song2.toString() << endl;
    cout << endl;
}

void testPlaylist() {
    cout << "===== Testing Playlist =====" << endl;
    
    // Create a playlist
    Playlist playlist("My Favorite Songs");
    
    // Test empty and size
    cout << "Empty playlist: " << (playlist.empty() ? "true" : "false") << endl;
    cout << "Size: " << playlist.size() << endl;
    
    // Add songs
    Song* s1 = new Song(1, "Song1", "Artist1", "Album1", 100, 4, "url1");
    Song* s2 = new Song(2, "Song2", "Artist2", "Album2", 150, 1, "url2");
    Song* s3 = new Song(3, "Song3", "Artist3", "Album3", 200, 3, "url3");
    Song* s4 = new Song(4, "Song4", "Artist4", "Album4", 250, 5, "url4");
    
    playlist.addSong(s1);
    playlist.addSong(s2);
    playlist.addSong(s3);
    playlist.addSong(s4);
    
    cout << "After adding 4 songs - Size: " << playlist.size() << endl;
    cout << "Song at index 0: " << playlist.getSong(0)->toString() << endl;
    cout << "Song at index 2: " << playlist.getSong(2)->toString() << endl;
    
    // Test playNext and playPrevious
    cout << "\nTesting playback:" << endl;
    cout << "Current song (playNext): " << playlist.playNext()->toString() << endl;
    cout << "Next song (playNext): " << playlist.playNext()->toString() << endl;
    cout << "Previous song (playPrevious): " << playlist.playPrevious()->toString() << endl;
    
    // Test getTotalScore
    cout << "\nPlaylist score calculation:" << endl;
    cout << "Total Score: " << playlist.getTotalScore() << endl;
    
    // Test compareTo
    Playlist playlist2("Another Playlist");
    Song* p2s1 = new Song(5, "SongA", "ArtistA", "AlbumA", 120, 1, "urlA");
    Song* p2s2 = new Song(6, "SongB", "ArtistB", "AlbumB", 160, 2, "urlB");
    Song* p2s3 = new Song(7, "SongC", "ArtistC", "AlbumC", 210, 3, "urlC");
    
    playlist2.addSong(p2s1);
    playlist2.addSong(p2s2);
    playlist2.addSong(p2s3);
    
    cout << "Playlist 1 score: " << playlist.getTotalScore() << endl;
    cout << "Playlist 2 score: " << playlist2.getTotalScore() << endl;
    cout << "Compare playlists (numSong=2): " << (playlist.compareTo(playlist2, 2) ? "true" : "false") << endl;
    
    // Test playRandom
    cout << "\nTesting playRandom starting from index 0:" << endl;
    playlist.playRandom(0);
    
    // Test playApproximate
    cout << "\nTesting playApproximate with step=1:" << endl;
    int minDiff = playlist.playApproximate(1);
    cout << "Minimum total duration difference: " << minDiff << endl;
    
    // Test removeSong
    cout << "\nRemoving song at index 1:" << endl;
    playlist.removeSong(1);
    cout << "Size after removal: " << playlist.size() << endl;
    
    // Cleanup
    playlist.clear();
    playlist2.clear();
    
    cout << endl;
}

int main() {
    try {
        testBotkifyLinkedList();
        testSong();
        testPlaylist();
        cout << "===== All Tests Completed Successfully =====" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}