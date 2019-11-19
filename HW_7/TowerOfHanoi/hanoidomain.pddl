;Header and description

(define (domain hanoi)

(:requirements :strips :equality)
(:predicates (on ?x ?y) (smaller ?x ?y) (disc ?X) (clear ?x)
)

(:action move
    :parameters (?disc ?from ?to)
    :precondition (and (smaller ?disc ?to) (smaller ?disc ?from)
                        (on ?disc ?from)
                        (clear ?disc) (clear ?to)
                        (not (= ?from ?to)))
    :effect (and 
                (clear ?from)
                (on ?disc ?to)
                (not (on ?disc ?from))
                (not (clear ?to))
            )
)
)