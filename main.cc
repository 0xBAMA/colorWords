#include <iostream>
using std::cout;
using std::cin;
#define newline '\n'

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
using std::find_if;
using std::sort;
using std::replace;
using std::transform;

#include <functional>
using std::bind1st;
using std::not_equal_to;

#include <regex>
using std::regex;
using std::regex_replace;

#include <iterator>
using std::back_inserter;

#include <set>
using std::set;

// data conditioning steps
void Conditioning ( string &input ) {

	// trim trailing spaces
	input.erase( find_if( input.rbegin(), input.rend(), bind1st( not_equal_to<char>(), ' ' ) ).base(), input.end() );

	// split words by capitals - kinda based on https://stackoverflow.com/questions/18379254/regex-to-split-camel-case
	string temp = input;
	input.clear();
	regex eval ( "([a-z])([A-Z])" );
	regex_replace( back_inserter( input ), temp.begin(), temp.end(), eval, "$1 $2" );

	// spaces to dashes
	replace( input.begin(), input.end(), ' ', '-' );

	// all alpha chars to lowercase - how to handle accented chars? tbd
	transform( input.begin(), input.end(), input.begin(), []( unsigned char c ){ return std::tolower( c ); } );
}

int main ( int argc, char const *argv[] ) {
	vector<string> strings;
	ifstream inputData( "unprocessed/sorted.txt" );

	// parse input + process
	do {
		string temp;
		getline( inputData, temp );
		Conditioning( temp );
		if ( !temp.empty() ) {
			strings.push_back( temp );
		}
	} while ( inputData.peek() != EOF );
	inputData.close();

	// duplicate removal
	set<string> duplicatesRemoved;
	for ( auto& s : strings ) { duplicatesRemoved.insert( s ); }
	strings.clear();
	for ( auto& s : duplicatesRemoved ) { strings.push_back( s ); }

	// prep for output ( alphabetize )
	sort( strings.begin(), strings.end() );

	// debug output
	for ( auto& s : strings ) { cout << s << newline; }

	// report
	const size_t numInitial = strings.size();
	const size_t numFinal = duplicatesRemoved.size();
	cout << newline << "Processing started with " << numInitial << " entries and ended up with " << numFinal << " entries"<< newline;

	return 0;
}
