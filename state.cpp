#include"state.h"

// since ids of the States are unique, we can just sort it by id.
bool operator<(const State& s1, const State& s2){
  return s1.get_id() < s2.get_id();
}