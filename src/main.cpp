#include <cassert>
#include <iostream>

#include "AnalogPoint.hpp"
#include "Rules.hpp"

// Example usage
int main() {
    apl::AnalogPoint analogPoint{10};
    analogPoint.value_ = 0.0;
    analogPoint.AddUpperBoundary(10);
    analogPoint.AddLowerBoundary(-10);
    auto state = analogPoint.GetAlarmState();
    assert(!state);

    analogPoint.value_ = 10.0;
    state = analogPoint.GetAlarmState();
    assert(state);
    std::cout << state.GetBrokenRule()->GetFailDescription() << '\n';

    analogPoint.value_ = -10.0;
    assert(analogPoint.GetAlarmState());
    state = analogPoint.GetAlarmState();
    assert(state);
    std::cout << state.GetBrokenRule()->GetFailDescription() << '\n';

    analogPoint.value_ = 9.9;
    assert(!analogPoint.GetAlarmState());
    analogPoint.value_ = -9.9;
    assert(!analogPoint.GetAlarmState());

    return 0;
}
