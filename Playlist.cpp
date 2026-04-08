#include "Playlist.h"

// =======================
// Song implementation
// =======================

Song::Song(int id,
           string title,
           string artist,
           string album,
           int duration,
           int score,
           string url)
    : id(id), title(title), artist(artist), album(album),
      duration(duration), score(score), url(url) {}

int Song::getID() const
{
    return id;
}

int Song::getDuration() const
{
    return duration;
}

int Song::getScore() const
{
    return score;
}

string Song::toString() const
{
    return title + "-" + artist;
}

// =======================
// Playlist implementation
// =======================

Playlist::Playlist(string name)
    : name(name), currentIndex(-1) {}

int Playlist::size() const
{
    return lstSong.size();
}

bool Playlist::empty() const
{
    return lstSong.empty();
}

void Playlist::clear()
{
    // Clean up all Song pointers before clearing the list
    while (!lstSong.empty())
    {
        Song* song = lstSong.removeAt(0);
        delete song;
    }
    currentIndex = -1;
}

void Playlist::addSong(Song* s)
{
    lstSong.add(s);
}

void Playlist::removeSong(int index)
{
    Song* song = lstSong.removeAt(index);
    delete song;

    if (lstSong.empty())
    {
        currentIndex = -1;
        return;
    }

    if (index < currentIndex)
    {
        currentIndex--;
    }
    else if (currentIndex >= lstSong.size())
    {
        currentIndex = lstSong.size() - 1;
    }
}

Song* Playlist::getSong(int index) const
{
    return lstSong.get(index);
}

// =======================
// Playing control
// =======================

Song* Playlist::playNext()
{
    if (lstSong.empty())
    {
        throw out_of_range("Index is invalid!");
    }

    if (currentIndex < 0 || currentIndex >= lstSong.size() - 1)
    {
        currentIndex = 0;
    }
    else
    {
        currentIndex++;
    }

    return lstSong.get(currentIndex);
}

Song* Playlist::playPrevious()
{
    if (lstSong.empty())
    {
        throw out_of_range("Index is invalid!");
    }

    if (currentIndex <= 0)
    {
        currentIndex = lstSong.size() - 1;
    }
    else
    {
        currentIndex--;
    }
    return lstSong.get(currentIndex);
}

// =======================
// Score-related
// =======================

int Playlist::getTotalScore()
{
    int totalScore = 0;
    int n = lstSong.size();

    // For each possible group length
    for (int len = 1; len <= n; len++)
    {
        // For each starting position
        for (int start = 0; start <= n - len; start++)
        {
            // Find minimum score in the group
            int minScore = lstSong.get(start)->getScore();
            int sumScore = minScore;

            for (int i = start + 1; i < start + len; i++)
            {
                int score = lstSong.get(i)->getScore();
                minScore = min(minScore, score);
                sumScore += score;
            }

            totalScore += minScore * sumScore;
        }
    }

    return totalScore;
}

bool Playlist::compareTo(const Playlist& p, int numSong)
{
    if (numSong <= 0 || numSong > lstSong.size() || numSong > p.lstSong.size())
    {
        return false;
    }

    // Calculate average score for this playlist
    double thisAverage = 0.0;
    int thisCount = lstSong.size() - numSong + 1;

    for (int i = 0; i <= lstSong.size() - numSong; i++)
    {
        int maxScore = lstSong.get(i)->getScore();
        for (int j = i + 1; j < i + numSong; j++)
        {
            maxScore = max(maxScore, lstSong.get(j)->getScore());
        }
        thisAverage += maxScore;
    }
    thisAverage /= thisCount;

    // Calculate average score for other playlist
    double otherAverage = 0.0;
    int otherCount = p.lstSong.size() - numSong + 1;

    for (int i = 0; i <= p.lstSong.size() - numSong; i++)
    {
        int maxScore = p.lstSong.get(i)->getScore();
        for (int j = i + 1; j < i + numSong; j++)
        {
            maxScore = max(maxScore, p.lstSong.get(j)->getScore());
        }
        otherAverage += maxScore;
    }
    otherAverage /= otherCount;

    return thisAverage >= otherAverage;
}

// =======================
// Advanced playing modes
// =======================

void Playlist::playRandom(int index)
{
    if (index < 0 || index >= lstSong.size())
    {
        return;
    }

    bool* visited = new bool[lstSong.size()];
    for (int k = 0; k < lstSong.size(); k++)
    {
        visited[k] = false;
    }
    stringstream ss;

    int currentSongIndex = index;
    visited[currentSongIndex] = true;
    ss << lstSong.get(currentSongIndex)->toString();

    int currentDuration = lstSong.get(currentSongIndex)->getDuration();

    while (true)
    {
        int nextIndex = -1;
        int minDifference = 1000000;

        // Find the closest song with duration > currentDuration
        for (int i = 0; i < lstSong.size(); i++)
        {
            if (!visited[i])
            {
                int songDuration = lstSong.get(i)->getDuration();
                if (songDuration > currentDuration)
                {
                    int difference = songDuration - currentDuration;
                    if (difference < minDifference)
                    {
                        minDifference = difference;
                        nextIndex = i;
                    }
                }
            }
        }

        if (nextIndex == -1)
        {
            break;
        }

        visited[nextIndex] = true;
        ss << "," << lstSong.get(nextIndex)->toString();
        currentDuration = lstSong.get(nextIndex)->getDuration();
        currentSongIndex = nextIndex;
    }

    cout << ss.str() << endl;
    delete[] visited;
}

int Playlist::playApproximate(int step)
{
    int n = lstSong.size();
    if (n == 0)
        return 0;

    // dp[i] = minimum total duration difference to reach song i
    int* dp = new int[n];
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1000000000;
    }
    dp[0] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (dp[i] == 1000000000)
            continue;

        int currentDuration = lstSong.get(i)->getDuration();

        // Can skip up to 'step' songs, so can reach songs from i+1 to i+step+1
        for (int j = i + 1; j <= min(i + step + 1, n - 1); j++)
        {
            int nextDuration = lstSong.get(j)->getDuration();
            int difference = abs(nextDuration - currentDuration);
            dp[j] = min(dp[j], dp[i] + difference);
        }
    }

    int result = dp[n - 1] == 1000000000 ? 0 : dp[n - 1];
    delete[] dp;
    return result;
}
