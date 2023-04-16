#pragma once
#include "proffesor.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

enum class EType {
	Good,
	Middle,
	Bad
};
enum class ESol {
	ZERO,
	ONE_LINEAR,
	ONE_PARABOLIC,
	TWO,
	INF
};
std::vector <std::array<double, 3>> Equations();
std::vector<std::pair<std::string, EType>> Students();
std::array<double, 2> QuadOut(ESol num, double a, double b, double c);
std::array<double, 2> LineSol(std::array<double, 3> coef);
std::array<double, 2> QuadSol(std::array<double, 3> coef);
std::vector<std::array<double, 2>> Solutions(std::vector <std::array<double, 3>>& equation);
std::array<double, 2> StudentSolutions(std::array<double, 3>& coef);
std::vector<std::array<double, 5>> Answer(std::vector<std::array<double, 3>>& eqt, std::vector<std::array<double, 2>>& sol);
std::queue<std::pair<std::array<double, 5>, std::string>> List(std::vector <std::array<double, 3>>& equation, std::vector<std::pair<std::string, EType>>& stdnts);
std::vector<std::pair<std::string, int>> Check(std::queue <std::pair<std::array<double, 5>, std::string>>& list, std::vector<std::pair<std::string, EType>>& stdnts, std::vector<std::array<double, 5>>& ans);
void GradeTable(std::vector<std::pair<std::string, int>> table);

class Student
{
public:
	Student();
protected:
	std::vector<std::array<double, 3>> equations;
	std::vector<std::pair<std::string, EType>> students;
	std::queue <std::pair<std::array<double, 5>, std::string>> list;
};

class Proffesor : public Student
{
public:
	Proffesor();
	void Check();
	void GradeTable();
private:
	std::vector<std::array<double, 2>> solutions;
	std::vector<std::array<double, 5>> answers;
	std::vector<std::pair<std::string, int>> results;
};