#!/usr/bin/env python3
import sys, time
import argparse
from pathlib import Path
from signal import signal, SIGINT

class Node:
    def __init__(self, data):
        self.item = data
        self.nref = None
        self.pref = None

class DoublyLinkedList:
    def __init__(self):
        self.start_node = None
        self.length = 0

    def insert_at_start(self, data):
        if self.start_node is None:
            new_node = Node(data)
            self.start_node = new_node
            print("Node inserted")
            return
        new_node = Node(data)
        new_node.nref = self.start_node
        self.start_node.pref = new_node
        self.start_node = new_node
        self.length += 1

    def insert_at_end(self, data):
        if self.start_node is None:
            new_node = Node(data)
            self.start_node = new_node
            return
        n = self.start_node
        while n.nref is not None:
            n = n.nref
        new_node = Node(data)
        n.nref = new_node
        new_node.pref = n
        self.length += 1

    def delete_at_start(self):
        if self.start_node is None:
            print("The list has no element to delete")
            return
        if self.start_node.nref is None:
            self.start_node = None
            return
        self.start_node = self.start_node.nref
        self.start_node.pref = None
        self.length -= 1

    def delete_at_end(self):
        if self.start_node is None:
            print("The list has no element to delete")
            return
        if self.start_node.nref is None:
            self.start_node = None
            return
        n = self.start_node
        while n.nref is not none:
            n = n.nref
        n.pref.nref = none
        self.length -= 1

    def read_list(self, start_time):
        if self.start_node is None:
            print("List has no elements")
            return
        else:
            n = self.start_node
            counter = 1
            while n is not None:
                progress = round((counter / self.length) * 100, 2)
                elapsed = round((time.time() - start_time), 2)
                print(f"-> {n.item}")
                print(f"{elapsed}s [{progress}%]")
                sys.stdout.write("\033[F")
                sys.stdout.write("\033[K")
                sys.stdout.write("\033[F")
                sys.stdout.write("\033[K")
                if n.nref is not None:
                    time.sleep(len(n.item) / 12)
                    counter += 1
                    n = n.nref
                else:
                    sys.stdout.write("\033[K")
                    print(f"{__file__}: EOF reached")
                    print(f"{__file__}: Time elapsed={elapsed}s")
                    return

def file_to_array(path):
    line_list = word_list = []
    with open(path) as f:
        line_list = f.readlines()

    line_list = [x.strip() for x in line_list]
    words_list = [x.split(" ") for x in line_list]

    return words_list

def array_to_dll(array, dll):
    for line in array:
        for word in line:
            dll.insert_at_end(word)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='reader',
                    description="A speed reader implemented in Python")
    parser.add_argument('-i', '--input', action='store', type=Path,
                    help="Input file to read from")
    args = parser.parse_args()

    if (args.input.exists()):
        print(f"{__file__}: Using input file `{args.input}'")
    elif not args.input:
        print(f"{__file__}: No input file provided");
        exit(1)
    else:
        print(f"{__file__}: Input file `{args.input}' not found")
        exit(1)

    # create new DLL
    DLL = DoublyLinkedList()
    # read file into DLL structure
    array = file_to_array(args.input)
    array_to_dll(array, DLL)

    # read through DLL
    start = time.time()
    DLL.read_list(start)

