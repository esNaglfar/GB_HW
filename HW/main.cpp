#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
/*
	1. ���������� ��������� ������� Swap, ������� ��������� ��� ��������� � ���������� ������� ��������,
�� ������� ��������� ��� ��������� (����� ���������� ������ ���� ���������, ���������� ������ ���������� � ��� �� ������� ������).
*/


template<typename T>
void Swap(T& _firstPtr, T& _secondPtr)
{
	auto ptrBuffer = std::move(_firstPtr);
	_firstPtr = std::move(_secondPtr);
	_secondPtr = std::move(ptrBuffer);
}

/*
	2. ���������� ��������� ������� SortPointers, ������� ��������� ������ ���������� � ��������� ��������� �� ���������, �� ������� ��� ���������.
*/

template<typename T>
void SortPointers(std::vector<T*>& _vecPointers)
{
	for (size_t i = 0; i < _vecPointers.size(); i++)
	{
		for (size_t j = 0; j < _vecPointers.size() - 1; j++)
		{
			if (*_vecPointers[j] > *_vecPointers[j + 1]) Swap(_vecPointers[j], _vecPointers[j + 1]);
		}
	}
}

/*
	3.����������� ���������� ������� ���� � ����� ������ � ���. ��� �������� ����������� 4 �������:
	  - count_if � find
	  - count_if � ���� for
      - ���� for � find
	  - 2 ����� for
	  �������� ����� ������� ������� �������� � �������� ������.
*/

std::string vowels = "���������";

class Timer
{
public:
	explicit Timer(std::string _func_name) :
		func_name(std::move(_func_name)),
		timestamp(std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::milliseconds(1)) {}

	~Timer()
	{
		auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
		auto result = std::chrono::duration_cast<std::chrono::milliseconds>(now) - timestamp;
		std::cout << std::endl << func_name << " duration : " << result.count() << "ms" << std::endl;
	}
	 
private:
	std::chrono::milliseconds timestamp;
	std::string func_name;
	std::string param;
};

enum FindingType
{
	cif_find = 0,
	cif_for = 1,
	for_find,
	for_for
};

bool IsVovel(char c)
{
	return (vowels.find(c) != std::string::npos) ? true : false;
}

bool IsVovelFor(char c)
{
	bool ret = false;

	for (size_t i = 0; i < vowels.length(); i++)
	{
		if (c == vowels[i])
		{
			ret = true;
			break;
		}
	}

	return ret;
}

size_t CountLetters(FindingType _ftype, std::string&& text)
{
	Timer timer(__func__);
	size_t count = 0;
	size_t letters = 0;

	switch (_ftype)
	{
	case cif_find:
		std::cout << "������� � ������ (cif_find) : " << std::count_if(text.begin(), text.end(), IsVovel);
		break;
	case cif_for:
		std::cout << "������� � ������ (cif_for) : " << std::count_if(text.begin(), text.end(), IsVovelFor);
		break;
	case for_find:
		
		for (size_t i = 0; i < text.length(); i++)
		{
			if (IsVovel(text[i])) { count++; }
		}
		std::cout << "������� � ������ (for_find) : " << count;
		break;
	case for_for:
		for (size_t i = 0; i < text.length(); i++)
		{
			if (IsVovelFor(text[i])) { count++; }
		}
		std::cout << "������� � ������ (for_find) : " << count;
		break;
	}
	
	return letters;
}

// -----------------------------------------------------

void PrintVec(std::vector<int*>& _vecPointers)
{
	for (size_t i = 0; i < _vecPointers.size(); i++)
	{
		std::cout << *_vecPointers[i] << std::endl;
	}
}


int main()
{
	setlocale(LC_CTYPE, "rus");

	// Task 1
	std::cout << "Task 1\n\n";

	std::vector<int> vec1;
	std::vector<int> vec2;
	
	vec1.push_back(50);
	vec2.push_back(100);

	std::cout << &vec1 << " _ " << vec1[0] << std::endl;
	std::cout << &vec2 << " _ " << vec2[0] << std::endl;

	Swap<std::vector<int>>(vec1, vec2);

	std::cout << &vec1 << " _ " << vec1[0] << std::endl;
    std::cout << &vec2 << " _ " << vec2[0] << std::endl;

	// Task 2
	std::cout << std::endl << "Task 2\n\n";


	int a = 5;
	int b = 8;
	int c = -2;
	int d = 1;
	int e = 12;
	int f = 10;
	int g = 0;
	int h = -5;

	std::vector<int*> vPointers;
	vPointers.push_back(&a);
	vPointers.push_back(&b);
	vPointers.push_back(&c);
	vPointers.push_back(&d);
	vPointers.push_back(&e);
	vPointers.push_back(&f);
	vPointers.push_back(&g);
	vPointers.push_back(&h);

	SortPointers(vPointers);

	PrintVec(vPointers);

	// Task 3
	std::cout << std::endl << "Task 3\n\n";

	CountLetters(cif_find,"�������������� ����� ���� ����������� �������� '����� � ���', � ������� ���� ��������");
	CountLetters(cif_for, "�������������� ����� ���� ����������� �������� '����� � ���', � ������� ���� ��������");
	CountLetters(for_find, "�������������� ����� ���� ����������� �������� '����� � ���', � ������� ���� ��������");
	CountLetters(for_for, "�������������� ����� ���� ����������� �������� '����� � ���', � ������� ���� ��������");

}