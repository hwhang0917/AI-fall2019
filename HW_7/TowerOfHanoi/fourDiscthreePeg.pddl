(define (problem threeDiscHanoi) (:domain hanoi)
(:objects peg1 peg2 peg3 d1 d2 d3 d4
)

(:init
    (smaller d1 peg1) (smaller d1 peg2) (smaller d1 peg3) ;disc 1 is smaller than peg 1,2,3
    (smaller d2 peg1) (smaller d2 peg2) (smaller d2 peg3) ;disc 2 is smaller than peg 1,2,3
    (smaller d3 peg1) (smaller d3 peg2) (smaller d3 peg3) ;disc 3 is smaller than peg 1,2,3
    (smaller d4 peg1) (smaller d4 peg2) (smaller d4 peg3) ;disc 4 is smaller than peg 1,2,3

    (smaller d1 d2) (smaller d1 d3) (smaller d1 d4);disc 1 is smaller than disc 2,disc 3, disc 4
    (smaller d2 d3) (smaller d2 d4);disc 2 is smaller than disc 3, disc 4
    (smaller d3 d4) ; disc 3 is smaller than disc 4

    (clear d1) (clear peg2) (clear peg3) ;disc 1 is movable / peg 1, peg 2 is available
    (on d1 d2) (on d2 d3) (on d3 d4) (on d4 peg1) ;disc 1 is on disc 2, disc 2 is on disc 3, disc 3 is on disc 4, disc 4 is on peg 1
)

(:goal (and (on d1 d2) (on d2 d3) (on d3 d4) (on d4 peg3) ;dis 1 is on disc 2, disc 2 is on disc 3, disc 3 is on disc 4, disc 4 is on peg 3
))
)
