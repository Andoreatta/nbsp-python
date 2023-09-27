# NBioBSP for Python
This is a Python module for NBioBSP SDK. Built with C/C++ and pybind11.

You can test the module with the following code:
```python
import nbsp_python as nbsp

nbsp.initialize()
nbsp.get_version()
nbsp.enumerate_device()
...
```