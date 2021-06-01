//
// Copyright 2020 Santanu Sen. All Rights Reserved.
//
// Licensed under the Apache License 2.0 (the "License").  You may not use
// this file except in compliance with the License.  You can obtain a copy
// in the file LICENSE in the source distribution.
//

#include <turing/turing_machine.hpp>

const Turing::rules_table_t &turing_add_rule_table() {
  static Turing::rules_table_t rt;

  if (rt.empty()) {
	  rt += Turing::rule_t(0, 'A', 'C', Turing::Right, 0);
	  rt += Turing::rule_t(0, 'B', 'C', Turing::Right, 0);
	  rt += Turing::rule_t(0, '\0', '\0', Turing::Left, 1);
  }

  return rt;
}

// Add two unsigned integers using turing machine.
unsigned int turing_add(unsigned int a, unsigned int b) {
  Turing::tape_t tp;
  for (unsigned int i = 0; i < a; ++i) {
    tp.write('A');
    tp.move_head(Turing::Right);
  }
  for (unsigned int i = 0; i < b; ++i) {
    tp.write('B');
    tp.move_head(Turing::Right);
  }

  tp.reset_head();

  auto& rt = turing_add_rule_table();

  Turing::machine_t tm(rt, tp, 0, 2);
  tm.run();

  tp.reset_head();

  unsigned int res = 0;
  do {
    if (tp.read() == 'C')
      ++res;
  } while (tp.move_head(Turing::Right, false));

  return res;
}

int main() {
  int x = 10, y = 20;
  std::cout << x << " + " << y << " = " << turing_add(10, 20) << std::endl;
  return 0;
}
