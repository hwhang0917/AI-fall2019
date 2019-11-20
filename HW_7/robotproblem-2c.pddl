(define (problem robotCase_2) (:domain robotDomain)
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
    (bot-at R2) ; bot is at room 1
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
