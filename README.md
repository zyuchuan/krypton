# krypton

In C++ programming world, when you define a variable, you define its type and its value, for example:

```c++
int i = 0;  // type is int, value is zero
```

But, in real world, every quantity comes with three properties: type, value, and dimension. such as:

```c++
5.3 meters  // type is double, value is 5.3, dimension is length
```

The gold of krypton is to narrow down the gap between programming world and real world.

Krypton is a C++ dimension calculation library inspired by [chrono](en.cppreference.com/w/cpp/header/chrono).

In krypton, you should be able to do this:

```c++
velocity<double> v{5.0}   // v's type is double, vlaue is 5.0, and dimension is velocity, or "merter/second"
second<int> t{5}          // t's type is int, value is 5, dimension is second
kilogram k = v * t        // this won't compile, because k's dimension is kilogram,
                          // but dimension of v * t is meter, becasue distance = velocity * time
```

This is what I call it "dimension calculation".

We can do more:

```c++
feet f = v * t          // automatically convert meter to feet
kilometer km = v * t    // automatically convert meter to kilometer
```

This is possible, because there are only **seven** dimensions in this world: *meter*, *kilogram*, *second*, *ampere*, *kelvins*...

Dimension calculation should be done at compile time so it won't impact the run time performance.
     

