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

int fit(std::vector<std::vector<int>> *arrs, std::vector<int> currPath, int pathNum) {
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

std::vector<std::vector<int>> gen_mutate(std::vector<std::vector<int>> arrs, std::vector<std::vector<int>> currPaths, std::vector<std::vector<std::vector<std::vector<bool>>>> *possibleCombinations) {
  // Loop through all arrays
  for (unsigned int x = 1; x < currPaths.size(); ++x) {
    // Loop through all current paths
    
    // Initiate all values to 1 at start to signify all following branches are possible
    // AND with possible values from follow branches. Resulting bool array will contain 1's everywhere a branch is possible
    // If all values are 0, tree is impossible, discard
    std::vector<bool> possibleBranchAcc(currPaths.at(x).size()-1, 1);

    for (unsigned int y = 0; y < currPaths.at(x).size(); ++y) {
      unsigned int toChange = rand() % arrs.at(y).size();
      unsigned int toChangeCheck = rand() % 100;

      std::vector<bool> *possibleBranch = NULL;

      if (y > 0)
        possibleBranch = &((*possibleCombinations)[y][currPaths.at(x).at(y-1)][y-1]);
      else
        possibleBranch = &possibleBranchAcc;

      for (unsigned int z = 0; z < (*possibleBranch).size(); ++z) {
        possibleBranchAcc[z] = possibleBranchAcc[z] & (*possibleBranch)[z];
        std::cout << possibleBranchAcc[z] << ", ";
      }
      std::cout << std::endl;

      // x percentage chance of mutation
      if (toChangeCheck < 100) {
        currPaths.at(x).at(y) = toChange;
      }
    }
    std::cout << std::endl;
  }

  return currPaths;
}

struct gen_trim_struct {
  std::vector<int> top;
  int fitness;
};

gen_trim_struct gen_trim(std::vector<std::vector<int>> arrs, std::vector<std::vector<int>> currPaths, int pathNum, int compare(int, int), int fitness(std::vector<std::vector<int>>*, std::vector<int>, int)) {
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

std::vector<std::vector<int>> gen_base(std::vector<std::vector<int>> currPaths, std::vector<int> base, int groupSize) {
  for (int x = 0; x < groupSize; x++) {
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

bool filt(int a, int b) {
  if (a == b)
    return false;
  return true;
}

void gen(std::vector<std::vector<int>> arrs, int compare(int, int), int fitness(std::vector<std::vector<int>>*, std::vector<int>, int), bool filter(int, int)) {
  int groups = 1;
  int cycles = 2;
  int groupSize = 2;

  std::vector<std::vector<std::vector<std::vector<bool>>>> possibleCombinations;

  for (unsigned int i = 0; i < arrs.size(); ++i) {
    std::vector<std::vector<std::vector<bool>>> possibleOuter;
    for (unsigned int j = 0; j < arrs.at(i).size(); ++j) {
      int curr = arrs[i][j];

      std::vector<std::vector<bool>> outer;
      for (unsigned int i2 = 0; i2 < arrs.size(); ++i2) {
        std::vector<bool> inner;
        for (unsigned int j2 = 0; j2 < arrs.at(i2).size(); ++j2) {
          inner.push_back(filter(curr, arrs[i2][j2]));
        }
        outer.push_back(inner);
        inner.clear();
      }
      possibleOuter.push_back(outer);
      outer.clear();
    }
    possibleCombinations.push_back(possibleOuter);
    possibleOuter.clear();
  }

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
    currPaths = gen_base(currPaths, base_path, groupSize);

    currPathsGroup.push_back(currPaths);
  }

  for (int cycle = 0; cycle < cycles; ++cycle) {
    // mutate
    for (int x = 0; x < groups; ++x) {
      currPathsGroup.at(x) = gen_mutate(arrs, currPathsGroup.at(x), &possibleCombinations);
    }

    for (auto x : currPathsGroup) {
      for (unsigned int i = 0; i < x.size(); ++i) {
        for (auto z : x.at(i)) {
          std::cout << z << ", ";
        }
      std::cout << std::endl;
      }
      std::cout << "_______________________" << std::endl;
    }

    // trim
    std::vector<int> endCondition;
    for (int x = 0; x < groups; ++x) {
      gen_trim_struct topGen = gen_trim(arrs, currPathsGroup.at(x), x, compare, fitness);

      currPathsGroup.at(x).clear();
      currPathsGroup.at(x) = gen_base(currPathsGroup.at(x), topGen.top, groupSize);
    }

    std::cout << std::endl;
  }
  //std::cout << possibleCombinations[1][1][1].size() << std::endl;

}

int main() {
  srand (time(NULL));

  /*std::vector<int> arr1 = {153,622,906,759,562,5 ,243, 91,362,730,253,383,361,423,219,987,747,492,991};
  std::vector<int> arr2 = {319,752,704,272,755,666,630,137,245,790,806,665,344,890, 58,953,819,554,358,529};
  std::vector<int> arr3 = {217,289,406,587,375,534,569,133,394,171,363,206,810,743, 15,654,669,437,392, 66};
  std::vector<int> arr4 = {209,230,250,779,280,892,783, 42,655,258,365,595,125,737,159,168,315, 89,717,285};
  std::vector<int> arr5 = {464,151,776,946,227,203,214,572,336,364, 85,925,728,635,504,588,924, 31,760,935};
  std::vector<int> arr6 = {295,537,582,395,714, 41, 49,402,508,377, 62,164,300,862,546,426,749,229,112,157};
  std::vector<int> arr7 = {856,114,260,328,984,460,558,796,501,267,542,990,117,893,591,899,510,805,321,866};

  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3, arr4, arr5, arr6, arr7};*/

  std::vector<int> arr1 = {1,0};
  std::vector<int> arr2 = {0,2};
  std::vector<int> arr3 = {0,0};
  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3};

  gen(arrs, comp, fit, filt);

  //test1();

  return 0;
 }
