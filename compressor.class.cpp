#include "compressor.class.h"

Compressor::Compressor()
{
	_relativePath = "/tmp";
	_cacheDir = "/tmp";
}

void Compressor::addCss(string path)
{
	_styles.push_back(path);
}

void Compressor::addJs(string path)
{
	_scripts.push_back(path);
}

string Compressor::_merge(vector<string> &files)
{
	string mergedFileName = "";

	vector<string>::iterator it=files.begin(), ite=files.end();
	for( ; it!=ite ; it++)
	{
		mergedFileName += "_"+*it;
	}

	mergedFileName = _md5(mergedFileName);

	return mergedFileName;
}

void Compressor::_compress()
{

}

string Compressor::getCss()
{
	string file = _merge(_styles);

	return file;
}

string Compressor::getJs()
{
	string file = _merge(_scripts);

	return file;
}

string Compressor::_md5(const string& text)
{
	unsigned char hash[16];
	char hashHex[32];
	MD5((unsigned char*)text.c_str(), text.length(), hash);
	sprintf(hashHex, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x",
			hash[0], hash[1], hash[2], hash[3], hash[4], hash[5], hash[6], hash[7],
			hash[8], hash[9], hash[10], hash[11], hash[12], hash[13], hash[14], hash[15]);

	return hashHex;
}
