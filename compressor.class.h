#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <vector>
#include <openssl/md5.h>
#include <fstream>



using namespace std;

class Compressor
{
	public:
    	Compressor();
    	void addCss(string path);
    	void addJs(string path);

    	 string getCss();
    	 string getJs();
	private:
    	string _cacheDir;
    	string _relativePath;
    	vector<string> _scripts;
    	vector<string> _styles;

    	string _merge(vector<string> &files);
    	void _compress();
    	string _md5(const string& text);

};

#endif /* COMPRESSOR_H */

