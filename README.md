# am2inc #

am2inc reads [AMALTHEA models](https://eclipse.dev/app4mc/) and converts
them to INCHRON version 3 models, which are used by [INCHRON's chronSUITE
3.X](https://www.inchron.com/chronsuite/). am2inc is implemented in C++ and
uses the [EMF4CPP framework](https://github.com/inchron/emf4cpp).

# Features #

* Reads all AMALTHEA models from 1.2.0 to 3.3.0. A single ecore file is used for
  metamodels without structural differences between them.
* Converts the AMALTHEA model into an INCHRON model as far as the Amalthea elements
  are supported.

For more details, see [INCHRON Amalthea Importer](https://www.inchron.com/amalthea/).

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
Version 3.3.0 Build Oct 10 2024 (f0c8579)
AMALTHEA : http://app4mc.eclipse.org/amalthea/1.2.0
           http://app4mc.eclipse.org/amalthea/2.0.0
           http://app4mc.eclipse.org/amalthea/2.1.0
           http://app4mc.eclipse.org/amalthea/2.2.0
           http://app4mc.eclipse.org/amalthea/3.0.0
           http://app4mc.eclipse.org/amalthea/3.1.0
           http://app4mc.eclipse.org/amalthea/3.2.0
           http://app4mc.eclipse.org/amalthea/3.3.0
INCHRON  : http://inchron.com/realtime/root/3.5.0

version: 3.5.0
capabilities: +multi
```

The ```version:``` and ```capabilities:``` line are checked at runtime and used to
control the external importer interface of the INCHRON chronSUITE 3.X.

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

# Version Counting

Semantic versioning is a thing, but inappropriate here: Changing the output
model version is always an incompatible change as you have to update the
tools, which process the generated output.

Instead, we count the version of the am2inc as follows:

1. The major version denotes the code structure and the algorithm. Aside of
   model changes, source-code extensions will probably continue to work.
2. The minor version is incremented, when either the input model version, the
   output model version, or both, are changed.
3. The patch number is incremented with bug fixes or converting new model
   elements from one model to the other.

# Updating the Models #

The AMALTHEA model is maintained by the APP4MC project and can be retrieved
from [their
repository](https://gitlab.eclipse.org/eclipse/app4mc/org.eclipse.app4mc/-/tree/master/plugins/org.eclipse.app4mc.amalthea.model/model-gen/ecore/).
It
can not be used directly by EMF4CPP, the references to the ecore.ecore need to
be corrected. Furthermore, AMALTHEA uses the Java notation for floating point
representation, and literal names, which are reserved keywords in C++.

When the new model version has been copied to EcoreModels/amalthea.ecore, the
necessary changes will be applied automatically during the build process.

Download and adaption can be triggered manually in a single step:

``` sh
$ ./Amalthea/adaptC++.sh --update EcoreModels/amalthea.ecore
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  428k    0  428k    0     0   344k      0 --:--:--  0:00:01 --:--:--  344k
Adapted EcoreModels/amalthea.ecore
```

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
