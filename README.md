# Installation Guide

## Mac OS

1. Copy the Blitz folder under the Library folder(of this repo) and paste it inside your project directory.

2. Install OpenCv, just run `brew install opencv` on your terminal

3. If you want to use some other library, you can install them in a similar way, using brew.

4. Use `clang++ -std=c++14 yourProgamFile.cpp -I./Blitz/include/ -L./Blitz/lib/ -lBlitz $(pkg-config --cflags --libs opencv4)` to compile your code.

5. If you have installed some other library, then add them to the above command after opencv4.s

Thats it! It is as simple as that, no need to worry about anything else.

# Creating static library

1. From the folder where you have all of your source files, run `clang++ -std=c++14 -c src1.cpp src2.cpp src3.cpp -I./include/ ${pkg-config --cflags --libs <additionalLibraries>}`

2. Replace < additionalLibraries > with the 3rd party libraries you have used in your source files seperated by space.

3. The above command creates object files (with extension .o). The same command would run with any number of source files, just make sure that all the corresponding header files are in the ./include folder.

4. Then run `ar rcs libYourLibraryName.a src1.o src2.o src3.o`

5. The resulting .a is your static library.Place the resulting .a file into ./lib folder.

6. Your can delete the .o files, the only thing that is required is .h files and .a file, place your .h files in ./include directory and .a file in the ./lib directory.

7. Now, create a new directory with your library and copy paste the include folder and lib folder into that, or rename the current directory with your library name.

8. Place that folder inside the project directory where you want to use this file.

9. To compile your code, `clang++ -std=c++14 yourProgamFile.cpp -I./YourLibraryName/include/ -L./YourLibraryName/lib/ -lYourLibraryName`.

10. You can use any compiler to run the above commands, its not neccessary to use clang++.
