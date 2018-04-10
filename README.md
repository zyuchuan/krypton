# krypton

In C++ programming world, when you define a variable, you define its type and its value, e.g.

```c++
int i = 0;  // type of i is integer, value is 0
```

However, in real world, every quantity comes with four properties: `type`, `value`, `dimension` and `unit`. Such as, when we say: 

```c++
the length of the wall is 5.3 meters
```
We literally define a quantity with **value** equals `5.3`, we also specify its **type** is `float point value`, its **dimension** is `length`, and this dimension is described by **unit** `meter`.

Ideally when we define a varable in programming world, we would have wanted to defined it with four properties determined, as we do in real world. Unfortunatelly computer, in essence, is just a numerical computing device, it's difficult to make it understand complex concepts, like **Dimension** or **Unit**.

This is why **krypton** is created. **Krypton** is a C++ dimension calculation library designed to solve the dilemma described above.

**krypton** is inspired by [chrono](en.cppreference.com/w/cpp/header/chrono).

## 1. How krypton works

In krypton, every varaible is a quantity and every quantity is born with four attributes: `type`, `value`, `dimension` and `unit`:

```c++
template<class T, class Dim, class Ratio, class Unit>
struct quantity {
    // ...
};
```

where 

- `T` represents quantity's type, e.g. `int` or `float`.
- `Dim` represents quantity's dimension, e.g. `lenght` or `time`, we'll talk more about this later.
- `Ratio` specifies the magnitude of quantity's value, denoted by `std::ratio`, we'll talk more about this later.
- `Unit` specify quanity's unit (metric system, british system or others).

### 1.1 What is dimension

In krypton, *dimension* is not what we know as *3D* or *2D* graphic thing, instead it's a physical term that describes the basic attributes of physical quantities, such as `length`, `mass` or `electric charge`, etc. [Click here](https://en.wikipedia.org/wiki/Dimensional_analysis) to know more about Dimension and Dimensional Analysis.

### 1.1.1 How dimension is represented in krypton

The good news about physical dimension is that our world is entirly built upon [seven base dimensions](https://en.wikipedia.org/wiki/International_System_of_Quantities): 

- length
- mass
- time
- electric current
- thermodynamic temperature
- amount of substance
- luminous intensity

All dimensions we see in physical text books are either part of these seven base dimensions or derived from these seven dimensions. This makes it possible to build complex dimension system in programming world, following code shows how we do it in krypton:

```c++
// definition of compile time integral constants
using __2 = std::integral_constant<kr_int_t, -2>;   // -2
using __1 = std::integral_constant<kr_int_t, -1>;   // -1
using  _0 = std::integral_constant<kr_int_t,  0>;   // 0
using  _1 = std::integral_constant<kr_int_t,  1>;   // 1
using  _2 = std::integral_constant<kr_int_t,  2>;   // 2

// definition of sequence
template<class... T> struct sequence{};

// definition of seven base dimension
using length    = sequence<_1, _0, _0, _0, _0, _0, _0>;
using mass      = sequence<_0, _1, _0, _0, _0, _0, _0>;
using time      = sequence<_0, _0, _1, _0, _0, _0, _0>;
using current   = sequence<_0, _0, _0, _1, _0, _0, _0>;
using tempature = sequence<_0, _0, _0, _0, _1, _0, _0>;
using substance = sequence<_0, _0, _0, _0, _0, _1, _0>;
using intensity = sequence<_0, _0, _0, _0, _0, _0, _1>;
```

So we can define derived dimensions like this

```c++
using area      = pow<length, 2>::type;         // area = length * length
using velocity  = divide<length, time>::type;   // velocity = length / time
```

### 1.2 What is quantity's ratio

### 1.3 What is `Unit`

### 1.4 Summary

## 2. What can we do with krypton


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
     

