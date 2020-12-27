#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#undef max
#undef min

using ::std::cout;
using ::std::endl;
using ::std::cin;

#define COLOR_BLACK 0
#define COLOR_GREEN 2
#define COLOR_RED 4
#define COLOR_WHITE 7
#define COLOR_YELLO 6

#define MAKE_BACKGROUND_COLOR(color) ((color) << (sizeof(WORD) >> 1))
#define MAKE_TEXT_COLOR(color) (color)
#define MAKE_TEXT_ATTRIBUTE_COLOR(bkcolor, textcolor) (MAKE_BACKGROUND_COLOR(bkcolor) | MAKE_TEXT_COLOR(textcolor))

#define TEXT_GREEN() (::SetConsoleTextAttribute(hConsoleOutput, MAKE_TEXT_ATTRIBUTE_COLOR(COLOR_BLACK, COLOR_GREEN)))
#define TEXT_WHITE() (::SetConsoleTextAttribute(hConsoleOutput, MAKE_TEXT_ATTRIBUTE_COLOR(COLOR_BLACK, COLOR_WHITE)))
#define TEXT_RED() (::SetConsoleTextAttribute(hConsoleOutput, MAKE_TEXT_ATTRIBUTE_COLOR(COLOR_BLACK, COLOR_RED)))
#define TEXT_YELLO() (::SetConsoleTextAttribute(hConsoleOutput, MAKE_TEXT_ATTRIBUTE_COLOR(COLOR_BLACK, COLOR_YELLO)))

inline char GetRandChar()
{
	return rand() % 26 + 'a';
}

int main()
{
	::system("color 07");
	::srand((unsigned)::time(nullptr));
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	

	int initHeight = 20;		//must be even
	int heightIncrement = 8;	//must be even

	int numOfTr = 3;

	int period = 8;

	cout << "使用默认设置？(Y/n)" << endl;
	char input;
	do
	{
	reInput:
		cin >> input;
		switch (input)
		{
		case 'Y': case 'y': break;
		case 'N': case 'n': 
		{
			cout << "树的初始高度？（推荐为20，至少为2）" << endl;
			while (!(cin >> initHeight) || initHeight <= 1)
			{
				cout << "输入非法，请重新输入！" << endl;
				cin.clear();
				cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');
			}
			initHeight = initHeight / 2 * 2;
			cin.clear();
			cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');

			cout << "树的层数？（推荐为3）" << endl;
			while (!(cin >> numOfTr) || numOfTr <= 0)
			{
				cout << "输入非法，请重新输入！" << endl;
				cin.clear();
				cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');
			}
			cin.clear();
			cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');

			cout << "颜色变化周期？（推荐为8，至少为2）" << endl;
			while (!(cin >> period) || period <= 1)
			{
				cout << "输入非法，请重新输入！" << endl;
				cin.clear();
				cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');
			}
			cin.clear();
			cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');

			cout << "高度增幅？（推荐为8，至少为2）" << endl;
			while (!(cin >> heightIncrement) || heightIncrement <= 1)
			{
				cout << "输入非法，请重新输入！" << endl;
				cin.clear();
				cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');
			}
			heightIncrement = heightIncrement / 2 * 2;
			cin.clear();
			cin.ignore(::std::numeric_limits<::std::streamsize>::max(), '\n');
			break;
		}
		default: cout << "输入非法，请重新输入！" << endl; goto reInput;
		}
	} while (false);



	const int maxLen = 2 * (initHeight + (numOfTr - 1) * heightIncrement) + 2;
	const int midPos = maxLen / 2;

	cout << endl;

	TEXT_GREEN();

	int row = 0;

	for (int i = 0; i < numOfTr; ++i)
	{
		int height = initHeight + i * heightIncrement;
		//int topRow = i ? (i + 1) * initHeight / 2 + i * (i - 1) * heightIncrement / 4 : 0;
		//int mid = topRow + height / 2;
		//int end = topRow + height;
		for (int j = 0; j < height; ++j)
		{
			if (j < height / 2 && i) continue;

		#ifdef _DEBUG

			cout << ::std::setw(2) << i << ": " << ::std::setw(3) << row;

		#endif	//_DEBUG

			int num = 2 * j + 1;
			int colorItr = row % period;
			for (int k = 0; k < (midPos - 1 - num / 2); ++k)
			{
				cout.put(' ');
				++colorItr;
			}
			for (int k = 0; k < num; ++k)
			{
				if (colorItr % period == 0) TEXT_RED();

				cout.put(GetRandChar());

				if (colorItr % period == 0) TEXT_GREEN();
				++colorItr;
			}
			cout << endl;
			++row;
		}
	}

	TEXT_YELLO();

	int trunkNum = ((2 * (initHeight + (numOfTr - 1) * heightIncrement - 1) + 1) * 2 / 5) / 2 * 2 + 1;
	
	for (int j = 0; j < initHeight + (numOfTr - 1) * heightIncrement; ++j)
	{

	#ifdef _DEBUG

		cout << ::std::setw(2) << numOfTr << ": " << ::std::setw(3) << row;

	#endif	//_DEBUG

		for (int k = 0; k < (midPos - 1 - trunkNum / 2); ++k)
		{
			cout.put(' ');
		}

		for (int k = 0; k < trunkNum; ++k)
		{
			cout.put(GetRandChar());
		}

		cout << endl;
		++row;
	}

	TEXT_WHITE();

	cout << endl;

	cout << "输入任意以关闭……" << endl;

	cin >> input;

	return 0;
}
