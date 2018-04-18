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
template<class T, 
         class Dim, 
         class Ratio = std::ratio<1>,
         class Unit = metric_system<Dim>>
struct quantity {
    const T value;
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

A quantity's ratio denotes the magnitude of it's value. such as when you write

```c++
template<T>
using type1 = quantity<T, length, std::ratio<1>, metric_system<length>>;
```

you defines a `quantity` type whose dimension is `meter`. If you change above code a little bit, like this

```c++
template<T>
using type2 = quantity<T, length, std::ratio<1000, 1>, metric_system<length>>;
```

you actually defines a `quantity` type whose dimension is `kilometer`, because its value's magnitude is `std::<1000, 1>`, which means `1000 times`.

### 1.3 What is `Unit`

The template parameter `Unit` is a placeholder which indicates what unit (metric or british) the variable is. Currently krypton supports two types of unit: metric and british, declared as following:

```c++
template<class T> struct metric_system;

template<class T> struct british_system;
```

### 1.4 Quantity runtime performance

The good thing of `quantity` is although it comes with a couple of attributes, these attributes exist only in compile time, at run time a quantity is as simple as a plain value type, so we don't need worry about its runtime performance.

## 2. What can we do with krypton

### 2.1 Type check

In krypton, a quantity's "type" is determined by its `dimension`, if two quantity has different `dimensions`, they are treated as different types.

```c++
velocity<double> v{5.0};        // v's dimension is velocity
second<int> t1{v};              // this won't compilem, because t's dimension is time, it can't be
                                // initialized by a "velocity"    
second<int> t{5};               // t's dimension is time

kilogram<double> kilo = v * t;  // this won't compile, because kilo's dimension is mass,
                                // but dimension of v * t is length (velocity * time = distance)
                          
meter<double> m = v * t;        // OK, distance = velocity * time                         

feet<double> f = v * t;         // OK, feet's dimension is also length

kilometer<double> km = v * t;   // OK
```

### 2.2 Automatic ratio conversion

```c++
meter<double> m{5000.0};

kilometer<double> km{m};        // km.value = 5.0

millimeter<double> mm{m};       // mm.value = 5000000.0
```

### 2.3 Automatic unit conversion

```c++
meter<double> m{.50};

feet<double> ft{m};             // OK
```