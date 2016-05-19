/*
 * Copyright (c) 2016 dresden elektronik ingenieurtechnik gmbh.
 * All rights reserved.
 *
 * The software in this package is published under the terms of the BSD
 * style license a copy of which has been included with this distribution in
 * the LICENSE.txt file.
 *
 */

#ifndef REST_NODE_BASE_H
#define REST_NODE_BASE_H

#include <QTime>
#include "deconz.h"

/*! \class NodeValue

    Holds bookkeeping data for numeric ZCL values.
 */
class NodeValue
{
public:
    enum UpdateType { UpdateInvalid, UpdateByZclReport, UpdateByZclRead };

    NodeValue() :
        updateType(UpdateInvalid),
        clusterId(0),
        attributeId(0)
    {
        value.u64 = 0;
    }

    QTime timestamp;
    QTime timestampLastReport;
    QTime timestampLastReadRequest;
    UpdateType updateType;
    quint16 clusterId;
    quint16 attributeId;
    deCONZ::NumericUnion value;
};


/*! \class RestNodeBase

    The base class for all device representations.
 */
class RestNodeBase
{
public:
    RestNodeBase();
    virtual ~RestNodeBase();
    deCONZ::Node *node();
    void setNode(deCONZ::Node *node);
    deCONZ::Address &address();
    const deCONZ::Address &address() const;
    bool isAvailable() const;
    void setIsAvailable(bool available);
    const QString &id() const;
    void setId(const QString &id);
    const QString &uniqueId() const;
    void setUniqueId(const QString &uid);
    bool mustRead(uint32_t readFlags);
    void enableRead(uint32_t readFlags);
    void clearRead(uint32_t readFlags);
    const QTime &nextReadTime() const;
    void setNextReadTime(const QTime &time);
    int lastRead() const;
    void setLastRead(int lastRead);
    int lastAttributeReportBind() const;
    void setLastAttributeReportBind(int lastBind);
    bool mgmtBindSupported() const;
    void setMgmtBindSupported(bool supported);
    void setZclValue(NodeValue::UpdateType updateType, quint16 clusterId, quint16 attributeId, const deCONZ::NumericUnion &value);
    const NodeValue &getZclValue(quint16 clusterId, quint16 attributeId) const;
    NodeValue &getZclValue(quint16 clusterId, quint16 attributeId);

private:
    deCONZ::Node *m_node;
    deCONZ::Address m_addr;
    QString m_id;
    QString m_uid;
    bool m_available;
    bool m_mgmtBindSupported;

    uint32_t m_read; // bitmap of READ_* flags
    int m_lastRead; // copy of idleTotalCounter
    int m_lastAttributeReportBind; // copy of idleTotalCounter
    QTime m_nextReadTime;

    NodeValue m_invalidValue;
    std::vector<NodeValue> m_values;
};

#endif // REST_NODE_BASE_H
