***To ensure that your code can be easily understood by outside programmers, you must comply with the following standard :***

- Code and comments must be written in English
- Function/variable names should describe their use _(what they're for/what they do)_
- Class, Struct, Enum, Function and Namespace names must start with a capital letter and respect the PascalCase
- Variable names must begin with a lower case letter and respect the camelCase
- The `enum class` type should be preferred over the `enum` type
- Enum names must begin with "E" (`EMyEnum`)
- Class/Structure member variables must begin with "m_" (`m_myVar`)
- Global variables must begin with "g_" (`g_myGlobal`) and must be used sparingly.
- Function parameters must begin with "p_" (`p_myParam`)
- Static variables must begin with "s_" (`s_myStatic`)
- The unit of measurement of a variable must be explicitly represented (struct or unit suffix)
- Functions should aim for a maximum of 35 lines, but the limit may be increased if the situation so requires
- Functions must not take more than 5 parameters
- Structs should not have private members
- Structs should never inherit from other structs or classes
- A line must not exceed 132 characters (remember to return to the next line)

```cpp
// Wrong
if (playerPosition->x >= m_points[pointFollowed].x && playerPosition->x <= m_points[pointFollowed].x && playerPosition->y >= m_points[pointFollowed].y && playerPosition->y <= m_points[pointFollowed].y && pointFollowed == m_points->size())

// Ok
if (playerPosition->x >= m_points[pointFollowed].x &&
    playerPosition->x <= m_points[pointFollowed].x &&
    playerPosition->y >= m_points[pointFollowed].y &&
    playerPosition->y <= m_points[pointFollowed].y &&
    pointFollowed == m_points->size())
```

- Each brace must be placed on a separate line

```cpp
int addition_int(int a, int b) {	// Wrong
		return a + b; }				// Wrong

int addition_int(int a, int b)
{									// Ok
	return a + b;
}									// Ok
```

- Variable declarations and assignments should be grouped and aligned as much as possible

```cpp
int counter = 5;					// Wrong
char array[3] = { 'a', 'b', 'c' };	// Wrong

int  counter  = 5;					// Ok
char array[3] = { 'a', 'b', 'c' };	// Ok
```

- Each instruction must separate the variables and operators used with a space

```cpp
result=a+b;		// Wrong
result = a + b;	// Ok
```

- Each keyword using a condition must have a space between it and its condition

```cpp
if(condition)		// Wrong
while(condition)	// Wrong

if (condition)		// Ok
while (condition)	// Ok
```

- ASCII values must be represented in their character form

```cpp
char myChar = 65;	// Wrong

char    myChar  = ‘A’;	// Ok
int8_t  myByte  = 65;	// Ok
uint8_t myUByte = 65;	// Ok
```

- Preprocessor aliases and constexpr variables must be written in uppercase

```cpp
// Wrong
#define min_pos_x 0
#define max_pos_x 800

constexpr int offset_x = 32;

// Ok
#define MIN_POS_X 0
#define MAX_POS_X 800

constexpr int OFFSET_X = 32;
```

- Constant values must be represented by constant or constexpr variables or by preprocessor aliases

```cpp
if (_pos.x >= 0 && _pos.x <= 800)	// Wrong

// Ok
const int minPosX = 0;
const int maxPosX = 800;

if (_pos.x >= minPosX && _pos.x <= maxPosX)

// Ok
constexpr int MIN_POS_X = 0;
constexpr int MAX_POS_X = 800;

if (_pos.x >= MIN_POS_X && _pos.x <= MAX_POS_X)

// Ok
#define MIN_POS_X 0
#define MAX_POS_X 800

if (_pos.x >= MIN_POS_X && _pos.x <= MAX_POS_X)
```

- Enum constants must be capitalized

```cpp
// Wrong
enum Type
{
	alpha,
	beta
}

// Ok
enum class EType
{
	ALPHA,
	BETA
}
```

- A blank line must separate includes and functions

```cpp
#include <stdlib.h>

int main()
{
	return 0;
}
```

- A blank line must separate preprocessor directives from the rest

```cpp
#ifndef __MY_PUT_CHAR__
#define __MY_PUT_CHAR__

void MyPutChar(char c);

#endif
```

- Function and enumerator declarations must be commented using the Doxygen format

```cpp
/**
 * \brief Supported culling modes
 */
enum class ECullingMode
{
	NONE,
	MODEL,
	MESH
};

/**
 * \brief Calculates the sum of the given numbers
 * \param p_a The first number to add
 * \param p_b The second number to add
 * \return The sum of the two numbers
 */
int Add(int p_a, int p_b);
```