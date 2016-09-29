/*
 * Parameters.h
 *
 *  Created on: Aug 31, 2015
 *      Author: orib
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <map>



// The search words from the parameters file.
typedef std::map<std::string, std::pair<double, double> > SearchWords;

/**
 * This class represents objects of parameter files with their data.
 */
class Parameters
{
public:
    /**
	 * A constructor.
	 * Constructs a parameters object with the following params all from the parameters file.
	 * @param tagMatchScore
	 * @param lyricsMatchScore
	 * @param instrumentMatchScore
	 * @param bpmLikelihoodWeight
	 * @param searchWords - map of the name of the word and its average and deviation.
	 */
	Parameters(int tagMatchScore, int lyricsMatchScore, int instrumentMatchScore,
			   int bpmLikelihoodWeight, SearchWords searchWords);
	/**
	 * @return the tag match score.
	 */
	int getTagMatchScore() const;
	/**
	 * @return the lyrics match score.
	 */
	int getLyricsMatchScore() const;
	/**
	 * @return the instruments match score.
	 */
	int getInstrumentMatchScore() const;
	/**
	 * @return the bpm likelihood weight.
	 */
	int getBpmLikelihoodWeight() const;
	/**
	 * @return the search words.
	 */
	SearchWords getSearchWords() const;

private:
	int _tagMatchScore;
	int _lyricsMatchScore;
	int _instrumentMatchScore;
	int _bpmLikelihoodWeight;
	SearchWords _searchWords;
};



#endif /* PARAMETERS_H_ */
