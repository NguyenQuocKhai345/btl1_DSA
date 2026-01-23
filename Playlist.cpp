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
    : id(id),
      title(title),
      artist(artist),
      album(album),
      duration(duration),
      score(score),
      url(url)
{
    // TODO: Student implementation
}

int Song::getID() const
{
    // TODO: Student implementation
    return id;
}

int Song::getDuration() const
{
    // TODO: Student implementation
    return duration;
}

int Song::getScore() const
{
    // TODO: Student implementation
    return score;
}

string Song::toString() const
{
    // TODO: Student implementation
    return title + " " + artist;
}

// =======================
// Playlist implementation
// =======================

Playlist::Playlist(string name) : name(name), size(0), currentSongIndex(0)
{
    // TODO: Student implementation
}

Playlist::~Playlist()
{
    clear();
}

int Playlist::getSize() const
{
    // TODO: Student implementation
    return size;
}

bool Playlist::empty() const
{
    // TODO: Student implementation
    return size == 0;
}

void Playlist::clear()
{
    // TODO: Student implementation
    for (int i = 0; i < size; i++)
    {
        delete lstSong.get(i);
    }
    lstSong.clear();
    size = 0;
    currentSongIndex = 0;
}

void Playlist::addSong(Song *s)
{
    // TODO: Student implementation
    lstSong.add(s);
    size++;
}

void Playlist::removeSong(int index)
{
    // TODO: Student implementation
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index is invalid!");
    }
    Song *needDelete = lstSong.removeAt(index);
    delete needDelete;

    if (index < currentSongIndex)
    {
        currentSongIndex--;
    }

    size--;
    if ((currentSongIndex >= size && size > 0) || size == 0)
    {
        currentSongIndex = 0;
    }
}

Song *Playlist::getSong(int index) const
{
    // TODO: Student implementation
    return lstSong.get(index);
}

// =======================
// Playing control
// =======================

Song *Playlist::playNext()
{
    // TODO: Student implementation
    if (size == 0)
    {
        throw std::out_of_range("Index is invalid!");
    }
    currentSongIndex++;
    if (currentSongIndex >= size)
    {
        currentSongIndex = 0;
    }
    return lstSong.get(currentSongIndex);
}

Song *Playlist::playPrevious()
{
    // TODO: Student implementation
    if (size == 0)
    {
        throw std::out_of_range("Index is invalid!");
    }
    currentSongIndex--;
    if (currentSongIndex < 0)
    {
        currentSongIndex = size - 1;
    }
    return lstSong.get(currentSongIndex);
}

// =======================
// Score-related
// =======================

int Playlist::getTotalScore()
{
    // TODO: Student implementation
    return 0;
}

bool Playlist::compareTo(Playlist p, int numSong)
{
    // TODO: Student implementation
    return false;
}

// =======================
// Advanced playing modes
// =======================

void Playlist::playRandom(int index)
{
    // TODO: Student implementation
}

int Playlist::playApproximate(int step)
{
    // TODO: Student implementation
    return 0;
}
