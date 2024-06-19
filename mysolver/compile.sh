

for i in `seq 1 5`; do 
    g++ -o mysolver${i} mysolver${i}.cpp -std=c++11
done