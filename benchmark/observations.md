## DAC
n=8192
### Balanced:
- gcc: 
  - DAC multiplication Strassen combined:13.059913 seconds
  - DAC multiplication Alpha:            17.361530 seconds
  - DAC multiplication cBLAS:            21.610152 seconds

- gcc -O3:
  - DAC multiplication Strassen combined:10.306680 seconds
  - DAC multiplication Alpha:            15.675244 seconds
  - DAC multiplication cBLAS:            26.820126 seconds


- icx -O3:
    - DAC multiplication Strassen combined:13.337292 seconds
    - DAC multiplication Alpha:            14.367895 seconds
    - DAC multiplication cBLAS:            12.349947 seconds

### Performance
- gcc: 
    - DAC multiplication Strassen combined:12.279295 seconds
    - DAC multiplication Alpha:            12.100314 seconds
    - DAC multiplication cBLAS:            4.517011 seconds


- gcc -O3:
    - DAC multiplication Strassen combined:10.570404 seconds
    - DAC multiplication Alpha:            9.976218 seconds
    - DAC multiplication cBLAS:            5.766934 seconds



- icx -O3:
    - DAC multiplication Strassen combined:10.578901 seconds
    - DAC multiplication Alpha:            9.594534 seconds
    - DAC multiplication cBLAS:            4.894781 seconds
