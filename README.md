# C++ File mapping into memory

Normally projects have the need to read some configuration files such application parameters, important data, etc. As a back endpoint
everyone wants better speed performing routines, in this case reading files. To check, investigate and corroborate which manner is the
best way to choice, I have tested different options.

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


#### Linux OS, Ubuntu 18.04 LTS **WSL**. (g++)

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

It seems and **is** demonstrated that Linux is faster than windows.

## Kernel IO

If you want know more about, see [https://github.com/AErbis/Umi](https://github.com/AErbis/Umi).
Memory functions were grabbed from there.

## Contact

You can send me a private message on telegram [@CRaW69](https://t.me/CRaW69).

## License

[GNU](LICENSE.md)











