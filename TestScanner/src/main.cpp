/*
 * main.cpp
 *
 *  Created on: 19.11.2013
 *      Author: typical
 */

#include <Scanner.hpp>
#include <stdio.h>

#include <vector>

int main (int argc, char** argv) {




	Scanner scanner;
	ScannerError::type_t result;

	printf("Input: %s\n", argv[1]);

	result = scanner.init(argv[1]);
	if(result != ScannerError::OK) {
		printf("Scanner init error <%d>!\n", result);
	}

	std::vector<Token*> tokenVec;


	do {
		Token* currentToken = new Token();
		result = scanner.getToken(*currentToken);
		tokenVec.push_back(currentToken);


	} while(result == ScannerError::OK);

	for(size_t i = 0; i < tokenVec.size(); i++) {
		printf("Token<%lu>\n", i);
		delete tokenVec[i];
	}

	printf("\n\tENDE!!");

	return 0;
}
