//
// Created by OriB on 01/09/2015.
//
#include "Song.h"


/**
 * A constructor.
 * Constructs an abstract song with its title, tags and score. Will be used
 * for inheritance only since constructing an abstract song is forbidden.
 * @param title - the song's title.
 * @param tags - the song's map of tags.
 * @param score - the calculated score of the song.
 */
Song::Song(string title, map<string, int> tags, int score)
{
	_title = title;
	_tags = tags;
	_score = score;
}

/**
 * Calculates the tag match score for any type of song.
 * @param query - the query word we calculate score with given by the query file.
 * @param tagMatchScore - the tag score given by the parameters file.
 * @return the tag match score of the song.
 */
int Song::calculateTagMatchScore(string query, int tagMatchScore)
{
    map <string, int> tags = _tags;
    // Go over the tags and update the score if the query was found in the tags.
    for (map <string, int>::iterator it = tags.begin(); it != tags.end(); ++it)
    {
        string tagName = it -> first;
        int tagSignificance;
        if (tagName.compare(query) == 0)
        {
            tagSignificance = it -> second;
            _score += (tagSignificance) * (tagMatchScore);
        }
    }
    return _score;
}

/**
* The printing method of the songs.
* Prints the performer of the instrumental song or the lyricist of the lyrics song.
* @param out - the output object we write to.
* @param song - pointer to the current song we want to print.
* @return the output object we write to.
*/
ostream& operator<<(ostream& out, const Song& song)
{
    song.printSong(out);
    return out;
}

/**
 * Virtual Deconstructor.
 */
Song::~Song(){}
