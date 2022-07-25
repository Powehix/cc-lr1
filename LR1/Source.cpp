#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isID(const string &str);
bool isNumericConstant(const string &str);
bool isStringConstant(const string &str);
bool isKeyword(const string &str);
bool isDelimeter(const string &str);
bool isSpace(const string &str);
void role(const string &token);
void print();
void scan(const string &file);

const vector<string> keywords{ "procedure", "var", "byte", "char", "array", "of", "longint", "string", "begin", "if", "and", "then", "else", "end" };
const vector<string> delimeters{ ".", ";", ":", "[", "]", ",", "(", ")", "=", ":=", "'", "-", "..", "" };
const vector<string> numericConstants{ "0", "1", "15", "8" };
const vector<string> stringConstants{ "'%d:%d'", "':'" };
vector<string> findedID;
vector<string> findedKeywords;
vector<string> findedDelimeters;
vector<string> findedNumericConstants;
vector<string> findedStringConstants;

bool ex = false;

void main()
{
	cout << "Scan:\n";
	scan("code.txt");
	system("PAUSE");
}

bool isID(const string &str)
{
	try
	{
		for (int i = 0; i < str.size(); i++)
			if (!(isalpha(str[i])))      //������������� ����� ��������� ������ �����
				throw (str);
	}

	catch (const string)
	{
		if (!ex)
		{
			ex = true;
			cout << "\nError! An identifier can only contain a letters!" << endl;
		}
		return false;
	}

	return true;
}

bool isNumericConstant(const string &str)
{
	bool flag = false;   //���������� ��� ������������ ����� �����������

	for (int i = 0; i < str.size(); i++) 
	{
		if (!(isdigit(str[i])))   //����� ������ ��������� ������ �����
		{
			flag = true;
			return false;
		}
	}

	if (!flag)
		for (auto numericConstant : numericConstants)
			if (numericConstant == str)
			{
				flag = true;
				return true;
			}
	try
	{
		if (!flag)
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError! Number is not a registered numeric constant!" << endl;
		return false;
	}
}

bool isStringConstant(const string &str)
{
	bool flag = false;

	for (auto stringConstant : stringConstants)
		if (stringConstant == str)
		{
			flag = true;
			return true;
		}

	try 
	{
		if ((!flag) && (str[0] == char(39) && (str[str.size() - 1]) == char(39)))   //char(39) - ���� ��������� (') �� ������� ASCII
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError! String is not a registered string constant!" << endl;
		return false;
	}

	return false;
}

bool isKeyword(const string &str)
{
	string buffer = str;

	for (int i = 0; i < str.size(); i++)
		buffer[i] = tolower(str[i]);    //����� ����� ���� ������ ��������

	for (auto keyword : keywords)
		if (keyword == buffer)
			return true;

	return false;
}

bool isDelimeter(const string &str)
{
	bool flag = false;

	for (int i = 0; i < str.size(); i++)
	{
		if (!(ispunct(str[i])))   //����������� ����� ��������� ������ ����� ����������
		{
			flag = true;
			return false;
		}
	}

	if ((!flag) && (str.size() != 1 && str[0] == char(39) && (str[str.size() - 1]) == char(39)))   //��������� ���������, ���������� ������ �����������, �� ������ ��������������
	{
		flag = true;
		return false;
	}

	if (!flag)
		for (auto delimeter : delimeters)
			if (delimeter == str)
			{
				flag = true;
				return true;
			}

	try
	{
		if (!flag)
			throw (str);
	}

	catch (const string)
	{
		ex = true;
		cout << "\nError! Delimeter is not a registered delimeter!" << endl;
		return false;
	}
}

bool isSpace(const string &str)
{
	if (str == " " || str == "\n")
		return true;

	return false;
}

void role(const string& str)
{
	bool flag = false;   //���������� ��� ���������� ���������� ��� �������� ��������
	string bufferStr = str;   //���������� ��� �������� �������� ���������� ������
	string bufferID;   //���������� ��� �������� �������� ���������� ���������������

	if (isKeyword(str))
	{
		for (auto keyword : findedKeywords)
			if (keyword == str) 
				flag = true;
		if (!flag)
				findedKeywords.push_back(str);   //���� ���������� �� ���� �������, ������� ������������ � ������ � ���� ����������
		flag = false;
	}
	else if (isDelimeter(str))
	{
		for (auto delimeter : findedDelimeters)
			if (delimeter == str)
				flag = true;
		if (!flag)
			findedDelimeters.push_back(str);
		flag = false;
	}
	else if (isNumericConstant(str))
	{
		for (auto numericConstant : findedNumericConstants)
			if (numericConstant == str)
				flag = true;
		if (!flag)
			findedNumericConstants.push_back(str);
		flag = false;
	}
	else if (isStringConstant(str))
	{
		for (auto stringConstant : findedStringConstants)
			if (stringConstant == str)
				flag = true;
		if (!flag)
			findedStringConstants.push_back(str);
		flag = false;
	}
	else if (isID(str))
	{
		for (int i = 0; i < str.size(); i++)
			bufferStr[i] = tolower(str[i]);

		for (auto ID : findedID)
		{
			bufferID = ID;
			for (int i = 0; i < ID.size(); i++)
				bufferID[i] = tolower(ID[i]);
			if (bufferID == bufferStr)
				flag = true;
		}

		if (!flag)
			findedID.push_back(str);
		flag = false;
	}
	else
	{
		cout << "Invalid token: " << str << endl;
		ex = false;
	}
}

void print()
{
	//����� ������ ������������ ������
	cout << "\n==============\nIDENTIFIERS\n==============\n\n";
	for (auto ID : findedID)
	{
		cout << ID << endl;
	}

	cout << "\n==============\nKEYWORDS\n==============\n\n";
	for (auto keyword : findedKeywords)
	{
		cout << keyword << endl;
	}

	cout << "\n==============\nDELIMETERS\n==============\n\n";
	for (auto delimeter : findedDelimeters)
	{
		cout << delimeter << endl;
	}

	cout << "\n==============\nNUMERIC CONSTANTS\n==============\n\n";
	for (auto numericConstant : findedNumericConstants)
	{
		cout << numericConstant << endl;
	}

	cout << "\n==============\nSTRING CONSTANTS\n==============\n\n";
	for (auto stringConstant : findedStringConstants)
	{
		cout << stringConstant << endl;
	}
}

void scan(const string &fileName)
{
	char ch;            //���������� ��� �������� ��������
	string buffer;       //���������� ��� �������� ������������������� ��������
	string twoposDelim;   //���������� ��� �������� ��������������� ������������
	string strConstant;   //���������� ��� �������� ��������� ��������
	bool flag = false;   //���������� ��� ������������ ������ � ����� ������ ��������� ��������

	fstream file(fileName, fstream::in);
	if (!file.is_open())
	{
		cout << "Error while opening the file\n";
		exit(0);
	}
	else
	{
		while (file >> noskipws >> ch)   //������ �������� �� ����� � ������ ��������� ���������� ��������
		{
			if (isSpace(string(1, ch)))  //1 - ������ ������, ch - ������ ��� ���������� �������. � ����� ����������� �� ������ �������
			{
				if (!buffer.empty())   //���� ����� �� ����, ��������� ���������� ������ �� ���������� � ������������� ���������, ����� ���� ����� ����������
				{
					role(buffer);   //����������� ���� �������
					buffer = "";   //��������� ������
				}
				continue;
			}

			if (flag)   //���� �������� flag ����� true, ���� ������ ��������� ��������� � ���������� strConstant
			{
				if (string(1, ch) == "'")   //���� � ���� ������ ��������� ��������� ����������� ��������, ������ ������������� � ���������� ���������� strConstant ����������� �� ���������� � ���������
				{
					strConstant += string(1, ch);
					role(strConstant);
					flag = false;
					buffer = "";
				}
				strConstant += string(1, ch);
				continue;
			}

			if (!flag && string(1, ch) == "'")   //���� �������� ��������, ���������� ������ ��������� ���������
			{
				strConstant = "";
				strConstant += string(1, ch);
				flag = true;
			}

			if (isDelimeter(string(1, ch)) || isDelimeter(buffer))   //���� �������� ������ ��� ���������� ������ �������� ������������
			{
				if (isDelimeter(string(1, ch)) && !isDelimeter(buffer))   //���� �������� ������ �������� ������������, � ���������� ������ - ���, �� ����� ����������� �� ���������� � ��������� � ����������
				{
					if (!buffer.empty())
					{
						role(buffer);
						buffer = "";
					}
				}
				else if (!isDelimeter(string(1, ch)) && isDelimeter(buffer))
				{
					role(buffer);
					buffer = "";
				}
				else if ((string(1, ch) == "." || string(1, ch) == "=") && (buffer == "." || buffer == ":"))   //�������� ��������������� ������������
				{
					twoposDelim = buffer + string(1, ch);
					role(twoposDelim);
					twoposDelim = "";
				}
				else if (string(1, ch) == ";")   //�������� ��������� ������
				{
					role(buffer);
					buffer = "";
					role(string(1, ch));
				}
				else
				{
					role(buffer);
					buffer = "";
				}
			}
			buffer += ch;   //������������ ������, ������������ ����������
		}
		print();   //����� ������ ������������ ������
	}
	file.close();
}