echo '' > output
for ((i=0; i<100; i++)); do
	./a.out >> output
	echo $i
	sleep 1
done
