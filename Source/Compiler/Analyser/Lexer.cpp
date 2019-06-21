#include "Lexer.h"

#include "Parser.h"

#include <iostream>

/*
Actually parses the words in the Parsed class then start the whole thing.
Also I don't want to talk about the code here. I have a problem with knowing
wtf to do, in theses organised sections. This is like bad but ok code, because
you wouldn't want to do it in the same functions as the syntax parsing.
*/
void Parser::Tokenize(Environement* env)
{
	// Now, here you separate unclassified strings into tokens that will then be analyzed
	// later, and then made into assembly.

	long Pos = -1;
	bool IsString = false; // If it's a string then it wont parse the words below and when the string is closed will be pushed as arguments

	for (auto& txt : env->Processed)
	{
		bool identified = false;
		Pos++;

		Token t; // yep it's ya boi, one letter variables here

		if (txt.compare("int") == 0 || txt.compare("char") == 0 || txt.compare("float") == 0 || txt.compare("string") == 0)
		{
			t.Identifier = OBJECT_TYPE_TOKEN;
			t.Lexeme = txt;
			identified = true;
			env->Cluster.push_back(t);
		}
		else if (txt.compare("=") == 0)
		{
			t.Identifier = ASSIGNEMENT_OPERATOR_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (txt.compare("entry") == 0)
		{
			t.Identifier = KEYWORD_ENTRY_TOKEN;
			t.Lexeme = txt;
			identified = true;
			env->Cluster.push_back(t);
		}
		else if (txt.compare(":") == 0)
		{
			// Variable
			t.Identifier = VAR_CONFIRM_TOKEN;
			t.Lexeme = ":";
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (txt.compare("+") == 0 || txt.compare("-") == 0 || txt.compare("/") == 0 || txt.compare("*") == 0)
		{
			t.Identifier = ARITHMETIC_OPERATOR_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (txt.compare("<") == 0 || txt.compare(">") == 0 || txt.compare("==") == 0)
		{
			t.Identifier = COMPARAISON_OPERATOR_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (txt.compare("{") == 0 || txt.compare("}") == 0)
		{
			t.Identifier = GATE_SCOPE_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (txt.compare("(") == 0 || txt.compare(")") == 0)
		{
			t.Identifier = GATE_ARG_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
			identified = true;
		}
		else if (!identified)
		{
			t.Identifier = UNPARSED_TOKEN;
			t.Lexeme = txt;
			env->Cluster.push_back(t);
		}
	}
}