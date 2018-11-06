// Aleksander Ficek
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std; 

const int MAX = 50;	

void read_current (ifstream & fin, bool staffCUR[], string nameCUR[])
{
	bool staff_student = 0;
	string name;
	int position = 0;
	while (fin >> staff_student >> name >> position)
	{
		staffCUR[position - 1] = staff_student; 
		nameCUR[position - 1] = name; 			
	}
}

int numPeople (ifstream & fin, bool staff[], string name[])
{
	int count = 0;
	while (fin >> staff[count] >> name[count])
		count++;
	return count;
}

void freeSpace (bool staffCUR[], bool staffREM[], string nameCUR[], string nameREM[])
{
	int count = 0;
	while (nameREM[count] != "")
	{	
		int count2 = 0;
		while (nameREM[count] != nameCUR[count2])
			count2++;
		nameCUR[count2] = "";
		staffCUR[count2] = 0;
		count++;
	}
}

int findFree (bool staffCUR[], string nameCUR[], int count2)
{
	while (nameCUR[count2] != "")
		count2++;
	return count2;
}

bool assignSpace (bool staffCUR[], bool staffADD[], string nameCUR[], string nameADD[], int count)
{		
		if (staffADD[count] == false)
		{
			int free_space = findFree(staffCUR, nameCUR, 26);		// starts at 26 for students
			if (free_space == 51)
				return false;		
			else 
			{
				nameCUR[free_space] = nameADD[count];
				staffCUR[free_space] = staffADD[count];
				return true;	
			}
		}
		else 
		{
			int free_space = findFree(staffCUR, nameCUR, 0);		// starts at 0 for staff
			if (free_space == 51)
				return false;		
			else 
			{
				nameCUR[free_space] = nameADD[count];
				staffCUR[free_space] = staffADD[count];
				return true;	
			}
		}
}

void optimize (bool staffCUR[], bool staffADD[], string nameCUR[], string nameADD[])
{
	int count = 0, count3 = 26, free_s = 0; 
	while (count3 < 50)
	{
		if (staffCUR[count3] == true)
		{
			free_s = findFree(staffCUR, nameCUR, 0);
			if (free_s < 26)
			{
				nameCUR[free_s] = nameCUR[count3];
				staffCUR[free_s] = staffCUR[count3];	
				staffCUR[count3] = 0;					// call function d
				nameCUR[count3] = "";
			}
		}
			count3++;
	}
	while (nameADD[count] != "")
	{
		bool check_if_exists = 0;
		for (int count0 = 0; count0 < 50; count0++)
		{
			if (nameADD[count] == nameCUR[count0]) 
				check_if_exists = 1;
		}
			if (check_if_exists == false)
				assignSpace (staffCUR, staffADD, nameCUR, nameADD, count);	
			count++;
	}		
}

int main()
{
	ifstream fin("parking_current.txt");
	if (!fin)
	{
		cout << "No file.";
		return EXIT_FAILURE;
	}
	
	ifstream fin_remove("parking_remove.txt");
	if (!fin_remove)
	{
		cout << "No file.";
		return EXIT_FAILURE;
	}
	
	ifstream fin_add("parking_add.txt");
	if (!fin_add)
	{
		cout << "No file.";
		return EXIT_FAILURE;
	}
	
	ofstream fout("parking_output");
	
	bool staffCUR[MAX] = {0}, staffREM[MAX] = {0}, staffADD[MAX] = {0};
	string nameCUR[MAX], nameREM[MAX], nameADD[MAX];
	
	read_current (fin, staffCUR, nameCUR);
	
	int people_in_rem = numPeople (fin_remove, staffREM, nameREM);
//	int people_in_add = numPeople (fin_add, staffADD, nameADD);
	
//	freeSpace (staffCUR, staffREM, nameCUR, nameREM);
	
//	optimize (staffCUR, staffADD, nameCUR, nameADD);
	
	int count = 0;
	
//	while (nameADD[count] != "")
//	{
//
//		assignSpace (staffCUR, staffADD, nameCUR, nameADD, count);	
//		count++;
//	}
//	

	
	for (int count1 = 0; count1 < 50; count1++)
		fout << staffCUR[count1] << " " << nameCUR[count1] << endl;
	
	fin.close(), fin_remove.close(), fin_add.close(), fout.close();
	return EXIT_SUCCESS;
}
