# Welcome to Frogman Engine API Programming Convention Guideline Document

**// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved**

**// UNKNOWN STRYKER is Hojin Lee.**

# Commandment: KISS rule

***Keep It Simple and Stupid.***

# Things to AVOID

### using namespace name; is a bad practice

DO NOT “using namespace name;”. It will generate name conflicts between other classes and functions that use the same names with different namespaces.

```cpp
#include <memory>
#include "memory.unique_ptr.hxx"
using namespace std;
using namespace FE;


int main(void)
{
    unique_ptr<int> l_standard_unique_ptr = make_unique<int>(5); // Name confliction error!
    unique_ptr<int> l_frogman_api_unique_ptr = 6;
    return 0;
}
```

### Passing a raw pointer to a parameter is unsafe.

There is a potential issue of accessing nullptr if the pointer type parameter is nullptr.
The object being pointed by the pointer type parameter can be removed during the function execution, leading to undefined behavior. Replace pointer type parameters with reference(ampersand/&) types.

```cpp
void fn(my_class* obj_ptr_p) noexcept; // It has possible issues.


void fn(my_class& obj_ref_p) noexcept; // Great!


// It applies the same with out-return parameters
void fn_with_out_return(my_class* obj_out_ptr_p) noexcept; // It can lead to undefined bahaviour.


void fn_with_out_return(my_class& obj_out_ref_p) noexcept; // Beautiful!
```

### Utilize managed smart pointers instead of primitive pointers if possible or appropriate.

```cpp
#include <memory>
#include "memory.unique_ptr.hxx"
#include "memory.proxy_ptr.hxx"


void leak_int() noexcept
{
    int* l_iptr = new int(0);
}


int main(void)
{
    std::unique_ptr<int> l_standard_unique_ptr = make_unique<int>(5); // A lightweight standard unique_ptr.
	
    FE::unique_ptr<int> l_frogman_api_unique_ptr = 6; // It is a thread-safe unique_ptr built for a multi-threaded environment. Note that its size is sixteen bytes.
    FE::proxy_ptr<int> l_ptr_that_refers_to_fe_unique = l_frogman_api_unique_ptr; // It is a smart pointer that can reference a FE::unique_ptr<T, allocator> concurrently without data race condition issues.
    // Choose the smart pointer precisely, which meets the needs of your code. By the way, the size of FE::proxy_ptr<T> is twenty-four bytes.
	
    leak_int();	// the four bytes integer is unreachable.

    return 0; 
}
```

# Conventions

## General Conventions

### Primitive Type Conventions

```cpp
// **primitive types are const by default.**
FE::int32 name_a = 0; **// a constant.**


FE::var::int32 name_b = 0; **// a variable**

// **use a question sentence for booleans.**
FE::var::boolean is_player_dead = false; 
**/* OR */**
FE::var::boolean is_it_dead = false; // **accepted.**
```

### How to name a Pre-Processor Macro and Global constexpr Constants

```cpp
#define **_HELLO_I_AM_MACRO_

	
#define MACRO_FUNCTION(param)

	
constexpr FE::uint64 _SBYTE_HASH_CODE_ = 646473;**
```

### How to name a Local Variable

```cpp
// **primitive types are const by default.**
FE::var::int32 l_name = 0; **// a local variable.**
```

### How to name a Static Variable

```cpp
// **primitive types are const by default.**
static FE::var::int32 s_name = 0; **// a static variable.**
```

### How to name a Local Static Variable

```cpp
// **primitive types are const by default.**
static FE::var::int32 l_s_name = 0; **// a local static variable.**
```

### How to name a Pointer

```cpp
// **primitive types are const by default.**
FE::var::int32* name_ptr = nullptr; **// a pointer.**
```

### How to name a Reference Variable

```cpp
// **primitive types are const by default.**
FE::var::int32& name_ref = &some;
```

### How to name a Function

```cpp
**void some_fn() noexcept;


void some_fn() noexcept
{
    ...
}**
```

### How to name a Function Parameter

```cpp
**void some_fn(**FE::**int32 number_p) noexcept;** // **primitive types are const by default.**
```

### How to name a Function Output Parameter

```cpp
// **primitive types are const by default.**
**void some_fn(**FE::**int32& out_name_ref_p) noexcept;**
```

### How to use **“if-else” S**tatements

```cpp
FE::var::boolean a = true;


if( a )
{
    ...
}
else
{
    ...
}

if( a )
{
    ...
}
else if(...)
{
    ...
}

// **if the "if" statement contains only one code line.**
if( a ) { return; }
```

### How to use “switch” Statements

```cpp
switch( a )
{
case 0:
    ...
    break;

case 1:
    ...
    break;

default:
    ...
    break;
}
```

### How to use “for” Loops

```cpp
// **primitive types are const by default.**
for( FE::var::int32 i = 0; i < 100; ++i )
{
    ...
}


for( auto& ref : container )
{
    ...
}
```

### How to use “while” Loops

```cpp
while( a == true )
{
    ...
}
```

### How to use “do while” Loops

```cpp
do
{
    ...
} 
while( a == true );
```

### How to use “goto” Keywords

```cpp
// **primitive types are const by default.**
for( FE::var::int32 i = 0; i < 100; ++i )
{
    for( FE::var::int32 j = 0; j < 100; ++j )
    {
        if( exception )
	{
	    ...
	    goto EXIT;
	}
    }
}

EXIT:

...
```

### How to invoke Functions

```cpp
some_fn(parameter_01, parameter_02, parameter_03, parameter_04);

some_fn_with_long_name_or_parameter(parameter_01,
																		parameter_02,
																		parameter_03,
																		parameter_04
																		);
```

### “this” Keyword

```cpp
this->m_integer; // **a class member variable.**


this->_integer; // **a struct field variable.**
```

### How Member Variable Alignment can affect the Total Size of your Class and Struct instance in MSVC++

```cpp
class my_class_a // total size of class my_class_a is 16 byte
{
    FE::var::schar m_a; // FE::var::schar is one byte.
    FE::var::int16 m_b; // FE::var::int16 is two bytes.
    FE::var::int32 m_c; // FE::var::int32 is four bytes.
    FE::var::int64 m_d; // FE::var::int64 is eight bytes.
};


class my_class_b // total size of class my_class_b is 24 byte
{
    FE::var::int32 m_c; // FE::var::int32 is four bytes.
    FE::var::int64 m_d; // FE::var::int64 is eight bytes.
    FE::var::schar m_a; // FE::var::schar is one byte.
    FE::var::int16 m_b; // FE::var::int16 is two bytes.
};


// the same with structures.
struct my_struct_a // total size of struct my_struct_a is 16 byte
{
    FE::var::int32 m_c; // FE::var::int32 is four bytes.
    FE::var::int64 m_d; // FE::var::int64 is eight bytes.
    FE::var::schar m_a; // FE::var::schar is one byte. 
    FE::var::int16 m_b; // FE::var::int16 is two bytes.
};


struct my_struct _b // total size of struct my_struct is 24 byte
{
    FE::var::int32 m_c; // FE::var::int32 is four bytes.
    FE::var::int64 m_d; // FE::var::int64 is eight bytes.
    FE::var::schar m_a; // FE::var::schar is one byte.
    FE::var::int16 m_b; // FE::var::int16 is two bytes.
};
```

## Class

### How to name Class Member Variables

```cpp
// **primitive types are const by default.**
class my_class
{
    FE::var::int32 m_integer;
};
```

### How to name Getters and Setters

```cpp
// **primitive types are const by default.**
class my_class
{
    FE::var::int32 m_integer;

public:
    inline FE::int32 integer() noexcept { return this->m_integer; }
    inline void integer(FE::int32 value_p) noexcept { this->m_integer = value_p; }
};
```

### Initializing Member Variables and Instances

```cpp
my_class::my_class() noexcept : m_integer(), ...
{
    // **initialize parent's property below**
}
```

### How to name and set up a Class

```cpp
class my_class
{
    FE::var::int32 m_integer;

protected:
    FE::var::float32 m_floating_point32;

public:
    inline FE::int32 integer() noexcept { return this->m_integer; }
    inline void integer(FE::int32 value_p) noexcept { this->m_integer = value_p; }
    //more...
};
```

**Template Class Example**

```cpp
template <typename T>
class my_class
{
    FE::var::int32 m_integer;

protected:
    FE::var::float32 m_floating_point32;

public:
    inline int32 integer() noexcept { return this->m_integer; }
    inline void integer(FE::int32 value_p) noexcept { this->m_integer = value_p; }
    //more...
};
```

## Struct

### How to name Struct Field Variables

```cpp
// **primitive types are const by default.**
template <typename T>
struct my_struct
{
    FE::var::int32 _name;
};
```

### Initializing Field Variables and Instances

```cpp
my_struct::my_struct() noexcept : _name(), ...
{
    // **initialize parent's property below**
}
```

### How to name and set up a Struct

```cpp
struct my_struct
{
    // **field variables**
    ...

    // ***structs can only have constructors, a destructor, and operators.***
    my_struct() noexcept;
    my_struct(const my_struct&  other_ref_p) noexcept;
    my_struct(my_struct&&  rvalue_p) noexcept;
    ~my_struct() noexcept;
		
    my_struct& operator=(const my_struct&  other_ref_p) noexcept;
    my_struct& operator=(my_struct&&  rvalue_p) noexcept;
    // **more operators (e.g.): + - * / ...**
};
```

**Template Struct Example**

```cpp
template <typename T>
struct my_struct
{
    // **field variables**
    ...

    // ***structs can only have constructors, a destructor, and operators.***
    my_struct() noexcept;
    my_struct(const my_struct&  other_ref_p) noexcept;
    my_struct(my_struct&&  rvalue_p) noexcept;
    ~my_struct() noexcept;
		
    my_struct& operator=(const my_struct&  other_ref_p) noexcept;
    my_struct& operator=(my_struct&&  rvalue_p) noexcept;
    // **more operators (e.g.): + - * / ...**
};
```

## Enum

```cpp
enum struct MY_ENUM : FE::int32
{
    _VALUE = 0;
    ...
};
```
