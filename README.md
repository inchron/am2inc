# am2inc #

am2inc reads [AMALTHEA models](https://www.eclipse.org/app4mc) and converts
them to INCHRON version 3 models, which are used by [INCHRON's chronSUITE
3.X](https://www.inchron.com/chronsuite/). am2inc is implemented in C++ and
uses the [EMF4CPP framework](https://github.com/inchron/emf4cpp).


# Features #


# Installation #

## Requirements ##

* G++ (4.8.5 or greater due to C++11 - we are using g++ 8.3)

* Java Runtime Environment (1.8 or greater)

* Qt5 (5.6.2 or greater)

* [EMF4CPP](https://github.com/inchron/emf4cpp) (3.0.0 or greater)

## Installation ##

1. Checkout a clone of this repository
```
$ git clone https://github.com/inchron/am2inc.git
$ cd am2inc
```

2. Run qmake, then make and make install.
``` sh
$ qmake && make && make install PREFIX=/opt/am2inc
```

The installation will copy the executable and the libraries to $PREFIX/bin. On
Linux, the libraries are copied to $PREFIX/lib (the binary is linked with a
relativ path).

# Usage #

am2inc is a command line tool. It can either operate on files, or on stdin and
stdout. The general usage is:
``` sh
$ am2inc -o output.iprx input.amxmi [input2.amxmi] [... inputn.amxmi]
```

The extensions are not mandatory, the tool will try to parse all input files into the
same resource.

The version information does not only contain the version and the commit id of
the tool itself, but also the versions of the integrated models:
``` sh
$ am2inc --version
Version 1.0.0 Build Feb  3 2021 (8668187)
Amalthea : http://app4mc.eclipse.org/amalthea/0.9.9
INCHRON  : http://inchron.com/realtime/root/3.0.1
```

As usual, the integrated help can be obtained by:
``` sh
$ am2inc --help
Usage: am2inc [options] model.amxmi
Amalthea to INCHRON Converter

Options:
  -h, --help                   Displays help on commandline options.
  -o, --output <->             Write the new INCHRON project to file FILE. If
                               FILE is '-' or this option is not specified,
                               write to stdout.
...
```

# Updating the Models #

The AMALTHEA model is maintained by the APP4MC project and can be retrieved
from [their
repository](https://git.eclipse.org/r/plugins/gitiles/app4mc/org.eclipse.app4mc/+/refs/heads/master/plugins/org.eclipse.app4mc.amalthea.model/model-gen/ecore/). It
can not be used directly by EMF4CPP, the references to the ecore.ecore need to
be corrected. Furthermore, AMALTHEA uses the Java notation for floating point
representation, and literal names, which are reserved keywords in C++.

When the new model version has been copied to EcoreModels/amalthea.ecore, the
necessary changes will be applied automatically during the build process.

The INCHRON model is intended for the use with EMF4CPP and does not need any
special treatment. A new version can be stored in EcoreModels/root.ecore.

# License #

This program and the accompanying materials are made available under the terms
of the Eclipse Public License 2.0 which is available at
[https://www.eclipse.org/legal/epl-2.0/](https://www.eclipse.org/legal/epl-2.0/)

# Contact #

The AMALTHEA to INCHRON Model Importer is actively maintained and provided to
all users of INCHRON's chronSUITE. If you would like more information or
would like to provide feedback on the conversion strategy or even suggest a
new one, please feel free to contact us at
[INCHRON](mailto:support@inchron.com?subject=[am2inc]%20Your%20subject).
