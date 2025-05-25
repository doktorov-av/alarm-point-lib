#include <cassert>
#include <iostream>

#include "AnalogPoint.hpp"
#include "Rules.hpp"

// Example usage
int main() {
    apl::AnalogPoint analogPoint{10};
    analogPoint.value = 0.0;
    analogPoint.AddUpperBoundary(10);
    analogPoint.AddLowerBoundary(-10);
    assert(!analogPoint.InAlarm());

    analogPoint.value = 10.0;
    assert(analogPoint.InAlarm());
    analogPoint.value = -10.0;
    assert(analogPoint.InAlarm());

    analogPoint.value = 9.9;
    assert(!analogPoint.InAlarm());
    analogPoint.value = -9.9;
    assert(!analogPoint.InAlarm());

    return 0;
}
