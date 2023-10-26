# Dynamic Memory Allocation Demo
This demo shows:
1. Motivation for using pointers (in the heap) over variables in the stack.
2. Importance of managing allocated memory.
3. Shared pointers' ability to avoid memory leaks.

## Stack limitations
Programs use the stack to manage functions and the variables they use. Stacks are fast, but are often limited in size. The Ubuntu operating system often uses 8 megabytes for every program. This means, if you create variables that contain more than 8 megabytes, then the program will crash.

Let's see this in action. Open `image.h` and go over the `Image` class. If you have not used an array before, the `data` member variable's type is a character array (`char data[8000000000]`). This code will create an array of 8,000,000,000 characters.

> Arrays are used to store a collection of information much like `std::vector`. The difference is that arrays are primitive data types so they do not offer any member functions. They do not grow either so you cannot add any more data to an array after you define its size.

Go over `main.cc`. Take note that it creates an `Image` object in the stack. Try compiling and running the program. Provide any filename and hit <kbd>enter</kbd>.

```
clang++ -std=c++17 main.cc -o main
./main
```

### Pop quiz!
1. What warning do you get when compiling the code? 
1. Any idea what the warning means?
1. What error do you get when you run the program?

## Dynamic Memory Allocation to the rescue!
Although your program runs on the stack with limited space, there is another part of your computer's memory that can be shared by any program -- the heap. To access the heap, we need to first reserve or allocate space in the heap. We do that by using the `new` keyword. We then create a pointer variable to store the location of that space. Modify the `LoadImage` function to dynamically allocate an Image object in the heap. Also make sure to use the arrow notation to use a pointer to access the member function of the obect in the heap. See the code below.

```
Image* my_image_ptr = new Image{filename};
my_image_ptr->Display();
```

Recompile the program and try running it again.

### Pop quiz!
1. Does the modified code still give you an error?
1. How do you think using pointers solve the error?

## Memory leaks
Everything in the world is good again. No more Segmentation faults. But wait, remember that we allocated or reserved space in the heap? Much like checking in a hotel or reserving a locker, what do you do when you are done using the space? If we don't check out of our room or give back our locker keys no one can use that space. In the same way, if we dynamically allocate space (using `new`) we also need to deallocate the space. Otherwise the space in the heap cannot be used by other programs, also called a `memory leak`. Take note that we access the space using a pointer, so the moment the `LoadImage` function exits we no longer have access to `my_image_ptr`. We can't even use the space despite being the one who allocated the space.

### Detecting memory leaks
Unfortunately, many times memory leaks are not detected early enough so a long-running program might be slowly using up the heap until it has no more memory to reserve or it crashes. This is not something you want to happen especially if your program is mission critical (e.g., air traffic control program).

The `clang++` compiler provides an `AddressSanitizer` that can help us detect memory leaks. We can access this by using the `-fsantize=address` flag during compilation. Recompile your code using the command below and run it.

```
clang++ -std=c++17 -fsanitize=address main.cc -o main
./main
```

#### Pop quiz!
1. What happens after running the program and providing the file name?
1. Why do you think the program gives you such output?

As a responsible developer, it is your job to deallocate memory in the heap after you used it. We do this by using the `delete` keyword. Modify the `LoadImage` function by adding the code below. It basically tells the operating system to deallocate or release its control over the memory it previously reserved. It is similar to checking out of the hotel or giving back your locker keys.

```
delete my_image_ptr;
```

Recompile and rerun your program.

### Pop quiz!
1. Do you still see errors after running the program?
1. How did the delete keyword fix the problem?

## Shared pointers
Everything in the world is yet good again. However, we remember that we are human. If it is a few lines of code, you can probably remember dynamically allocating and deallocating space in the heap. It is an entirely different story if you are instead dealing with a large code base (see this [Google Chrome source code](https://source.chromium.org/chromium/chromium/src/+/main:chrome/browser/ui/views/tabs/tab.cc) as an example) and you write code that dynamically allocates space in one part of the code and deallocate somewhere else.

Shared pointers, which is a subset of a larger group of data structures called `Smart Pointers`, helps address this problem. They are smart, because you can rely on them to clean up after themselves. Unlike raw pointers, which is a term we use to refer to pointers that we manually allocate and deallocate  with `new` and `delete`, shared pointers allocate memory for us. When a shared pointer is `destroyed``, it automatically deallocates the memory for us as well. That way as a developer, we only need to declare the shared pointer and not worry so much about memory leaks.

Shared pointers, much like other variables, are destroyed automatically when their containing function exits. In our example, the `my_image_ptr` variable is destroyed when the `LoadImage` function exits. Modify `LoadImage` to use a shared pointer as shown below. Make sure to include the `memory` library to use `std::shared_pointer` (`#include <memory>`). Take note that we do not need the `delete` keyword.

```
std::shared_ptr<Image> my_image_ptr = std::make_shared<Image>(filename);
```

Try recompiling and running the program.

### Pop quiz!
1. Recall you did not delete your pointer. Does the program report a memory leak?
1. Explain how std::shared_ptr avoids memory leaks in this situation.