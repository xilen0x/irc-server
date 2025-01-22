# [Internet Relay Chat: Channel Management](https://datatracker.ietf.org/doc/html/rfc2811)

## Channel Characteristics

A channel is a named group of one or more users which will all receive messages addressed to that channel.  A channel is  characterized by:
- its name
- properties
- current members.

### [Namespace](https://datatracker.ietf.org/doc/html/rfc2811#section-2.1)

Namespace are:
- strings beginning with a special char (*channel prefix*) : 
	- `#`, `+`(don-t support channel modes, with the exception of the `t` channel flag which is set) or `!`(known to one (1) or more servers that are connected to the network, depending on the channel mask. See [Channel Scope](https://datatracker.ietf.org/doc/html/rfc2811#section-2.2))
	- `&` (located on serverd where is created), 
- length : =< 50 chars
- case insensitive
- it SHALL NOT contain:
	- any spaces (` `)
	- a **Ctrl+G** (^G or ASCII 7)
	- a comma (`,`) which is used as a list item separator by the protocol
	- a colon (`:`) is used as a delimiter for the channel mask

### [Channel Properties](https://datatracker.ietf.org/doc/html/rfc2811#section-2.3)

Channel properties are defined by channel modes. Channel modes can be manipulated by the channel members.

### [Privileged Channel Members](https://datatracker.ietf.org/doc/html/rfc2811#section-2.4)

- [Channel Operators](https://datatracker.ietf.org/doc/html/rfc2811#section-2.4.1) (*chop* or *chanop*) : Identified by `@` next to their nickname
- [Channel Creator](https://datatracker.ietf.org/doc/html/rfc2811#section-2.4.2) is the user qho creates a channel with the character `!` as prefix. They are endowed with the ability to toggle certain modes of the channel which channel operators may not manipulate.

### [Channel lifetime](https://datatracker.ietf.org/doc/html/rfc2811#section-3)

- [Standard channels](https://datatracker.ietf.org/doc/html/rfc2811#section-3.1). Prefix: `&`, `#` or `+`. They are created implicitly when the first user joins it ( this user is the *channel operator*, and cease to exist when the last user leaves it
- [Safe Channels](https://datatracker.ietf.org/doc/html/rfc2811#section-3.2). Prefix: `!`.

### [Channel Modes](https://datatracker.ietf.org/doc/html/rfc2811#section-4)

Here only the options that they are in **ft_irc**'s mandatory. See [Channel Modes](https://datatracker.ietf.org/doc/html/rfc2811#section-4) for mor options. 

#### [Member Status](https://datatracker.ietf.org/doc/html/rfc2811#section-4.1)

- [`o`](https://datatracker.ietf.org/doc/html/rfc2811#section-4.1.2): give/take channel operator privilege;

#### [Channel Flags](https://datatracker.ietf.org/doc/html/rfc2811#section-4.2)

- [`i`](https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.2): toggle the invite-only channel flag;
- [`t`](https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.8): toggle the topic settable by channel operator only flag;
- [`k`](https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.10): set/remove the channel key (password);
- [`l`](https://datatracker.ietf.org/doc/html/rfc2811#section-4.2.9): set/remove the user limit to channel;

### [Channel Access Control](https://datatracker.ietf.org/doc/html/rfc2811#section-4.3)

- [Channel Ban and Exception](https://datatracker.ietf.org/doc/html/rfc2811#section-4.3.1)
- [Channel Invitation](https://datatracker.ietf.org/doc/html/rfc2811#section-4.3.2) : users whose address matches an invitation mask set for the channel are allowed to join the channel without any invitation.


## [Current Implementations](https://datatracker.ietf.org/doc/html/rfc2811#section-5)

Use for server implementation (some part can be used for client implementation).

- [Tracking Recently Used Channels](https://datatracker.ietf.org/doc/html/rfc2811#section-5.1)
- [Safe Channels](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2)
	- [Channel Identifier](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2.1)
	- [Channel Delay](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2.2)
	- [Abuse Window](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2.3)
	- [Preserving Sanity In The Name Space](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2.4)
	- [Server Reop Mechanism](https://datatracker.ietf.org/doc/html/rfc2811#section-5.2.5)

## [Current problems](https://datatracker.ietf.org/doc/html/rfc2811#section-6)

- [Labels](https://datatracker.ietf.org/doc/html/rfc2811#section-6.1)
	- [Channel Delay](https://datatracker.ietf.org/doc/html/rfc2811#section-6.1.1). Affects channels with prefix `#`.
	- [Safe Channels](https://datatracker.ietf.org/doc/html/rfc2811#section-6.1.2).
	- [Mode Propagation Delays](https://datatracker.ietf.org/doc/html/rfc2811#section-6.2): in a network of servers???.
- [Collisions And Channel Modes](https://datatracker.ietf.org/doc/html/rfc2811#section-6.3). Affects *server's netowrk*.
- [Resource Exhaustion](https://datatracker.ietf.org/doc/html/rfc2811#section-6.4). Result of mask use in [Channel Access Control](https://datatracker.ietf.org/doc/html/rfc2811#section-4.3). **RECOMMENDED** that a limit be put on the number of such masks per channels as mentioned in [Channel Access Control](https://datatracker.ietf.org/doc/html/rfc2811#section-4.3)

## [Security Considerations](https://datatracker.ietf.org/doc/html/rfc2811#section-6.4)

- [Access Control](https://datatracker.ietf.org/doc/html/rfc2811#section-7.1)
- [Channel Privacy](https://datatracker.ietf.org/doc/html/rfc2811#section-7.2)

## [Anonymity](https://datatracker.ietf.org/doc/html/rfc2811#section-7.3)
