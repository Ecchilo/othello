#! /usr/bin/env tclsh

package require Tk

set L 57
set position ""
set colors [list "green" "black" "white"]
set turn "white"
set player [lindex $argv 0]

wm title . "Othello"

frame .a -width [expr 10*$L] -height [expr $L] -relief sunken
label .a.score -text "score:"
label .a.playerlabel -text "player:"
label .a.player -text $player
label .a.space -width 30

pack .a -side top
pack .a.playerlabel -side left
pack .a.player -side left
pack .a.space -side left
pack .a.score -side right

canvas .c -width [expr 10*$L] -height [expr 10*$L] 
.c create rectangle $L $L [expr 9*$L] [expr 9*$L] -fill green
for {set i 1} {$i <= 9} {incr i} {
    set s [expr $i * $L]
    .c create line $L $s [expr 9*$L] $s
    .c create line $s $L $s [expr 9*$L]
}
pack .c

proc piece {i j color} {
    global L
    incr i
    incr j
    set x1 [expr ($i + 0.1) * $L]
    set y1 [expr ($j + 0.1) * $L]
    set x2 [expr ($i + 0.9) * $L]
    set y2 [expr ($j + 0.9) * $L]
    .c create oval $x1 $y1 $x2 $y2 -fill $color -outline "green"
}

proc read_position {} {
    global turn
    global player
    global colors
    puts stderr "$player reading position"
    global position
    gets stdin position
    set index [string index $position 0]
    set turn [lindex $colors $index]
    puts stderr "$player read position:"
    puts stderr $position
    display_position
}

proc display_position {} {
    global player
    global position
    global colors
    for {set i 0} {$i < 8} {incr i} {
	for {set j 0} {$j < 8} {incr j} {
	    set r [expr 8*$i + $j + 1]
	    set s [string index $position $r]
	    set color [lindex $colors $s]
	    piece $i $j $color
	}
    }
    puts stderr "$player displayed position:"
    puts stderr $position
}

proc send_move {i j} {
    global player
    puts "${i}${j}"
    puts stderr "$player sent move:"
    puts stderr ${i}${j}
}

bind .c <1> {
    global player
    puts stderr "$player intercepted button click"
    global L
    puts stderr "player: $player"
    puts stderr "turn: $turn"
    
    if {$turn != $player} {
	puts stderr "not ${player}'s turn"
	return 
    }
    set x [expr %x / $L - 1]
    set y [expr %y / $L - 1]
    send_move $x $y
    read_position
    display_position
    update
}

puts stderr "$player started"
fileevent stdin readable read_position

