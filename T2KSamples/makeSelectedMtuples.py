#!/usr/bin/env python

import os, sys
from ROOT import *
import argparse


if __name__ == "__main__":
    
    # Get arguments (ie. SK file name)
    parser = argparse.ArgumentParser(description='Splits an SK file into five files, containing the numu-,nue-, nue1pi- numucc1pi- selected events')
    parser.add_argument('filename', nargs=1)
    args = parser.parse_args()
    skfile = args.filename[0]

    print "Working on file ", skfile

    # Get SK tree
    f_sk = TFile(skfile, "OPEN")
    if not f_sk:
        print "Error: could not open file ", skfile
        sys.exit()
    sk_tree = f_sk.Get("minituple")
    if not sk_tree:
        sk_tree = f_sk.Get("h1")

    # Get entries in SK tree
    n_total = sk_tree.GetEntries()
    print n_total, " events in tree."

    # Get the SK filename (without '.root')
    # skfile = skfile[:-5]

    # Make new filenames for files containing only the numu/nue trees
    numufile = skfile[:-5]+"_numuselec.root"
    nuefile = skfile[:-5]+"_nueselec.root"
    cc1pifile = skfile[:-5]+"_cc1piselec.root"
    numucc1pifile =skfile[:-5]+"_numucc1piselec.root"

    print "Making three new files: "
    print numufile
    print nuefile
    print cc1pifile
    print numucc1pifile

    print "Check: number of events in original SK tree = ", n_total

    # Make numu tree and save to file
    f_numu = TFile(numufile,"RECREATE")
    numu_tree = sk_tree.CloneTree(0)

    for i in xrange(0,n_total):
        sk_tree.GetEntry(i)
        if sk_tree.iclass==13: #numu selection
            numu_tree.Fill()

    n_numu = numu_tree.GetEntries()
    print "Check: number of events in numu tree = ", n_numu

    numu_tree.Write("mtuple")
    f_numu.Close()

    # Make nue tree and save to file
    f_nue = TFile(nuefile,"RECREATE")
    nue_tree = sk_tree.CloneTree(0)

    for i in xrange(0,n_total):
        sk_tree.GetEntry(i)
        if sk_tree.iclass==11: #nue selection
            nue_tree.Fill()

    n_nue = nue_tree.GetEntries()
    print "Check: number of events in nue tree = ", n_nue

    nue_tree.Write("mtuple")
    f_nue.Close()

    # Make cc1pi tree and save to file
    f_cc1pi = TFile(cc1pifile,"RECREATE")
    cc1pi_tree = sk_tree.CloneTree(0)

    for i in xrange(0,n_total):
        sk_tree.GetEntry(i)
        if sk_tree.iclass==14: #cc1pi selection
            cc1pi_tree.Fill()

    n_cc1pi = cc1pi_tree.GetEntries()
    print "Check: number of events in cc1pi tree = ", n_cc1pi

    cc1pi_tree.Write("mtuple")
    f_cc1pi.Close()

    f_numucc1pi = TFile(numucc1pifile, "RECREATE")
    numucc1pi_tree = sk_tree.CloneTree(0)

    for i in xrange(0,n_total):
      sk_tree.GetEntry(i)
      if sk_tree.iclass==31 or sk_tree.iclass==32:
         numucc1pi_tree.Fill()

    n_numucc1pi =numucc1pi_tree.GetEntries()
    print "Check: number of events in numucc1pi tree = ", n_numucc1pi

    numucc1pi_tree.Write("mtuple")
    f_numucc1pi.Close()

    print n_numu, " + ", n_nue, " + ", n_cc1pi, " + ", n_numucc1pi, " = ", n_numu+n_nue+n_cc1pi+n_numucc1pi
