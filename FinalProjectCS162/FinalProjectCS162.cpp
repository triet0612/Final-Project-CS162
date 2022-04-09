#include <string>
#include <iostream>
#include <fstream>
#include "CourseSystem.h"
#include "SinglyLinkedList.h"



using namespace std;

int main()
{
	CourseSystem courseSystem;
	courseSystem.startProgram();
	system("cls");
	ConsoleGraphics graphics = ConsoleGraphics::getInstance();
	graphics.gotoXY(0, 0);
	graphics.color(15);
	string s = R"(MMMMMMMMMMMMMMMMMMMMMMMMMMMMWKOXMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMNOl;oXMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMWKx:'.,kWMMMMMMMM
MMMMMMMMMMMMMMMMMMMMWN0o;....:KMMMMMMMMM
MMMMMMMMMMMMMMMMMWXkoc,.....'oNMMMMMMMMM
MMMMMMMMMMMMMMMWKd:'........,OMMMMMMMMMM
MMMMMMMMMMMMWNOl,...........cKMMMMMMMMMM
MMMMMMMMMMMXkc,............'dWMMMMMMMMMM
MMMMMMMMWXx:'',,'';;,'.....;OMMMMMMMMMMM
MMMMMMWXx;'..:c:cc:cl:'....lXMMMMMMMMMMM
MMMMMXx;'..';cc:cccclc;,'.,xWMMMMMMMMMMM
MMMNk:'....;c:c:lo:coc::'.:0MMMMMMMMMMMM
MWKl'......',:c::c::cc;...oNMMMMMMMMMMMM
M0:..........,:;;:;;:;'..,kWMMMMMMMMMMMM
Wx'...........''.........cKMMMMMMMMMMMMM
NKo,....................'dWMMMMMMMMMMMMM
xOXOc,..................;OMMMMMMMMMMMMMM
OdxOKOd:'...............lXMMMMMMMMMMMMMM
dcodxkO0Odc;'..........'xWMMMMMMMMMMMMMM
x,';looxkkOOkxoc;''....:0MMMMMMMMMMMMMMM
0:...',clloxkkkOkkkxddokNMMMMMMMMMMMMMMM
Xl.......',:cllodxkkkkkO0KXNWMMMMMMMMMMM
Nd'............';:ccllllodxkkkOKNWMMMMMM
Wk,....................'',;:clldxk0NMMMM
M0:...........................';codxONMM
MXl..............................':oddKW
MWx'......;c:c:;c;,cc:cllc:c:;:;...'ldd0
MMO;.....'dXX0clK0kKXxlOKol0KOKd'...'odd
MMKc.....'oOxkolkxoO0l,dk;:kxx0o'....:do
MMXl......,;',;,;,';;,.,;'';,';,.....;do
)";

	

	cout << s;
	system("pause");
	return 0;
}
