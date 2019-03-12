// Bloxorz.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include "levels.h"
#include "node.h"
#include "operators.h"
#include "runner.h"

int main() {
  
  /*
  node initial(LVL1, 5, 7);
  auto second = roll_right(initial, inc);
  auto third = roll_left(second, inc);
  auto fourth = roll_right(third, inc);

  initial.print();
  std::cout << std::endl << std::endl;
  second.print();
  std::cout << std::endl << std::endl;
  third.print();
  std::cout << std::endl << std::endl;
  fourth.print();

  std::cout << std::endl << initial.cost << std::endl << second.cost <<
   std::endl << third.cost << std::endl;

  if (third.objective()) {
    std::cout << "HEY";
    }
  */
  auto r = runner(bfs, LVL1, LVL1_R, LVL1_C);
  auto sol = r.run();

  std::cout << sol << std::endl << std::endl << "COST: " << sol.cost << std::endl;
  
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
