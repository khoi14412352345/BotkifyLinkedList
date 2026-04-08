#include "Playlist.h"
#include "BotkifyLinkedList.h"

void test_005() {
    Playlist p("Pop Hits");
    p.addSong(new Song(1, "A", "Art", "Alb", 100, 10, "url"));
    p.addSong(new Song(2, "B", "Art", "Alb", 100, 10, "url"));
    p.addSong(new Song(3, "C", "Art", "Alb", 100, 10, "url"));

    cout << "test_005 next: ";
    for(int i = 0; i < 4; i++) {
        Song* s = p.playNext();
        cout << s->toString() << (i == 3 ? "" : " -> ");
    }
    cout << endl;

    cout << "test_005 prev: ";
    for(int i = 0; i < 4; i++) {
        Song* s = p.playPrevious();
        cout << s->toString() << (i == 3 ? "" : " -> ");
    }
    cout << endl;
    
    p.clear();
}

void test_007() {
    Playlist pA("ListA");
    pA.addSong(new Song(1, "A", "A", "A", 0, 4, "A"));
    pA.addSong(new Song(2, "B", "B", "B", 0, 1, "B"));
    pA.addSong(new Song(3, "C", "C", "C", 0, 3, "C"));
    pA.addSong(new Song(4, "D", "D", "D", 0, 5, "D"));

    Playlist pB("ListB");
    pB.addSong(new Song(5, "E", "E", "E", 0, 1, "E"));
    pB.addSong(new Song(6, "F", "F", "F", 0, 2, "F"));
    pB.addSong(new Song(7, "G", "G", "G", 0, 3, "G"));

    cout << "test_007 compareTo (Spec 3.4): " << (pA.compareTo(pB, 2) ? "true" : "false") << endl;
    
    pA.clear();
    pB.clear();
}

int main() {
    test_005();
    test_007();
    cout << "All tests passed!" << endl;
    return 0;
}
