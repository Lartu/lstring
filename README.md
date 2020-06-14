<p align="center">
  <img src="img/logo.png">
  <br>
  <img src="https://img.shields.io/badge/license-MIT-yellow?style=flat-square">
  <img src="https://img.shields.io/badge/current_release-1.0-blue.svg?style=flat-square">
</p>

**lstring** is a simple, utf-8 string library for C++. If lets you use strings like `"你好，世界！"` 
and index and substring them and take their length. I mean, it does what you'd expect a library like
this to do. The complexity for each function has been curated so that it's efficient to use. PRs are
welcome!

## Usage
```c++
// Initializing a new lstring:
lstring foo1;
lstring foo2 = "Hello world";
lstring foo3 = -18.22;
lstring foo4 = (string)"Hi there!";

// Getting the length of an lstring:
size_t len = lstring.length();

// Using an lstring with a stream;
lstring myLstring = "Hello world!";
stream << myLstring << endl;

// Appending values to an lstring
myLstring.append(foo2);
myLstring.append("Bye!");
myLstring.append((string)"Bye again!");
myLstring.append(67.5);

// Obtaining grapheme at given index
lstring helloWorldChinese = "你好，世界！";
lstring firstGraph = helloWorldChinese.graphat(0);
// firstGraph now equals "你"

// Obtaining substrings
lstring worldInChinese = helloWorldChinese.substr(3, 2);
// worldInChinese now equals "世界"

// Obtaining a string from an lstring
string world_in_chinese = worldInChinese;

// Obtaining a double from an lstring
lstring numericValue = 123.456;
double myVal = numericValue;
```

## Complexity

Check the [lstring.hpp](lstring.hpp) file to see the complexity of each function.

## License

**lstring** is released under the **MIT** [license](LICENSE) so you can use it for anything you want.
