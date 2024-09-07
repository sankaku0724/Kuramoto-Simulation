# order.txt を用いた可視化 (秩序変数の時間変化)
set terminal pngcairo
set output 'order_time_evolution.png'

set xlabel "Time (t)"
set ylabel "Order Parameter (R)"
set title "Order Parameter Over Time"
set grid

plot 'order.txt' using 1:2 with lines lw 2 title "Order (R)", \
     'order.txt' using 1:3 with lines lw 2 title "Argument (Theta)"
