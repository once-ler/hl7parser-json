# hl7parser-json
Fork of the fantastic [hl7parser](https://github.com/jcomellas/hl7parser) by @jcomellas

Added:
+ High level wrapper classes for C++14.
+ Parse HL7 messages to JSON or XML.
+ Build with VS2015.

Installation in Ubuntu:
```bash
$ sudo apt-get install qt4-qmake libqt4-dev
$ cd ~ && git clone https://github.com/eztier/hl7parser-json.git
$ cd hl7parser-json
$ ./configure
$ make
$ sudo make install
$ sudo ldconfig
```

Installation in RedHat:
```bash
$ sudo yum install qt-devel
# Then same as above for Ubuntu
```
