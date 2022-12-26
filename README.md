# syssec2022 Exercise 6
### Panagiotis Savvaidis, AM 2013030180

For this exercise, we implement an ad blocker by not accepting packets from known advertising domains. We first separate some domains for their incoming packets to be DROPPEDand the rest of the domains' packets to be REJECTED. 

The difference between `DROP` and `REJECT` is that when packets are rejected, the sender knows that the firewall blocked them. While dropping, the packets are simply not propagated further in. The sender only thinks that the packets are lost or the target is not found.

In this implementation, we do the clustering mentioned above, apply the DROP and REJECT rules in the firewall, save and load rules from the `adblockRules` file, reset the firewall and list all the rules.
