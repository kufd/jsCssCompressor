#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <vector>
#include <openssl/md5.h>
#include <fstream>
#include <iostream>
#include "zlib.h"
#include <stdio.h>



using namespace std;

class Compressor
{
	public:
    	Compressor(string projectPath, string cachePath);
    	void addCss(string path);
    	void addJs(string path);

    	 string getCss();
    	 string getJs();
	private:
    	string _projectPath;
    	string _cachePath;
    	vector<string> _scripts;
    	vector<string> _styles;

    	string _merge(vector<string> &files);
    	string _md5(const string& text);
    	string _getFileExtension(const string &filename);
    	string _getFileName(const string &path);
    	string _removeDoubleBackSlashes(string str);
};

#endif /* COMPRESSOR_H */

