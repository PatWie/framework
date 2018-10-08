/*
 * Copyright 2017 - 2018 The WizTK Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "thread/private.hpp"

#include <stdexcept>

namespace wiztk {
namespace system {
namespace threading {

Thread::ID Thread::ID::GetCurrent() {
  ID id;
  id.native_ = pthread_self();
  return id;
}

// -----

/**
 * @brief A helper class to set/get low-level thread attributes.
 */
class WIZTK_NO_EXPORT Thread::Attribute {
  friend class Thread;

 public:

  WIZTK_DECLARE_NONCOPYABLE_AND_NONMOVALE(Attribute);

  enum DetachStateType {
    kCreateDetached = PTHREAD_CREATE_DETACHED,
    kCreateJoinable = PTHREAD_CREATE_JOINABLE
  };

  enum ScopeType {
    kSystem = PTHREAD_SCOPE_SYSTEM,
    kProcess = PTHREAD_SCOPE_PROCESS
  };

  enum SchedulerType {
    kInheritSched = PTHREAD_INHERIT_SCHED,
    kExplicitSched = PTHREAD_EXPLICIT_SCHED
  };

  Attribute();

  ~Attribute();

  void SetDetachState(DetachStateType state_type);

  DetachStateType GetDetachState() const;

  void SetScope(ScopeType scope_type);

  ScopeType GetScope() const;

  void SetStackSize(size_t stack_size);

  size_t GetStackSize() const;

  const pthread_attr_t *data() const { return &native_; }

 private:

  pthread_attr_t native_;

};

// -------

const Thread::DelegateDeleter Thread::kDefaultDelegateDeleter = [](Delegate *obj) {
  delete obj;
};

const Thread::DelegateDeleter Thread::kLeakyDelegateDeleter = [](Delegate *obj) {
  // WARNING: do nothing!
};

Thread::Thread() {
  p_ = std::make_unique<Private>();
}

Thread::Thread(Delegate *delegate, const DelegateDeleter &deleter) {
  p_ = std::make_unique<Private>(delegate, deleter);
}

Thread::Thread(const Options &options) {
  p_ = std::make_unique<Private>(options);
}

Thread::Thread(Thread &&other) noexcept {
  p_ = std::move(other.p_);
}

Thread::~Thread() {
  Stop();
}

Thread &Thread::operator=(Thread &&other) noexcept {
  p_ = std::move(other.p_);
  return *this;
}

void Thread::Start() {
  typedef void *(*fn)(void *);
  int ret = 0;

  Attribute attr;

  p_->options.joinable ? attr.SetDetachState(Attribute::kCreateJoinable)
                       : attr.SetDetachState(Attribute::kCreateDetached);

  if (p_->options.stack_size > 0) attr.SetStackSize(p_->options.stack_size);

  ret = pthread_create(&p_->id.native_,
                       attr.data(),
                       reinterpret_cast<fn>(Thread::Private::StartRoutine),
                       this);

  if (ret != 0) throw std::runtime_error("Error! Fail to start a thread!");
}

void Thread::Start(const Options &options) {
  // TODO: implement this method
}

void Thread::Stop() {
  if (p_->state == kRunning)
    pthread_cancel(p_->id.native_);
}

void Thread::Join() {
  if (0 != pthread_join(p_->id.native_, nullptr))
    throw std::runtime_error("Error! Fail to join a thread!");

  p_->id.native_ = pthread_self();
}

void Thread::Detach() {
  if (0 != pthread_detach(p_->id.native_))
    throw std::runtime_error("Error! Fail to detach a thread!");
}

const Thread::ID &Thread::GetID() const {
  return p_->id;
}

Thread *Thread::GetCurrent() {
  return Specific::kPerThreadStorage.Get()->thread;
}

void Thread::Run() {
  // Override in subclass
}

// ----

void Thread::Delegate::Run() {
  // Override in subclass
}

// ----

bool operator==(const Thread::ID &id1, const Thread::ID &id2) {
  return 0 != pthread_equal(id1.native_, id2.native_);
}

bool operator!=(const Thread::ID &id1, const Thread::ID &id2) {
  return 0 == pthread_equal(id1.native_, id2.native_);
}

// -----

Thread::Attribute::Attribute() {
  if (0 != pthread_attr_init(&native_))
    throw std::runtime_error("Error! Cannot initialize thread attribute!");
}

Thread::Attribute::~Attribute() {
  pthread_attr_destroy(&native_);
}

void Thread::Attribute::SetDetachState(DetachStateType state_type) {
  if (0 != pthread_attr_setdetachstate(&native_, state_type))
    throw std::runtime_error("Error! Cannot set detach state!");
}

Thread::Attribute::DetachStateType Thread::Attribute::GetDetachState() const {
  int val = 0;

  if (0 != pthread_attr_getdetachstate(&native_, &val))
    throw std::runtime_error("Error! Cannot get detach state!");

  return static_cast<DetachStateType>(val);
}

void Thread::Attribute::SetScope(ScopeType scope_type) {
  if (0 != pthread_attr_setscope(&native_, scope_type))
    throw std::runtime_error("Error! Cannot set scope!");
}

Thread::Attribute::ScopeType Thread::Attribute::GetScope() const {
  int val = 0;

  if (0 != pthread_attr_getscope(&native_, &val))
    throw std::runtime_error("Error! Cannot get scope!");

  return static_cast<ScopeType>(val);
}

void Thread::Attribute::SetStackSize(size_t stack_size) {
  if (0 != pthread_attr_setstacksize(&native_, stack_size))
    throw std::runtime_error("Error! Cannot set stack size!");
}

size_t Thread::Attribute::GetStackSize() const {
  size_t stack_size = 0;

  if (0 != pthread_attr_getstacksize(&native_, &stack_size))
    throw std::runtime_error("Error! Cannot get stack size!");

  return stack_size;
}

}  // namespace threading
}  // namespace system
}  // namespace wiztk
