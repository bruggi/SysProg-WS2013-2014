/*
 * PlantUML.cpp
 *
 *  Created on: 22.10.2013
 *      Author: typical
 *
 *   This file is only for PLANTUML code!
 */


/*	class diagram	*/
///@startuml

/// class FSM {
///		currentState: type_t
///		row: int
///		column: int
///   	currentChar: char
///		---
///		validateChar(char): status_struct
/// }

/// class StateMatrix {
///		MAX_STATES: const int
///		MAX_CHARACTER: const int
///		transitions[row][column]: states
/// }

/// class Buffer {
///		bufferA: void*
///		bufferB: void*
///		currentPos: int
///		wasFilled: bool
///		countChars: int
///		BUFSIZE: const int
///		---
///		getChar(char&): errorType
///		ungetChar(int)
///  	initBuffer(char*): errorType
/// }

/// class Scanner {
///		characterBuffer: char*
///		bufIndexer: int
///		isOverflow: bool
///		BUFSIZE: const int
///		---
///		init(char*, Symtable): errorType
///		getToken(Token&): errorType
/// }

/// class Token {
///		row: int
///		column: int
///		type: tokentype
///		value: long
///		---
///		generateINT(long, int, int): bool
///		generateID(Pair*, int, int): bool
///		generateSIGN(int, int, tokentype): bool
///		generateERROR(Pair*, int, int): bool
/// }

/// class Hashtable {
///		<generic>
/// }

/// class Symtable {
///
///		insert(char*, tokentype): Pair
/// }

/// class Pair {
/// 	value: tokentype
///		key: char*
/// }

/// FSM --> StateMatrix
/// Scanner --> FSM
/// Scanner --> Buffer
/// Scanner --> Symtable
/// Scanner --> Token
/// Symtable --> Hashtable
/// Hashtable -l-> Pair

///@enduml


/*	activity diagram	*/
/// @startuml
/// --> Scanner : nextToken()
/// activate Scanner
/// Scanner --> Buffer : getchar()
/// activate Buffer
/// loop until identified
///    Scanner --> FSM : validateChar()
///    activate FSM
/// end
/// deactivate FSM
/// Scanner --> Symtable : saveToken()
/// activate Symtable
/// deactivate Symtable
/// deactivate Buffer
/// deactivate Scanner

/// @enduml


