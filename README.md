# Flight Gear Simulator Interpreter

This is our first milestone of the project. Our goals are:
* Interprating a txt file with flight instructions.
* Establishing a TCP/IP connection with the simulator, as a client and server.

## Installation Instructions
* Install the FlightGear simulator from [here](https://www.flightgear.org/download/).
* You will need to have xml file which defines the TCP protocol. You'll add it to /data/Protocol directory
of the simulator. This file is added to the repository.
* Update inside the simulator the specific TCP/IP protocols.
To add it, go to the Flight Simulator -> Settings -> Additional Settings, and write these two lines:

--telnet=socket,in,10,127.0.0.1,5402,tcp
    
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small

## About The Project
The process of the project is as follows:
1. We recieved a txt file called fly.txt with all the instructions that need to be executed to make the 
plane fly in the simulator. The fly.txt file is also added to the repository.
2. We read the file and parsed it to specific commands to execute.
3. We sent data to update simulator's values, and recieved data from it. Some values of the txt file were
updated by the commands we executed according to the file, and some were updated by the simulator.
4. The simulator has now all the information it needs to start the engine and fly!

## Running Instructions
To run the projet, you'll need to have the txt file in the same folder as the project.
If not, when compiling, pass the path of the fly.txt file as an argument for the main.

## File Syntax
1. After every command, there will be space, and also after declaring a new variable. Variables are declared and
has to be initialized right after.
2. Nested Loops, and conditions inside while loops will not be in the txt file, and vice versa.

