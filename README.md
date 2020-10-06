# C++ File mapping into memory

Normally projects has the need to read some configuration files such application parameters, important data, etc. As a back endpoint
everyone wants most speed up performing routines, in this case reading files. To check, investigate and corroborate which manner is the
best way and option to choice, I have tested different ways.

### **Setup**

- CPU: Intel Core i7-9700K 3.6Ghz
- RAM: G.Skill Trident Z RGB DDR4 3200MHz PC4-25600 16GB 2x8GB CL16
- MB: Gigabyte Z390 Aorus Pro

### **Tests**

There are two files to test. small file is 391 KB big and big file is 24.607KB respectively.

- Kernel mapping is based on kernel API's offered from S.O.
- traditional_read is loop based, reading until no data is available (EOF reached).
- stream_mapping is stream buffer based on stl stream wrapper. In this case I have tried for vector and deque containers.

### **Benchmark results**

```cpp
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

Test was stopped at 1000 iterations on stream_mapping due to slow it was. Main reason is due to the overhead that stream plus memory reallocation of the dynamic containers (vector, deque).
As you can see, it is very slow way in comparison with the other ones.

## Kernel IO

If you want know more about, see [https://github.com/AErbis/Umi](https://github.com/AErbis/Umi).
Memory functions were grabbed from there.

## Contact

You can send me a private message on telegram [@CRaW69](https://t.me/CRaW69).

## License

[GNU](LICENSE.md)











