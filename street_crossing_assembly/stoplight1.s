// WORKING STREETCROSSING GAME
.equ INPUT, 0
.equ OUTPUT, 1
.equ LOW, 0
.equ HIGH, 1
.equ RED_PIN, 23	// wiringPi 23, bcm 13, phys 33
.equ GRN_PIN, 24	// wiringPi 24, bcm 19, phys 35
.equ YEL_PIN, 25	// wiringPi 25, bcm 26, phys 37
.equ RGB_RED, 27	// rgb red led pin wpi 27, bcm 16, phys 36
.equ RGB_GRN, 28	// rgb green led pin wpi 28, bcm 20, phys 38
.equ STP_PIN, 29	// wiringPi 29 - STOP PIN 

.text
.global main
main:
	push {lr}
	bl wiringPiSetup	// wiringPi()

	mov r0, #STP_PIN
	bl setPinInput		// set button as input

	mov r0, #RED_PIN
	bl setPinOutput		// set red pin to output (red stoplight)

	mov r0, #GRN_PIN
	bl setPinOutput		// set green pin to output (green stoplight)

	mov r0, #YEL_PIN
	bl setPinOutput		// set yellow pin to output (yellow stoplight)

	mov r0, #RGB_RED
	bl setPinOutput		// set rgb red to output (red crosswalk sign)

	mov r0, #RGB_GRN
	bl setPinOutput		// set rgb green to output (green crosswalk sign)

	mov r0, #RGB_RED
	bl pinOn		// turn on rbg red pin (red crosswalk sign)

	mov r2, #0		// counter (loop 4 times)
loop:
	cmp r2, #4
	bge end_loop		// if button pressed 4 times, end program
	mov r0, #GRN_PIN
	bl pinOn		// turn on green stoplight

	mov r0, #STP_PIN
	bl digitalRead		// read button 

	cmp r0, #LOW		// if not pressed (r0 = 0), loop back to top (stoplight still green)
	bne button_pressed	// if pressed (r0 = 1), go to button_pressed
	bal loop

button_pressed:
	mov r0, #GRN_PIN
	bl pinOff		// turn off green stoplight

	mov r0, #YEL_PIN
	bl pinOn		// turn on yellow stoplight to slow 
	ldr r0, =#3000		// keep yellow pin on for 3 seconds
	bl delay

	mov r0, #YEL_PIN
	bl pinOff		// turn yellow pin off

	mov r0, #RED_PIN
	bl pinOn		// turn red stoplight on
	ldr r0, =#3000
	bl delay

	mov r0, #RGB_GRN
	bl pinOn		// turn green crosswalk sign on
	ldr r0, =#3000
	bl delay

	mov r0, #RGB_GRN	// turn green crosswalk sign off
	bl pinOff

	// **** flashing red crosswalk sign *** (tried to do a for loop, failed)
	// flashes on 3 times
	mov r0, #RGB_RED
	bl pinOn		// turn on red crosswalk sign for blinking timer
	ldr r0, =#1000
	bl delay
	mov r0, #RGB_RED
	bl pinOff
	ldr r0, =#1000
	bl delay
	mov r0, #RGB_RED
	bl pinOn
	ldr r0, =#1000
	bl delay
	mov r0, #RGB_RED
	bl pinOff
	ldr r0, =#1000
	bl delay
	mov r0, #RGB_RED
	bl pinOn
	ldr r0, =#1000
	bl delay
	mov r0, #RGB_RED
	bl pinOff
	ldr r0, =#1000
	bl delay

	mov r0, #RGB_RED
	bl pinOn
	ldr r0, =#3000
	bl delay

	mov r0, #RED_PIN
	bl pinOff

	add r2, r2, #1
	b loop

end_loop:
	mov r0, #0
	pop {pc}


setPinInput:
	push {lr}
	mov r1, #INPUT
	bl pinMode
	pop {pc}

setPinOutput:
	push {lr}
	mov r1, #OUTPUT
	bl pinMode
	pop {pc}

pinOn:
	push {lr}
	mov r1, #HIGH
	bl digitalWrite
	pop {pc}

pinOff:
	push {lr}
	mov r1, #LOW
	bl digitalWrite
	pop {pc}
