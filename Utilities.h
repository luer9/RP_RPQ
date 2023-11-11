/*
Copyright 2014 Sairam Gurajada

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <string>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <deque>
//#include<windows.h>

#ifndef UTILITIES_H
#define UTILITIES_H

using namespace std;

typedef std::vector<std::string> VECTOR_STRING;
typedef std::vector<uint32_t> VECTOR_INT_32;

// contains static utility functions for hashing and sorting as well as basic data type definitions
class Utilities {

public:

	// a 64-bit hash key
	typedef unsigned long long hash64_t; // enforce 64 bits

	// a 64-bit value
	typedef unsigned long long value64_t; // enforce 64 bits

	class StringHash64 {
	public:
		value64_t operator()(const string& s) const {
			return hash64(s, 0);
		}
	};


	// hash arbitrary data into a 64-bit value
	static hash64_t
		hash64(const void* buffer, unsigned size, hash64_t init = 0);

	// hash a string into a 64-bit value
	static hash64_t hash64(const string& text, hash64_t init = 0);



};

#endif

