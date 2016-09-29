/*
 * LyricalSong.cpp
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */



// Point.cpp

#include "Song.h"
#include "LyricalSong.h"



// --------------------------------------------------------------------------------------
// This file contains the implementation of the class LyricalSong.
// --------------------------------------------------------------------------------------


/**
 * A constructor.
 * Constructs a lyrical song with the following params.
 * @param title - the song's title.
 * @param tags - the map of song tags.
 * @param lyricist - the lyrics writer of the song.
 * @param lyrics - the vector  of the lyrics of the song.
 */
LyricalSong::LyricalSong(string title, map<string, int> tags, string lyricist,
                         vector<string> lyrics) :  Song::Song(title, tags),
                                                   _lyricist(lyricist), _lyrics(lyrics)
{
}

/**
 * Calculates the song's score based on the query input and the given parameters.
 * @param query - the query word we calculate score with given by the query file.
 * @param parameters - the different parameters given by the parameters file.
 */
void LyricalSong::calculateSongScore(const string query, const Parameters& parameters)
{
	_score = 0;
	calculateTagMatchScore(query, parameters.getTagMatchScore());
	long queryCount = count(_lyrics.begin(), _lyrics.end(), query);
	_score += (queryCount) * (parameters.getLyricsMatchScore());
}

/**
 * Helper fuction for the printer << operator which wraps it.
 * This function does the actual printing for the friend << operator.
 * @param out - the object we write to.
 */
void LyricalSong::printSong(ostream& out) const
{
    out << this -> _title << "\t" << this -> _score << "\t" << "lyrics by: "
    << this -> _lyricist  << endl;
}

/**
 * deconstructor.
 */
LyricalSong::~LyricalSong(){}
