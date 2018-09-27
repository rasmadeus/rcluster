/*
Copyright (c) 2011, Andre Somers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Rathenau Instituut, Andre Somers nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL ANDRE SOMERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR #######; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H

#include <QString>
#include <QVector>
#include <QFlags>
#include "utils_global.h"

class UTILS_SHARED_EXPORT SimpleCrypt
{
public:
    enum CompressionMode
    {
        CompressionAuto,
        CompressionAlways,
        CompressionNever
    };

    enum IntegrityProtectionMode
    {
        ProtectionNone,
        ProtectionChecksum,
        ProtectionHash
    };
    /**
      Error describes the type of error that occured.
      */
    enum Error
    {
        ErrorNoError,
        ErrorNoKeySet,
        ErrorUnknownVersion,
        ErrorIntegrityFailed,
    };

public:
    static quint64 defaultKey();

public:
    SimpleCrypt();
    explicit SimpleCrypt(quint64 key);

public:
    void setKey(quint64 key);
    bool hasKey() const { return !_keyParts.isEmpty(); }
    void setCompressionMode(CompressionMode mode) { _compressionMode = mode; }
    CompressionMode compressionMode() const { return _compressionMode; }
    void setIntegrityProtectionMode(IntegrityProtectionMode mode) { _protectionMode = mode; }
    IntegrityProtectionMode integrityProtectionMode() const { return _protectionMode; }
    Error lastError() const { return _lastError; }
    QString encryptToString(QString const &plaintext);
    QString encryptToString(QByteArray plaintext);
    QByteArray encryptToByteArray(QString const &plaintext);
    QByteArray encryptToByteArray(QByteArray plaintext);
    QString decryptToString(QString const &cyphertext);
    QByteArray decryptToByteArray(QString const &cyphertext);
    QString decryptToString(QByteArray cypher);
    QByteArray decryptToByteArray(QByteArray cypher);

    enum CryptoFlag
    {
        CryptoFlagNone = 0,
        CryptoFlagCompression = 0x01,
        CryptoFlagChecksum = 0x02,
        CryptoFlagHash = 0x04,
    };
    Q_DECLARE_FLAGS(CryptoFlags, CryptoFlag)

private:
    void splitKey();

private:
    quint64 _key;
    QVector<char> _keyParts;
    CompressionMode _compressionMode{ CompressionAuto };
    IntegrityProtectionMode _protectionMode{ ProtectionChecksum };
    Error _lastError{ ErrorNoError };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SimpleCrypt::CryptoFlags)

#endif // SimpleCrypt_H
