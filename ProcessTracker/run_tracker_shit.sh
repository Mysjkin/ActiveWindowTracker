./gui &
a_pid=$!

./tracker &
b_pid=$!;

wait $a_pid
kill -9 $b_pid;