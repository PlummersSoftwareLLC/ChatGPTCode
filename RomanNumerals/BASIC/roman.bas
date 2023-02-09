10 rem dec-rom conv
20 dim sy$(13) : dim va(13)
30 sy$(1)="m" : sy$(2)="cm" : sy$(3)="d"
40 sy$(4)="cd" : sy$(5)="c" : sy$(6)="xc"
50 sy$(7)="l" : sy$(8)="xl" : sy$(9)="x"
60 sy$(10)="ix" : sy$(11)="v" : sy$(12)="iv"
70 sy$(13)="i"
80 va(1)=1000 : va(2)=900 : va(3)=500
90 va(4)=400 : va(5)=100 : va(6)=90
100 va(7)=50 : va(8)=40 : va(9)=10
110 va(10)=9 : va(11)=5 : va(12)=4
120 va(13)=1
130 let n=0 : let i=0 : let r$=""
140 input "decimal:"; n
150 for i=1 to 13
160 if n >= va(i) then r$=r$+sy$(i) : n=n-va(i) : goto 150
200 next i
210 print "rom:"; r$
230 end

