#include "parser.h"

Parser::Parser(const char* filename): m_fileName(filename)
{
}

Parser::Parser(QString filename): m_fileName(filename.toStdString())
{
}
 
Parser::~Parser()
{
}
