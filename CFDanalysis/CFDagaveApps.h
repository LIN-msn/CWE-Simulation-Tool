/*********************************************************************************
**
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


#ifndef CFDAGAVEAPPS_H
#define CFDAGAVEAPPS_H

#include <QString>
#include <QMap>
#include <QStringList>

//For debug:
#include <QTimer>

class FileTreeNode;
class CFDanalysisType;
class EasyBoolLock;
class JobOperator;

class VWTinterfaceDriver;

enum class stageState {UNRUN, RUNNING, FINISHED, LOADING, ERROR};

class CFDagaveApps : public QObject
{
    Q_OBJECT

public:
    CFDagaveApps(FileTreeNode * newCaseFolder, VWTinterfaceDriver * mainDriver);
    CFDagaveApps(CFDanalysisType * caseType, VWTinterfaceDriver * mainDriver); //For new cases

    bool isDefunct();
    bool knownNotValid();
    bool stateKnown();
    bool operationPending();

    //Note: For these, it can always answer "I don't know"
    CFDanalysisType * getMyType();
    QMap<QString, QString> getCurrentParams();
    QMap<QString, stageState> getStageStates();

    //This enacts the LS needed to get all info
    //Listen on dataStateChange till full state is known
    void forceInfoRefresh();

    //Of the following, only one enacted at a time
    void createCase(QString newName, FileTreeNode * containingFolder);
    void changeParameters(QMap<QString, QString> paramList);
    void mesh(FileTreeNode * geoFile = NULL); //Leave NULL if not used
    void rollBack(QStringList stagesToDelete);
    void openFOAM();
    void postProcess();

signals:
    void dataStateChange(bool fullStateKnown);

private slots:
    void underlyingFilesUpdated();
    void caseFolderRemoved();

    //Will call forceInfoRefresh() after finishing
    void agaveAppDone();

private:
    bool defunct = false;

    VWTinterfaceDriver * theDriver;

    FileTreeNode * caseFolder = NULL;
    CFDanalysisType * myType = NULL;

    EasyBoolLock * myLock;

    QString expectedNewCaseFolder;
};

#endif // CFDAGAVEAPPS_H