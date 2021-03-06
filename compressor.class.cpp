#include "compressor.class.h"

/**
 * projectPath - absolute path to project root
 * cachePath - path(from project root) to directory where will be saved cached files
 */
Compressor::Compressor(string projectPath, string cachePath)
{
	_projectPath = projectPath;
	_cachePath = cachePath;
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
	if(!files.size())
	{
		return "";
	}

	string mergedFileName = "";
	string mergedFileRelativePath = "";

	vector<string>::iterator it=files.begin(), ite=files.end();
	for( ; it!=ite ; it++)
	{
		mergedFileName += "_"+*it;
	}

	mergedFileRelativePath = _removeDoubleBackSlashes(_cachePath + "/" + _md5(mergedFileName) + "." + _getFileExtension(*files.begin()));
	mergedFileName = _removeDoubleBackSlashes(_projectPath + "/" + mergedFileRelativePath);

	ifstream mergedFile(mergedFileName.c_str());

	if(!mergedFile)
	{
		//merge and compress files into tmp file
		int bufSize = 10240; //10 kb
		char buffer[bufSize];
		string tmpArchFileName = mergedFileName + "." + _getFileName(tmpnam(NULL)) + ".gz";
		gzFile tmpArchFile = (gzFile)gzopen(tmpArchFileName.c_str(), "wb9");

		if(tmpArchFile)
		{
			vector<string>::iterator it=files.begin(), ite=files.end();
			for( ; it!=ite ; it++)
			{
				string filePath = _removeDoubleBackSlashes(_projectPath + "/" + *it);
				ifstream file(filePath.c_str(), ios::in | ios::binary);

				while(!file.eof())
				{
					file.read((char *)&buffer, bufSize);
					int count=file.gcount();
					gzwrite(tmpArchFile, (char *)&buffer, count);
				}

				file.close();

				gzwrite(tmpArchFile, "\n", 1);
			}
		}

		gzclose(tmpArchFile);

		//move compressed tmp file
		rename(tmpArchFileName.c_str(), mergedFileName.c_str());
	}

	mergedFile.close();

	return mergedFileRelativePath;
}

/**
 * Method returns path(from project root) to compressed file with styles
 * or empty string if no files were added
 */
string Compressor::getCss()
{
	string file = _merge(_styles);

	return file;
}

/**
 * Method returns path(from project root) to compressed file with scripts
 * or empty string if no files were added
 */
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

string Compressor::_getFileExtension(const string &filename)
{
	int loc1=filename.rfind(".");
	if(loc1!= std::string::npos)
	{
		return filename.substr(loc1+1);
	}
	return "";
}

string Compressor::_getFileName(const string &path)
{
	int loc1=path.rfind("/");
	if(loc1!= std::string::npos)
	{
		return path.substr(loc1+1);
	}
	return path;
}

string Compressor::_removeDoubleBackSlashes(string str)
{
	int pos1;
	while((pos1 = str.find("//")) != std::string::npos)
	{
		str.replace(pos1, 2, "/");
	}
	return str;
}

