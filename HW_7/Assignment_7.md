Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #7

11/20/2019

Robot Planning. In this assignment, you will gain experience with classical planning. You can use https://editor.planning.domains/ for testing your PDDL code. You must create two PDDL files: [robotdomain.pddl](./robotdomain.pddl) and [robotproblem.pddl](robotproblem.pddl). Write in PDDL the problem where a robot has to pick up object and transfer them to desired locations. There are several rooms R1....,Rn. some of them connected to each other. There are several objects O1....,Om. with at most one object per room. A robot is located in one of the rooms. You are also given goal rooms G1....,Gm for each of the objects.

* The robot can pick up only one object at a time.
* There can be at most one object in room.
* If the robot has picked up an object, it can only go to room that has no other

You will need to first write the domain file which defines the predicates and the actions necessary to solve this problem. You need to provide definitions for the following actions:

* move-without-object
* move-with-object
* pickup
* release

You also need to write a problem instance file which defines the initial and goal state. The problem instance should correspond to the picture shown in the attached file. Robot has transfer object O1 in room R7, object O2 in room R2, and object O3 in room R9. Black rectangles represent walls.

1. (**2 points**) The domain file code ([robotdomain.pddl](./robotdomain.pddl)). Please comment your code is clear on what the actions and predicates are supposed to do.
2. (**2 points**) The problem file ([robotproblem.pddl](./robotproblem.pddl)) and the solution.
3. (**1 points**) Change the problem files so the robot starts at R2. Submit changes made and the solution.