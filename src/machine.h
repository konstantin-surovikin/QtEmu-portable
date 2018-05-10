/*
 * This file is part of QtEmu project.
 * Copyright (C) 2017-2018 Sergio Carlavilla <carlavilla @ mailbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef MACHINE_H
#define MACHINE_H

// Qt
#include <QObject>
#include <QProcess>
#include <QHash>
#include <QUuid>

#include <QDebug>

// Local
#include "machineutils.h"

class Machine: public QObject {
    Q_OBJECT

    public:
        explicit Machine(QObject *parent = 0);
        ~Machine();

        enum States {
            Started, Stopped, Saved, Paused
        };

        QString getName() const;
        void setName(const QString &value);

        QString getOSType() const;
        void setOSType(const QString &value);

        QString getOSVersion() const;
        void setOSVersion(const QString &value);

        QString getPath() const;
        void setPath(const QString &value);

        QString getConfigPath() const;
        void setConfigPath(const QString &value);

        QString getUuid() const;
        void setUuid(const QString &value);

        Machine::States getState() const;
        void setState(const States &value);

        QString getCPUType() const;
        void setCPUType(const QString &value);

        qint64 getCPUCount() const;
        void setCPUCount(const qint64 &value);

        qint64 getSocketCount() const;
        void setSocketCount(const qint64 &value);

        qint64 getCoresSocket() const;
        void setCoresSocket(const qint64 &value);

        qint64 getThreadsCore() const;
        void setThreadsCore(const qint64 &value);

        qint64 getMaxHotCPU() const;
        void setMaxHotCPU(const qint64 &value);

        QString getGPUType() const;
        void setGPUType(const QString &value);

        QString getKeyboard() const;
        void setKeyboard(const QString &value);

        qlonglong getRAM() const;
        void setRAM(const qlonglong &value);

        QHash<QString, QString> getAudio() const;
        void setAudio(const QHash<QString, QString> &value);

        bool getUseNetwork() const;
        void setUseNetwork(bool value);

        QString getDiskName() const;
        void setDiskName(const QString &value);

        QString getDiskPath() const;
        void setDiskPath(const QString &value);

        qlonglong getDiskSize() const;
        void setDiskSize(const qlonglong &value);

        QString getDiskFormat() const;
        void setDiskFormat(const QString &value);

        bool getCreateNewDisk() const;
        void setCreateNewDisk(bool value);

        QHash<QString, QString> getAccelerator() const;
        void setAccelerator(const QHash<QString, QString> &value);

        void addAudio(const QString key, const QString value);
        void removeAudio(const QString key);

        void addAccelerator(const QString key, const QString value);
        void removeAccelerator(const QString accelerator);

        QString getAudioLabel();

        QString getAcceleratorLabel();

        void runMachine(const QUuid machineUuid);
        void stopMachine();
        void resetMachine();
        void pauseMachine();

    signals:
        void machineStateChangedSignal(States newState);

    public slots:

    private slots:
        void readMachineStandardOut();
        void readMachineErrorOut();
        void machineStarted();
        void machineFinished(int exitCode, QProcess::ExitStatus exitStatus);

    protected:

    private:
        // General
        QString name;
        QString OSType;
        QString OSVersion;
        QString path;
        QString configPath;
        QString uuid;
        States state;

        // Hardware - CPU
        QString CPUType;
        qint64 CPUCount;
        qint64 socketCount;
        qint64 coresSocket;
        qint64 threadsCore;
        qint64 maxHotCPU;

        // Hardware - GPU
        QString GPUType;
        QString keyboard;

        // Hardware - RAM
        qlonglong RAM;

        // Hardware - Audio
        QHash<QString, QString> audio;

        // Hardware - Network
        bool useNetwork;

        // Hardware - Disk
        QString diskName;
        QString diskPath;
        qlonglong diskSize;
        QString diskFormat;
        bool createNewDisk;

        // Accelerator
        QHash<QString, QString> accelerator;

        // Process
        QProcess *m_machineProcess;

        // Methods
        QProcessEnvironment buildEnvironment();

};

#endif // MACHINE_H
