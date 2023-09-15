#ifndef GLOBALACTION_HPP_
#define GLOBALACTION_HPP_

// Engine
#include "action.hpp"
#include "util/vector2.hpp"

class GlobalAction : public Action {
 private:
  // Base Class
  void InternalStart(Engine* const engine) noexcept override;
  void InternalUpdate(Engine* const engine) noexcept override;
  void InternalFinish(Engine* const engine) noexcept override;

 public:
  GlobalAction();
  ~GlobalAction();
};
#endif  // GLOBALACTION_HPP_