#ifndef DATAPACK_H
#define DATAPACK_H

// Data Structure
class DataPack {
  public:
    short s1, s2, s3, s4;
    double d1;

    // Constructor 1
    DataPack() {
      // Nothing here
    };

    // Constructor 2
    DataPack(short a, short b, short c, short d, double e) {
      s1 = a;
      s2 = b;
      s3 = c;
      s4 = d;
      d1 = e;
    };

    ~DataPack() {
      // Nothing here
    };
};

#endif
