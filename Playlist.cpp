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
    if (size == 0)
        return 0;

    Song **songs = lstSong.toArray();
    int *scores = new int[size];
    for (int i = 0; i < size; i++)
        scores[i] = songs[i]->getScore();

    // Tính Prefix Sum cho scores
    long long *P = new long long[size + 1];
    P[0] = 0; // P[i+1] lưu tổng 0..i
    for (int i = 0; i < size; i++)
        P[i + 1] = P[i] + scores[i];

    // Tính Prefix Sum của Prefix Sum (Double Prefix Sum)
    long long *PP = new long long[size + 2];
    PP[0] = 0;
    for (int i = 0; i <= size; i++)
        PP[i + 1] = PP[i] + P[i];

    // Tìm Previous Less Element (PLE) và Next Less Element (NLE)
    int *L = new int[size];
    int *R = new int[size];

    // Stack thủ công
    int *stack = new int[size];
    int top = -1;

    // Tính L[i]: index phần tử đầu tiên bên trái < scores[i]
    for (int i = 0; i < size; i++)
    {
        while (top != -1 && scores[stack[top]] >= scores[i])
            top--;
        L[i] = (top == -1) ? -1 : stack[top];
        stack[++top] = i;
    }

    // Reset stack
    top = -1;
    // Tính R[i]: index phần tử đầu tiên bên phải <= scores[i]
    for (int i = size - 1; i >= 0; i--)
    {
        while (top != -1 && scores[stack[top]] > scores[i])
            top--;
        R[i] = (top == -1) ? size : stack[top];
        stack[++top] = i;
    }

    long long total = 0;
    for (int i = 0; i < size; i++)
    {
        long long m = scores[i];
        int l = L[i] + 1; // Bắt đầu range
        int r = R[i] - 1; // Kết thúc range
        // Index thực tế trong P là k+1.
        // Công thức: sum_j sum_k (P[k+1] - P[j])
        // Tổng score các subarray qua i trong [l, r]

        // Term 1: (i - l + 1) * Sum(P[k+1] với k từ i đến r)
        // Sum(P[k+1]) = PP[r+2] - PP[i+1]
        long long term1 = (long long)(i - l + 1) * (PP[r + 2] - PP[i + 1]);

        // Term 2: (r - i + 1) * Sum(P[j] với j từ l đến i)
        // Lưu ý: P[j] tương ứng subarray bắt đầu tại j. Trong công thức P[k]-P[j-1], j chạy từ l..i.
        // Sum(P[j] với j=l..i) tương đương Sum(P[x] với index P từ l..i)
        // = PP[i+1] - PP[l]
        long long term2 = (long long)(r - i + 1) * (PP[i + 1] - PP[l]);

        total += m * (term1 - term2);
    }

    delete[] songs;
    delete[] scores;
    delete[] P;
    delete[] PP;
    delete[] L;
    delete[] R;
    delete[] stack;

    return (int)total;
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
