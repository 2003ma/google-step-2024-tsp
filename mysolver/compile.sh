

for i in `seq 1 4`; do 
    g++ -o mysolver${i} mysolver${i}.cpp -std=c++11
done