# Implementation of T-DCTCP in ns-3
## Course Code: CO365
### Assignment: #20
#### Overview

The assignment involves implementing modifications mentioned in the T-DCTCP paper [1] in ns-3 [3]. The modifications are as follows:

[1] Increasing cwnd when ECE = 0 in Congestion Avoidance algorithm

[2] Resetting alpha (Congestion Indicator) to zero once Delayed Ack Timeout Event occurs

[3] Dynamic calculation of Delayed Ack Timeout

#### References 

[1] Tanmoy Das and Krishna M. Sivalingam, "[TCP improvements for data center networks](http://ieeexplore.ieee.org/xpls/icp.jsp?arnumber=6465539)"

[2] [RFC 8257](https://tools.ietf.org/html/rfc8257)- Data Center TCP (DCTCP): TCP Congestion Control for Data Centers

[3] The ns-3 network simulator. http://www.nsnam.org/

[4] [RFC 2001](https://dl.acm.org/citation.cfm?id=RFC2001)- TCP Slow Start, Congestion Avoidance, Fast Retransmit, and Fast Recovery Algorithms


