echo ************************ 
echo DO NOT CLOSE THIS WINDOW 
echo *************************

echo Load bin compiler directory
cd C:\gbdk\bin

echo Compile Libreries
lcc -c -o collisions.o C:\Users\andres\Documents\repositories\starcombat\Libreries\collisions.c
lcc -c -o backgrounds.o C:\Users\andres\Documents\repositories\starcombat\Libreries\backgrounds.c

echo Compile Main file
lcc -c -o main.o C:\Users\andres\Documents\repositories\starcombat\main.c

echo Linking and creating gb file
lcc -o c:\Users\andres\Documents\repositories\starcombat\starcombat.gb main.o collisions.o backgrounds.o
