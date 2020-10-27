# C++ File mapping into memory

Normally projects has the need to read some configuration files such as application parameters, important data, etc. As a backend,
everyone wants the most speed up performing routines, in this case reading files. To check, investigate and corroborate which manner is the
best way and better option to choice, I have tested different ways to do it.

## **Setup**

- CPU: Intel Core i7-9700K 3.6Ghz
- RAM: G.Skill Trident Z RGB DDR4 3200MHz PC4-25600 16GB 2x8GB CL16
- MB: Gigabyte Z390 Aorus Pro

## **Tests**

There are two files to test. small file is 391 KB big and big file is 24.607KB respectively.

- Kernel mapping is based on kernel API's offered from S.O.
- traditional_read is loop based, reading until no data is available (EOF reached).
- stream_mapping is stream buffer based on stl stream wrapper. In this case I have tried for vector and deque containers.

### **Benchmark results**


#### Windows OS, W10 (MVSC)
##### OPTIMIZATIONS **DISABLED**

```
Kernel mapping (small.file) --> 1 iteration: 00m:00s:00ms:160000ns:00?s:
traditional_read (small.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:00ms:495000ns:00?s:
traditional_read (small.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:00ms:274000ns:00?s:
traditional_read (small.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:00ms:231000ns:00?s:
traditional_read (small.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:00ms:212000ns:00?s:
traditional_read (small.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:00ms:206000ns:00?s:
stream_mapping_deque (small.file) --> 1 iteration: 00m:00s:516ms:424000ns:00?s:
stream_mapping_vector (small.file) --> 1 iteration: 00m:00s:124ms:428200ns:00?s:

Kernel mapping (small.file) --> 1000 iteration: 00m:00s:66ms:592000ns:00?s:
traditional_read (small.file). Buffer size: 512 bytes --> 1000 iteration: 00m:00s:294ms:864000ns:00?s:
traditional_read (small.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:00s:239ms:86000ns:00?s:
traditional_read (small.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:00s:205ms:902000ns:00?s:
traditional_read (small.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:00s:192ms:53000ns:00?s:
traditional_read (small.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:00s:184ms:625000ns:00?s:
stream_mapping_deque (small.file) --> 1000 iteration: 08m:27s:481ms:271900ns:00?s:
stream_mapping_vector (small.file) --> 1000 iteration: 02m:02s:97ms:739500ns:00?s:

Kernel mapping (small.file) --> 10000 iteration: 00m:00s:649ms:439000ns:00?s:
traditional_read (small.file). Buffer size: 512 bytes --> 10000 iteration: 00m:02s:884ms:373000ns:00?s:
traditional_read (small.file). Buffer size: 1024 bytes --> 10000 iteration: 00m:02s:294ms:856000ns:00?s:
traditional_read (small.file). Buffer size: 2048 bytes --> 10000 iteration: 00m:02s:15ms:295000ns:00?s:
traditional_read (small.file). Buffer size: 4096 bytes --> 10000 iteration: 00m:01s:932ms:788000ns:00?s:
traditional_read (small.file). Buffer size: 8192 bytes --> 10000 iteration: 00m:01s:834ms:6000ns:00?s:
stream_mapping_deque (small.file) --> 10000 iteration: 84m:28s:351ms:587200ns:00?s:
stream_mapping_vector (small.file) --> 10000 iteration: 20m:32s:105ms:739000ns:00?s:


Kernel mapping (big.file) --> 1 iteration: 00m:00s:00ms:213000ns:00?s:
traditional_read (big.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:19ms:635000ns:00?s:
traditional_read (big.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:15ms:968000ns:00?s:
traditional_read (big.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:13ms:960000ns:00?s:
traditional_read (big.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:13ms:643000ns:00?s:
traditional_read (big.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:12ms:875000ns:00?s:
stream_mapping_deque (big.file) --> 1 iteration: 00m:32s:39ms:906600ns:00?s:
stream_mapping_vector (big.file) --> 1 iteration: 00m:07s:761ms:89700ns:00?s:

Kernel mapping (big.file) --> 1000 iteration: 00m:00s:65ms:682000ns:00?s:
traditional_read (big.file). Buffer size: 512 bytes --> 1000 iteration: 00m:19s:296ms:127000ns:00?s:
traditional_read (big.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:15s:614ms:265000ns:00?s:
traditional_read (big.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:13s:792ms:902000ns:00?s:
traditional_read (big.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:13s:470ms:364000ns:00?s:
traditional_read (big.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:12s:945ms:756000ns:00?s:
```

Test was stopped at 1000 iterations on stream_mapping due to slow it was. 
Main reason is due to the overhead that stream has plus memory reallocation of the dynamic containers (vector, deque) when data is inserted on them.
As you can see, these ones are very slow ways in comparison with the other ones.

##### OPTIMIZATIONS **ENABLED**

```
Kernel mapping (small.file) --> 1 iteration: 00m:00s:00ms:205us:200ns
traditional_read (small.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:00ms:260us:800ns
traditional_read (small.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:00ms:205us:900ns
traditional_read (small.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:00ms:199us:700ns
traditional_read (small.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:00ms:180us:800ns
traditional_read (small.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:00ms:184us:700ns
one transaction seek (small.file) --> 1 iteration: 00m:00s:00ms:325us:600ns
one transaction fs (small.file) --> 1 iteration: 00m:00s:00ms:207us:200ns
stream_mapping_deque (small.file) --> 1 iteration: 00m:00s:03ms:863us:300ns
stream_mapping_vector (small.file) --> 1 iteration: 00m:00s:02ms:118us:100ns

Kernel mapping (small.file) --> 1000 iteration: 00m:00s:74ms:845us:800ns
traditional_read (small.file). Buffer size: 512 bytes --> 1000 iteration: 00m:00s:198ms:492us:700ns
traditional_read (small.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:00s:156ms:553us:00ns
traditional_read (small.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:00s:151ms:891us:300ns
traditional_read (small.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:00s:153ms:356us:200ns
traditional_read (small.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:00s:151ms:832us:800ns
one transaction seek (small.file) --> 1000 iteration: 00m:00s:192ms:130us:100ns
one transaction fs (small.file) --> 1000 iteration: 00m:00s:199ms:318us:500ns
stream_mapping_deque (small.file) --> 1000 iteration: 00m:03s:430ms:518us:800ns
stream_mapping_vector (small.file) --> 1000 iteration: 00m:01s:838ms:446us:900ns

Kernel mapping (small.file) --> 10000 iteration: 00m:00s:644ms:474us:100ns
traditional_read (small.file). Buffer size: 512 bytes --> 10000 iteration: 00m:01s:698ms:462us:900ns
traditional_read (small.file). Buffer size: 1024 bytes --> 10000 iteration: 00m:01s:580ms:255us:500ns
traditional_read (small.file). Buffer size: 2048 bytes --> 10000 iteration: 00m:01s:625ms:406us:700ns
traditional_read (small.file). Buffer size: 4096 bytes --> 10000 iteration: 00m:01s:521ms:679us:100ns
traditional_read (small.file). Buffer size: 8192 bytes --> 10000 iteration: 00m:01s:507ms:272us:200ns
one transaction seek (small.file) --> 10000 iteration: 00m:01s:504ms:228us:500ns
one transaction fs (small.file) --> 10000 iteration: 00m:01s:611ms:828us:900ns
stream_mapping_deque (small.file) --> 10000 iteration: 00m:32s:828ms:685us:00ns
stream_mapping_vector (small.file) --> 10000 iteration: 00m:18s:317ms:534us:300ns


Kernel mapping (big.file) --> 1 iteration: 00m:00s:00ms:128us:500ns
traditional_read (big.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:12ms:935us:100ns
traditional_read (big.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:12ms:64us:300ns
traditional_read (big.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:11ms:348us:00ns
traditional_read (big.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:11ms:580us:700ns
traditional_read (big.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:11ms:384us:200ns
one transaction seek (big.file) --> 1 iteration: 00m:00s:15ms:271us:700ns
one transaction fs (big.file) --> 1 iteration: 00m:00s:15ms:371us:900ns
stream_mapping_deque (big.file) --> 1 iteration: 00m:00s:230ms:220us:200ns
stream_mapping_vector (big.file) --> 1 iteration: 00m:00s:128ms:177us:800ns

Kernel mapping (big.file) --> 1000 iteration: 00m:00s:64ms:894us:100ns
traditional_read (big.file). Buffer size: 512 bytes --> 1000 iteration: 00m:12s:26ms:150us:600ns
traditional_read (big.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:11s:286ms:76us:500ns
traditional_read (big.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:11s:26ms:305us:800ns
traditional_read (big.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:11s:155ms:628us:400ns
traditional_read (big.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:11s:19ms:846us:700ns
one transaction seek (big.file) --> 1000 iteration: 00m:15s:73ms:317us:500ns
one transaction fs (big.file) --> 1000 iteration: 00m:14s:998ms:351us:900ns
stream_mapping_deque (big.file) --> 1000 iteration: 03m:41s:891ms:713us:800ns
stream_mapping_vector (big.file) --> 1000 iteration: 02m:05s:915ms:278us:100ns

Kernel mapping (big.file) --> 10000 iteration: 00m:00s:645ms:78us:800ns
traditional_read (big.file). Buffer size: 512 bytes --> 10000 iteration: 01m:59s:532ms:439us:900ns
traditional_read (big.file). Buffer size: 1024 bytes --> 10000 iteration: 01m:52s:720ms:897us:300ns
traditional_read (big.file). Buffer size: 2048 bytes --> 10000 iteration: 01m:49s:887ms:75us:900ns
traditional_read (big.file). Buffer size: 4096 bytes --> 10000 iteration: 01m:50s:379ms:666us:100ns
traditional_read (big.file). Buffer size: 8192 bytes --> 10000 iteration: 01m:49s:104ms:594us:900ns
one transaction seek (big.file) --> 10000 iteration: 02m:30s:72ms:135us:900ns
one transaction fs (big.file) --> 10000 iteration: 02m:30s:190ms:157us:300ns
stream_mapping_deque (big.file) --> 10000 iteration: 37m:02s:158ms:177us:200ns
stream_mapping_vector (big.file) --> 10000 iteration: 20m:58s:607ms:08us:100ns

Total time taken: 80m:47s:637ms:662us:300ns
```

As you can appreciate, the power of compiler and the magic of the optimizations are awesome even we could finish the test!
Again we can confirm that stream_mapping is slowest than other options and kernel is always winner, but now, difference is minimal.


#### Linux OS, Ubuntu 18.04 LTS **WSL**. (g++)
##### OPTIMIZATIONS **DISABLED**

```
Kernel mapping (small.file) --> 1 iteration: 00m:00s:09ms:550000ns:00μs:
traditional_read (small.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:00ms:277000ns:00μs:
traditional_read (small.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:00ms:213000ns:00μs:
traditional_read (small.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:00ms:208000ns:00μs:
traditional_read (small.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:00ms:216000ns:00μs:
traditional_read (small.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:00ms:188000ns:00μs:
stream_mapping_deque (small.file) --> 1 iteration: 00m:00s:20ms:383900ns:00μs:
stream_mapping_vector (small.file) --> 1 iteration: 00m:00s:21ms:923800ns:00μs:

Kernel mapping (small.file) --> 1000 iteration: 00m:00s:68ms:878000ns:00μs:
traditional_read (small.file). Buffer size: 512 bytes --> 1000 iteration: 00m:00s:191ms:751000ns:00μs:
traditional_read (small.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:00s:184ms:256000ns:00μs:
traditional_read (small.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:00s:189ms:880000ns:00μs:
traditional_read (small.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:00s:184ms:563000ns:00μs:
traditional_read (small.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:00s:171ms:595000ns:00μs:
stream_mapping_deque (small.file) --> 1000 iteration: 00m:19s:958ms:444300ns:00μs:
stream_mapping_vector (small.file) --> 1000 iteration: 00m:21s:920ms:453600ns:00μs:

Kernel mapping (small.file) --> 10000 iteration: 00m:00s:686ms:3000ns:00μs:
traditional_read (small.file). Buffer size: 512 bytes --> 10000 iteration: 00m:01s:982ms:367000ns:00μs:
traditional_read (small.file). Buffer size: 1024 bytes --> 10000 iteration: 00m:01s:889ms:142000ns:00μs:
traditional_read (small.file). Buffer size: 2048 bytes --> 10000 iteration: 00m:01s:881ms:591000ns:00μs:
traditional_read (small.file). Buffer size: 4096 bytes --> 10000 iteration: 00m:01s:852ms:704000ns:00μs:
traditional_read (small.file). Buffer size: 8192 bytes --> 10000 iteration: 00m:01s:725ms:118000ns:00μs:
stream_mapping_deque (small.file) --> 10000 iteration: 03m:20s:01ms:285700ns:00μs:
stream_mapping_vector (small.file) --> 10000 iteration: 03m:39s:323ms:950800ns:00μs:


Kernel mapping (big.file) --> 1 iteration: 00m:00s:20ms:277000ns:00μs:
traditional_read (big.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:19ms:615000ns:00μs:
traditional_read (big.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:11ms:478000ns:00μs:
traditional_read (big.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:11ms:401000ns:00μs:
traditional_read (big.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:11ms:342000ns:00μs:
traditional_read (big.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:10ms:502000ns:00μs:
stream_mapping_deque (big.file) --> 1 iteration: 00m:01s:287ms:345900ns:00μs:
stream_mapping_vector (big.file) --> 1 iteration: 00m:01s:373ms:586600ns:00μs:

Kernel mapping (big.file) --> 1000 iteration: 00m:00s:380ms:641000ns:00μs:
traditional_read (big.file). Buffer size: 512 bytes --> 1000 iteration: 00m:11s:665ms:690000ns:00μs:
traditional_read (big.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:11s:283ms:810000ns:00μs:
traditional_read (big.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:11s:73ms:377000ns:00μs:
traditional_read (big.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:11s:53ms:299000ns:00μs:
traditional_read (big.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:10s:145ms:325000ns:00μs:
stream_mapping_deque (big.file) --> 1000 iteration: 20m:59s:899ms:158100ns:00μs:
stream_mapping_vector (big.file) --> 1000 iteration: 22m:52s:348ms:981600ns:00μs:

Kernel mapping (big.file) --> 10000 iteration: 00m:03s:815ms:653000ns:00μs:
traditional_read (big.file). Buffer size: 512 bytes --> 10000 iteration: 01m:54s:292ms:204000ns:00μs:
traditional_read (big.file). Buffer size: 1024 bytes --> 10000 iteration: 01m:50s:865ms:396000ns:00μs:
traditional_read (big.file). Buffer size: 2048 bytes --> 10000 iteration: 01m:49s:934ms:714000ns:00μs:
traditional_read (big.file). Buffer size: 4096 bytes --> 10000 iteration: 01m:49s:662ms:63000ns:00μs:
traditional_read (big.file). Buffer size: 8192 bytes --> 10000 iteration: 01m:41s:348ms:871000ns:00μs:
```

It seems and **is** demonstrated that Linux is faster than windows. At least when we are comparing non optimized versions.

##### OPTIMIZATIONS **ENABLED**
```
Kernel mapping (small.file) --> 1 iteration: 00m:00s:00ms:79us:800ns
traditional_read (small.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:00ms:282us:400ns
traditional_read (small.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:00ms:192us:300ns
traditional_read (small.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:00ms:193us:100ns
traditional_read (small.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:00ms:224us:500ns
traditional_read (small.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:00ms:181us:900ns
one transaction seek (small.file) --> 1 iteration: 00m:00s:00ms:297us:600ns
one transaction fs (small.file) --> 1 iteration: 00m:00s:00ms:272us:400ns
stream_mapping_deque (small.file) --> 1 iteration: 00m:00s:01ms:05us:00ns
stream_mapping_vector (small.file) --> 1 iteration: 00m:00s:01ms:316us:800ns

Kernel mapping (small.file) --> 1000 iteration: 00m:00s:51ms:29us:600ns
traditional_read (small.file). Buffer size: 512 bytes --> 1000 iteration: 00m:00s:179ms:273us:900ns
traditional_read (small.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:00s:172ms:766us:900ns
traditional_read (small.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:00s:172ms:704us:900ns
traditional_read (small.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:00s:174ms:634us:800ns
traditional_read (small.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:00s:158ms:527us:00ns
one transaction seek (small.file) --> 1000 iteration: 00m:00s:67ms:242us:00ns
one transaction fs (small.file) --> 1000 iteration: 00m:00s:66ms:526us:400ns
stream_mapping_deque (small.file) --> 1000 iteration: 00m:00s:981ms:306us:600ns
stream_mapping_vector (small.file) --> 1000 iteration: 00m:01s:515ms:845us:800ns

Kernel mapping (small.file) --> 10000 iteration: 00m:00s:506ms:754us:400ns
traditional_read (small.file). Buffer size: 512 bytes --> 10000 iteration: 00m:01s:768ms:713us:800ns
traditional_read (small.file). Buffer size: 1024 bytes --> 10000 iteration: 00m:01s:719ms:127us:300ns
traditional_read (small.file). Buffer size: 2048 bytes --> 10000 iteration: 00m:01s:708ms:917us:00ns
traditional_read (small.file). Buffer size: 4096 bytes --> 10000 iteration: 00m:01s:705ms:724us:700ns
traditional_read (small.file). Buffer size: 8192 bytes --> 10000 iteration: 00m:01s:592ms:674us:300ns
one transaction seek (small.file) --> 10000 iteration: 00m:00s:645ms:906us:900ns
one transaction fs (small.file) --> 10000 iteration: 00m:00s:635ms:452us:900ns
stream_mapping_deque (small.file) --> 10000 iteration: 00m:09s:798ms:258us:100ns
stream_mapping_vector (small.file) --> 10000 iteration: 00m:15s:73ms:79us:500ns


Kernel mapping (big.file) --> 1 iteration: 00m:00s:00ms:396us:700ns
traditional_read (big.file). Buffer size: 512 bytes --> 1 iteration: 00m:00s:11ms:690us:700ns
traditional_read (big.file). Buffer size: 1024 bytes --> 1 iteration: 00m:00s:11ms:166us:300ns
traditional_read (big.file). Buffer size: 2048 bytes --> 1 iteration: 00m:00s:11ms:216us:200ns
traditional_read (big.file). Buffer size: 4096 bytes --> 1 iteration: 00m:00s:11ms:50us:900ns
traditional_read (big.file). Buffer size: 8192 bytes --> 1 iteration: 00m:00s:10ms:737us:600ns
one transaction seek (big.file) --> 1 iteration: 00m:00s:29ms:321us:500ns
one transaction fs (big.file) --> 1 iteration: 00m:00s:27ms:237us:400ns
stream_mapping_deque (big.file) --> 1 iteration: 00m:00s:64ms:375us:800ns
stream_mapping_vector (big.file) --> 1 iteration: 00m:00s:86ms:409us:200ns

Kernel mapping (big.file) --> 1000 iteration: 00m:00s:364ms:950us:400ns
traditional_read (big.file). Buffer size: 512 bytes --> 1000 iteration: 00m:11s:287ms:655us:800ns
traditional_read (big.file). Buffer size: 1024 bytes --> 1000 iteration: 00m:11s:86ms:698us:800ns
traditional_read (big.file). Buffer size: 2048 bytes --> 1000 iteration: 00m:11s:42ms:189us:200ns
traditional_read (big.file). Buffer size: 4096 bytes --> 1000 iteration: 00m:10s:904ms:247us:500ns
traditional_read (big.file). Buffer size: 8192 bytes --> 1000 iteration: 00m:10s:173ms:756us:700ns
one transaction seek (big.file) --> 1000 iteration: 00m:04s:190ms:396us:300ns
one transaction fs (big.file) --> 1000 iteration: 00m:04s:174ms:767us:500ns
stream_mapping_deque (big.file) --> 1000 iteration: 01m:03s:589ms:643us:400ns
stream_mapping_vector (big.file) --> 1000 iteration: 01m:20s:232ms:719us:400ns

Kernel mapping (big.file) --> 10000 iteration: 00m:03s:650ms:78us:400ns
traditional_read (big.file). Buffer size: 512 bytes --> 10000 iteration: 01m:53s:252ms:303us:200ns
traditional_read (big.file). Buffer size: 1024 bytes --> 10000 iteration: 01m:50s:405ms:273us:300ns
traditional_read (big.file). Buffer size: 2048 bytes --> 10000 iteration: 01m:49s:375ms:588us:200ns
traditional_read (big.file). Buffer size: 4096 bytes --> 10000 iteration: 01m:50s:51ms:240us:200ns
traditional_read (big.file). Buffer size: 8192 bytes --> 10000 iteration: 01m:42s:983ms:857us:400ns
one transaction seek (big.file) --> 10000 iteration: 00m:43s:668ms:527us:600ns
one transaction fs (big.file) --> 10000 iteration: 00m:42s:634ms:494us:600ns
stream_mapping_deque (big.file) --> 10000 iteration: 10m:31s:782ms:879us:400ns
stream_mapping_vector (big.file) --> 10000 iteration: 13m:35s:215ms:478us:200ns

Total time taken: 40m:21s:28ms:536us:300ns
```

Finally, winner is obvius... although windows is scalling very well in kernel mapping, with few iterations is so closed, but, when 
bunch increases, the difference is noticeable.

To conclude and sumarize up, best way to map a file into memory is using kernel API.

## Kernel IO

If you want know more about, see [https://github.com/AErbis/Umi](https://github.com/AErbis/Umi).
Memory functions were grabbed from there.

## Contact

You can send me a private message on telegram [@CRaW69](https://t.me/CRaW69).

## License

[GNU](LICENSE.md)











