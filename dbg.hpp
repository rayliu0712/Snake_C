#pragma once
#include "str.hpp"
#include <fstream>

class Dbg {
  private:
	static ofstream file;

  public:
	static Dbg _dbg;
	static void *_ln;

	Dbg() {
		file.open("log.txt", ofstream::trunc);
		file.close();
		file.open("log.txt", ofstream::app);
	}
	~Dbg() { file.close(); }

	template <typename T>
	friend Dbg &operator<<(Dbg &dbg, const vector<T> &v) {
		for (const auto &e : v)
			file << " ";
		file << "\n";
		return dbg;
	}

	template <typename T>
	friend Dbg &operator<<(Dbg &dbg, const T &t) {
		file << t << " ";
		return dbg;
	}

	friend Dbg &operator<<(Dbg &dbg, void *ptr) {
		file << "\n";
		return dbg;
	}
};

ofstream Dbg::file;
Dbg Dbg::_dbg;
void *Dbg::_ln = (void *)0;
#define dbg (Dbg::_dbg)
#define ln (Dbg::_ln)