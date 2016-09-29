/*
 * Parameters.cpp
 *
 *  Created on: Aug 31, 2015
 *      Author: orib
 */
#include "Parameters.h"

// Parameters.cpp

	/**
	 * A constructor.
	 * Constructs a parameters object with the following params all from the parameters file.
	 * @param tagMatchScore
	 * @param lyricsMatchScore
	 * @param instrumentMatchScore
	 * @param bpmLikelihoodWeight
	 * @param searchWords - map of the name of the word and its average and deviation.
	 */
	Parameters::Parameters(int tagMatchScore, int lyricsMatchScore, int instrumentMatchScore,
						   int bpmLikelihoodWeight, SearchWords searchWords) :
						   _tagMatchScore(tagMatchScore),
						   _lyricsMatchScore(lyricsMatchScore),
						   _instrumentMatchScore(instrumentMatchScore),
						   _bpmLikelihoodWeight(bpmLikelihoodWeight),
						   _searchWords(searchWords)

	{
	}

	/**
	 * @return the tag match score.
	 */
	int Parameters::getTagMatchScore() const
	{
		return _tagMatchScore;
	}
	/**
	 * @return the lyrics match score.
	 */
	int Parameters::getLyricsMatchScore() const
	{
		return _lyricsMatchScore;
	}
	/**
	 * @return the instruments match score.
	 */
	int Parameters::getInstrumentMatchScore() const
	{
		return _instrumentMatchScore;
	}
	/**
	 * @return the bpm likelihood weight.
	 */
	int Parameters::getBpmLikelihoodWeight() const
	{
		return _bpmLikelihoodWeight;
	}
	/**
	 * @return the search words.
	 */
	SearchWords Parameters::getSearchWords() const
	{
		return _searchWords;
	}







