# krypton

In C++ programming world, when you define a variable, you define its type and its value, e.g.

```c++
int i = 0;  // type of i is integer, value is 0
```

However, in real world, every quantity comes with four properties: `type`, `value`, `dimension` and `unit`. Such as, when we say: "*the length of the wall is 5.3 meters*", we literally define a quantity with **value** equals `5.3`, we also specify its **type** is `float point value`, its **dimension** is `length`, and this dimension is described by **unit** `meter`.

Ideally when we define a varable in programming world, we would have wanted to defined it with four properties determined, as we do in real world. Unfortunatelly computer, in essence, is just a numerical computing device, it's difficult to make it understand complex concepts, like **Dimension** or **Unit**.

The goal of krypton is to fill the gap between programming world and real world.

Krypton is a C++ dimension calculation library inspired by [chrono](en.cppreference.com/w/cpp/header/chrono).

In krypton, you should be able to do this:

```c++
velocity<double> v{5.0}   // v's type is double, vlaue is 5.0, and dimension is velocity, metric is "merter/second"
second<int> t{5}          // t's type is int, value is 5, dimension is time, metric is second

kilogram<double> kilo = v * t        // this won't compile, because k's dimension is kilogram,
                                     // but dimension of v * t is meter (velocity * time = distance)
                          
meter<double> m = v * t          // this is OK becasue distance = velocity * time                           
feet<double> f = v * t           // this is OK because feet and meter share are actually in same dimension
kilometer<double> km = v * t     // automatically convert meter to kilometer
```

This is what I call it "dimension calculation".

This is possible, because there are only **seven** dimensions in this world: *meter*, *kilogram*, *second*, *ampere*, *kelvins*...

Dimension calculation should be done at compile time so it won't impact the run time performance.
     

