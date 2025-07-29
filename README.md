# Purpose

This repository contains a possible implementation of 'Rule' system that are applied to 'Alarm points' to create an alarm state. 

The target of this repository is to provide users an interface where they can:

1. Create their own static rules (e.g. `Point1.Greater(100) or Point2.Less(40)`)
2. Create dynamic rules that rely on other points (e.g. `Point1.Less(Point2) or Point2.Equal(Multiply(Point2, 2))`)  
3. Combine rules into complex ones (e.g. `Point1.Less(-10) || Point1.Less(5)`)
4. Apply rules to a point to create an 'Alarm state' (e.g. `Point1.AddRule(...)`)
5. Create a handler for when alarm state is broken (e.g. `Point1.SetHandler(...)`)

To achieve this there still lots of work to do, so any contribution welcome.