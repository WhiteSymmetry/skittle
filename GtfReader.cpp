#include <QtGui>
#include "GtfReader.h"
#include "NucleotideDisplay.h"
#include "BasicTypes.h"
#include "UiVariables.h"
#include "ui_BookmarkDialog.h"
#include "SkittleUtil.h"

#include <QDebug>
#include <QThread>
#include <QString>
#include <qtconcurrentrun.h>
#include <QApplication>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include <stdlib.h>
#include <ctime>

using namespace QtConcurrent;
using namespace std;

/** **********************************
  GtfReader is the file reader for Annotation files.  Primarily the GTF
  and GFF file format.  This file format is tab delimited plain text file.
  Each line int the file represent one annotation, one element.
  The two main columns of interest are the start and stop position. This
  is connected with a text string description that takes up the end of the line.

  GtfReader also has the ability to output files that are generated by the user.
  These files contain the bookmarks from views that the user has created.  They are
  outputted in the same GFF format so that they can be read in as any other annotation.
  The bookmark functionality references the ui layout Ui_BookmarkDialog.h.  GtfReader
  provides the information for AnnotationDisplay to display.  Both use the track_entry class.

**************************************/

GtfReader::GtfReader(UiVariables* gui)
{	
    ui = gui;
    inputFilename = string("blank.fa");
    outputFilename = string("user.gff");
    bytesInFile = 0;
    blockSize = 1000000;
    chrName = string("");
}

bool GtfReader::initFile(string fileName)
{
    file.clear();//reset the fail state to normal
    file.open (fileName.c_str(), ifstream::in | ifstream::binary);
    if(file.fail())
    {
        ErrorBox msg("Could not read the file.");
        return false;
    }
    int begin = file.tellg();
    file.seekg (0, ios::end);
    int end = file.tellg();
    bytesInFile = end - begin;
    file.seekg(0, ios::beg);//move pointer to the beginning of the file

    return true;
}

/**SLOTS**/
void GtfReader::addBookmark(int start, int end)
{
    QDialog parent;
    Ui_BookmarkDialog dialog;
    dialog.setupUi(&parent);

    std::stringstream startText;
    startText << start;
    dialog.start->setText( QString( startText.str().c_str() ) );
    std::stringstream endText;
    endText << end;
    dialog.end->setText( QString(endText.str().c_str() ) );
    dialog.sequence->setText( QString(chrName.c_str()) );

    parent.show();

    int result = parent.exec();
    if(result == QDialog::Accepted)
    {
        ofstream outFile;
        outFile.open(outputFilename.c_str(), ios::app);
        if(!outFile.fail())
        {
            outFile << dialog.sequence->text().toStdString()<<"\t";
            outFile << dialog.source->text().toStdString()<<"\t";
            outFile << dialog.feature->text().toStdString()<<"\t";
            outFile << dialog.start->text().toStdString() <<"\t";
            outFile << dialog.end->text().toStdString() << "\t";
            outFile << dialog.score->text().toStdString() << "\t";
            outFile << (dialog.strand->isChecked() ? "+" : "-") << "\t";//QCheckBox
            outFile << dialog.frame->currentText().toStdString() << "\t";//QComboBox
            outFile << dialog.note->toPlainText().toStdString() << "\t";//QPlainTextEdit
            outFile << "\n";
            outFile.close();

            track_entry entry = track_entry(dialog.start->text().toInt(), dialog.end->text().toInt(), color_entry(), dialog.note->toPlainText().toStdString());
            emit BookmarkAdded(entry, outputFilename);
        }
        else
        {
            ErrorBox msg("Could not read the file.");
            outFile.close();
        }
    }
}

void GtfReader::determineOutputFile(QString file)
{
    string filename = file.toStdString();
    outputFilename = filename;
    outputFilename.append("-skittle_notes.gff");
    chrName = trimPathFromFilename(filename);
}

vector<track_entry>  GtfReader::readFile(QString filename)
{

    vector<track_entry> annotation_track;
    inputFilename = filename.toStdString();
    if( inputFilename.empty() || !initFile(inputFilename) )
    {
        return vector<track_entry>();
    }

    annotation_track.clear();

    bool skittleNotes = false;
    string chromosomeRead;
    if(filename.contains("skittle_notes"))
    {
        skittleNotes = true;
    }
    //Get name of chromosome from the beginning of the line and make sure that it matches the current viewed chromosome file
    else
    {
        if(!chrName.empty()){
            string chrDelim = "chr";
            int chrStart = chrName.find(chrDelim);
            int chrEnd = chrName.find(".fa");
            chromosomeRead = chrName.substr((chrStart + chrDelim.length()), (chrEnd - (chrStart + chrDelim.length())));
        }
        else
        {
            chromosomeRead = "NONE";
        }

        //Ask user if our parsed chromosome name is correct
        QStringList items;
        items  = getChromosomes();

        bool ok;
        int index = items.indexOf(QString::fromStdString(chromosomeRead));
        if (index == -1)
        {
            index = 0;
            QString temp = QInputDialog::getItem(0, tr("Current Chromosome Name"), tr("Please pick the name of the current chromosome from the Annotation File."), items, index, false, &ok);

            if(ok && !temp.isEmpty())
            {
                chromosomeRead = temp.toStdString();
            }
        }
        file.close();
        initFile(filename.toStdString());
    }

    srand(time(0));
    string line;
    while( getline(file, line) )
    {
        line.erase(line.size()-1);//erase last character, should be a newline character
        stringstream lineStr( line );
        int start = 0;
        int stop = 0;
        //string repClass;

        string chromosomeAnnotation;
        lineStr >> chromosomeAnnotation;

        if(chromosomeRead.compare(chromosomeAnnotation) == 0 || skittleNotes)
        {
            lineStr.ignore(10000, '\t');//1
            lineStr.ignore(10000, '\t');//2
            lineStr.ignore(10000, '\t');//3
            /*
            lineStr.ignore(10000, '\t');//4
            lineStr.ignore(10000, '\t');//5
            lineStr.ignore(10000, '\t');//6*/
            //getline(lineStr, repClass, '\t');//repClass - type
            lineStr >> start >> stop;//genoStart	//genoEnd
            color c = color_entry();//repClass);
            if(!lineStr.fail())
            {
                annotation_track.push_back( track_entry(start, stop, c, line) );
                int last_entry = annotation_track.size() -1;
                annotation_track[last_entry].index = last_entry;
            }
        }
    }
    file.close();
    return annotation_track;
}

QStringList GtfReader::getChromosomes()
{
    QStringList list;

    srand(time(0));
    string line;
    while(getline(file, line))
    {
        stringstream lineStr(line);

        string chromosomeName;
        lineStr >> chromosomeName;

        QString cn = QString::fromStdString(chromosomeName);

        if(!list.contains(cn))
            list.append(cn);
    }

    list.removeDuplicates();

    return list;
}

/*PRIVATE FUNCTIONS*/

/***********OUTPUT ANNOTATED SEQUENCE************** /
void GtfReader::snipAnnotatedSequence()
{
    const string* seq = glWidget->nuc->sequence;
    ofstream fout("clipped.fa");
    for(int i = 0; i < annotation_track.size(); i++)
    {
        fout << seq->substr(annotation_track[i].start, annotation_track[i].stop - annotation_track[i].start);
    }
    fout.close();
}*/

color GtfReader::color_entry()
{
    volatile int r = (int)(((float)rand() / RAND_MAX)* 255);
    volatile int g = (int)(((float)rand() / RAND_MAX)* 255);
    volatile int b = (int)(((float)rand() / RAND_MAX)* 255);
    color c = color(r, g, b);
    return c;
}

bool GtfReader::eq(string& str1, const char* str2)
{
    return str1[0] == str2[0];//strcomp(str1.c_str(), str2) == 0;
}

string GtfReader::outputFile()
{
    return outputFilename;
}
