//
// Created by OriB on 01/09/2015.
//


#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include "LyricalSong.h"
#include "InstrumentalSong.h"
#include "FileReader.h"

#define PARSING_SPACER 2
#define START_OF_STR 0

const std::string SEPARATOR = "=";
const std::string END_OF_SONGS = "***";
const std::string TITLE = "title";
const std::string TAGS = "tags";
const std::string LYRICS = "lyrics";
const std::string LYRICS_BY = "lyricsBy";
const std::string INSTRUMENTS = "instruments";
const std::string PERFORMED_BY = "performedBy";
const std::string BPM = "bpm";
const std::string TAG_MATCH_SCORE = "tagMatchScore";
const std::string LYRICS_MATCH_SCORE = "lyricsMatchScore";
const std::string INSTRUMENT_MATCH_SCORE = "instrumentMatchScore";
const std::string BPM_LIKELIHOOD_WEIGHT = "bpmLikelihoodWeight";
const std::string OPEN_BRACKET = "{";
const std::string CLOSE_BRACKET = "}";
const std::string DOUBLE_DOTS = ":";
const std::string COMMA = ",";

/**
* return all the line between {}
*/
static std::string getWordList(const std::string line)
{

    size_t pos1 = line.find(OPEN_BRACKET);
    size_t pos2 = line.find(CLOSE_BRACKET);

    return line.substr(pos1 + 1, pos2-pos1-1);
}


/**
 * Returns the map of tag names and their significance obtained from text.
 * @param tags - the line of tags in the file.
 * @return the map of tags.
 */
static map<string, int> getTagsMap(const std::string tags)
{
    map<string, int> tagsMap;
    std::string tag;
    istringstream converter(tags);
    // Assuming input is legal.
    // Save the tag name.
    while (converter >> tag)
    {
        std::string name = tag;
        // The next word in the line is the significance number.
        int significance;
        converter >> significance;
        tagsMap.insert(std::pair<std::string, int>(name, significance));
    }
    return tagsMap;
}

/**
 * Return a vector of lyrics in case of lyrical song and a vector of instrument
 * in case of instrumental.
 * @param melodyMakers - the line of lyrics or instruments in the file.
 * @return the vector of lyrics/instruments.
 */
static std::vector<string> getMelodyMakers(const std::string melodyMakers)
{
    std::vector<string> melodyMakersVector;
    std::string melodyMaker;
    istringstream converter(melodyMakers);
    while (converter >> melodyMaker)
    {
    	melodyMakersVector.push_back(melodyMaker);
    }
    return melodyMakersVector;
}


/**
 * Parse the given songs file and obtain from it the songs.
 * @param songsFileName - the name of the file.
 * @return a vector of pointers to the songs object being created.
 */

std::vector<Song*> readSongsFromFile(std::string songsFileName)
{
    std::ifstream instream(songsFileName.c_str());
    if (!instream.is_open())
    {
        std::cerr << "Error! Can't open file: " << songsFileName << "." << std::endl;
        throw std::exception();
    }

    std::string line = "";


    std::vector<Song*> songsMap;
    Song* song;
    int lastSong = 0;

    while(instream.good() && !lastSong)
    {
        if (line.compare(SEPARATOR) != 0)
        {
            getline(instream, line);
            skipEmptyLines(instream, line);
            // Expect a line of "="
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
                break;
            }

        }

        getline(instream, line);
        skipEmptyLines(instream, line);
        // Expect a line of "title: ..."
        size_t pos = TITLE.size() + PARSING_SPACER;
        std::string title = line.substr(pos);

        getline(instream, line);
        skipEmptyLines(instream, line);
        // Expect a line of "tags: {...}"
        std::string tags = getWordList(line);

        map<string, int> tagsMap = getTagsMap(tags);

        std::string lyrics = "";
        std::string lyricsBy = "";
        std::string instruments = "";
        std::string performedBy = "";
        std::string bpmStr = "";

        getline(instream, line);
        skipEmptyLines(instream, line);
        // Expect either lyrics or instruments.
        if (line.substr(START_OF_STR, LYRICS.size()).compare(LYRICS) == 0)
        {
            // Then we have a lyric song

            // Lets get the lyrics:
            lyrics = getWordList(line);

            // Lets get the lyricsBy:
            getline(instream, line);
            skipEmptyLines(instream, line);
            pos = LYRICS_BY.size() + PARSING_SPACER;
            lyricsBy = line.substr(pos);
            vector<string> lyricsVec = getMelodyMakers(lyrics);
            song = new LyricalSong(title, tagsMap, lyricsBy, lyricsVec);

        }
        else
        {
            // Then we have an instrumental song

            // Lets get the instruments:
            instruments = getWordList(line);

            vector<string> instrumentsVector = getMelodyMakers(instruments);
            // Lets get the performedBy:
            getline(instream, line);
            skipEmptyLines(instream, line);
            pos = PERFORMED_BY.size() + PARSING_SPACER;
            performedBy = line.substr(pos);

            // Lets see if we have bpm:
            if (!instream.good())
            {
                break;
            }
            getline(instream, line);
            skipEmptyLines(instream, line);
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
            }


            if (line.substr(0, BPM.size()).compare(BPM) == 0)
            {

                pos = BPM.size() + PARSING_SPACER;
                bpmStr = line.substr(pos);
                istringstream converter(bpmStr);
                double bpm;
                converter >> bpm;
                song = new InstrumentalSong(title, tagsMap, performedBy,
                                            instrumentsVector, bpm);
            }
            else
            {
                assert ( (line.compare(SEPARATOR) == 0) || (line.compare(END_OF_SONGS) == 0));
                song = new InstrumentalSong(title, tagsMap, performedBy,
                                            instrumentsVector);
            }
        }
        songsMap.push_back(song);
    }

    instream.close();

    // return something
    return songsMap;
}

/**
 * Read the search words from the Parameters file.
 * @param instream - the stream object to read the file.
 * @param line - current line we read.
 */
static void readSearchWords(std::ifstream& instream, std::string& line,
							SearchWords& searchWords)
{
	while(instream.good())
	{
		getline(instream, line);
		skipEmptyLines(instream, line);
		size_t pos = line.find(DOUBLE_DOTS);
		std::string word = line.substr(START_OF_STR, pos);
		istringstream iss(line);
		std::string number;
		double average;
		double standardDeviation;
		line = line.substr(pos + 1);
		istringstream averageSplitter(line);
		averageSplitter >> average;
		pos = line.find(COMMA);
		line = line.substr(pos + 1);
		istringstream deviationSplitter(line);
		deviationSplitter >> standardDeviation;
		std::pair<double, double> pair(average, standardDeviation);
		searchWords.insert(std::pair<std::string, std::pair<double, double>>(word, pair));
	}
}

/**
 * Read the parameters file and create object of parameters representing it.
 * @param parametersFileName - the name of the parameters file.
 * @return pointer to the parameters object that was created.
 */
Parameters* readParametersFromFile(std::string parametersFileName)
{

    std::ifstream instream(parametersFileName.c_str());
    if (!instream.is_open())
    {
        std::cerr << "Error! Can't open file: " << parametersFileName << "." << std::endl;
        throw std::exception();
    }

    std::string line = "";

    Parameters* parameters;
    // Read the constant word scores from file.
    getline(instream, line);
    skipEmptyLines(instream, line);
    size_t pos = TAG_MATCH_SCORE.size() + PARSING_SPACER;
    int tagMatchScore = std::stoi(line.substr(pos));
    getline(instream, line);
    skipEmptyLines(instream, line);
    pos = LYRICS_MATCH_SCORE.size() + PARSING_SPACER;
    int lyricsMatchScore = std::stoi(line.substr(pos));
    getline(instream, line);
    skipEmptyLines(instream, line);
    pos = INSTRUMENT_MATCH_SCORE.size() + PARSING_SPACER;
    int instrumentMatchScore = std::stoi(line.substr(pos));
    getline(instream, line);
    skipEmptyLines(instream, line);
    pos = BPM_LIKELIHOOD_WEIGHT.size() + PARSING_SPACER;
    int bpmLikelihoodWeight = std::stoi(line.substr(pos));
    SearchWords searchWords;

    // Get search words from file.
    readSearchWords(instream, line, searchWords);

    parameters = new Parameters(tagMatchScore, lyricsMatchScore,
                                instrumentMatchScore, bpmLikelihoodWeight, searchWords);

    instream.close();

    return parameters;
}
