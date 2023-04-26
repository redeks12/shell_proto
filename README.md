# SimpleShell
Low-Level Programming and Algorithm Project assigned by  Holberton School.

## Prerequisites
Required files:

0. main.c
1. helperFunc.c
2. printFunc.c
3. specialFunc.c
4. stringFunc.c
5. stringFunc2.c
6. memoryFunc.c
7. customFunc.c
8. history.c
9. shellHeader.h

What things you need to install the program and how to install them:

GCC:
```
sudo apt-get install gcc
```

### Compiling and Executing
A step by step series of required commands need to get our HSH running.
 
##Compiling
Complile the code:
```
make
```
**or**

Manually compile:
```
gcc shellHeader.h memoryFunc.c stringFunc.c stringFunc2.c customFunc.c printFunc.c helperFunc.c specialFunc.c history.c main.c -o hsh
```
##Executing
Run hsh in **interactive** mode:
```
./hsh
```
Expected Result:
```
$
```
**or**

Run hsh in **non-interactive** mode:
```
echo **cmd** | ./hsh
```

## Authors
* **Anoop Macharla** (https://github.com/amacharla)

* **Minas Anton** (https://github.com/MinasA1)

## Additonal Help
Refer to **Man Page**
```
./man_1_simple_shell
```
## Acknowledgments

* https://intranet.hbtn.io/concepts/64
* Batch 3 Peers
