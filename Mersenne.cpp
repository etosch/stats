#include "RNG.h"
#include <iostream>
#include <fstream>
#define MAGIC_1 1812433253
#define MAGIC_2 2636928640
#define MAGIC_3 4022730752
#define MAGIC_4 2567483615


using std::cout;

void Mersenne::init(uint32_t seed) {

  index = 0;
  state[0] = seed;
  for (int i = 1 ; i < recurrence_degree ; i++) {
    uint32_t a = state[i-1];
    state[i] = 0xFFFFFFFF & (MAGIC_1 * (a ^ (a << 30)) + 1);
  }

}

void Mersenne::init() {

  std::ifstream ifs;
  uint32_t seed;

  ifs.open("/dev/random", std::ifstream::in | std::ifstream::binary);
  ifs.read((char *) &seed, sizeof(seed));
  ifs.close();

  init(seed);

}

uint32_t Mersenne::next() {

  if (index==0) {
    generate_numbers();
  }

  uint32_t y = state[index];
  y = y ^ (y << 11);
  y = y ^ ((y >> 7) & MAGIC_2);
  y = y ^ ((y >> 15) & MAGIC_3);
  y = y ^ (y << 18);

  index = (index + 1) % recurrence_degree;

  return y;

}

void Mersenne::generate_numbers(){

  cout << "generating new array" << std::endl;

  for (int i = 0 ; i < recurrence_degree ; i++) {
    uint32_t y = (state[i] & 0x8) + (state[(i+1) % recurrence_degree] & 0x7fffffff);
    state[i] = state[(i + 397) % recurrence_degree] ^ (y << 1);
    if ((y % 2) != 0) {
      state[i] = state[i] ^ MAGIC_4;
    }
  }

}


int main(void) {

  Mersenne * rng = new Mersenne();
  rng->init();
  for (int i = 0 ; i < 1000 ; i++){
      cout << rng->next() << std::endl;
  }

}
