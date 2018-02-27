## Implementation of T-DCTCP in ns-3
## Course Code: CO365
### Assignment: #20

#### References 

[1] [RFC 8257](https://tools.ietf.org/html/rfc8257)- Data Center TCP (DCTCP): TCP Congestion Control for Data Centers

[2] [T-DCTCP](http://ieeexplore.ieee.org/xpls/icp.jsp?arnumber=6465539)- TCP improvements for data center networks

[3] [Notes](https://docs.google.com/document/d/1waPUTyqbXhkUqWOotZvzC89Wf7NSsDmaMUmthbU1BtE/edit?usp=sharing)- General notes for the project

#### Modifications proposed in the paper:
- Increasing cwnd when ECE = 0 in Congestion Avoidance algorithm
- Resetting alpha (Congestion Indicator) to zero once Delayed Ack Timeout Event occurs
- Dynamic calculation of Delayed Ack Timeout

