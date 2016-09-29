/*
 * Song.h
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */

#ifndef SONG_H_
#define SONG_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Parameters.h"

using namespace std;
// Song.h


/**
 *  An abstract song class.
 *  This class represents a general song.
 */
class Song
{
public:

	/**
	 * Virtual deconstructor.
	 */
	virtual ~Song();
	/**
	 * The printing method of the songs.
	 * Prints the performer of the instrumental song or the lyricist of the lyrics song.
	 * @param out - the output object we write to.
	 * @param song - pointer to the current song we want to print.
	 * @return the output object we write to.
	 */
	friend ostream& operator<<(ostream& out, const Song& song);
	/**
	 * Helper fuction for the printer << operator which wraps it.
	 * This function does the actual printing for the friend << operator.
	 * @param out - the object we write to.
	 */
    virtual void printSong(ostream& out) const = 0;
    /**
     * Calculates the song's score based on the query input and the given parameters.
     * @param query - the query word we calculate score with given by the query file.
     * @param parameters - the different parameters given by the parameters file.
     */
    virtual void calculateSongScore(const string query, const Parameters& parameters) = 0;
    /**
     * Calculates the tag match score for any type of song.
     * @param query - the query word we calculate score with given by the query file.
     * @param tagMatchScore - the tag score given by the parameters file.
     * @return the tag match score of the song.
     */
    int calculateTagMatchScore(string query, int tagMatchScore);
    /**
     * @return the score of the song.
     */
    inline int getScore() const
    {
    	return _score;
    }



protected:
	string _title; /**< The name of the song */
	map <string, int> _tags;  /**< A map of the tags of the song, indicated by pairs
	 	 	 	 	 	 	 	 	 of tag name and tag significance*/
	int _score;   /**< The overall score of the song */
	/**
	 * A constructor.
	 * Constructs an abstract song with its title, tags and score. Will be used
	 * for inheritance only since constructing an abstract song is forbidden.
	 * @param title - the song's title.
	 * @param tags - the song's map of tags.
	 * @param score - the calculated score of the song.
	 */
	Song(string title, map<string, int> tags, int score = 0);


};


#endif /* SONG_H_ */
