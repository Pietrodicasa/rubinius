#include "interpreter/instructions.hpp"

#include "class/call_site.hpp"

namespace rubinius {
  namespace instructions {
    inline bool send_stack(STATE, CallFrame* call_frame, intptr_t literal, intptr_t count) {
      Object* recv = stack_back(count);
      CallSite* call_site = reinterpret_cast<CallSite*>(literal);

      Arguments args(call_site->name(), recv, cNil, count,
                     stack_back_position(count));

      Object* ret = call_site->execute(state, args);

      stack_clear(count + 1);

      state->vm()->checkpoint(state);

      CHECK_AND_PUSH(ret);
    }
  }
}
