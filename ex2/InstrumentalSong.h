/*
 * InstrumentalSong.h
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */

#ifndef INSTRUMENTALSONG_H_
#define INSTRUMENTALSONG_H_

#include <cmath>
#include "Song.h"
#include <algorithm>

#define NO_BPM 0
#define SQUARE 2.0
enum FormulaVars
{   MINUS = -1,
	MULT_TWO = 2
};
// InstrumentalSong.h

/**
 *  An InstrumentalSong class.
 *  This class represents a song with musical instruments.
 */
class InstrumentalSong : public Song
{
public:
	/**
     * A constructor.
     * Constructs an instrumental song with the following params.
     * @param title - the song's title.
     * @param tags - the map of song tags.
     * @param performer - the performer of the song.
     * @param instruments - the vector  of the instruments of the song.
     * @param bpm - the bpm of the song, 0 on default.
     */
	InstrumentalSong(string title, map<string, int> tags, string performer,
					 vector<string> instruments, double bpm = NO_BPM);

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
	 * Calculates the formula of the bpm likelihood.
	 * @param bpm - the bpm of the song.
	 * @param average - statistic data for calculation.
	 * @param standardDeviation - same.
	 * @return the bpm likelihood.
	 */
	inline double bpmLikelihoodFormula(double bpm, double average, double standardDeviation)
	{
	    return exp((MINUS) * pow(bpm - average,
	    		SQUARE) / (MULT_TWO * pow(standardDeviation, SQUARE)));
	}
	/**
	 * deconstructor.
	 */
	~InstrumentalSong();


private:
	string _performer; /**< The performer of the song */
	 vector<string> _instruments; /**< The instruments being used in the song */
	double _bpm; /**< The bpm of the song. If the bpm is not provided, the value of this
	 	 	 	 	 	member will remain 0 */

};



#endif /* INSTRUMENTALSONG_H_ */
