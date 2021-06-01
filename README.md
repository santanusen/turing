Turing
======
A C++ Header Only, Easy to Use, Turing Machine

**How to Use**
- **Step 1: Include header:**
```
#include <turing/turing_machine.hpp>
```
- **Step 2: Create a rule table:**
```
Turing::rules_table_t rt;
```
Add some rules:
```
/*                  (current_state, symbol_at_tape_head,    new_symbol_to_write, move_head_to, new_state) */
rt += Turing::rule_t(0,             'A',                    'C',                 Turing::Right, 0);
rt += Turing::rule_t(0,             'B',                    'C',                 Turing::Right, 0);
rt += Turing::rule_t(0,             '\0',                   '\0',                Turing::Left,  1);
```
- **Step 3: Initialize the tape:**
```
Turing::tape_t tp;
```
Write some symbols to the tape:
```
tp.write('A');
tp.move_head(Turing::Right);
tp.write('B');
tp.move_head(Turing::Right);
```
Adjust tape head to where you want it to be.
```
tp.reset_head();
```
- **Step 4: Create the Turing machine:**
```
/* Rules table: rt, Tape: tp, Initial state: 0, Stop at state: 2 */
Turing::machine_t tm(rt, tp, 0, 2);
```
- **Step 5: Fire:**
```
tm.run();
```
Check what's on tape
```
cout << tp << endl;
```

It's that easy to use !!!
