/*********************************************************************************
**
** Copyright (c) 2017 The University of Notre Dame
** Copyright (c) 2017 The Regents of the University of California
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Written by Peter Sempolinski, for the Natural Hazard Modeling Laboratory, director: Ahsan Kareem, at Notre Dame

#ifndef RESULTVISUALBASE_H
#define RESULTVISUALBASE_H

#include <QWidget>
#include <QMap>

#include "../AgaveExplorer/remoteFileOps/filenoderef.h"

//TODO: Need to deal with situation when bsae folder is removed

class FileNodeRef;
enum class FileSystemChange;

class ResultProcureBase : public QWidget
{
    Q_OBJECT
public:
    explicit ResultProcureBase(QWidget *parent = nullptr);
    ~ResultProcureBase();

    void initializeWithNeededFiles(FileNodeRef baseFolder, QMap<QString, QString> neededFiles);
    //Note: needed files is a map: internalID => path relative to base folder

protected:
    virtual void allFilesLoaded() = 0;

    QMap<QString, FileNodeRef> getFileNodes();
    QMap<QString, QByteArray *> getFileBuffers();

    void computeFileBuffers();

    virtual void underlyingDataChanged(QString fileID) = 0;
    //Note: input to the above method might be an empty string
    //This can be used for force a re-load of the data

    virtual void initialFailure() = 0;

private slots:
    void fileChanged(FileNodeRef changedFile);

private:
    bool checkForAndSeekFiles(); //Returns true if all files loaded
    FileNodeRef getFinalResultFolder();
    QString getIDfromNode(FileNodeRef fileNode);

    FileNodeRef myBaseFolder;

    QMap<QString, QString> myFileNames;
    QMap<QString, FileNodeRef> myFileNodes;
    QMap<QString, QByteArray *> myBufferList;
    bool initLoadDone = false;
};

#endif // RESULTVISUALBASE_H
