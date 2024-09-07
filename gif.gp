# gif.txt を用いた可視化 (位相の時間発展)
set terminal gif animate delay 10
set output 'phase_animation.gif'

set xrange [-1.5:1.5]
set yrange [-1.5:1.5]
set size square
set key off
set title "Phase Evolution"

do for [i=0:100] {
    plot 'gif.txt' index i using 1:2 with points pt 7 ps 1 lc rgb "red"
}
