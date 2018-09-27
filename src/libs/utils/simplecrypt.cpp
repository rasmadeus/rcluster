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

#include "simplecrypt.h"
#include <QByteArray>
#include <QtDebug>
#include <QtGlobal>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDataStream>

quint64 SimpleCrypt::defaultKey()
{
    return Q_UINT64_C(0x3f8ecf7b1ef00);
}

SimpleCrypt::SimpleCrypt()
    : SimpleCrypt{ defaultKey() }
{
}

SimpleCrypt::SimpleCrypt(quint64 key)
    : _key{ key }
{
    qsrand(uint(QDateTime::currentMSecsSinceEpoch() & 0xFFFF));
    splitKey();
}

void SimpleCrypt::setKey(quint64 key)
{
    _key = key;
    splitKey();
}

void SimpleCrypt::splitKey()
{
    _keyParts.clear();
    _keyParts.resize(8);

    for (int i = 0; i < 8; ++i)
    {
        quint64 part = _key;
        for (int j = i; j > 0; --j)
            part = part >> 8;
        part = part & 0xff;
        _keyParts[i] = static_cast<char>(part);
    }
}

QByteArray SimpleCrypt::encryptToByteArray(QString const &plaintext)
{
    auto const plaintextArray = plaintext.toUtf8();
    return encryptToByteArray(plaintextArray);
}

QByteArray SimpleCrypt::encryptToByteArray(QByteArray plaintext)
{
    if (_keyParts.isEmpty())
    {
        qWarning() << "No key set.";
        _lastError = ErrorNoKeySet;
        return {};
    }

    QByteArray ba = plaintext;

    CryptoFlags flags = CryptoFlagNone;
    if (_compressionMode == CompressionAlways)
    {
        ba = qCompress(ba, 9);
        flags |= CryptoFlagCompression;
    }
    else if (_compressionMode == CompressionAuto)
    {
        QByteArray compressed = qCompress(ba, 9);
        if (compressed.count() < ba.count())
        {
            ba = compressed;
            flags |= CryptoFlagCompression;
        }
    }

    QByteArray integrityProtection;
    if (_protectionMode == ProtectionChecksum)
    {
        flags |= CryptoFlagChecksum;
        QDataStream s{ &integrityProtection, QIODevice::WriteOnly };
        s << qChecksum(ba.constData(), static_cast<uint>(ba.length()));
    }
    else if (_protectionMode == ProtectionHash)
    {
        flags |= CryptoFlagHash;
        QCryptographicHash hash{ QCryptographicHash::Sha1 };
        hash.addData(ba);

        integrityProtection += hash.result();
    }

    char randomChar = char(qrand() & 0xFF);
    ba = randomChar + integrityProtection + ba;

    int pos{ 0 };
    char lastChar{ 0 };

    int const cnt = ba.count();

    while (pos < cnt)
    {
        ba[pos] = ba.at(pos) ^ _keyParts.at(pos % 8) ^ lastChar;
        lastChar = ba.at(pos);
        ++pos;
    }

    QByteArray resultArray;
    resultArray.append(char(0x03));  //version for future updates to algorithm
    resultArray.append(char(flags)); //encryption flags
    resultArray.append(ba);

    _lastError = ErrorNoError;
    return resultArray;
}

QString SimpleCrypt::encryptToString(QString const &plaintext)
{
    auto const plaintextArray = plaintext.toUtf8();
    auto const cypher = encryptToByteArray(plaintextArray);
    return QString::fromLatin1(cypher.toBase64());
}

QString SimpleCrypt::encryptToString(QByteArray plaintext)
{
    auto const cypher = encryptToByteArray(plaintext);
    return QString::fromLatin1(cypher.toBase64());
}

QString SimpleCrypt::decryptToString(QString const &cyphertext)
{
    auto const cyphertextArray = QByteArray::fromBase64(cyphertext.toLatin1());
    auto const plaintextArray = decryptToByteArray(cyphertextArray);
    return QString::fromUtf8(plaintextArray, plaintextArray.size());
}

QString SimpleCrypt::decryptToString(QByteArray cypher)
{
    auto const ba = decryptToByteArray(cypher);
    return QString::fromUtf8(ba, ba.size());
}

QByteArray SimpleCrypt::decryptToByteArray(QString const &cyphertext)
{
    auto const cyphertextArray = QByteArray::fromBase64(cyphertext.toLatin1());
    return decryptToByteArray(cyphertextArray);
}

QByteArray SimpleCrypt::decryptToByteArray(QByteArray cypher)
{
    if (_keyParts.isEmpty())
    {
        qWarning() << "No key set.";
        _lastError = ErrorNoKeySet;
        return {};
    }

    QByteArray ba = cypher;

    if(cypher.count() < 3)
        return {};

    char const version = ba.at(0);

    if (version !=3)
    {
        _lastError = ErrorUnknownVersion;
        qWarning() << "Invalid version or not a cyphertext.";
        return {};
    }

    auto const flags = CryptoFlags{ ba.at(1) };

    ba = ba.mid(2);
    int pos(0);
    int cnt(ba.count());
    char lastChar = 0;

    while (pos < cnt)
    {
        char const currentChar = ba[pos];
        ba[pos] = ba.at(pos) ^ lastChar ^ _keyParts.at(pos % 8);
        lastChar = currentChar;
        ++pos;
    }

    ba = ba.mid(1);

    bool integrityOk(true);
    if (flags.testFlag(CryptoFlagChecksum))
    {
        if (ba.length() < 2)
        {
            _lastError = ErrorIntegrityFailed;
            return {};
        }
        quint16 storedChecksum;
        {
            QDataStream s{ &ba, QIODevice::ReadOnly };
            s >> storedChecksum;
        }
        ba = ba.mid(2);
        quint16 const checksum = qChecksum(ba.constData(), static_cast<uint>(ba.length()));
        integrityOk = (checksum == storedChecksum);
    }
    else if (flags.testFlag(CryptoFlagHash))
    {
        if (ba.length() < 20)
        {
            _lastError = ErrorIntegrityFailed;
            return QByteArray();
        }
        auto const storedHash = ba.left(20);
        ba = ba.mid(20);
        QCryptographicHash hash{ QCryptographicHash::Sha1 };
        hash.addData(ba);
        integrityOk = (hash.result() == storedHash);
    }

    if (!integrityOk)
    {
        _lastError = ErrorIntegrityFailed;
        return {};
    }

    if (flags.testFlag(CryptoFlagCompression))
        ba = qUncompress(ba);

    _lastError = ErrorNoError;
    return ba;
}
