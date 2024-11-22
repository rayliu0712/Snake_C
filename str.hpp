#pragma once
#include <fmt/core.h>
#include <sstream>
#include <string>
#include <vector>
using fmt::format;
using namespace std;
using ValStr = const string &;

namespace Str {

template <typename T>
inline string from(const T &t) { return format("{}", t); }

inline string ascii(int code) { return string{(char)code}; }

string repeat(ValStr pattern, int times) {
	string str;
	str.reserve(pattern.size() * times);
	for (int i = 0; i < times; i++)
		str += pattern;
	return str;
}

} // namespace Str