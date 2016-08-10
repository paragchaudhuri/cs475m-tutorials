## INTRODUCTION
This program demonstarates the use of glPushMatrix() and glPopMatrix() to build a hierarchical modle. For more details please refer tutorial_04.pdf.<br>
Following is the key defination :

|    Key    |                Operation                                    |
|:---------:|:-----------------------------------------------------------:|
| Esc       | Close the window                                            |
| 1         | Sets root arm as curren operational node                    |
| 2         | Sets second arm as curren operational node                  |
| 3         | Sets last arm as curren operational node                    |
| Left      | Rotates the current arm counter clockwise local over y-axis |
| Right     | Rotates the current arm clockwise over local y-axis         |
| Up        | Rotates the current arm counter clockwise over local x-axis |
| Down      | Rotates the current arm clockwise over local x-axis         |
| Page Up   | Rotates the current arm counter clockwise over local z-axis |
| Page Down | Rotates the current arm clockwise over local z-axis         |


## COMPILATION
Compile the code using makefile. <br>
`$ make`

## RUN
After successfull compilation just type the following command in your terminal to execute the binary.<br>
`$ ./tutorial_04` <br>
