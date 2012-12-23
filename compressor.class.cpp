#include "compressor.class.h"

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

	mergedFileRelativePath = _cachePath + _md5(mergedFileName) + "." + _getFileExtension(*files.begin());
	mergedFileName = _projectPath + mergedFileRelativePath;

	ifstream mergedFile(mergedFileName.c_str());

	if(!mergedFile)
	{
		//merge and compress files into tmp file
		int bufSize = 10240; //10 kb
		char buffer[bufSize];
		string tmpArchFileName = mergedFileName + "." + _getFileName(tmpnam(NULL)) + ".gz";
		//gzFile *tmpArchFile = (gzFile *)gzopen(tmpArchFileName.c_str(), "wb0T");
		ofstream tmpArchFile(tmpArchFileName.c_str());

		if(tmpArchFile)
		{
			vector<string>::iterator it=files.begin(), ite=files.end();
			for( ; it!=ite ; it++)
			{
				string filePath = _projectPath + *it;
				ifstream file(filePath.c_str(), ios::in | ios::binary);

				while(!file.eof())
				{
					file.read((char *)&buffer, bufSize);
					int count=file.gcount();
					//gzwrite(tmpArchFile, (char *)&buffer, count);
					tmpArchFile.write((char *)&buffer, count);
				}

				file.close();

				//gzwrite(tmpArchFile, "\n", 1);
				tmpArchFile.write("\n", 1);
			}
		}

		//gzclose(tmpArchFile);
		tmpArchFile.close();

		//move compressed file
		rename(tmpArchFileName.c_str(), mergedFileName.c_str());
	}

	mergedFile.close();

	return mergedFileRelativePath;
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
