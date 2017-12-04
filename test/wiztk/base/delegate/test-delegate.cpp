//
// Created by zhanggyb on 16-9-19.
//

#include "test-delegate.hpp"

#include "wiztk/base/delegate.hpp"

using namespace wiztk;
using namespace wiztk::base;

class Mockup {

 public:

  Mockup() : count_(0) {}

  virtual ~Mockup() {}

  int Foo(int param) {
    count_ = param;
    return count_;
  }

  int ConstFoo(int param) const {
    return count_;
  }

  virtual int VirtualFoo(int param) const {
    return param + count_;
  }

  int count() const { return count_; }

  static int Add(int a, int b) {
    return a + b;
  }

 private:

  int count_;

};

class MockupSub : public Mockup {

 public:

  MockupSub() : Mockup() {}

  virtual ~MockupSub() {}

  virtual int VirtualFoo(int param) const override {
    return param - count();
  }
};

TEST_F(TestDelegate, constructor1) {
  Mockup obj;
  Delegate<int(int)> d(&obj, &Mockup::Foo);
  ASSERT_TRUE(1 == d(1));
  ASSERT_TRUE(d.type() == kDelegateTypeMethod);
}

TEST_F(TestDelegate, constructor2) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
  ASSERT_TRUE(1 == d(1));
  ASSERT_TRUE(d.type() == kDelegateTypeMethod);
}

TEST_F(TestDelegate, constructor3) {
  Mockup obj;
  Delegate<int(int)> d(&obj, &Mockup::ConstFoo);
  ASSERT_TRUE(0 == d(1));
  ASSERT_TRUE(d.type() == kDelegateTypeMethod);
}

TEST_F(TestDelegate, constructor4) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::ConstFoo);
  ASSERT_TRUE(0 == d(1));
  ASSERT_TRUE(d.type() == kDelegateTypeMethod);
}

/*
 * Delegate to virtual
 */
TEST_F(TestDelegate, constructor5) {
  Mockup *obj = new MockupSub;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(obj, &Mockup::VirtualFoo);
  obj->Foo(1);  // count_ == 1

  int result = d(2);

  delete obj;

  ASSERT_TRUE(result == 1);
}

TEST_F(TestDelegate, constructor6) {
  Delegate<int(int, int)> d(Mockup::Add);

  int result = 0;
  result = d(1, 2);

  ASSERT_TRUE(result == 3);
}

TEST_F(TestDelegate, type_1) {
  Delegate<int(int)> d;
  ASSERT_TRUE(d.type() == kDelegateTypeUndefined);
}

/*
 *
 */
TEST_F(TestDelegate, compare1) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
// const not equal to non-const
  ASSERT_TRUE(d.Equal(&obj, &Mockup::Foo));
}

TEST_F(TestDelegate, compare2) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
// const not equal to non-const
  ASSERT_TRUE(!d.Equal(&obj, &Mockup::ConstFoo));
}

TEST_F(TestDelegate, compare3) {
  Mockup obj1;
  Delegate<int(int)> d1 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  Delegate<int(int)> d2 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  ASSERT_TRUE(d1 == d2);
}

TEST_F(TestDelegate, compare4) {
  Mockup obj1;
  Delegate<int(int)> d1 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::ConstFoo);
  Delegate<int(int)> d2 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  ASSERT_TRUE(d1 != d2);
}

TEST_F(TestDelegate, compare5) {
  Delegate<int(int, int)> d(Mockup::Add);

  ASSERT_TRUE(d.Equal(Mockup::Add));
}

TEST_F(TestDelegate, lambda_1) {
  auto d = Delegate<int(int, int)>::FromFunction(
      [](int x, int y) -> int {
        return x + y;
      }
  );

  ASSERT_TRUE(3 == d(1, 2));
  ASSERT_TRUE(d.type() == kDelegateTypeFunction);
}

TEST_F(TestDelegate, move_1) {
  Delegate<int(int, int)> d1(Mockup::Add);
  Delegate<int(int, int)> d2 = std::move(d1);

  ASSERT_TRUE((!d1) && d2);
}

TEST_F(TestDelegate, delegate_ref_1) {
  Mockup obj;

  Delegate<int(int)> d1(&obj, &Mockup::Foo);
  Delegate<int(int)> d2(&obj, &Mockup::ConstFoo);

  DelegateRef<int(int)> r1(d1);
  DelegateRef<int(int)> r2(d2);

  r1.Bind(&obj, &Mockup::Foo);
  r2.Bind(&obj, &Mockup::ConstFoo);

  ASSERT_TRUE(r1 && r2);

  bool result1 = r1.IsBoundTo(&obj, &Mockup::Foo);
  bool result2 = r2.IsBoundTo(&obj, &Mockup::ConstFoo);

  ASSERT_TRUE(result1 && result2);
  r1.Reset();
  r2.Reset();

  ASSERT_TRUE((!r1) && (!r2));
}