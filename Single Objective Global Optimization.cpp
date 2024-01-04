// Single Objective Global Optimization.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#define _USE_MATH_DEFINES // for C++
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include "float.h"
#include "Generation.h"
#include "Point.h"
#include "test.h"


using namespace std;
vector<int>   dim_arr = { 2,10,30 };
int population_cnt, generation_cnt, func_val, method;
enum func { func_Ackley = 1, func_Rastrigin = 2, func_Sphere = 3, func_Rosenbrock = 4, func_Michalewicz = 5, func_Griewank = 6, func_Schwefel = 7, func_SumSquares = 8, func_Zakharov = 9, func_Powell = 10 };
static const char* func_str[] = { "","Ackley", "Rastrigin", "Sphere", "Rosenbrock", "Michalewicz", "Griewank", "Schwefel", "SumSquares", "Zakharov", "Powell" };
map<int, vector<double>> func_size = { {func_Ackley, {-30, 30}}, {func_Rastrigin, {-5.12, 5.12}}, {func_Sphere, {-5.12, 5.12}}, {func_Rosenbrock, {-10, 10}}, {func_Michalewicz, {0, M_PI}}, {func_Griewank, {-600, 600}}, {func_Schwefel, {-500, 500}}, {func_SumSquares, {-5.12, 5.12}}, {func_Zakharov, {-5, 10}} ,{func_Powell, {-4, 5}} };
random_device rd;
mt19937 generator(rd());

double w1 = 0.9;
double c1 = 1.49, c2 = 1.49;
vector<Generation> genreations;
vector<Point> local_opt_point;//local opt 每個點
vector<double> local_opt_val;//local opt 每個點的最佳value
Point global_opt_point;//全局最佳的點
double global_opt_value;//全局最佳的點的value
int repeat_cnt = 30;
vector<double> repaet_global;//global  每個點
vector<double> fitness;//此回合各點的fitness
double totalfitness = 0;//此回合全部點的fitness加總


//operator overload
vector<double> operator*(double alfa, const vector<double>& v)
{
	vector<double> temp;
	for (int i = 0; i < v.size(); i++)
	{
		temp.push_back(v.at(i) * alfa);
	}
	return temp;
}
vector<double> operator*(const vector<double>& v, double alfa)
{
	vector<double> temp;
	for (int i = 0; i < v.size(); i++)
	{
		temp.push_back(v.at(i) * alfa);
	}
	return temp;
}
vector<double> operator+(const vector<double>& v1, const vector<double>& v2)
{
	vector<double> temp;
	for (int i = 0; i < v1.size(); i++)
	{
		temp.push_back(v1.at(i) + v2.at(i));
	}
	return temp;
}
vector<double> operator-(const vector<double>& v1, const vector<double>& v2)
{
	vector<double> temp;
	for (int i = 0; i < v1.size(); i++)
	{
		temp.push_back(v1.at(i) - v2.at(i));
	}
	return temp;
}

double random() {//random小數
	uniform_real_distribution<double> unif(0, 1);
	return unif(generator);
}
void random(int population_cnt, int func_val, int dim) {
	Generation generation;
	uniform_real_distribution<double> unif(func_size[func_val][0], func_size[func_val][1]);
	local_opt_point.clear();
	local_opt_val.clear();
	genreations.clear();
	for (int i = 0; i < population_cnt; i++) {
		Point point;
		for (int j = 0; j < dim; j++) {
			double a = unif(generator);
			if (a < func_size[func_val][0] || func_size[func_val][1] < a) {
				int hhh = 0;
			}
			point.position.push_back(a);
			point.velocity.push_back(0);
		}
		generation.points.push_back(point);
		local_opt_point.push_back(point);
		local_opt_val.push_back(DBL_MAX);
	}
	global_opt_value = DBL_MAX;
	genreations.resize(generation_cnt + 1);
	genreations[0] = generation;
}
void init(int population_cnt, int func_val, int dim) {
	random(population_cnt, func_val, dim);
}
string getStringForEnum(int enum_val)
{
	string tmp(func_str[enum_val]);
	return tmp;
}

void compare(double  cal_value, int i, int j) {
	if (cal_value < local_opt_val[j]) {
		local_opt_val[j] = cal_value;
		local_opt_point[j] = genreations[i].points[j];
	}
	if (cal_value < global_opt_value) {
		global_opt_value = cal_value;
		global_opt_point = genreations[i].points[j];
	}
}
int main()
{
	cout << "請輸入欲產生迭代次數、點的數量、function數值、方法" << endl;
	cout << "function數值:Ackley = 1, Rastrigin = 2, Sphere = 3, Rosenbrock = 4, Michalewicz = 5, Griewank=6, Schwefel=7, SumSquares=8, Zakharov=9, Powell=10" << endl;
	cout << "方法:原PSO=1、線性更改=2、自適應=3" << endl;
	cout << "重複次數:"<<repeat_cnt << endl;

	cin >> generation_cnt >> population_cnt >> func_val >> method;
	for (int totalfunc_cnt = 1; totalfunc_cnt <= 10; totalfunc_cnt++) {	
		func_val = totalfunc_cnt;
		for (int dim_index = 0; dim_index < dim_arr.size(); dim_index++) {
			repaet_global.resize(generation_cnt);
			for (int i = 0; i < generation_cnt; i++)
			{
				repaet_global[i] = 0;
			}
			string filename = "";
			switch (method) {
				case 1:
					filename = "E:\\中山大學碩士課程\\碩一下\\群體智慧\\test\\Single Objective Global Optimization\\Single Objective Global Optimization\\file2\\original_pso\\" + getStringForEnum(func_val) + "\\" + to_string(dim_arr[dim_index]) + ".csv";
					break;
				case 2:
					filename = "E:\\中山大學碩士課程\\碩一下\\群體智慧\\test\\Single Objective Global Optimization\\Single Objective Global Optimization\\file2\\linear_pso\\" + getStringForEnum(func_val) + "\\" + to_string(dim_arr[dim_index]) + ".csv";
					break;
				case 3:
					filename = "E:\\中山大學碩士課程\\碩一下\\群體智慧\\test\\Single Objective Global Optimization\\Single Objective Global Optimization\\file2\\adaptive_pso\\" + getStringForEnum(func_val) + "\\" + to_string(dim_arr[dim_index]) + ".csv";
					break;
			}
			for (int repeat = 0; repeat < repeat_cnt; repeat++) {
				//filename = "D:\\Garena\\" + getStringForEnum(func_val) + "_" + to_string(dim_arr[dim_index]) + ".csv";
				freopen(filename.c_str(), "w", stdout);
				cout << dim_arr[dim_index] << endl;
				init(population_cnt, func_val, dim_arr[dim_index]);
				fitness.resize(population_cnt);
				for (int i = 0; i < generation_cnt; i++) {
					totalfitness = 0;
					switch (func_val) {
					case func_Ackley:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Ackley(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Rastrigin:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Rastrigin(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Sphere:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Sphere(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Rosenbrock:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Rosenbrock(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Michalewicz:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Michalewicz(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Griewank:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Griewank(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Schwefel:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Schwefel(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_SumSquares:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = SumSquares(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Zakharov:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Zakharov(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					case func_Powell:
						for (int j = 0; j < population_cnt; j++) {
							double cal_value = Powell(dim_arr[dim_index], &genreations[i].points[j].position[0]);
							fitness[j] = cal_value;
							totalfitness += cal_value;
							compare(cal_value, i, j);
						}
						break;
					default:
						break;
					}
					//cout << global_opt_value << endl;
					repaet_global[i] += global_opt_value;

					//顯示最好的點在哪
					//for (int k = 0; k < global_opt_point.position.size(); k++) {
					//    cout << global_opt_point.position[k]<< ",";
					//}
					//cout << endl;        
					for (int j = 0; j < population_cnt; j++) {
						//列出此代所有的點
						//for (int k = 0; k < genreations[i].points[j].position.size(); k++) {
						//    cout << genreations[i].points[j].position[k] << ",";
						//}
						//cout << endl;
						Point temp;
						if (method == 1) {//固定在0.9
							vector<double> new_velocity;
							double r1 = random();
							double r2 = random();
							for (int h = 0; h < dim_arr[dim_index]; h++) {
								new_velocity.push_back(w1* genreations[i].points[j].velocity[h]
											+ c1 * r1 * (local_opt_point[j].position[h] - genreations[i].points[j].position[h])
											+ c2 * r2 * (global_opt_point.position[h] - genreations[i].points[j].position[h]));
							}
							temp.velocity = new_velocity;
							/*temp.velocity = w1 * genreations[i].points[j].velocity +
								c1 * random() * (local_opt_point[j].position - genreations[i].points[j].position) +
								c2 * random() * (global_opt_point.position - genreations[i].points[j].position);*/
						}
						else if (method == 2) {//0.9-0.4線性遞減
							double change_w1 = 0.9 - (i * (0.5) / generation_cnt);
							vector<double> new_velocity;
							double r1 = random();
							double r2 = random();
							for (int h = 0; h < dim_arr[dim_index]; h++) {
								new_velocity.push_back(change_w1 * genreations[i].points[j].velocity[h]
									+ c1 * r1 * (local_opt_point[j].position[h] - genreations[i].points[j].position[h])
									+ c2 * r2 * (global_opt_point.position[h] - genreations[i].points[j].position[h]));
							}
							temp.velocity = new_velocity;						
						}
						else {
							double change_w1;
							double avg_fitness = totalfitness / population_cnt;
							if (avg_fitness >= fitness[j]) {
								change_w1 = 0.4 + 0.5 * (fitness[j] - global_opt_value) / (avg_fitness - global_opt_value);
							}
							else {
								change_w1 = 0.9;
							}
							vector<double> new_velocity;
							double r1 = random();
							double r2 = random();
							for (int h = 0; h < dim_arr[dim_index]; h++) {
								new_velocity.push_back(change_w1 * genreations[i].points[j].velocity[h]
									+ c1 * r1 * (local_opt_point[j].position[h] - genreations[i].points[j].position[h])
									+ c2 * r2 * (global_opt_point.position[h] - genreations[i].points[j].position[h]));
							}
							temp.velocity = new_velocity;
						}
						temp.position = genreations[i].points[j].position + temp.velocity;

						for (int k = 0; k < temp.position.size(); k++) {
							if (temp.position[k] > func_size[func_val][1]) {
								temp.velocity[k] -= (temp.position[k] - func_size[func_val][1]);
								temp.position[k] = func_size[func_val][1];
							}
							else if (temp.position[k] < func_size[func_val][0]) {
								temp.velocity[k] -= (temp.position[k] - func_size[func_val][0]);
								temp.position[k] = func_size[func_val][0];
							}
						}
						genreations[i + 1].points.push_back(temp);
					}
				}
			}
			for (int i = 0; i < generation_cnt; i++) {
				cout << (repaet_global[i] / repeat_cnt) << endl;
			}
			fclose(stdout);
			freopen("CON", "w", stdout);
			cout << getStringForEnum(func_val)<<"_" << to_string(dim_arr[dim_index])<< "完成" << endl;
		}

	}


}
