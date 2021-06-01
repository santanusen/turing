//
// Copyright 2020 Santanu Sen. All Rights Reserved.
//
// Licensed under the Apache License 2.0 (the "License").  You may not use
// this file except in compliance with the License.  You can obtain a copy
// in the file LICENSE in the source distribution.
//

#include <turing/turing_machine.hpp>

// Rules to flip alternate bits
const Turing::rules_table_t &flip_alt_rule_table() {
  static Turing::rules_table_t rt;

  if (rt.empty()) {
    rt += Turing::rule_t(0, '0', '0', Turing::Right, 1);
    rt += Turing::rule_t(0, '1', '1', Turing::Right, 1);
    rt += Turing::rule_t(0, '\0', '\0', Turing::Right, 2);
    rt += Turing::rule_t(1, '0', '1', Turing::Right, 0);
    rt += Turing::rule_t(1, '1', '0', Turing::Right, 0);
    rt += Turing::rule_t(1, '\0', '\0', Turing::Right, 2);
  }

  return rt;
}

int main() {
	//std::cout << flip_alt_rule_table() << std::endl;

	Turing::tape_t tp;
	// Initialie the tape with some 1's and 0's.
	for (auto i = 0; i < 4; ++i) {
		tp.write('1');
		tp.move_head(Turing::Right);
		tp.write('0');
		tp.move_head(Turing::Right);
		tp.write('1');
		tp.move_head(Turing::Right);
	}
	tp.reset_head();

	std::cout << "Input:  " << tp << std::endl;

	// Flip alternate bits in tape using Turing machine.
	Turing::machine_t tm(flip_alt_rule_table(), tp, 0, 2);
	tm.run();

	std::cout << "Output: " << tp << std::endl;

  return 0;
}
