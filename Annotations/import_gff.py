from django.db import models
from models import Annotation, GFF
from DNAStorage.StorageRequestHandler import GetRelatedChromosomes, GetFastaChunkFile, GetSpecimen
from django.conf import settings

import sys, math, re

#Import a GFF for a specific specimen
def ImportGFF(specimen, file):
    gff = GFF()
    #Get the specimen this annotation file is for
    gff.Specimen = GetSpecimen(specimen)
    #Set default version type
    gff.GFFVersion = 2
    
    #Open file and check for version type
    #TODO: Grab GFF Info and store in database
    annotationFile = open(file, 'r')
    counter = 0
    for line in annotationFile.readlines():
        counter = counter + 1
        
        if line.startswith("##"):
            if "gff-version" in line:
                temp = line.split(' ')
                gff.GFFVersion = temp[1]
        
        if counter == 10:
            break
    annotationFile.close()
    
    #Grab a list of chromosomes related to this specimen
    validChromosomes = GetRelatedChromosomes(specimen)
    
    annotations = list()
    
    #In GFF format, each line is an annotation. 
    #Read in each annotation and split at tabs (as per gff spec)
    #Then store as needed into an Annotation object which will be pushed onto the annotations stack
    #TODO: Bust out version reading into methods
    if gff.GFFVersion == 2:
        print "BEGINNING READING OF VERSION 2 FILE...\n"
        annotationFile = open(file, 'r')
        counter = 0
        for line in annotationFile.readlines():
            counter = counter + 1
            if not line.startswith('#'):
                elements = line.split('\t')   

                annotation = Annotation()
                #TODO: Handle when values come back null from not finding a matching chromosome!
                annotation.Connection = parseConnection(validChromosomes, specimen, elements[0], elements[3]) #Related validChromosomes, specimen, chromosome, start position
                annotation.Source = elements[1]
                annotation.Feature = elements[2]
                annotation.Start = elements[3]
                annotation.End = elements[4]
        
                #Do checking for Score
                if elements[5] == '.':
                    annotation.Score = 0
                else:
                    annotation.Score = elements[5]
            
                annotation.Strand = elements[6]
        
                #Do checking for frame
                if elements[7] == '.':
                    annotation.Frame = None
                else:
                    annotation.Frame = elements[7]
            
                #Check for existence of attribute and possible extra length
                if len(elements) >= 9:
                    annotation.Attribute = elements[8:]
                else:
                    annotation.Attribute = None
                
                if counter % 10000 == 0:
                    sys.stdout.write('.')
            
                #print "RESULTS: ", annotation.Connection.FastaFile.Chromosome, annotation.Source, annotation.Feature, annotation.Start, annotation.End, annotation.Score, annotation.Strand, annotation.Frame, annotation.Attribute
        
        print "DONE READING FILE!"
        print "BEGINNING SORTING LIST..."
    else:
        print "THIS GFF VERSION IS NOT SUPPORTED: Version", gff.GFFVersion
        
    #Sort the list of annotations read in by their start value (this could probably be optimized by using an always ordered list and inserting in order above)
    annotations = sorted(annotations, key = lambda annotation: annotation.Start)
    print "DONE SORTING!"
    
    chunkAndStoreAnnotations(gff, annotations)
    
#Parse which FastaChunkFile the specific annotation is associated with
def parseConnection(validChromosomes, specimen, seqname, start):
    possibleMatches = list()
    
    for chromosome in validChromosomes: 
        if seqname in chromosome:
            possibleMatches += [chromosome]
            
    if len(possibleMatches) == 1:
        #Grab fastachunk for one and only match
        return GetFastaChunkFile(specimen, possibleMatches[0], getRoundedIndex(start))
    else:
        #Look at possible matches and try to guess at the best one
        #First, why don't we remove all non-numbers from both comparisons
        for possible in possibleMatches:
            if re.sub("[^0-9]", "", possible) == re.sub("[^0-9]", "", seqname):
                return GetFastaChunkFile(specimen, possible, getRoundedIndex(start))
        return None
        
#Take a sorted list of annotations and chunk it into json chunks
def chunkAndStoreAnnotations(gff, annotations):
    print ""
    
def getRoundedIndex(index):
    return int(math.floor(int(index) / settings.CHUNK_SIZE) * settings.CHUNK_SIZE) + 1