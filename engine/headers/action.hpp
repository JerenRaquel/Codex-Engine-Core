#ifndef ACTION_HPP_
#define ACTION_HPP_

// Custom
#include "engine.hpp"

class Action {
 protected:
  virtual void InternalStart(Engine* const engine) noexcept = 0;
  virtual void InternalUpdate(Engine* const engine) noexcept = 0;
  virtual void InternalFinish(Engine* const engine) noexcept = 0;

 public:
  Action();
  virtual ~Action();

  void OnStart(Engine* const engine) noexcept;
  void OnUpdate(Engine* const engine) noexcept;
  void OnFinish(Engine* const engine) noexcept;
};
#endif  // ACTION_HPP_