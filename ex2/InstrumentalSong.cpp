/*
 * InstrumentalSong.cpp
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */


// Point.cpp
#include "Song.h"
#include "InstrumentalSong.h"



// --------------------------------------------------------------------------------------
// This file contains the implementation of the InstrumentalSong class.
// --------------------------------------------------------------------------------------


// Constructor
/**
 * A constructor.
 * Constructs an instrumental song with the following params.
 * @param title - the song's title.
 * @param tags - the map of song tags.
 * @param performer - the performer of the song.
 * @param instruments - the vector  of the instruments of the song.
 * @param bpm - the bpm of the song, 0 on default.
 */
InstrumentalSong::InstrumentalSong(string title, map<string, int> tags, string performer,
								   vector<string> instruments,
								   double bpm) : Song::Song(title, tags),
								   _performer(performer), _instruments(instruments),
								   _bpm(bpm)
{
}

/**
 * Calculates the song's score based on the query input and the given parameters.
 * @param query - the query word we calculate score with given by the query file.
 * @param parameters - the different parameters given by the parameters file.
 */
void InstrumentalSong::calculateSongScore(const string query, const Parameters& parameters)
{
	_score = 0;
	calculateTagMatchScore(query, parameters.getTagMatchScore());
	// Update the score if the query was found in the instruments.
	if(find(_instruments.begin(), _instruments.end(), query) != _instruments.end())
	{
		_score += parameters.getInstrumentMatchScore();
	}
	// Bpm Likelihood grade calculation
	if (_bpm > NO_BPM)
	{
		// If the query is in the search words use the formula.
		int bpmLikelihoodWeight = parameters.getBpmLikelihoodWeight();
		SearchWords searchWords = parameters.getSearchWords();
		if (searchWords.find(query) != searchWords.end())
		{
			double average = searchWords.at(query).first;
			double standardDeviation = searchWords.at(query).second;
			_score += floor((bpmLikelihoodFormula(_bpm, average, standardDeviation))
					 * (bpmLikelihoodWeight));
		}
	}
}

/**
 * Helper fuction for the printer << operator which wraps it.
 * This function does the actual printing for the friend << operator.
 * @param out - the object we write to.
 */
void InstrumentalSong::printSong(ostream& out) const
{
	out << this -> _title << "\t" << this -> _score << "\t" << "performed by: "
    << this -> _performer  << endl;
}

/**
 * deconstructor.
 */
InstrumentalSong::~InstrumentalSong() {}

