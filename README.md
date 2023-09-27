# NBioBSP for Python
This is a Python module for NBioBSP SDK. Built with C/C++ and pybind11.  
**Works only on Windows for now.**

## Requirements
- Python 3.10 or higher 
- eNBSP SDK greater than or equal to 4.8.9
- MSVC 2019 or higher

## TODO:
- [ ] Readable error output
- [ ] Implement all functions that are possible in Windows
- [ ] Implement all functions that are *possible* in Linux **(no priority)** 

You can test the module with the following code:
```python
import nbsp_python as nbsp

nbsp.initialize()
nbsp.get_version()
nbsp.enumerate_device()
...
```
