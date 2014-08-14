#include <stdint.h>

class RNG {

 public:
  
  virtual uint32_t next() = 0;
  virtual void init(uint32_t seed) = 0;
  virtual void init() = 0;

};

class Mersenne : public RNG {

  static const uint32_t recurrence_degree = 624;
  uint32_t index = 0;
  uint32_t state[recurrence_degree];

  void generate_numbers();

 public:
  virtual uint32_t next();
  virtual void init(uint32_t seed);
  virtual void init();  


};
