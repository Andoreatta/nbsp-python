# NBioBSP for Python
### Do not use this module in production, theres no release yet.
This is a Python module for NBioBSP SDK. Built with C/C++ and pybind11.  
**Works only on Windows at the moment.**  

**All code is self contained into a single file, as it is just bindings.**

## Requirements
- Python 3.10 or higher 
- eNBSP SDK greater or equal to 5.2
- MSVC 2019 or higher (maybe it works with another compiler, didn't test it yet)

## To Do:
- [x] Readable error output using NBioAPI types **(priority)**
- [x] Handle errors properly
    - [x] Throw translatable and proper exceptions from C++ to Python
- [x] Handle return values properly **(priority)**
- [x] Handle fingerprint purposes on capture properly
- [ ] Implement IndexSearch methods
- [ ] Implement all functions that are possible in Windows
- [ ] Implement all functions that are *possible* in Linux **(no priority)**

You can test the module with the following code:
```python
import nbsp_python as nbsp

handle = nbsp.initialize()
nbsp.get_version()
nbsp.enumerate_device()
nbsp.open_device()
nbsp.capture("enroll", 10000)
nbsp.verify(handle)
fingerprint_hash = nbsp.extract_fir_text(handle)
nbsp.terminate()
```
