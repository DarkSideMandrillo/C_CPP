A functor is pretty much just a class which defines the operator(). 
That lets you create objects which "look like" a function:

Simile, nell'utilizzo base ad una funzione puntatore (chiamata a func senza parentesi)
Ma Possono tenere gli stati e conservare i dati tra chiamate, oltre ad avere diverse conste


// this is a functor
struct add_x {
  add_x(int val) : x(val) {}  // Constructor
  int operator()(int y) const { return x + y; }

private:
  int x;
};

// Now you can use it like this:
add_x add42(42); // create an instance of the functor class
int i = add42(8); // and "call" it
assert(i == 50); // and it added 42 to its argument

std::vector<int> in; // assume this contains a bunch of values)
std::vector<int> out(in.size());
// Pass a functor to std::transform, which calls the functor on every element 
// in the input sequence, and stores the result to the output sequence
std::transform(in.begin(), in.end(), out.begin(), add_x(1)); 
assert(out[i] == in[i] + 1); // for all i

/*
There are a couple of nice things about functors. One is that unlike regular functions, 
they can contain state. The above example creates a function which adds 42 to whatever 
you give it. But that value 42 is not hardcoded, it was specified as a constructor argument 
when we created our functor instance. I could create another adder, which added 27, just by 
calling the constructor with a different value. This makes them nicely customizable.

As the last lines show, you often pass functors as arguments to other functions such as 
std::transform or the other standard library algorithms. You could do the same with a regular 
function pointer except, as I said above, functors can be "customized" because they contain state, 
making them more flexible (If I wanted to use a function pointer, I'd have to write a function 
which added exactly 1 to its argument. The functor is general, and adds whatever you initialized 
it with), and they are also potentially more efficient. In the above example, the compiler knows 
exactly which function std::transform should call. It should call add_x::operator(). That means 
it can inline that function call. And that makes it just as efficient as if I had manually called 
the function on each value of the vector.

If I had passed a function pointer instead, the compiler couldn't immediately see which function 
it points to, so unless it performs some fairly complex global optimizations, it'd have 
to dereference the pointer at runtime, and then make the call.

*/