//
// Created by OriB on 01/09/2015.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <vector>
#include "Song.h"
#include "Parameters.h"

/**
 * Parse the given songs file and obtain from it the songs.
 * @param songsFileName - the name of the file.
 * @return a vector of pointers to the songs object being created.
 */
std::vector<Song*> readSongsFromFile(std::string songsFileName);

/**
 * Read the parameters file and create object of parameters representing it.
 * @param parametersFileName - the name of the parameters file.
 * @return pointer to the parameters object that was created.
 */
Parameters* readParametersFromFile(std::string parametersFileName);

/**
 * Handles empty lines in file.
 * @param instream the stream for the file.
 * @param line - the current line of the file.
 */
inline void skipEmptyLines(std::ifstream& instream, std::string& line)
{
    while (instream.good() && line.empty())
    {
        getline(instream, line);
    }
}

#endif //FILEREADER_H
