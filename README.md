
### REQUIREMENTS

```
sudo apt-get install gnuplot libgnuplot-iostream-dev
```
### Compilation

```
g++ -o main knapsack.cpp -lboost_iostreams -lboost_system -lboost_filesystem
```
### Entry Pattern
```
x y
a b
w1 c1
...
wn cn
```
where:
X: Number of items
Y: Maximum capacity
w1 to wn: Weight of each item
c1 to cn: Cost of each item
### Run

```
./main entry.txt
``` 