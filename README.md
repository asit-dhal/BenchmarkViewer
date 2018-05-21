### BenchmarkViewer

Qt application to view Google Microbenchmarking data https://github.com/google/benchmark. 

### Build Status
| Build  | Status |
|------- | -------- |
| AppVeyor | [![Build status](https://ci.appveyor.com/api/projects/status/2ryk3cvxmygfp22g?svg=true)](https://ci.appveyor.com/api/projects/status/2ryk3cvxmygfp22g?svg=true) |
| Travis | [![Build Status](https://travis-ci.org/asit-dhal/BenchmarkViewer.svg?branch=master)](https://travis-ci.org/asit-dhal/BenchmarkViewer.svg?branch=master) |


### Supported Platforms

The standalone binary packages support the following platforms:

* Windows 7 or later
* (K)Ubuntu Linux 16.04 (64-bit) or later

### Usages
* Generate json report from your benchmark
```bash
./benchmark_binary --benchmark_format=json > benchmark.json
```
* Open the json file in BenchmarkViewer. It will list all generated benchmarks.
* Select on any benchmarks by clicking the checkbox.

### Sample Screenshot 
![alt text](https://github.com/asit-dhal/BenchmarkViewer/raw/master/screenshot.png "Screenshot of chart view")
![alt text](https://github.com/asit-dhal/BenchmarkViewer/raw/master/app_screenshot.gif "Recording of BenchmarkViewer")
