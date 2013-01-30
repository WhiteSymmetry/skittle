'''
Created on Dec 12, 2012

@author: Josiah
'''
from SkittleCore.models import RequestPacket
from models import OligomerUsageState
from SkittleGraphTransforms import chunkUpList, countNucleotides,\
    normalizeDictionary, generateExhaustiveOligomerList, oligCountToColorSpace
from SkittleCore.GraphRequestHandler import registerGraph

registerGraph('o', "Oligomer Usage", __name__, False)

def calculateOutputPixels(state, oligState = OligomerUsageState()):
    assert isinstance(state, RequestPacket)
    assert isinstance(oligState, OligomerUsageState)
#    print state.seq
    overlap = oligState.oligomerSize-1
    lines = chunkUpList(state.seq, state.nucleotidesPerLine(), overlap) #chunk sequence by display line #we can't do this simply by line because of the overhang of oligState.oligState
#    print lines
    counts = countNucleotides(lines, oligState.oligomerSize)
    
    values = map(lambda x: x.values(), counts)
    single = reduce(lambda current, ilist: current+ilist, values, [])
    wholeScreenMaximum = max(single)
    
    counts = normalizeDictionary(counts, wholeScreenMaximum)#this is currently per line normalization.  Test to see which is more/less confusing
#    print counts
    #per line normalization is going to screw up the math used in the similarity heat map, make sure not to use normalized data for that
    #TODO: create a sparse display for the oligomer display
    orderedWords = generateExhaustiveOligomerList(oligState.oligomerSize)
    pixels = oligCountToColorSpace(counts, orderedWords)
    
    return pixels

