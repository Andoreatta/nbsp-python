# NBioBSP for Python
### Do not use this module in production, theres no release yet.
This is a Python module for NBioBSP SDK. Built with C/C++ and pybind11.  
**Works only on Windows at the moment.**  
**All code is self contained into a single file, as it is just bindings.**
## Requirements
- Python 3.10 or higher 
- eNBSP SDK greater or equal to 4.8.9
- MSVC 2019 or higher

## To Do:
- [x] Readable error output using NBioAPI types **(priority)**
- [x] Handle errors properly
    - [x] Throw translatable and proper exceptions from C++ to Python
- [x] Handle return values properly **(priority)**
- [x] Handle fingerprint purposes on capture properly
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
