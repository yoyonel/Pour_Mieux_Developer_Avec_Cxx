# Function template instantiation

A function template by itself is not a type, or a function, or any other entity.
No code is generated from a source file that contains only template definitions. 
In order for any code to appear, a template must be instantiated: 
the template arguments must be determined so that the compiler can generate an actual function (or class, from a class template).


Explicit instantiation
1. `template return-type name < argument-list > ( parameter-list ) ;`
2. `template return-type name ( parameter-list ) ;`
3. `extern template return-type name < argument-list > ( parameter-list ) ;` (since C++11)
4. `extern template return-type name ( parameter-list ) ;` (since C++11)