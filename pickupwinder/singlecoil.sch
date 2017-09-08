*version 9.1 1037291972
u 30
L? 2
R? 2
C? 2
V? 3
? 4
@libraries
@analysis
.AC 1 2 0
+0 101
+1 10
+2 20k
.OP 0 
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 1770 
@status
n 0 116:05:18:02:41:04;1466232064 e 
s 2832 116:05:18:02:41:07;1466232067 e 
*page 1 0 970 720 iA
@ports
port 28 GND_earth 370 290 h
@parts
part 24 vac 250 250 h
a 0 u 13 0 -19 23 hcn 100 ACMAG=200mv
a 0 sp 0 0 0 50 hln 100 PART=vac
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 ap 9 0 20 10 hcn 100 REFDES=V2
part 2 l 270 250 h
a 0 sp 0 0 0 10 hlb 100 PART=l
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=L2012C
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=L1
a 0 ap 9 0 15 0 hln 100 REFDES=L1
a 0 u 13 0 15 25 hln 100 VALUE=10h
part 3 r 330 250 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 0 hln 100 REFDES=R1
a 0 u 13 0 15 25 hln 100 VALUE=15k
part 4 c 370 280 v
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 35 30 hln 100 REFDES=C1
a 0 u 13 0 10 40 hln 100 VALUE=200p
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 25 vdb 370 250 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=VDB(0)
a 0 a 0 0 4 22 hlb 100 LABEL=2
@conn
w 21
a 0 up 0:33 0 0 0 hln 100 V=
s 250 250 270 250 19
a 0 up 33 0 260 249 hct 100 V=
w 7
a 0 up 0:33 0 0 0 hln 100 V=
s 370 290 370 280 11
s 250 290 370 290 8
a 0 up 33 0 310 289 hct 100 V=
@junction
j 330 250
+ p 3 1
+ p 2 2
j 370 250
+ p 4 2
+ p 3 2
j 370 280
+ p 4 1
+ w 7
j 270 250
+ p 2 1
+ w 21
j 250 250
+ p 24 +
+ w 21
j 250 290
+ p 24 -
+ w 7
j 370 290
+ s 28
+ w 7
j 370 250
+ p 25 pin1
+ p 3 2
j 370 250
+ p 25 pin1
+ p 4 2
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
