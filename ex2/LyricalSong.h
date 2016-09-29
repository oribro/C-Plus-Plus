/*
 * LyricalSong.h
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */

#ifndef LYRICALSONG_H_
#define LYRICALSONG_H_

#include "Song.h"
#include <algorithm>

// LyricalSong.h

/**
 *  A LyricalSong class.
 *  This class represents a song with lyrics.
 */

class LyricalSong : public Song
{
public:
	/**
     * A constructor.
     * Constructs a lyrical song with the following params.
     * @param title - the song's title.
     * @param tags - the map of song tags.
     * @param lyricist - the lyrics writer of the song.
     * @param lyrics - the vector  of the lyrics of the song.
     */
	LyricalSong(string title, map<string, int> tags, string lyricist, vector<string> lyrics);
	/**
	 * Helper fuction for the printer << operator which wraps it.
	 * This function does the actual printing for the friend << operator.
	 * @param out - the object we write to.
	 */
    void printSong(ostream& out) const override;
    /**
     * Calculates the song's score based on the query input and the given parameters.
     * @param query - the query word we calculate score with given by the query file.
     * @param parameters - the different parameters given by the parameters file.
     */
	void calculateSongScore(const string query, const Parameters& parameters) override;
	/**
	 * deconstructor.
	 */
	~LyricalSong();

private:
	string _lyricist; /**< The writer of the lyrics of the song */
	vector<string> _lyrics; /**< The lyrics of the song */

};


#endif /* LYRICALSONG_H_ */
