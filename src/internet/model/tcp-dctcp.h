/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Shravya K.S. <shravya.ks0@gmail.com>
 *
 */

#ifndef TCP_DCTCP_H
#define TCP_DCTCP_H

#include "ns3/tcp-congestion-ops.h"

namespace ns3 {

/**
 * \ingroup congestionOps
 *
 * \brief An implementation of DCTCP. This model implements all the functionalities mentioned
 * in the DCTCP SIGCOMM paper except dynamic buffer allocation in switches
 */

class TcpDctcp : public TcpNewReno
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * Create an unbound tcp socket.
   */
  TcpDctcp ();

  /**
   * \brief Copy constructor
   * \param sock the object to copy
   */
  TcpDctcp (const TcpDctcp& sock);

  /**
   * \brief Destructor
   */
  virtual ~TcpDctcp (void);

  /**
   * \brief Get the name of the TCP flavour
   *
   * \return The name of the TCP
   */
  virtual std::string GetName () const;

  /**
   * \brief Set the associated TCP Socket Base
   *
   * \param tsb the TCP Socket Base
   */
  virtual void SetSocketBase (Ptr<TcpSocketBase> tsb);
  virtual Ptr<TcpCongestionOps> Fork ();

  /**
   * \brief Reduce congestion window based on DCTCP algorithm
   *
   * \param tcb internal congestion state
   */
  virtual void ReduceCwnd (Ptr<TcpSocketState> tcb);

  /**
   * \brief Increase congestion window based on TDCTCP modification
   *
   * \param tcb internal congestion state
   * \param segmentsAcked count of segments acked
   */
  virtual void IncreaseWindow (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked);

  /**
   * \brief Set alpha to zero when sender finds out Delayed Ack Timeout has happened
   *
   * \param tcb internal congestion state
   */
  virtual void DelAckTimeoutEvent ();

  /**
   * \brief congestion avoidance based on DCTCP and TDCTCP algorithm
   *
   * \param tcb internal congestion state
   * \param segmentsAcked count of segments ACKed 
   */
  virtual void CongestionAvoidance (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked);

  /**
   * \brief Get information from the acked packet
   *
   * \param tcb internal congestion state
   * \param segmentsAcked count of segments ACKed
   * \param rtt The estimated rtt
   */
  virtual void PktsAcked (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked,
                          const Time &rtt);
  /**
   * \brief Trigger events/calculations on occurrence of congestion window event
   *
   * \param tcb internal state
   * \param event congestion window event which triggered this function
   */
  virtual void CwndEvent (Ptr<TcpSocketState> tcb,
                          const TcpSocketState::TcpCaEvent_t event);

private:
  /**
   * \brief Changes state of m_ceState to true
   *
   * \param tcb internal congestion state
   */
  void CeState0to1 (Ptr<TcpSocketState> tcb);

  /**
   * \brief Changes state of m_ceState to false
   *
   * \param tcb internal congestion state
   */
  void CeState1to0 (Ptr<TcpSocketState> tcb);

  /**
   * \brief Updates the value of m_delayedAckReserved
   *
   * \param tcb internal congestion state
   * \param event the congestion window event
   */
  void UpdateAckReserved (Ptr<TcpSocketState> tcb,
                          const TcpSocketState::TcpCaEvent_t event);

  /**
   * \brief Resets the value of m_ackedBytesEcn, m_ackedBytesTotal and m_nextSeq
   *
   * \param tcb internal congestion state
   */
  void Reset (Ptr<TcpSocketState> tcb);

  /**
   * \brief Sets the value of m_alpha
   *
   * \param alpha DCTCP alpha parameter
   */
  void SetDctcpAlpha (double alpha);

  /**
   * \brief decides which protocol to use
   *
   */
  enum ProtocolType 
  {
    DCTCP,
    TDCTCP
  };

  Ptr<TcpSocketBase> m_tsb;             //!< TCP Socket Base state
  uint32_t m_ackedBytesEcn;             //!< Number of acked bytes which are marked
  uint32_t m_ackedBytesTotal;           //!< Total number of acked bytes
  SequenceNumber32 m_priorRcvNxt;       //!< Sequence number of the first missing byte in data
  bool m_priorRcvNxtFlag;               //!< Variable used in setting the value of m_priorRcvNxt for first time
  double m_alpha;                       //!< Parameter used to estimate fraction of sent bytes that encountered congestion
  SequenceNumber32 m_nextSeq;           //!< TCP sequence number threshold for beginning a new observation window
  bool m_nextSeqFlag;                   //!< Variable used in setting the value of m_nextSeq for first time
  bool m_ceState;                       //!< DCTCP Congestion Experienced state
  bool m_delayedAckReserved;            //!< Delayed Ack state
  double m_g;                           //!< Estimation gain
  enum ProtocolType m_pType;            //!< 0 for DCTCP, 1 for TDCTCP
};

} // namespace ns3

#endif /* TCP_DCTCP_H */
