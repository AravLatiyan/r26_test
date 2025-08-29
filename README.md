# R26_test

<p align="center">
  <img src="https://github.com/teamrudra/r26_test/blob/main/misc/rover.webp" width="480" height="480"/>

#### Some Instructions
1. You may use any online resources, datasheets, or documentation needed, but be mindful of your time and stay focused on the task.
2. The duration of the test is 90 mins from 5:15pm to 6:45 pm.
3. There will be a MCQ test conducted [here](https://rudra26test.vercel.app/)
4. There are 4 tasks in the tests. Complete all of them.
5. In case you are not able to complete all the tasks, do upload whatever you are able to.
6. In the `README.md` of your repository include your thought process, places where you got stuck, where you used the help of AI, google or other online resources.
7. Even if you are not able to solve anything, do fill the readme and what your thought process would have been.
8. Carefully read the instructions to implement the required functionality.
9. Install [mingw(c compiler)](https://www.mingw-w64.org/downloads/#w64devkit) and [git](https://git-scm.com/downloads) if you haven't already done it.
10. After finishing your test, provide the link to your forked repository in the google form provided at the end.

### Aim/Objective: To decode GPS data of start and goal position, and create a path planning algorithm which computes an optimal path over a predefined gridmap

## Description
You are implementing code to decode GPS position data, received from a u-blox GNSS module on-board a rover (check out the [datasheet](https://drive.google.com/file/d/1rOcPxpP-3JE8l39kBMiQV6KKe8B6zlDf/view)). You are given the current/start position of the rover and the goal position where the rover has to reach, your goal is to develop a path planning algorithm to traverse over a pre-defined gridmap and generate necessary odometry commands (total time & angle traversed) to guide the rover along the generated path. 

### Task 0: Fork the provided repository and ensure it is set to PUBLIC so we can access and assess your work.
### Task 1: Decoding gps data (in ubx format) from u-blox reciever.
Working with UBX format and extracted relevant navigation data for use in the planner.
### Task 2: Develop a path planning algorithm to traverse over a gridmap.
Implemented a grid-based path planner that computes an optimal route from start to goal.
### Task 3: Generate odometry commands to guide the rover along the generated path.
Converted the path into motion commands (direction and timing) based on wheel parameters.
### Task 4: Compile and run the code.
Verified the workflow on sample inputs and ensured the project compiles successfully with g++.

#### Code
1. [src/main.cpp](src/main.cpp): Code for running the test.
2. [src/ublox_reader.cpp](src/ublox_reader.cpp): Recitfy errors in this code to compute correct lat & lon coordinates.
3. [src/planning.cpp](src/planning.cpp): Complete the defined `Planner::pathplanning` function 
4. [src/odometry.cpp](src/odometry.cpp): Complete the defined `Odometry::computeCommands` function 

#### How to Compile & Check your code
(make sure you are in the root directory)   
1. Compile your code by running: `make build`
2. To check if your code is implemented correctly run: `make check`
   
If you are able to compile your code successfully you should see something like this on your screen:

```
*** Success: ***
--------------------------------------------
```

4. If your make check was unsuccesfull, you can clean your attempt by running `make clean`, review your implementation and repeat the previous steps.

# Solution
## Understanding
This project made me understand that we had to work with diffrent libraries in the project yet, somehow had to integrate them all together so they all work in synchorony also diffrent part of th project had diffrent things to work .So we can say we had to break down this complex piece of machinary's mind and work with simple well divided parts in order to come up with a working model. In conclusion multiple small not so hard coding parts ---> complex logic.  

## Thought Process
At first i wasent aware of the time we had to work with code so my work was done consideing i had less than half an hour at hand to complete it i took muliple parts of the code and considering the time uploaded to chat gpt ot further break down the parts of code and understanding what eah part was doing and this was what i was able to come up with:

gripmap helped with getting the occupancy using simple grid mapping i.e. it marked cells in the grid as either free, occipied or unkown. This helped us with forming a map path by creating a simulated environment.

planning deals with the path-planning algorithm after getting the value from gridmap creating a collisin free from initail to final position.This helped us gettign an idea of where the robot should go from in order to visit safely.

odomentry helped us doing the odomentry calulation typically calculating the values using the values that is if wheels are moving equally the rover moved in a straight line .However if it didnt and wheels moved unevenly it created some sort of rotation along the x,y plane .This helps us get the position of rover even without the gps.

ublox_reader does a lot of things including getting us latitude , longitude , height ,etc .It does something related to GPS ,i couldnt get the exact idea.

main calls func from all gridmap, planner, odomentry and ublox_reader.Also runs given test cases reads the input passes them to function and checks the output.



## Implementation
for planning.cpp:
The planning part was partly done but not complete so I asked ChatGPT to help me finish it. The idea was to use BFS, which checks each nearby cell step by step and avoids blocked ones. It also remembers the parent of each cell so that in the end we can rebuild the path from the goal back to the start. I tested this using the given test case in main.cpp. It printed the path for a start and goal position, and the output matched the expected result, so I knew it worked.

for odomentry.cpp:
Odometry was also given in part, and I used ChatGPT to help complete it. The logic works by checking the difference in wheel encoder ticks. If both wheels move the same it goes straight, otherwise it turns in a curve. The code updates the robot’s x, y, and angle using the basic formulas as given in code. I tested this with the provided test case in main.cpp which gave some wheel tick values. The function returned the new robot pose, and the numbers matched what was expected in the test, so that confirmed it was correct.

for Ublox_reader.cpp:
This one I fixed myself at first the GPS values were not coming out right. I read the documentation and found that each field in the UBX NAV-POSLLH message is stored at a fixed offset (0, 4, 8, 12 …){<-- these are some sorts of bytes used by the system incicating where each field starts}.So I used memcpy with the correct offsets from the buffer into the struct fields. After this change, the GPS data (like longitude and latitude) came out properly when I tested it with the given input.

# Google Form
[Link to Repo Submission](https://docs.google.com/forms/d/e/1FAIpQLSdlVJ2LzP8wUOATRD804zDVL611rwwGMO1y_ecYu5aoV5YQfw/viewform)


<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/feynman-simple.jpg" width="600" height="600"/>
</p>
     
