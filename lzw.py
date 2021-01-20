# LZW encoder and decoder for strings
# Python 3.8.0
import sys

def make_txt_ready(string):
    symbols = [' ', '.', ',', ';', '?', ':', '<', '>', '(', ')', '[', ']', '{', '}', '!', '-', '_', "'"]
    ready_txt = string.upper()
    for s in symbols:
        ready_txt = ready_txt.replace(s, '')
    return ready_txt


def compress(data_in):
    # data_in is a string, data to be compressed
    # output is a list of symbols, compressed data
    data_in = make_txt_ready(data_in)
    output = []

    # max dictionary size is 2^12=4096
    max_dict_size = 4096
    dictionary = {chr(i): i - 64 for i in range(65, 91)}
    current_size = 26

    p = ''
    for c in data_in:
        pc = p + c
        if pc in dictionary.keys():
            p = pc
        elif len(dictionary) < max_dict_size:
            current_size += 1
            dictionary.update({pc: current_size})
            output.append(dictionary[p])
            p = c

    # give an output for the last character
    output.append(dictionary[p])
    return output


def decompress(compressed_data):
    out = ''
    max_dict_size = 4096
    dictionary = {i - 64: chr(i) for i in range(65, 91)}
    current_size = 26

    p = ''
    for i in compressed_data:
        c = dictionary[i]
        if len(c) == 1:
            pc = p + c
        else:
            pc = p + c[:-1]
        if pc in dictionary.values():
            p = c
        elif len(dictionary) < max_dict_size:
            current_size += 1
            dictionary.update({current_size: pc})
            out += p
            p = c

    # give an output for the last encoding data
    out += dictionary[compressed_data[-1]]
    return out


# MAIN / EXAMPLE #
while True:
    print('Options:\n1.Press enter for the stock example.\n2.Give your text and press enter.\n3.Press Q for exit\n')
    key = input('Give text: ')
    if key == '':
        data = 'kostaskostaskostaslafalafakolafakostlafa'
    elif key == 'Q':
        break
    else:
        data = str(key)
    print('Input data = ', data)
    compressed = compress(data)
    print('\nCompressed data = ', compressed)
    print('Successful compression')
    decompressed = decompress(compressed)
    print('\nDecompressed/ original data = ', decompressed)
    print('Successful decompression')
    print('\nLength of input data:', len(data))
    print('Lenght of output data:', len(compressed))
    print('Note: The actual size of the output data is larger because of using a list.')
    print('But this is only a demo for LZW :)')
    print('<-- End of program -->\n')


