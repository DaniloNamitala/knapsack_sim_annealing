#include <iostream>
#include "knapsack.hpp"
#include <fstream>
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>

Knapsack first_solution(const char* filename) {
  std::ifstream file(filename);
  int n, c;
  file >> n >> c;
  Knapsack pack = Knapsack(c);
  return pack;
}

Item* read_list(const char* filename, int* capacity, int* itens_count) {
  std::ifstream file(filename);
  Item* list;
  if (file.is_open()) {
    file >> *itens_count >> *capacity;
    list = new Item[*itens_count];
    for (int i=0; i<*itens_count; i++) {
      float w, c;
      file >> w >> c;
      list[i] = Item(w, c);
    }
  }
  return list;
}

std::vector<std::pair<double, double>> simulated_annealing(double initial_temp, double final_temp, Item* items, Knapsack* solution, int n_itens) {
  int iterations = 0;
  std::vector<std::pair<double, double>> to_plot = std::vector<std::pair<double, double>>();
  Knapsack actual_solution = *solution;

  for (double t = initial_temp; t > final_temp; t = NEW_TEMP(t)) {

    Knapsack new_solution = actual_solution;
    if (random() % 2) {
      new_solution.addRandom(items[random() % n_itens]);
    } else {
      new_solution.removeRandom();
    }

    float delta = actual_solution - new_solution;
    double error = 0;
    if (delta < 0 || (double(random()) / double(RAND_MAX)) >= ((delta)/t)) {
      error = actual_solution - new_solution;
      actual_solution = new_solution;
    }
    iterations++;
    to_plot.push_back(std::make_pair(double(iterations), double(actual_solution.value())));
  }
  *solution = actual_solution;
  return to_plot;
}

void plotChangeTemp(int argc, char** argv) {
  int capacity;
  int itens_count;
  Item* items = read_list(argv[1], &capacity, &itens_count);
  
  Knapsack* solution1 = new Knapsack(capacity);
  auto to_plot1 = simulated_annealing(100, 0.001, items, solution1, itens_count);

  Knapsack* solution2 = new Knapsack(capacity);
  auto to_plot2 = simulated_annealing(1000, 0.001, items, solution2, itens_count);

  Knapsack* solution3 = new Knapsack(capacity);
  auto to_plot3 = simulated_annealing(10000, 0.001, items, solution3, itens_count);

  Knapsack* solution4 = new Knapsack(capacity);
  auto to_plot4 = simulated_annealing(100000, 0.001, items, solution4, itens_count);

  Gnuplot gp;
  double yLimit = std::max({solution1->value(), solution2->value(), solution3->value(), solution4->value()});
  gp << "set xrange [0:" << to_plot4.size() << "]\nset yrange [-2:" << yLimit*1.2 <<"]\nset key right bottom\n";
  gp << "set term wxt title 'Temperature Variation'\n";
	gp << "plot" << gp.file1d(to_plot1) << "with lines title 'TEMP 100 - 0.001 " << *solution1 << "' lt rgb 'red',";
	gp << gp.file1d(to_plot2) << "with lines title 'TEMP 1000 - 0.001 " << *solution2 << "' lt rgb 'blue',";
	gp <<  gp.file1d(to_plot3) << "with lines title 'TEMP 10000 - 0.001 " << *solution3 << "' lt rgb 'green',";
	gp << gp.file1d(to_plot4) << "with lines title 'TEMP 100000 - 0.001 " << *solution4 << "' lt rgb 'violet'" << std::endl;
}


void plotChangeStart(int argc, char** argv) {
  int capacity;
  int itens_count;
  Item* items = read_list(argv[1], &capacity, &itens_count);
  
  Knapsack* solution1 = new Knapsack(capacity, std::vector<Item>({items[0], items[1], items[2]}));
  auto to_plot1 = simulated_annealing(10000, 0.001, items, solution1, itens_count);

  Knapsack* solution2 = new Knapsack(capacity, std::vector<Item>({items[7], items[10], items[20]}));
  auto to_plot2 = simulated_annealing(10000, 0.001, items, solution2, itens_count);

  Knapsack* solution3 = new Knapsack(capacity, std::vector<Item>({items[55], items[100], items[250]}));
  auto to_plot3 = simulated_annealing(10000, 0.001, items, solution3, itens_count);

  Knapsack* solution4 = new Knapsack(capacity, std::vector<Item>({items[30], items[13], items[2]}));
  auto to_plot4 = simulated_annealing(10000, 0.001, items, solution4, itens_count);

  Gnuplot gp;
  double yLimit = std::max({solution1->value(), solution2->value(), solution3->value(), solution4->value()});
  gp << "set xrange [0:" << to_plot4.size() << "]\nset yrange [-2:" << yLimit*1.2 <<"]\nset key right bottom\n";
  gp << "set term wxt title 'Start Point Variation'\n";
	gp << "plot" << gp.file1d(to_plot1) << "with lines title 'TEMP 10000 - 0.001 " << *solution1 << "' lt rgb 'red',";
	gp << gp.file1d(to_plot2) << "with lines title 'TEMP 10000 - 0.001 " << *solution2 << "' lt rgb 'blue',";
	gp <<  gp.file1d(to_plot3) << "with lines title 'TEMP 10000 - 0.001 " << *solution3 << "' lt rgb 'green',";
	gp << gp.file1d(to_plot4) << "with lines title 'TEMP 10000 - 0.001 " << *solution4 << "' lt rgb 'violet'" << std::endl;
}

int main(int argc, char** argv) {
  plotChangeTemp(argc, argv);
  plotChangeStart(argc, argv);
}

