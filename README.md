# Ackermann Steering Controller
[![Build Status](https://app.travis-ci.com/markosej11/ackermann_controller.svg?branch=main)](https://app.travis-ci.com/markosej11/ackermann_controller)
[![Coverage Status](https://coveralls.io/repos/github/markosej11/ackermann_controller/badge.svg?branch=main)](https://coveralls.io/github/markosej11/ackermann_controller?branch=main)


Overview and purpose of the project (what does it do? Main Features? This should be a write-up of several paragraphs like a short report). Include results/performance examples.

## Authors
Markose Jacob - markj11@terpmail.umd.edu
Pooja Kabra - pkabra@umd.edu

## License
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Overview
The starting point for explaining the Ackermann steering geometry is obvious: while on a bend, the outer front wheel traces a wider curve than the inner wheel (which has a narrower curve). A turning kart must have a rotation centre around which to do so, and around which the front wheels can rotate.
If the front wheels are perfectly parallel during the bend, no rotation centre would be created and the front wheels would slide, generating friction between tread and asphalt, tyre wear and loss of performance.

Ackermann’s steering geometry serves to offset the different direction covered by the front wheels along the curved trajectory to avoid this happening.
How? By causing the front wheels to rotate in a non-linear direction when turning the steering wheel. In doing so, a theoretical point is created (“theoretical” because, with the slipping of a 4-wheeled kart, the point actually varies) in which the 2 axes of the front wheels and the axis of the rear axle intersect.

Among other things, the bend geometry of a kart’s steering will lower the inner front wheel and lift the outer front wheel, with the transfer of much of the load to the front. The grip on the front is accentuated and the wheel travel direction is even more decisive.

In this project, we implement an Ackerman Steering controller for a robot. We assume that it is four-wheeled and rear drive robot. The task is to make the robot attain the desired heading and speed in a fixed World Frame. 

System Input: goal heading(degree, world frame), goal speed(degree, world frame)
System Output: inner wheel linear speed(m/s), outer wheel linear speed(m/s), inner wheel angle(degree, robot frame), outer wheel angle(degree, robot frame)

               
(For inner wheel angle and outer wheel angle, by robot frame, we mean that they are measured with respect to the robot's longitudinal axis)

## Assumptions
1. Four wheeled robot with rear wheel drive and front wheel steering
2. left turn is +ve rotation and right turn is -ve rotation
3. The initial heading and speed for the robot is zero
4. Friction is assumed to be minimum
5. robot can only steer 15 degrees in 1 second
6. Maximum linear speed of the robot is 16.667 m/s
7. Maximum acceleration possible is 1 m/s^2
8. Robot cannot go in reverse


## API Google spread sheet
https://docs.google.com/spreadsheets/d/1yhOUowKENOIwfs4re1dwxyGSYlhCP-KEqHWIA955CD0/edit#gid=0

## Sprint notes 
https://docs.google.com/document/d/1CDC3BQAcqqWPXwyzGGFP_2MjMRhd2xdqWWC8LeXDoHQ/edit

## Standard install via command-line
```
git clone --recursive https://github.com/pooja-kabra/ackermann_controller/tree/second_phase
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Running instructions
Enter the target heading in degrees. To turn left enter +ve rotation in degrees and for right turn enter -ve rotation in degrees
Enter the target speed in m/s

## Building for code coverage 
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Doxygen

Doxygen is a tool used for generating software reference documentation.

To install it use 
```
sudo apt install doxygen
```
To generate doxygen documentation after installation use 
```
doxygen -g <config-file>
```
where ```<config-file>``` is the name of the configuration file that you want to create. 
In this file edit the input and output directories, and the files that have to be included or excluded while generating the Doxygen comments.
Finally, to run the Doxygen configuration file, use the following command
 ```
doxygen <config-file>
 ```
This will generate a HTML and LATEX output of the Doxygen comments inside the output directory specified in the configuration file.

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/pooja-kabra/ackermann_controller/tree/second_phase
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of ackermann

```
cd ~/workspace
mkdir -p boilerplate-eclipse
cd boilerplate-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../ackermann/
```

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "ackermann" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold ackermann project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the ackermann in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


## Debug


1. Set breakpoint in source file (i.e. double click in the left margin on the line you want 
the program to break).

2. In Eclipse, right click on the ackermann in Project Explorer, select Debug As -> 
Local C/C++ Application, choose the binaries to run (e.g. shell-app).

3. If prompt to "Confirm Perspective Switch", select yes.

4. Program will break at the breakpoint you set.

5. Press Step Into (F5), Step Over (F6), Step Return (F7) to step/debug your program.

6. Right click on the variable in editor to add watch expression to watch the variable in 
debugger window.

7. Press Terminate icon to terminate debugging and press C/C++ icon to switch back to C/C++ 
perspetive view (or Windows->Perspective->Open Perspective->C/C++).


## Plugins

- CppChEclipse

    To install and run cppcheck in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> cppcheclipse.
    Set cppcheck binary path to "/usr/bin/cppcheck".

    2. To run CPPCheck on a project, right click on the project name in the Project Explorer 
    and choose cppcheck -> Run cppcheck.


- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml




























































# Authors
Pooja Kabra (Graduate Student in Robotics at the University of Maryland College Park, May 2022), 
Markose Jacob (Graduate Student in Robotics at the University of Maryland College Park, Dec 2021)

# Shareable link to sprint planning notes and review Google Doc
https://docs.google.com/document/d/1BkXeVk6V7ksHjORvei8yQkGbdUtxJc3uc8dqAFlbF6g/edit

# Sections for (stubs in Phase I, completed by end of Phase II):

# Operation/run/test/demo steps

# Dependencies (and how to install if not included in the repository)

# Known issues/bugs

# API and other developer documentation (e.g. parameters and their definitions and default values)


# How to build
1. On your local computer, at the desired location, open a terminal and clone the repository by running
	$ git clone --recursive https://github.com/pooja-kabra/ackermann_controller/tree/second_phase

2. $ cd <path to repository> i.e. (../ackermann_controller/)
	$ mkdir build
 	$ cd build

3. In the same terminal(in ../ackermann_controller/build/), run 
	$ cmake ../
   (Every time you add new files to app, you should edit ../ackermann_controller/app/CMakeLists.txt to include them and run $ cmake ../)

4. In the same terminal, run
	$ make
	
# How to run the demo
1. After finishing build, run(in ../ackermann_controller/build/)
	$ ./app/shell-app

2. Enter desired goal heading and goal speed values.

# How to run tests
	$ ./test/cpp-test
# How to generate Doxygen documentation
The repository contains documentation. Although, if you would still like to generate it, follow the instructions below:

1. Install doxygen using below commands
	$ sudo apt-get install doxygen
	$ sudo apt-get install doxygen-gui

2. After installation run following command to open the doxywizard.
	$ doxywizard
   Here, you can fill in the details as required and set the source code folder to the repository as well. Create a new folder in the repository and select that as the destination directory. Add paths to include and src folders and then proceed with the default settings and generate the documentation.

# Product Backlog Google spreadsheet:
https://docs.google.com/spreadsheets/d/1yhOUowKENOIwfs4re1dwxyGSYlhCP-KEqHWIA955CD0/edit#gid=0

Copyright <2021> <POOJA KABRA> <MARKOSE JACOB>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
