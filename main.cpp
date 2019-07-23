#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>

#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "mcr.h"

int comp(int in1, int in2) {
  return -in1+in2;
}

int fit(std::vector<std::vector<void*>> *arrs, std::vector<int> currPath, int pathNum) {
  int acc = 0;
  for (unsigned int x = 0; x < currPath.size(); ++x) {
    acc += *(int*)(arrs->at(x)[currPath.at(x)]);
  }
  return acc;
}

bool filt(void* a, void* b, int aPlace, int bPlace) {
  if (*(int*)a == *(int*)b || (*(int*)a < *(int*)b && aPlace < bPlace))
    return false;
  return true;
}

int main() {
  srand (time(NULL));
  
  //                         0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
  std::vector<int> arr1 = {153,622,906,759,562,5  ,243, 91,362,730,253,383,361,423,219,987,747,492,991};
  std::vector<int> arr2 = {319,752,704,272,755,666,630,137,253,790,806,665,344,890, 58,990,819,554,358,991};
  std::vector<int> arr3 = {217,289,406,587,375,534,569,133,394,171,363,206,810,743, 15,654,669,437,392, 66};
  std::vector<int> arr4 = {409,10,250,779,280,991,783, 42,655,258,365,595,125,737,159,168,315, 89,717,285};
  std::vector<int> arr5 = {464,151,776,946,227,203,214,572,336,364, 85,925,728,635,504,588,924, 31,760,935};
  std::vector<int> arr6 = {295,537,582,395,714, 41, 49,402,508,377, 62,164,300,862,546,426,749,229,112,157};
  std::vector<int> arr7 = {856,114,260,328,984,460,558,796,501,267,542,990,117,893,591,899,510,805,321,866};
  std::vector<int> arr8 = {857,115,261,327,983,461,559,797,502,268,543,991,118,894,592,898,511,804,320,867,910,920};

  // 7553
  // 15, 15, 12, 5, 3, 13, 4, 4

  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8};

  std::vector<void*> inner;
  std::vector<std::vector<void*>> outer;

  for (int x = 0; x < arrs.size(); ++x) {
    inner.clear();
    for (int y = 0; y < arrs.at(x).size(); ++y) {
      inner.push_back(&arrs.at(x).at(y));
    }
    outer.push_back(inner);
  }

  /*std::vector<int> arr1 = {1,0,5};
  std::vector<int> arr2 = {0,2,0,5};
  std::vector<int> arr3 = {0,0,0,0};

  std::vector<std::vector<int>> arrs = {arr1, arr2, arr3};*/

  gen(outer, comp, fit, filt);

  //test1();

  return 0;
 }
