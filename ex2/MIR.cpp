/*
 * MIR.cpp
 *
 *  Created on: Aug 29, 2015
 *      Author: orib
 */
#include <iostream>
#include <fstream>
#include "Parameters.h"
#include "FileReader.h"
#include "Song.h"
#include "SortHelper.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define LYRICAL "lyrical"
#define INSTRUMENTAL "instrumental"
#define LEGAL_ARGS_NUMBER 4
#define SEPARATOR_LINE_LENGTH 40
enum ArgsIndex
{	SONGS_INDEX = 1,
	PARAMETERS_INDEX = 2,
	QUERIES_INDEX = 3
};


/**
 * This file is the driver of the program.
 * Input: File with songs, file with parameters, and file with queries.
 * Processing: The program will read the files and for each query it will
 * score the songs and print them according to their matching of the query
 * and the different parameters.
 * Output: The relevant songs that matched the criteria sorted by grades for each query.
 */




/**
 * Sorts the songs from the highest grade to lowest grade given by the
 * query and parameters, then print only the songs with positive grade.
 * @param query - the query word to calculate the grades.
 * @param songs - the vector of songs to sort and print.
 * @parameters - the parameters to calculate the grades with.
 */
static void sortSongsAndPrintScores(const string query, vector<Song*> songs,
                                    Parameters& parameters)
{
	// Use the sorter helper object to sort the songs.
	SortHelper helper = SortHelper();
	// Calculate the grades for the songs.
	for (vector<Song*>::iterator it = songs.begin(); it != songs.end(); ++it)
	{
		(*it) -> calculateSongScore(query, parameters);
		helper.addItem((*it) -> getScore());
	}
	// Get the sorted indexes of the songs.
	vector<int> sortedSongsIndexes = helper.getSortedOrderInVector();
	// Print the songs from the highest to lowest grade.
	for (unsigned int i = 0; i < sortedSongsIndexes.size() ; i++)
	{
		 int sortedIndex = sortedSongsIndexes[i];
		 if(songs[sortedIndex] -> getScore() == 0)
		 {
			 break;
		 }
		 cout << *songs[sortedIndex];
	}
}

/**
 * The main method of the program.
 */
int main(int argc, char *argv[])

{
	if (argc != LEGAL_ARGS_NUMBER)
	{
		cerr << "Usage: MIR < songs file name > < parameters file name > < queries file name >"
				<< endl;
		return EXIT_FAILURE;
	}

	string songsFileName = argv[SONGS_INDEX];
	string parametersFileName = argv[PARAMETERS_INDEX];
	string queriesFileName = argv[QUERIES_INDEX];

	ifstream instream(queriesFileName.c_str());
	if (!instream.is_open())
	{
		cerr << "Error! Can't open file: " << queriesFileName << "." << endl;
		return EXIT_FAILURE;
	}
	// Input is legal.
	string query = "";
	Parameters* parameters = nullptr;
	vector<Song*> songs;
	// Attempt to parse the parameters and songs files to get data from them.
	try
	{
		parameters = readParametersFromFile(parametersFileName);
		songs = readSongsFromFile(songsFileName);
	}
	catch(std::exception&)
	{
		if (parameters != nullptr)
		{
			delete parameters;
		}
		return EXIT_FAILURE;
	}
	// Go over the queries and print the sorted songs matching every query.
	while(instream.good())
	{
		getline(instream, query);
		skipEmptyLines(instream, query);
		if (query.empty())
		{
			break;
		}
        for (int i = 0; i < SEPARATOR_LINE_LENGTH; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "Query word: " << query << endl;
        cout << endl;
        sortSongsAndPrintScores(query, songs, *parameters);
	}
	// Cleanup for the objects we created by parsing the files.
	instream.close();
	delete parameters;
	for (unsigned int i = 0; i < songs.size(); i++)
	{
		delete songs[i];
	}
    return EXIT_SUCCESS;

}
