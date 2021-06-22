# PLATOTERM Skeleton for RunCPM

This is a PLATOTERM skeleton for RunCPM.

It contains a complete RunCPM environment, with a system on drive A:, a copy of HiTech C on B:, the source code on C:, and the binary output on D:.

It needs:

* Keyboard routines, in keyboard.c
* Screen routines, in screen.c
* I/O routines (get/put from socket) in io.c

I've commented out example code throughout each.

# Building

```
B0>SUBMIT BUILD
```

# Running

```
D0>PLATO <hostname> <port> e.g.
D0>PLATO IRATA.ONLINE 8005 
```

# Keyboard Mapping

CP/M Keyboard
-----------------

The PLATO keyboard is mapped onto the CP/M keyboard. CTRL is used to access the special PLATO keys, with ESC acting as a SHIFT key in combination for shifted combinations.

| PLATO KEY  	| Apple Key  	|
|---	|---	|
| ANS  	| CTRL-A  	|
| BACK  	| CTRL-B  	|
| SHIFT-BACK | ESC CTRL-B |
| COPY | CTRL-C |
| SHIFT-COPY | ESC CTRL-C |
| DATA | CTRL-D ||
| SHIFT-DATA | ESC CTRL-D |
| EDIT | CTRL-E |
| SHIFT-EDIT | ESC CTRL-E |
| FONT | CTRL-F |
| &#247; | CTRL-G | 
| HELP | CTRL-I |
| SHIFT-HELP | ESC CTRL-H |
| LAB | CTRL-L |
| SHIFT-LAB | ESC CTRL-L |
| SUPER | CTRL-P |
| SHIFT-SUPER | ESC CTRL-P |
| SQUARE | CTRL-Q | 
| ACCESS | ESC CTRL-Q |
| STOP | CTRL-S |
| SHIFT-STOP | ESC CTRL-S | 
| TERM | CTRL-T |
| &#215; | CTRL-X |
| SUB | CTRL-Y |
| SHIFT-SUB | ESC CTRL-Y |
| Setup | CTRL-Z |
| Shift Lock (for CPM) | ESC ESC |  
--
