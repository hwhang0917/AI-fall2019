Heesang Mark Whang

CSCI 440: Artificial Intelligence

Assignment #7

11/20/2019

Robot Planning. In this assignment, you will gain experience with classical planning. You can use https://editor.planning.domains/ for testing your PDDL code. You must create two PDDL files: [robotdomain.pddl](./robotdomain.pddl) and [robotproblem.pddl](robotproblem.pddl). Write in PDDL the problem where a robot has to pick up object and transfer them to desired locations. There are several rooms R1....,Rn. some of them connected to each other. There are several objects O1....,Om. with at most one object per room. A robot is located in one of the rooms. You are also given goal rooms G1....,Gm for each of the objects.

* The robot can pick up only one object at a time.
* There can be at most one object in room.
* If the robot has picked up an object, it can only go to room that has no other

![](C:\Users\hwhan\Biola Works\Fall 2019\AI-fall2019\HW_7\robotState.png)

You will need to first write the domain file which defines the predicates and the actions necessary to solve this problem. You need to provide definitions for the following actions:

* move-without-object
* move-with-object
* pickup
* release

You also need to write a problem instance file which defines the initial and goal state. The problem instance should correspond to the picture shown in the attached file. Robot has transfer object O1 in room R7, object O2 in room R2, and object O3 in room R9. Black rectangles represent walls.

1. (**2 points**) The domain file code ([robotdomain.pddl](./robotdomain.pddl)). Please comment your code is clear on what the actions and predicates are supposed to do.

   ```PDDL
   (define (domain robotDomain)
   
   (:requirements :strips :equality :negative-preconditions)
   
   (:predicates 
               ; General predicate
               (isRoom ?x) ; x is a room
               (isObject ?x) ;x is an object
               (isRobot ?x) ;x is a robot
   
               ; Robot related
               (clear ?x) ;x robot is free to hold an object
               (holding ?x) ;robot is holding object x
               (bot-at ?x) ;robot is at room x
   
               ; Object location
               (obj-at ?x ?y) ;object x is at room y
   
               ; Room accessibility
               (can-go ?x ?y) ;can move from room x to room y
   )
   
   (:action move-without-object
       :parameters (?start ?dest ?robot)
       :precondition (and 
                   ; Check variables
                   (isRoom ?start) (isRoom ?dest) (isRobot ?robot)
                   
                   ; robot spec
                   (bot-at ?start) ; robot is in start room
                   (clear ?robot) ; robot is free
   
                   ; Room accessibility
                   (not (= ?start ?dest)) ;  room start != room dest
                   (can-go ?start ?dest) ; can go from start to dest
       )
       :effect (and    
                   ; Move robot from start room to dest room
                   (bot-at ?dest)
                   (not (bot-at ?start))
       )
   )
   
   (:action move-with-object
       :parameters (?start ?dest ?object ?robot)
       :precondition (and 
                   ; Check variables
                   (isRoom ?start) (isRoom ?dest) (isObject ?object) (isRobot ?robot)
                   
                   ; Object location
                   (not (obj-at ?object ?start)) (not (obj-at ?object ?dest)) ; There are no objects in either room start or end
   
                   ; robot spec
                   (bot-at ?start) ; robot is in start room
                   (not (clear ?robot)) ; robot is not free
   
                   ; Room accessibility
                   (not (= ?start ?dest)) ;  room start != room dest
                   (can-go ?start ?dest) ; can go from start to dest
   
       )
       :effect (and 
                   ; Move robot from start room to dest room
                   (bot-at ?dest)
                   (not (bot-at ?start))
       )
   )
   
   (:action pickup
       :parameters (?room ?object ?robot)
       :precondition (and 
                   ; Check variables
                   (isRoom ?room) (isObject ?object) (isRobot ?robot)
   
                   ; Object location
                   (obj-at ?object ?room) ; object is at the room
   
                   ; robot spec
                   (bot-at ?room) ; robot is in the room
                   (clear ?robot) ; robot is free 
                   (not (holding ?object)) ; robot is NOT holding an object
       )
       :effect (and 
                   ; Pick up object
                   (not (obj-at ?object ?room)) ; remove object from room
                   (not (clear ?robot)) ; robot is no longer free
                   (holding ?object) ; robot is holding the object
       )
   )
   
   (:action release
       :parameters (?room ?object ?robot)
       :precondition (and 
                   ; Check variables
                   (isRoom ?room) (isObject ?object) (isRobot ?robot)
   
                   ; Object location
                   (not (obj-at ?object ?room)) ; object is NOT at the room
   
                   ; robot spec
                   (bot-at ?room) ; robot is in the room
                   (not (clear ?robot)) ; robot is NOT free 
                   (holding ?object) ; robot is holding an object
       )
       :effect (and 
                   ; Release object
                   (obj-at ?object ?room) ; put object in room
                   (clear ?robot) ; robot is free
                   (not (holding ?object)) ; robot is no longer holding the object
       )
   )
   
   
   )
   ```

2. (**2 points**) The problem file ([robotproblem.pddl](./robotproblem.pddl)) and the solution.

   ```PDDL
   (define (problem robotCase_1) (:domain robotDomain)
   (:objects R1 R2 R3 R4 R5 R6 R7 R8 R9 ; Room numbers (1~9)
               O1 O2 O3 ; Objects (1~3)
               BOT ; robot
   )
   
   (:init
       ; Initial variable
       (isRoom R1) (isRoom R2) (isRoom R3) ; R1~R9 is a room
       (isRoom R4) (isRoom R5) (isRoom R6)
       (isRoom R7) (isRoom R8) (isRoom R9)
   
       (isObject O1) (isObject O2) (isObject O3) ; O1, O2, O3 are objects
       (isRobot BOT) ; BOT is a robot
   
       ; Bot spec init
       (bot-at R1) ; bot is at room 1
       (clear BOT) ; BOT is free
       
       ; Accessibility of Rooms
       (can-go R1 R4) ; Can go from R1 -> R4
       (can-go R2 R3) ; Can go from R2 -> R3
       (can-go R3 R2) (can-go R3 R6) ; Can go from R3 -> R2 & R3 -> R6
       (can-go R4 R1) (can-go R4 R5) ; Can go from R4 -> R1 & R4 -> R5
       (can-go R5 R4) (can-go R5 R6) (can-go R5 R8) ; Can go from R5 -> R4 & R5 -> R6 & R5 -> R8
       (can-go R6 R3) (can-go R6 R5) (can-go R6 R9) ; Can go from R6 -> R3 & R6 -> R5 & R6 -> R9
       (can-go R7 R8) ; Can go from R7 -> R8
       (can-go R8 R5) (can-go R8 R7) ; Can go from R8 -> R5 & R8 -> R7
       (can-go R9 R6) ; Can go from R9 -> R6
   
       ; Object Locations
       (obj-at O1 R6) ; Object 1 at Room 6
       (obj-at O2 R4) ; Object 2 at Room 4
       (obj-at O3 R7) ; Object 3 at Room 7
   )
   
   (:goal (and
       (obj-at O1 R7) ; Object 1 at Room 6
       (obj-at O2 R2) ; Object 2 at Room 4
       (obj-at O3 R9) ; Object 3 at Room 7
   ))
   )
   
   ```
   **RSULT**
   
   ```
   
   Cite our paper if this tool was useful for your work:
   
   @inproceedings{magnaguagno2017web,
     title={WEB PLANNER: A Tool to Develop Classical Planning Domains and Visualize Heuristic State-Space Search},
     author={Magnaguagno, Maur{\'i}cio C and Pereira, Ramon Fraga and M{\'o}re, Martin D and Meneguzzi, Felipe},
     booktitle={Proceedings of the Workshop on User Interfaces and Scheduling and Planning, UISP},
     pages={32--38},
     year={2017}
   }
   
   Tue Nov 19 2019 02:07:16 GMT-0800
   Result: SUCCESS
   Domain: robotdomain
   Problem: robotcase_1
   Plan:
     (move-without-object r1 r4 bot)
     (pickup r4 o2 bot)
     (move-with-object r4 r5 o1 bot)
     (move-with-object r5 r6 o2 bot)
     (move-with-object r6 r3 o2 bot)
     (move-with-object r3 r2 o1 bot)
     (release r2 o2 bot)
     (move-without-object r2 r3 bot)
     (move-without-object r3 r6 bot)
     (pickup r6 o1 bot)
     (move-with-object r6 r5 o1 bot)
     (move-with-object r5 r8 o1 bot)
     (move-with-object r8 r7 o1 bot)
     (release r7 o1 bot)
     (pickup r7 o3 bot)
     (move-with-object r7 r8 o2 bot)
     (move-with-object r8 r5 o1 bot)
     (move-with-object r5 r6 o1 bot)
     (move-with-object r6 r9 o1 bot)
     (release r9 o3 bot)
   Execution time: 0.1205s
   ```
   
   
   
3. (**1 points**) Change the problem files so the robot starts at R2. Submit changes made and the solution.

   ```PDDL
   just changed line[17]
   from: (bot-at R1)
   to: (bot-at R2)
   ```

   **RESULT**
   
   ```
   Cite our paper if this tool was useful for your work:
   
   @inproceedings{magnaguagno2017web,
     title={WEB PLANNER: A Tool to Develop Classical Planning Domains and Visualize Heuristic State-Space Search},
     author={Magnaguagno, Maur{\'i}cio C and Pereira, Ramon Fraga and M{\'o}re, Martin D and Meneguzzi, Felipe},
     booktitle={Proceedings of the Workshop on User Interfaces and Scheduling and Planning, UISP},
     pages={32--38},
     year={2017}
   }
   
   Tue Nov 19 2019 02:09:23 GMT-0800
   Result: SUCCESS
   Domain: robotdomain
   Problem: robotcase_1
   Plan:
     (move-without-object r2 r3 bot)
     (move-without-object r3 r6 bot)
     (pickup r6 o1 bot)
     (move-with-object r6 r5 o1 bot)
     (move-with-object r5 r8 o1 bot)
     (move-with-object r8 r7 o1 bot)
     (release r7 o1 bot)
     (pickup r7 o3 bot)
     (move-with-object r7 r8 o2 bot)
     (move-with-object r8 r5 o1 bot)
     (move-with-object r5 r6 o1 bot)
     (move-with-object r6 r9 o1 bot)
     (release r9 o3 bot)
     (move-without-object r9 r6 bot)
     (move-without-object r6 r5 bot)
     (move-without-object r5 r4 bot)
     (pickup r4 o2 bot)
     (move-with-object r4 r5 o1 bot)
     (move-with-object r5 r6 o1 bot)
     (move-with-object r6 r3 o1 bot)
     (move-with-object r3 r2 o1 bot)
     (release r2 o2 bot)
   Execution time: 0.1525s
   ```
   
   

