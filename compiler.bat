echo ************************ 
echo DO NOT CLOSE THIS WINDOW 
echo *************************

echo Load bin compiler directory
cd C:\gbdk\bin

echo Compile Libreries
lcc -c -o collisions.o C:\gbdk\projects\StarCombat\Libreries\collisions.c
lcc -c -o backgrounds.o C:\gbdk\projects\StarCombat\Libreries\backgrounds.c

echo Compile Main file
lcc -c -o main.o C:\gbdk\projects\StarCombat\main.c

echo Linking and creating gb file
lcc -o starcombat.gb main.o collisions.o backgrounds.o
