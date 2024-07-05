echo '' > output
for ((i=0; i<10; i++)); do
    ./a.out >> output
    echo $i
    sleep 1
done
