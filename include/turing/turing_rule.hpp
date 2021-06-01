//
// Copyright 2020 Santanu Sen. All Rights Reserved.
//
// Licensed under the Apache License 2.0 (the "License").  You may not use
// this file except in compliance with the License.  You can obtain a copy
// in the file LICENSE in the source distribution.
//

#pragma once

#include <iostream>
#include <map>
#include <tuple>

#include "turing_defs.hpp"

namespace Turing {
template <typename symbol_t> class turing_rules_key_t {

public:
  state_t mState;

  symbol_t mSymbol;

  turing_rules_key_t(state_t st, symbol_t sym) : mState(st), mSymbol(sym) {}

  inline bool operator<(const turing_rules_key_t &rhs) const {
    return (mState < rhs.mState ||
            (mState == rhs.mState && mSymbol < rhs.mSymbol));
  }
};

template <typename symbol_t>
inline std::ostream &operator<<(std::ostream &os,
                                const turing_rules_key_t<symbol_t> &trk) {
  return (os << trk.mState << " " << trk.mSymbol);
}

template <typename symbol_t> class turing_rules_val_t {

public:
  symbol_t mNewSymbol;

  direction_t mDir;

  state_t mNewState;

  turing_rules_val_t(symbol_t newsym = symbol_t(), direction_t dir = Right,
                     state_t newst = 0)
      : mNewSymbol(newsym), mDir(dir), mNewState(newst) {}
};

template <typename symbol_t>
inline std::ostream &operator<<(std::ostream &os,
                                const turing_rules_val_t<symbol_t> &trv) {
  return (os << trv.mNewSymbol << " " << (trv.mDir == Left ? "L" : "R") << " "
             << trv.mNewState);
}

template <typename symbol_t = default_symbol_t>
using turing_rules_table_t =
    std::map<turing_rules_key_t<symbol_t>, turing_rules_val_t<symbol_t>>;

template <typename symbol_t>
inline std::ostream &operator<<(std::ostream &os,
                                const turing_rules_table_t<symbol_t> tbl) {
  for (const auto &kvp : tbl)
    os << kvp.first << " : " << kvp.second << std::endl;
  return os;
}

template <typename symbol_t = default_symbol_t>
using turing_rule_t =
    std::tuple<state_t, symbol_t, symbol_t, direction_t, state_t>;

template <typename symbol_t>
inline void operator+=(turing_rules_table_t<symbol_t> &tbl,
                       const turing_rule_t<symbol_t> &rule) {
  tbl[turing_rules_key_t<symbol_t>(std::get<0>(rule), std::get<1>(rule))] =
      turing_rules_val_t<symbol_t>(std::get<2>(rule), std::get<3>(rule),
                                   std::get<4>(rule));
}

typedef turing_rules_table_t<> rules_table_t;
typedef turing_rule_t<> rule_t;

} // namespace Turing
