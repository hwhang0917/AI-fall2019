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