#include <iostream>
#include <vector>

class Offering {
  public:
    bool *day;

    int time_start;
    int time_end;

  Offering(int a, int b, bool *c) {
    time_start = a;
    time_end = b;
    day = c;
  }

  std::string toString() {
    std::string acc = std::to_string(time_start) + " -> " + std::to_string(time_end) + " : [";
    for (int x = 0; x < 5; ++x) {
      acc += std::to_string(day[x]) + ", ";
    }

    acc[acc.size()-1] = ']';

    return acc;
  }
};

class Section {
  public:
    // Json::Value thisSection; // Write this back if used
    double instructorRating;

    std::vector<Offering*> *offerings;

    Section(std::vector<Offering*> *a) {
      offerings = a;
    }

    std::string toString() {
      std::string acc = "";
      for (auto x : *offerings) {
        acc += x->toString() + '\n';
      }

      return acc;
    }
};

class Course {
  public:
    std::vector<Section> *sections;

    Course(std::vector<Section> *s) {
      sections = s;
    }

    std::string toString() {
      std::string acc = "";
      for (auto x : *sections) {
        acc += x.toString();
      }

      acc += "\n";

      return acc;
    }
};



Course test1() {
  bool a[5] = {1,0,1,0,1};
  bool b[5] = {1,1,0,1,0};
  bool c[5] = {1,0,1,0,1};
  bool d[5] = {0,1,0,1,0};
  
  Offering a1  = Offering(830, 850, a);
  Offering a2  = Offering(1000, 1000+20, a);
  Offering a3  = Offering(1130, 1130+20, a);
  Offering a4  = Offering(1400, 1400+20, a);
  
  Offering b1  = Offering(830, 850, b);
  Offering b2  = Offering(930, 930+20, b);
  Offering b3  = Offering(1330, 1330+20, b);

  Offering c1  = Offering(1000, 1000+20, c);
  Offering c2  = Offering(1030, 1030+20, c);
  Offering c3  = Offering(1330, 1330+20, c);
  Offering c4  = Offering(1700, 1700+20, c);

  Offering d1  = Offering(900, 900+20, d);
  Offering d2  = Offering(1030, 1030+20, d);
  Offering d3  = Offering(1230, 1230+20, d);
  Offering d4  = Offering(1430, 1430+20, d);
  Offering d5  = Offering(1530, 1530+20, d);
  Offering d6  = Offering(1700, 1700+20, d);

  std::vector<Offering> oa = {a1,a2,a3,a4};
  std::vector<Offering> ob = {b1,b2,b3};
  std::vector<Offering> oc = {c1,c2,c3,c4};
  std::vector<Offering> od = {d1,d2,d3,d4,d5,d6};

  std::vector<Section> sa;
  std::vector<Section> sb;
  std::vector<Section> sc;
  std::vector<Section> sd;

  for (unsigned int x = 0; x < oa.size(); ++x) {
    std::vector<Offering*> *aa = new std::vector<Offering*>;
    aa->push_back(&oa[x]);
    sa.push_back(Section(aa));
  }

  for (unsigned int x = 0; x < ob.size(); ++x) {
    std::vector<Offering*> *bb = new std::vector<Offering*>;
    bb->push_back(&ob[x]);
    sb.push_back(Section(bb));
  }

  for (unsigned int x = 0; x < oc.size(); ++x) {
    std::vector<Offering*> *aa = new std::vector<Offering*>;
    aa->push_back(&oc[x]);
    sc.push_back(Section(aa));
  }

  for (unsigned int x = 0; x < od.size(); ++x) {
    std::vector<Offering*> *aa = new std::vector<Offering*>;
    aa->push_back(&od[x]);
    sd.push_back(Section(aa));
  }

  Course ca = Course(&sa);
  Course cb = Course(&sb);
  Course cc = Course(&sc);
  Course cd = Course(&sd);

  std::cout << ca.toString() << std::endl;
  std::cout << cb.toString() << std::endl;
  std::cout << cc.toString() << std::endl;
  std::cout << cd.toString() << std::endl;

}
