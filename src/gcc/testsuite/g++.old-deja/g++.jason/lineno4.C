// Build don't link: 
// Special g++ Options: 
// GROUPS passed error-reporting
// Bug: # line directive in template definition interferes with growing obstack
template <class T> class A
{
public:

# 200 "lineno4.C"
      int foo () { undef1(); } // ERROR - , LINE 200
};

template class A<int>;
