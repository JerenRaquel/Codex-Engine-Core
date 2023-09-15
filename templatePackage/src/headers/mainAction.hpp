#ifndef MAINACTION_HPP_
#define MAINACTION_HPP_

// Engine
#include "action.hpp"
#include "util/vector2.hpp"

class MainAction : public Action {
 private:
  // Base Class
  void InternalStart(Engine* const engine) noexcept override;
  void InternalUpdate(Engine* const engine) noexcept override;
  void InternalFinish(Engine* const engine) noexcept override;

 public:
  MainAction();
  ~MainAction();
};
#endif  // MAINACTION_HPP_