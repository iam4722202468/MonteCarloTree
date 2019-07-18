#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

#include <iostream>
#include <string>
#include <vector>

#include "course.h"

int comp(int in1, int in2) {
  return in1 - in2;
}

int fitness(std::vector<std::vector<int>> *arrs, std::vector<int> currPath, int pathNum) {
  int acc = 0;
  for (unsigned int x = 0; x < currPath.size(); ++x) {
    acc += arrs->at(x)[currPath.at(x)];
  }

  return acc;
}

std::vector<int> getPath(std::vector<int> path, int **arrs) {
  std::vector<int> vals;
  for (unsigned int x = 0; x < path.size(); ++x) {
    vals.push_back(arrs[x][path[x]]);
  }

  return vals;
}

std::vector<std::vector<int>> gen_mutate(std::vector<std::vector<int>> arrs, std::vector<std::vector<int>> currPaths) {
  // Start at 1 to keep parent
  for (unsigned int x = 1; x < currPaths.size(); ++x) {
    // Guarentee mutation
    unsigned int toChange = rand() % arrs.at(x).size();
    unsigned int changePlace = rand() % currPaths.at(x).size();

    currPaths.at(x).at(changePlace) = toChange;

    for (unsigned int y = 0; y < currPaths.at(x).size(); ++y) {
      unsigned int toChange = rand() % arrs.at(x).size();
      unsigned int toChangeCheck = rand() % arrs.at(x).size();

      if (toChangeCheck < 2) {
        currPaths.at(x).at(y) = toChange;
      }
    }
  }

  return currPaths;
}

struct gen_trim_struct {
  std::vector<int> top;
  int fitness;
};

gen_trim_struct gen_trim(std::vector<std::vector<int>> arrs, std::vector<std::vector<int>> currPaths, int pathNum, int compare(int, int)) {
  int fitPlaceHigh = 0;
  int fitValueHigh = 0;

  for (unsigned int x = 0; x < currPaths.size(); ++x) {
    int fit = fitness(&arrs, currPaths.at(x), x);
    if (x == 0 || compare(fit, fitValueHigh) > 0) {
      fitValueHigh = fit;
      fitPlaceHigh = x;
    }
  }

  std::vector<int> fitTop = currPaths.at(fitPlaceHigh);

  std::cout << "Top: " << fitValueHigh << std::endl;
  gen_trim_struct topFound;
  topFound.fitness = fitValueHigh;
  topFound.top = fitTop;

  return topFound;
}

std::vector<std::vector<int>> gen_base(std::vector<std::vector<int>> currPaths, std::vector<int> base) {
  for (unsigned int x = 0; x < base.size(); x++) {
    currPaths.push_back(base);
  }

  return currPaths;
}

float standard_deviation(std::vector<int> fitnesses) {
  float var = 0;
  float mean = 0;

  for (unsigned int n = 0; n < fitnesses.size(); ++n) {
    mean += fitnesses[n];
  }
  mean /= fitnesses.size();

  for (unsigned int n = 0; n < fitnesses.size(); n++) {
    var += (fitnesses[n] - mean) * (fitnesses[n] - mean);
  }
  var /= fitnesses.size();

  return sqrt(var);
}

void gen(std::vector<std::vector<int>> arrs, int compare(int, int)) {
  int groups = 15;
  int cycles = 50;

  std::vector<std::vector<std::vector<int>>> currPathsGroup;
  std::vector<int> base_path;

  if (arrs.size() == 0)
    return;

  for (unsigned int x = 0; x < arrs.size(); ++x) {
    base_path.push_back(0);
  }

  // init
  for (int x = 0; x < groups; ++x) {
    std::vector<std::vector<int>> currPaths;
    currPaths = gen_base(currPaths, base_path);

    currPathsGroup.push_back(currPaths);
  }

  for (int cycle = 0; cycle < cycles; ++cycle) {
    // mutate
    for (int x = 0; x < groups; ++x) {
      currPathsGroup.at(x) = gen_mutate(arrs, currPathsGroup.at(x));
    }

    // trim
    std::vector<int> endCondition;
    for (int x = 0; x < groups; ++x) {
      gen_trim_struct topGen = gen_trim(arrs, currPathsGroup.at(x), x, compare);

      currPathsGroup.at(x).clear();
      currPathsGroup.at(x) = gen_base(currPathsGroup.at(x), topGen.top);
    }

    /*for (auto x : currPathsGroup) {
      for (unsigned int i = 0; i < x.size(); ++i) {
        for (auto z : x.at(i)) {
          std::cout << z << ", ";
        }
      std::cout << std::endl;
      }
      std::cout << "_______________________" << std::endl;
    }*/

    std::cout << std::endl;
  }
}

int main() {
  srand (time(NULL));

  std::vector<int> arr1 = {100,153,622,906,759,562,  5,243, 91,362,730,253,383,361,423,219,987,747,492,991};
  std::vector<int> arr2 = {319,752,704,272,755,666,630,137,245,790,806,665,344,890, 58,953,819,554,358,529};
  std::vector<int> arr3 = {217,289,406,587,375,534,569,133,394,171,363,206,810,743, 15,654,669,437,392, 66};
  std::vector<int> arr4 = {209,230,250,779,280,892,783, 42,655,258,365,595,125,737,159,168,315, 89,717,285};
  std::vector<int> arr5 = {464,151,776,946,227,203,214,572,336,364, 85,925,728,635,504,588,924, 31,760,935};
  std::vector<int> arr6 = {295,537,582,395,714, 41, 49,402,508,377, 62,164,300,862,546,426,749,229,112,157};
  std::vector<int> arr7 = {856,114,260,328,984,460,558,796,501,267,542,990,117,893,591,899,510,805,321,866};

  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3, arr4, arr5, arr6, arr7};

  /*std::vector<int> arr1 = {1,0,0,0};
  std::vector<int> arr2 = {0,2,0,0};
  std::vector<int> arr3 = {0,0,3,0};
  std::vector<int> arr4 = {0,0,0,4};
  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3, arr4};*/

  gen(arrs, comp);

  test1();

  return 0;
 }
