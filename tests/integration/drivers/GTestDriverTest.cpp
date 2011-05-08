#include <gtest/gtest.h>
#include <cukebins/cukebins.hpp>

#include "../../utils/DriverTestRunner.hpp"

THEN(SUCCEED_MATCHER) {
    USING_CONTEXT(cukebins::internal::SomeContext, ctx);
    ASSERT_TRUE(true);
}

THEN(FAIL_MATCHER) {
    USING_CONTEXT(cukebins::internal::SomeContext, ctx);
    ASSERT_TRUE(false);
}

THEN(PENDING_MATCHER_1) {
    pending();
}

THEN(PENDING_MATCHER_2) {
    pending(PENDING_DESCRIPTION);
}

using namespace cukebins::internal;

class GTestStepDouble : public GTestStep {
public:
    bool isInitialized() {
        return GTestStep::initialized;
    }

    const InvokeResult invokeStepBody() {
        return GTestStep::invokeStepBody();
    };

    void body() {};
};

class GTestDriverTest : public DriverTest {
public:
    virtual void runAllTests() {
        stepInvocationInitsGTest();
        DriverTest::runAllTests();
    }

private:
    void stepInvocationInitsGTest() {
        GTestStepDouble step;
	expectFalse(step.isInitialized());
	step.invokeStepBody();
        expectTrue(step.isInitialized());
    }
};

int main() {
    GTestDriverTest test;
    return test.run();
}
