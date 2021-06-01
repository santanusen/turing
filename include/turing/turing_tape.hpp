//
// Copyright 2020 Santanu Sen. All Rights Reserved.
//
// Licensed under the Apache License 2.0 (the "License").  You may not use
// this file except in compliance with the License.  You can obtain a copy
// in the file LICENSE in the source distribution.
//

#pragma once

#include "turing_defs.hpp"

#include <iostream>
#include <list>

namespace Turing {

template <typename symbol_t = default_symbol_t> class turing_tape_t {

private:
  std::list<symbol_t> mTape;

  typename std::list<symbol_t>::iterator mHead;

  bool move_left(bool expand) {
    if (mHead == mTape.begin()) {
      if (!expand) {
        return false;
      }
      mTape.push_front(symbol_t());
    }
    --mHead;
    return true;
  }

  bool move_right(bool expand) {
    auto headNext = mHead;
    ++headNext;
    if (headNext == mTape.end()) {
      if (!expand) {
        return false;
      }
      mTape.push_back(symbol_t());
    }
    ++mHead;

    return true;
  }

public:
  turing_tape_t() {
    mTape.push_back(symbol_t());
    mHead = mTape.begin();
  }

  symbol_t read() const { return *mHead; }

  void write(symbol_t sym) {
    *mHead = sym;
  }

  bool move_head(direction_t dir, bool expand = true) {
    switch (dir) {
    case Left:
      return move_left(expand);

    case Right:
      return move_right(expand);

    default:
      return false;
    }
  }

  void reset_head() { mHead = mTape.begin(); }

  template <typename sym_t>
  friend std::ostream &operator<<(std::ostream &os,
                                  const turing_tape_t<sym_t> &tp);
};

template <typename symbol_t>
std::ostream &operator<<(std::ostream &os, const turing_tape_t<symbol_t> &tp) {
  for (const auto &sym : tp.mTape)
    os << sym << " ";
  return os;
}

typedef turing_tape_t<> tape_t;
} // namespace Turing
