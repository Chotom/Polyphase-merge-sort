# polyphase-merge-sort
Variation of merge sort based on Fibonacci distribution

## Description
Program sort input file with polyphase merge sort, which is a variation of merge sort that sorts a file using a tapes. This version of algorithm uses three tapes to distribute series.

## Input
Input is text file contains unsorted records, where each record is separated by ';' and record is two values separated by ','. 

Each value in record is decimal representation of positive number saved as string, where first value is height of triagle and second is base. Example:
```
83,83;396,396;656,656;1123,1123;1281,1281;13,13;363,363;765,765;1244,1244;1490,1490;18,18;183,183;647,647;772,772;1031,1031;3,3;233,233;412,412;551,551;746,746;26,26;241,241;631,631;963,963;1266,1266;31,31;167,167;606,606;730,730;1026,1026;4,4;465,465;695,695;1038,1038;1504,1504;8,8;201,201;452,452;916,916;1333,1333;52,52;387,387;639,639;1124,1124;1310,1310;30,30;308,308;692,692;1087,1087;1376,1376;13,13;435,435;911,911;1102,1102;1444,1444;62,62;553,553;764,764;1175,1175;1575,1575;21,21;146,146;276,276;673,673;819,819;
```
 
 ## Output
 Output is sorted records in file by size of triangle field.
 
 ## Comparison
Comparison of theoretical values with real ones.
