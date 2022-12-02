#include <iostream>
using std::cout;
using std::cin;
#define newline '\n'

#include <fstream>
using std::ifstream;

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

void Conditioning ( string &input ) {
// data conditioning steps

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
	ifstream inputData( "unprocessed/colorList.txt" );

	do {
		string temp;
		getline( inputData, temp );
		Conditioning( temp );
		if ( !temp.empty() ) {
			strings.push_back( temp );
		}
	} while ( inputData.peek() != EOF );

	// sort( strings.begin(), strings.end() );

	for ( auto& s : strings ) {
		cout << s << newline;
	}

	return 0;
}
