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
///   row:int
///   column:int
///   currentState:state
///   currentChar:char
/// ---
///   validateChar(char):status
/// }

/// class Buffer {
///
/// ---
///   getchar():char
///   ungetchar()
/// }

/// class Scanner {
///
/// ---
///   nextToken():Token
/// }

/// class SymTable {
/// }

/// class Token {
/// }

/// class Information {
/// }

/// Scanner -l-> FSM
/// Scanner --> Buffer
/// Scanner -u-> SymTable
/// Scanner -r-> Token
///
/// SymTable -r-> Information
/// Token --> Information

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


