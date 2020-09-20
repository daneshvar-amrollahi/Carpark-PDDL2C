(define   (problem parking)
  (:domain parking)
  (:objects
     car_00  car_01  car_02 - car
     curb_0 curb_1 - curb
  )
  (:init
    (= (total-cost) 0)
    (at-curb car_00)
    (at-curb-num car_00 curb_0)
    (behind-car car_01 car_00)
    (car-clear car_01)
    (at-curb car_02)
    (at-curb-num car_02 curb_1)
    (car-clear car_02)
  )
  (:goal
    (and
        (at-curb car_02)
        (at-curb-num car_02 curb_1)
        (behind-car car_01 car_02)
        (car-clear car_01)
        (at-curb car_00)
        (at-curb-num car_00 curb_0)
        (car-clear car_00)
    )
  )
(:metric minimize (total-cost))
)
; =========== INIT =========== 
;  curb_0: car_00 car_01 
;  curb_1: car_02
; ========== /INIT =========== 

; =========== GOAL =========== 
;  curb_0: car_00 
;  curb_1: car_02 car_01  
; =========== /GOAL =========== 
