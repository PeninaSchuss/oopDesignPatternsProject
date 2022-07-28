���� ������ ����� �����
������ ���
������: ����� ���. �"�: 207256215
���� ��� ���. �"�: 324102037
������� �� ������ �� ���� Xonix  "���� �����", ��� ����� ������ SFML.

����: ���� ����� �� ������ �� ���� ������� ��� ����� ����.

������� ������� �������:
AddTimeGift
���� ������� ����. ����� ������ Gift
Animation
����� ������ �� ��������� �������.
BackSoundCommand
����� �� ����� ������ ���� �������. ����� � Command
Board
����� ������� �� �� ����� ���� �����.
CanMoveToPlace
����� ������� �� ������ ����� �� �������. (����� ���� Strategy )
CollisionHandling
����� ������ �� ���������� �����. (������ � MultyMethod)
Command
����� �� ��� ������� �� �����. (Command design pattern)
Controller
����� ������ �� �����.
Display
����� ������ ������ ������� ��� ������� ������� ���.
DynamicObj
����� ����� ������ �� ��������� ��������� �����.
Enemies
����� ������� �� �����.
EnemyFactory
����� ������ �� ������� ( Factory pattern)
FreezeEnemiesGift
���� ������� �� ������� �����.  ����� � Gift
GameController
����� ������� �� ����� ������ �� ������ ���.
Gift
����� ����� ������ �� ������.
GiftFactory
����� ������ ���� ����� ������. (Factory design) 
Graphics
����� ��������, �� ������ �� ��������� �������� ���'.
ImmunePlayer
����� ������ � player , ��� ���� ����� ����� ���� ����� ������ ������� ����� ������ ������.
ImmunetyGift
����� ����� �� ����� ����� ���� �����. (����� � Gift)
InfoOfLevel
����� �� ������ ������� ���� �� ���.
InformationDisplay
����� �� ���� �� ����� ������ ������ �� ���� ����� �� �����.
KillEnemyGift
���� ������ ����� ����� ���� ����, ������ �� �� ������� ���� ����� ����. (����� � Gift)
KillingPlayer
����� ������ � Player . ��� ���� ���� ���� �����, ������ ������� ����� ����.
Level
����� ������ ��� ����� �����.
LifeGift
����� � Gift , ���� ������� ����.
Menu
������ �� ������ �� ������ ����� . (Command)
Move
������ �� ������ ������ ������ (Strategy) 
MoveEverywhere
����� ������� �� ����� ��� ����� ����. ����� � CanMoveToPlace 
MoveToBlocked
����� ������� �� ����� �� �� ������� ������� ����. ����� � CanMoveToPlace 
MoveToUnBlocked
����� ������� �� ����� �� �� ������� ����� ������ ����. ����� � CanMoveToPlace 
NewGameCommand
����� ����� �����. ����� � Command
NoiseCommand
����� ����� ���� �� ����� ���� �����. ����� � Command
Object
����� ����� ������ �� ���������� �����.
Player
������ �� �����.
RandomMove
������ ������� �� ����� ��������. ����� � Move
SettingsCommand
����� ����� �������. ����� � Command
SettingsMenu
����� �������. ����� � Menu
ShowInstructionsCommand
����� ����� ������ �����. ����� � Command
SimpleMove
����� ������� �� ����� ����� �� ����. ����� � Move
SmartMove
����� ������� �� ����� ���� ������ ��� �����. ����� � Move
StartMenu
������ �������, ����� � Menu
StaticObj
����� ����� ������ �� ��������� ������� �����. ����� � Object
TerritoryEater
���� ����� � Enemies. ��� ���� ����� ����� ����� ������ ����� ���� ������.


���� ������:

����� �� ������ ���������, ������ ����� ������:
   
AddTimeGift.h
Animation.h
BackSoundCommand.h
Board.h
CanMoveToPlace.h
CollisionHandling.h
Command.h
Controller.h
Display.h
DynamicObj.h
Enemies.h
EnemyFactory.h
FreezeEnemiesGift.h
GameController.h
Gift.h
GiftFactory.h
Graphics.h
ImmunePlayer.h
ImmunetyGift.h
InfoOfLevel.h
InformationDisplay.h
KillEnemyGift.h
KillingPlayer.h
Level.h
LifeGift.h
Menu.h
Move.h
MoveEverywhere.h
MoveToBlocked.h
MoveToUnBlocked.h
NewGameCommand.h
NoiseCommand.h
Object.h
Player.h
RandomMove.h
SettingsCommand.h
SettingsMenu.h
ShowInstructionsCommand.h
SimpleMove.h
SmartMove.h
StartMenu.h
StaticObj.h
TerritoryEater.h
Utilities.h
����� �� ������ �� �������� �enum�� �������� ������.



����� �� ����� ��������� ������� �� ������:
AddTimeGift.cpp
Animation.cpp
BackSoundCommand.cpp
Board.cpp
CollisionHandling.cpp
Controller.cpp
Display.cpp
Enemies.cpp
EnemyFactory.cpp
FreezeEnemiesGift.cpp
GameController.cpp
Gift.cpp
GiftFactory.cpp
Graphics.cpp
ImmunetyGift.cpp
InfoOfLevel.cpp
InformationDisplay.cpp
KillEnemyGift.cpp
Level.cpp
LifeGift.cpp
Menu.cpp
Move.cpp
MoveEverywhere.cpp
MoveToBlocked.cpp
MoveToUnBlocked.cpp
NoiseCommand.cpp
Player.cpp
RandomMove.cpp
SettingsCommand.cpp
SettingsMenu.cpp
ShowInstructionsCommand.cpp
SimpleMove.cpp
SmartMove.cpp
StartMenu.cpp
TerritoryEater.cpp

���� ������ ������� ���������:
������� �������� �� uniqe_ptr ���� ������� �������.
������� ������ �� ����� ���� ������� �� ����.

����� ������:
��� ����� �������!

���������� ������� �����:
������� ���� design patterns:
������� � MultyMethod ������ ����������.
������� �factory+strategy ���� ���� �������, ���� �� ����� ���� ��� ������. ���� ������ �� ������ �� ����� ���� ���� ��� ������� ����� ����� ���� �����. (strategy ���� strategy ) 
������� � factory ���� ���� ����� ������� ����� �����.
������� � Command ���� Command ���� ������ �������, ������ �� ����� ���� �� ������.
������� � singleton ���� ����� Graphics ��� ������ �� �Textures, Sounds ���� ����� ���'. ��� ���� ������ ���� ������� ���� ���� ����� �� �� �������.

����� ������� ��������� ��������� : FloodFIll  ���� ����� ���� ����� �"� �����. (����� ��� ��� ����� ���� ���� ����� ���� ���� ����)

����� ������:
�� ���� ����� �� ����� ������� �����.
���� ����� ����� ��� ��� �� ������ - ���� ������ ��� ����� �� ����� ����� �� ��� ������� �� "�� ���� ������ ���� ����", ������ � facrory �� ����� ����.
���� �����:
���� ����� ����� �� ���� ������ ��� ���.
�� �� ���� ����, ���� �� ������ ������ ���� ����� ����.
������ �������� ����� ����:
 �� ��� ���� ����� (��� ������ �����) .
�� ��� �� �� ���� ���� ����� ����� (���� ������ ������)
�� ���� ����.

������� �����:
���� ���� - ����� �� ���� .�� �� ���� ������ (���� ��� ����)
���� ��� - ���� ���� �����. ����� �� �� ���� .
����- ������ ����� �� ���� ����� ����. �� ����� ���� ��� ����� �� ���� ���� ����� ���� ����.
���� ����� - ���� �� ������ ������ �"� �����.

���� �����:
����� ����
����� ���
����� ������� ���� ��� �����
���� ������ �� ����� ����� ���� ��� �����
���� ������ �� ����� ����� �� �� ������� ����� ��� (���� ����� ����� ����� �� ���� �����) ���� ��� �����.
