# Test list

This files contains info about tests;

Folder | Description
------ | -----------
MakeFileTest | different Makefiles for each test
test         | different mains for test

## test description

make command | test file | Description
-----------  | --------- | -----------
`make -f ./MakeFileTest/MakefileTest_1` | mainTest_1.cpp | Channel, Server, Client , Messageprocessing objects creation/destruction
`make -f ./MakeFileTest/MakefileTest_2` | mainTest_2.cpp | Simulate **PING** Command  execution . Prints results on CLI
`make -f ./MakeFileTest/MakefileTest_3` | mainTest_3.cpp | prints default private vars Client object on CLI
`make -f ./MakeFileTest/MakefileTest_4` | mainTest_4.cpp | TEST  Channel modification Member and Invited 
`make -f ./MakeFileTest/MakefileTest_5` | mainTest_5.cpp | TEST  Channel Setters and Getters 

