//
// Copyright 2020 Santanu Sen. All Rights Reserved.
//
// Licensed under the Apache License 2.0 (the "License").  You may not use
// this file except in compliance with the License.  You can obtain a copy
// in the file LICENSE in the source distribution.
//

#include "turing_defs.hpp"
#include "turing_rule.hpp"
#include "turing_tape.hpp"

namespace Turing {
enum turing_machine_status_t { READY, RUNNING, FAILED, HALTED };

template <typename symbol_t = default_symbol_t> class turing_machine_t {

private:
  const turing_rules_table_t<symbol_t> &mRules;

  turing_tape_t<symbol_t> &mTape;

  state_t mState;

  const state_t mEndState;

  turing_machine_status_t mStatus;

public:
  turing_machine_t(const turing_rules_table_t<symbol_t> &rules,
                   turing_tape_t<symbol_t> &tape, state_t start_state,
                   state_t end_state)
      : mRules(rules), mTape(tape), mState(start_state), mEndState(end_state),
        mStatus(READY) {}

  auto get_state() const { return mState; }

  auto get_status() const { return mStatus; }

  void run() {
    mStatus = RUNNING;

    while (mState != mEndState) {
      auto sym = mTape.read();
      auto rule = mRules.find(turing_rules_key_t<symbol_t>(mState, sym));
      if (rule == mRules.end()) {
        mStatus = FAILED;
        return;
      }
      mTape.write(rule->second.mNewSymbol);
      mTape.move_head(rule->second.mDir);
      mState = rule->second.mNewState;
    }

    mStatus = HALTED;
  }
};

typedef turing_machine_t<> machine_t;
} // namespace Turing
