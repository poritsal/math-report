#include "proffesor.h"

// equations
std::vector <std::array<double, 3>> Equations()
{
	std::fstream file;
	file.open("equations.txt");
	if (!file.is_open()) {
		std::cout << "file open error";
		exit(1);
	}
	double d = 0;
	std::vector <std::array<double, 3>> res;
	std::array<double, 3> coef{};
	while (!file.eof()) {
		for (size_t i = 0; i < 3; i++) {
			file >> d;
			coef[i] = d;
		}
		res.push_back(coef);
	}
	file.close();
	return res;
}

//students
std::vector<std::pair<std::string, EType>> Students() {
	std::fstream file;
	file.open("students.txt");
	if (!file.is_open()) {
		std::cout << "file open error";
		exit(1);
	}
	std::string name;
	std::vector<std::pair<std::string, EType>> stdlst;
	std::srand(std::time(nullptr));
	int rnd;
	while (!file.eof()) {
		std::getline(file, name);
		rnd = 1 + std::rand() % 3;
		switch (rnd)
		{
		case 1:
			stdlst.push_back(std::make_pair(name, EType::Good));
			break;
		case 2:
			stdlst.push_back(std::make_pair(name, EType::Middle));
			break;
		case 3:
			stdlst.push_back(std::make_pair(name, EType::Bad));
			break;
		default:
			break;
		}
	}
	return stdlst;
}

//solutions
std::array<double, 2> QuadOut(ESol num, double a, double b, double c)
{
	std::array<double, 2> res{};
	switch (num)
	{
	case ESol::INF:
		res = { INT_MIN, INT_MAX };
		break;
	case ESol::ZERO:
		res = { INT_MAX, INT_MIN };
		break;
	case ESol::ONE_LINEAR:
		res = { (-c) / (b), INT_MIN };
		break;
	case ESol::ONE_PARABOLIC:
		res = { (-b) / (2 * a), INT_MAX };
		break;
	case ESol::TWO:
		if ((-b - sqrt(b * b - 4 * a * c)) / (2 * a) > (-b + sqrt(b * b - 4 * a * c)) / (2 * a)) {
			res = { (-b + sqrt(b * b - 4 * a * c)) / (2 * a), (-b - sqrt(b * b - 4 * a * c)) / (2 * a) };
		}
		else {
			res = { (-b - sqrt(b * b - 4 * a * c)) / (2 * a), (-b + sqrt(b * b - 4 * a * c)) / (2 * a) };
		}
		break;
	}
	return res;
}

std::array<double, 2> LineSol(std::array<double, 3> coef) {
	std::array<double, 2> res{};
	if (coef[1] == 0) {
		if (coef[2] == 0) {
			res = QuadOut(ESol::INF, coef[0], coef[1], coef[2]);
		}
		else {
			res = QuadOut(ESol::ZERO, coef[0], coef[1], coef[2]);
		}
	}
	else {
		res = QuadOut(ESol::ONE_LINEAR, coef[0], coef[1], coef[2]);
	}
	return res;
}

std::array<double, 2> QuadSol(std::array<double, 3> coef) {
	std::array<double, 2> res{};

	if (coef[1] * coef[1] - 4 * coef[0] * coef[2] < 0) {
		res = QuadOut(ESol::ZERO, coef[0], coef[1], coef[2]);
	}
	else if (coef[1] * coef[1] - 4 * coef[0] * coef[2] > 0) {
		res = QuadOut(ESol::TWO, coef[0], coef[1], coef[2]);
	}
	else if (coef[1] * coef[1] - 4 * coef[0] * coef[2] == 0) {
		res = QuadOut(ESol::ONE_PARABOLIC, coef[0], coef[1], coef[2]);
	}

	return res;
}

std::vector<std::array<double, 2>> Solutions(std::vector <std::array<double, 3>>& equation)
{
	std::vector<std::array<double, 2>> res(equation.size());
	for (size_t i = 0; i < equation.size(); i++) {
		if (equation[i][0] == 0) {
			res[i] = LineSol(equation[i]);
		}
		else {
			res[i] = QuadSol(equation[i]);
		}
	}
	return res;
}

//Student solution
std::array<double, 2> StudentSolutions(std::array<double, 3>& coef)
{
	std::array<double, 2> res{};

	if (coef[0] == 0) {
		res = LineSol(coef);
	}
	else {
		res = QuadSol(coef);
	}

	return res;
}

//answertable
std::vector<std::array<double, 5>> Answer(std::vector<std::array<double, 3>>& eqt, std::vector<std::array<double, 2>>& sol) {
	std::vector<std::array<double, 5>> res;
	for (size_t i = 0; i < sol.size(); i++)
	{
		res.push_back({ eqt[i][0], eqt[i][1], eqt[i][2], sol[i][0], sol[i][1] });
	}
	return res;
}

//queue
std::queue<std::pair<std::array<double, 5>, std::string>> List(std::vector <std::array<double, 3>>& equation, std::vector<std::pair<std::string, EType>>& stdnts) {
	std::queue <std::pair<std::array<double, 5>, std::string>> list;
	std::array<double, 5> element{};
	std::array<double, 2> sol{};
	std::srand(std::time(nullptr));
	for (size_t i = 0; i < stdnts.size(); i++)
	{
		if (stdnts[i].second == EType::Good) {
			for (size_t j = 0; j < equation.size(); j++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					element[k] = equation[j][k];
				}
				sol = StudentSolutions(equation[j]);
				element[3] = sol[0];
				element[4] = sol[1];
				list.push(std::make_pair(element, stdnts[i].first));
			}
		}
		else if (stdnts[i].second == EType::Bad) {
			for (size_t j = 0; j < equation.size(); j++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					element[k] = equation[j][k];
				}
				element[3] = 0;
				element[4] = 0;
				list.push(std::make_pair(element, stdnts[i].first));
			}
		}
		else {
			for (size_t j = 0; j < equation.size(); j++)
			{
				for (size_t k = 0; k < 3; k++)
				{
					element[k] = equation[j][k];
				}
				sol = StudentSolutions(equation[j]);
				int rnd = std::rand() % 2;
				element[3] = sol[0] + rnd;
				element[4] = sol[1] + rnd;
				list.push(std::make_pair(element, stdnts[i].first));
			}
		}
	}
	return list;
}

//check
std::vector<std::pair<std::string, int>> Check(std::queue <std::pair<std::array<double, 5>, std::string>>& list, std::vector<std::pair<std::string, EType>>& stdnts, std::vector<std::array<double, 5>>& ans) {
	std::pair<std::array<double, 5>, std::string> el;
	std::vector<std::pair<std::string, int>> res(stdnts.size());
	for (size_t i = 0; i < stdnts.size(); i++)
	{
		res[i].first = stdnts[i].first;
	}
	std::vector<std::array<double, 5>>::iterator an;
	while (!list.empty())
	{
		el = list.front();
		list.pop();
		an = std::find(ans.begin(), ans.end(), el.first);
		if (an != ans.end())
		{
			for (size_t i = 0; i < res.size(); i++)
			{
				if (el.second == res[i].first)
				{
					res[i].second += 1;
					break;
				}
			}
		}

	}
	return res;
}

//out
void GradeTable(std::vector<std::pair<std::string, int>> table) {
	std::fstream file;
	file.open("gradetable.txt", std::fstream::app);
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
	for (size_t i = 0; i < table.size(); i++)
	{
		file << table[i].first << " " << table[i].second << '\n';
	}
}

Student::Student()
{
	equations = Equations();
	students = Students();
	list = List(equations, students);
}
Proffesor::Proffesor()
{
	solutions = Solutions(equations);
	answers = Answer(equations, solutions);
	results.resize(students.size());
}

void Proffesor::Check()
{
	std::pair<std::array<double, 5>, std::string> el;
	for (size_t i = 0; i < students.size(); i++)
	{
		results[i].first = students[i].first;
	}
	std::vector<std::array<double, 5>>::iterator an;
	while (!list.empty())
	{
		el = list.front();
		list.pop();
		an = std::find(answers.begin(), answers.end(), el.first);
		if (an != answers.end())
		{
			for (size_t i = 0; i < results.size(); i++)
			{
				if (el.second == results[i].first)
				{
					results[i].second += 1;
					break;
				}
			}
		}

	}
}

void Proffesor::GradeTable()
{
	std::fstream file;
	file.open("gradetable.txt", std::fstream::app);
	if (!file.is_open())
	{
		std::cout << "file open error";
		exit(1);
	}
	for (size_t i = 0; i < results.size(); i++)
	{
		file << results[i].first << " " << results[i].second << '\n';
	}
}