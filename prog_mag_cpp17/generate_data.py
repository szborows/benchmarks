#!/usr/bin/env python3.4
#-*- coding: utf-8 -*-

import random

def generateDataForStringRefBenchmark():
    with open('string_ref_data.hpp', 'w') as fp:
        fp.write('std::string data {"\n')
        fp.write(' '.join([str(random.randint(0, 10000000))for x in range(1000000)]))
        fp.write('"};\n"')

if __name__ == "__main__":
    generateDataForStringRefBenchmark()
