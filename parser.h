#pragma once
#include "token.h"

double expression(Token_stream &ts);
double term(Token_stream &ts);
double primary(Token_stream &ts);
