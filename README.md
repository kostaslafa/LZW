# LZW
Implementation of LZW in C
Implementation of LZW in Python

## Table of contents
* [General info](#general-info)
* [LZW C](#lzw-c)
* [LZW Python](#lzw-python)
* [NOTE](#note)
* [Contact](#contact)

## General info 
LZW (Lempel-Ziv-Weich) is a lossless data compression algorithm created by Abraham Lempel, Jacob Ziv, and Terry Welch.
More info: en.wikipedia.org/wiki/Lempel–Ziv–Welch

## LZW C
This file icludes an implementation of LZW encoding in C.
Reads the raw data from the image: akiyo_cif_0_yuv420.yuv, which I have uploaded.

## LZW Python
LZW ENCODER & DECODER
Python 3.8.0

Data type dict (dictionary) is used for the dictionary of the algorithm.
The max size of the dictionary is set to 2^12 = 4096.

<-- Endoder -->
The "compress" function is responsible for the encoding. 
The input data can be any strings of characters which satisfies the following conditions:
1. The string must be written in latin characters (Capital or lowercase).
2. The string can have spaces.
3. The string can incude these symbols: '!', '-', '_', ',', '.', '?', '(', ')', '[', ']', '{', '}', ';', ':', '<', '>', '''.
4. The string must NOT have numbers or any other symbol.
BUT:
The input string is being encoded as a sentence without spaces and symbols.
Example: 
The input strings:  "Hello, what a nice day!" and "What's up?"
will be encoded as: "HELLOWHATANICEDAY".      and "WHATSUP".
The result is a list of output symbols (integers).

<-- function "make_txt_ready" -->
This function takes as an input the input string and prepares it for the encoding:
1. Makes all the letters capitals
2. Removes spaces and permitted symbols

<-- Decoder -->
The "decompress" function is responsible for the decoding.
The input is a list of symbols (integers, like the list that the encoder produces).
The output is a string of capital latin characters, without any spaces or symbols.

<-- MAIN/ EXAMPLE -->
For testing the user can write his/her own text or see how the program works with the string = 'kostaskostaskostaslafalafakolafakostlafa'.
Option:
1. Press enter for the stock example
2. Write text and press enter for custom string.
3. Press 'Q' for exit.

## NOTE 
The actual size of compressed data in Python file are actually larger in size than the input data. This is because I use a list data type.
BUT this is just a demo for LZW :)

## Contact
Created by [@kostaslafa], email: kostaslafa14@gmail.com - feel free to contact me!
