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

#include "thread_private.hpp"

namespace wiztk {
namespace system {
namespace threading {

ThreadLocal<Thread> Thread::Private::kPerThreadStorage;

Thread::ID Thread::Private::kMainThreadID;

void *Thread::Private::StartRoutine(Thread *thread) {
  kPerThreadStorage.Set(thread);

  if (thread->p_->delegate) thread->p_->delegate->Run();
  else thread->Run();

  kPerThreadStorage.Set(nullptr);
  pthread_exit((void *) thread);
}

}
}
}