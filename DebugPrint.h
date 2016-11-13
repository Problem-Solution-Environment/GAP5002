#pragma once

#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
using namespace std;

static void DebugOut(const char *szOut){
#ifdef _CONSOLEONLY_
	printf(szOut);
	printf("\n");
#else 
	OutputDebugString((LPCWSTR)szOut);
	OutputDebugString((LPCWSTR)"\n");
#endif 
}

static void DebugNum(float f, const char *szOut){	//output msg followed by num
	char s[80], t[50];
#ifdef _CONSOLEONLY_
	printf(szOut);
	printf("\n");
#else 
	strcpy_s(t, szOut);
	strcat_s(t, " %.3f");
	sprintf_s(s, t, f);
	OutputDebugString((LPCWSTR)s);
	OutputDebugString((LPCWSTR)"\n");
#endif 
}

static void DebugNum(int i, const char *szOut){	//output msg followed by num
	char s[80], t[50];
#ifdef _CONSOLEONLY_
	printf(szOut);
	printf("\n");
#else 
	strcpy_s(t, szOut);
	strcat_s(t, " %d");
	sprintf_s(s, t, i);
	OutputDebugString((LPCWSTR)s);
	OutputDebugString((LPCWSTR)"\n");
#endif 
}

template <class T>
static void save1DarrayToCSV(char *fileName, T *arry, int n){
	char fn[256];
	sprintf_s(fn, "%s.csv", fileName);
	ofstream outFile(fn, ios::out);	//Create a CSV file

	outFile << "Num, Value\n";
	for (int i = 0; i < n; i++)
		outFile << i << "," << arry[i] << "\n";

	outFile << "\nMin,=MIN(B2:B" << n+1 << ")\n";	//For Excel, output Summary stats
	outFile << "Max,=MAX(B2:B" << n+1 << ")\n";
	outFile << "Avg,=Average(B2:B" << n+1 << ")\n";

	outFile.close();
}

template <class T>
static void saveVectorToCSV(char *fileName, vector<T> arry){
	char fn[256];
	sprintf_s(fn, "%s.csv", fileName);
	ofstream outFile(fn, ios::out);	//Create a CSV file

	outFile << "Num, Value\n";
	for (int i = 0; i < arry.size(); i++)
		outFile << i << "," << arry[i] << "\n";

	outFile << "\nMin,=MIN(B2:B" << arry.size() + 1 << ")\n";	//For Excel, output Summary stats
	outFile << "Max,=MAX(B2:B" << arry.size() + 1 << ")\n";
	outFile << "Avg,=Average(B2:B" << arry.size() + 1 << ")\n";

	outFile.close();
}