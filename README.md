Manalgo: Generative art renderer
================================

What is Manalgo for ?
---------------------

Manalgo is a "Generative art renderer". It means that it can turn an 
algorithm into an image. This image might be printed or not.
Then this image might be considered as an art work or not.
In that case, the medium between artistic thought and artwork is the
algorithm.

Even if Manalgo comes with some "paintings" included, you can add yours.
In order to do so, you need a basic knowledge of the C++ language
and a basic knowledge of the Qt library (http://www.qt.io).

Anyway, if you like the included paintings you can just decorate your
living room with it. In that case I would be glad to see a picture of that.

Can I contrbute to Manalgo ?
----------------------------

Yes you can, contact me: managa@riseup.net
You can also fork it.

Compiling Manalgo
-----------------

To compile Manalgo you will need the folowing dependancy:
* Basic C/C++ build utility
* Qt5

If you have a Debian-based distribution the following command
will install all the dependency you need:

    sudo apt-get install build-essential qt5-default

Now you can compile Manalgo with the following commands:

    git clone https://github.com/managaganam/manalgo
    cd manalgo
    mkdir build
    cd build
    qmake ../manalgo.pro
    make

You can also use the QtCreator IDE, in this case just open the file
manalgo.pro with it, and you can directly compile through the IDE
interface.

Using Manalgo
-------------

Manalgo comes with a shell script _exhibit.sh_. This script allows
you to automatically generate every available paintings in an outputs
directory.
Put this script in the same folder as the manalgo binary then just type:

    chmod +x exhibit.sh
    ./exhibit.sh

The _manalgo_ binary is a classic command line tool working with option.
Below is the usage of the managa binary:

    Usage: ./manalgo [options]
    Digital and algorithmical art renderer
    
    Options:
      -h, --help             Displays this help.
      -v, --version          Displays version information.
      -l, --list-paintings   list available paintings
      --output <output>      output path
      --width <width>        width of the output
      --height <height>      height of the output
      --quality <quality>    quality of the output
      --painting <painting>  painting to use
    
For instance, if you want to generate the painting "strates" with the default
resolution, width, height, output and quality option just type:

    ./manalgo --painting strates

You'll find the result as a file named _output.png_ at the same location as
the binary.

Frequently Asked Questions
--------------------------

### What does it look like ?

Visit: [http://managaganam.github.io](http://managaganam.github.io)

Or download the code, compile it and execute it to generate the outputs images.

### What can I do with the source code ?

Basically anything you want, check the COPYING file for more information

### Is that really art ?

I don't know

### Have you already tried to print some of the output ? Where ?

Yes I did, mainly in 70x70cm and in 50x50cm as posters. I also tried 
50x50cm on a linen canvas. I personally love the result.
My favorite is "strates" on 70x70cm. I used a high quality JPEG of 
a 6000x6000px resolution to print it.
I did that through a commercial website whom first goal is not to print
digital art. I don't want to do any advertising here.
Anyway, I am satisfied with the result for the moment.

### I am totally in love with what you did and I want to do an exhibit of your art ! How can we do that ?

\o/ 

We can sure discuss that, just contact me:
managa@riseup.net

I am based in Berlin, Germany, at the moment.

### Why do you do that ?

Because I like it.

### I have a question, how can I contact you ?

By email: managa@riseup.net

### Are there ongoing work or idea ?

Yes, mainly some refactoring on the program, to separate the "engine" and the algorithms. 
Also adding more algorithms with some new and different ideas. Why not providing a library of graphical functions to use in the algorithms.

