// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>

using namespace std;
using namespace System;

void MarshalString(String ^ s, string& os);
void MarshalString(String ^ s, wstring& os);
