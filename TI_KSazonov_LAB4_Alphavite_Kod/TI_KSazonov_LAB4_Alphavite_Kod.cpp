#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;


fstream fin("in.txt", fstream::in);
fstream fou("out.txt", fstream::out);




string str = "abacabacabadaca";
string str_buff(str.length(), ' ');
string *buf = new string[5];
int ind_str_buff = 0;
int ind_buff = 0;
int ind_vector = -1;
vector<char> code_vect_char;
vector<int> code_vect_offset;
vector<int> code_vect_length;

//void search_for_characters_in_the_buffer(int i)
//{
//	
//	int k = i;
//	int max_sequence = 0, check_max_sequence = 0, index_max_sequence = 0, index = 0;
//	for (int j = 0; j < str_buff.length(); j++)
//	{
//		if (str[k] == str_buff[j])
//		{
//			k++;
//			check_max_sequence++;
//			index = j;
//		}
//		else
//		{
//			if (check_max_sequence > max_sequence)
//			{
//				max_sequence = check_max_sequence;
//				index_max_sequence = index;
//			}
//			index = 0;
//			check_max_sequence = 0;
//			k = i;
//		}
//	}
//
//	if (!max_sequence)
//	{
//		code_vect_char.push_back(str[i]);
//		code_vect_offset.push_back(0);
//		code_vect_length.push_back(0);
//	}
//	else
//	{
//		if (ind_buff + max_sequence == str.length())
//		{
//			code_vect_char.push_back(0);
//			code_vect_offset.push_back(ind_buff - (index_max_sequence - max_sequence));
//			code_vect_length.push_back(max_sequence);
//		}
//		else
//		{
//			code_vect_char.push_back(str[i + max_sequence + 1]);
//			code_vect_offset.push_back(ind_buff - (index_max_sequence - max_sequence));
//			code_vect_length.push_back(max_sequence);
//		}
//	}
//}

int main()
{
	
	for (int i = 0; i < str.length(); i++)
	{
		//	search_for_characters_in_the_buffer(i);
		int k = i;
		int max_sequence = 0, check_max_sequence = 0, index_max_sequence = 0, index = 0;
		for (int j = 0; j < ind_buff; j++)
		{
			if (str[k] == str_buff[j])
			{
				k++;
				check_max_sequence++;
				index = j;
				if (j == ind_buff - 1 && check_max_sequence >= max_sequence)
				{
					j = -1;
				}
			}
			else
			{
				if (check_max_sequence > max_sequence)
				{
					max_sequence = check_max_sequence;
					index_max_sequence = index;
				}
				index = 0;
				check_max_sequence = 0;
				k = i;
			}
		}
		
		if (check_max_sequence != 0 && max_sequence == 0)
		{
			max_sequence = check_max_sequence;
			index_max_sequence = index;
		}

		if (!max_sequence)
		{
			code_vect_char.push_back(str[i]);
			code_vect_offset.push_back(0);
			code_vect_length.push_back(0);
			ind_vector++;
		}
		else
		{
				code_vect_char.push_back(str[i + max_sequence]);
				int offset = 0;
				if (max_sequence > ind_buff)
					offset = ind_buff;
				else
					offset = ind_buff - 1 - (index_max_sequence - max_sequence);
				code_vect_offset.push_back(offset);
				code_vect_length.push_back(max_sequence);
		//		k = i;
				i = i + max_sequence;
				ind_vector++;
				
				if (ind_buff + max_sequence == str.length() - 1)
				{
					code_vect_char.push_back(0);
					code_vect_offset.push_back(ind_buff - 1 - (index_max_sequence - max_sequence));
					code_vect_length.push_back(max_sequence);
				//	ind_vector++;
				}
		}
	//	-------  запись в буфер последовательности 
		if (code_vect_offset[ind_vector] != 0)
		{
			k = ind_buff;
			int z = code_vect_length[ind_vector];
			int z1 = 0; // проверка полного обхода последовательности, при выходе за размерност ьбуфера
			if (z > ind_buff)
			{
				z = ind_buff;
			}
			for (int j = k - code_vect_offset[ind_vector]; j < ((k - code_vect_offset[ind_vector]) + z); j++)
			{				
				str_buff[ind_buff] = str_buff[j];
				ind_buff++;
				z1++;
				if ((z1 != code_vect_length[ind_vector]) && (j + 1 == ((k - code_vect_offset[ind_vector]) + z)))
				{
					z = code_vect_length[ind_vector] - z;
					j = -1;
				}
			}
		}
		
		if (code_vect_char[ind_vector] != 0)
		{
			str_buff[ind_buff] = code_vect_char[ind_vector];
			ind_buff++;
		}
	}
	
	for (int j = 0; j < ind_vector + 1; j++)
	{
		cout << "<" << code_vect_offset[j] << ", " << code_vect_length[j] << ", " << code_vect_char[j] << ">" << endl;
	}
		std::cout << "Hello World!\n"; 
}

