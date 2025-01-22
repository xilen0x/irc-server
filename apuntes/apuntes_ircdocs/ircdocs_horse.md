# [https://modern.ircdocs.horse](https://modern.ircdocs.horse)

## Connection Setup

Client-server connections are:
- TCP/6667 for plaintext
- TCP/6697 for TLS connections.

## Clients

All servers must have :

- unique nickname
- the real name/address of the host that the client is connecting from 
- the username of the client on that host
- the server to which the client is connected

Nicknames are **non-empty strings** with the following restrictions:

- They MUST NOT contain any of the following characters: space (' ', 0x20), comma (',', 0x2C), asterisk ('\*', 0x2A), question mark ('?', 0x3F), exclamation mark ('!', 0x21), at sign ('@', 0x40).
- They MUST NOT start with any of the following characters: dollar ('$', 0x24), colon (':', 0x3A).
- They MUST NOT start with a character listed as a channel type, channel membership prefix, or prefix listed in the IRCv3 multi-prefix Extension.
- They SHOULD NOT contain any dot character ('.', 0x2E).

Servers MAY have additional implementation-specific nickname restrictions and SHOULD avoid the use of nicknames which are ambiguous with commands or command parameters where this could lead to confusion or error.

## Channels

A channel is a named group of one or more clients. All clients in the channel will receive all messages addressed to that channel. The channel is created implicitly when the first client joins it, and the channel ceases to exist when the last client leaves it. While the channel exists, any client can reference the channel using the name of the channel.

> **CREO QUE ESTO NO SE PIDE** : Networks that support the concept of ‘channel ownership’ may persist specific channels in some way while no clients are connected to them.


List of Chanels concepts:

- [channel types](https://modern.ircdocs.horse/#channel-types) 
	- [regular channel](https://modern.ircdocs.horse/#regular-channels-)
	- [server-specific or local channels](https://modern.ircdocs.horse/#local-channels-)
- [Channel Modes](https://modern.ircdocs.horse/#channel-modes) that can alter the characteristics and behaviour of individual channels.
- [topic](https://modern.ircdocs.horse/#topic-message)
- [CHANLIMIT](https://modern.ircdocs.horse/#chanlimit-parameter) and [Feature Advertisement](https://modern.ircdocs.horse/#feature-advertisement) : Server limit a *client* to join chanels by [CHANLIMIT](https://modern.ircdocs.horse/#chanlimit-parameter)
- [channel operators](https://modern.ircdocs.horse/#channel-operators) or **chanops**

### Chanels Names

Channel names are strings (beginning with specified prefix characters). Apart from the requirement of the first character being a valid [channel type](https://modern.ircdocs.horse/#channel-types) prefix character; the only restriction on a channel name is that it may not containi:
- any spaces (' ', 0x20),
- a control G / BELL ('^G', 0x07)
- or a comma (',', 0x2C) (which is used as a list item separator by the protocol).

### [Types of chanels](https://modern.ircdocs.horse/#channel-types):

1. [regular channel](https://modern.ircdocs.horse/#regular-channels-), which is known to all servers that are connected to the network. The prefix character for this type of channel is ('#', 0x23).
2. [server-specific or local channels](https://modern.ircdocs.horse/#local-channels-), where the clients connected can only see and talk to other clients on the same server. The prefix character for this type of channel is ('&', 0x26). 
3. For others [Channel Types section](https://modern.ircdocs.horse/#channel-types)

### User in Chanels 

**To create a new channel or become part of an existing channel**, a user is required to join the channel using the [Join command](https://modern.ircdocs.horse/#join-message).

Conditions to join to a chanel:
- If the channel doesn’t exist prior to joining, the channel is created and the creating user becomes a channel operator.
- If the channel already exists, whether or not the client successfully joins that channel depends on the modes currently set on the channel.

**Join** example : 
- if the channel is set to invite-only mode (+i), the client only joins the channel :
	- if they have been invited by another user
	- or if they have been exempted from requiring an invite by the channel operators.

### [Chanel topic](https://modern.ircdocs.horse/#topic-message)

The **topic** is a line shown to all users when they join the channel, and all users in the channel are notified when the topic of a channel is changed.

Channel topics commonly state channel rules, links, quotes from channel members, a general description of the channel, or whatever the **channel operators** want to share with the clients in their channel.

### Server can limit a Client to be part of a max number of chanels 

A user may be joined to several channels at once, but a limit may be imposed by the server as to how many channels a client can be in at one time. This limit is specified by the [CHANLIMIT](https://modern.ircdocs.horse/#chanlimit-parameter) parameter. See the [Feature Advertisement](https://modern.ircdocs.horse/#feature-advertisement) section for more details on RPL_ISUPPORT.

### Channel Operators

Status : **moderator**
Specific prefixes and moderation levels are covered in the [Channel Membership Prefixes](https://modern.ircdocs.horse/#channel-membership-prefixes) section.

Levels:

1. **chanops** : Channel operator
2. **halfop** : half operator
3. **protected** : protected user/operator
4. **founder** : channel founder
5. any other positions the server wishes to define

These moderation levels have varying privileges and can execute, and not execute, various channel management commands based on what the server defines. Examples of member prefix used for replies to the [NAMES](https://modern.ircdocs.horse/#names-message), [WHO](https://modern.ircdocs.horse/#who-message), and [WHOIS](https://modern.ircdocs.horse/#whois-message) commands:
- **@** for standard channel operators
- **%** for halfops

#### Commands which may only be used by channel moderators

- [KICK](https://modern.ircdocs.horse/#kick-message): Eject a client from the channel
- [MODE](https://modern.ircdocs.horse/#mode-message): Change the channel’s modes
- [INVITE](https://modern.ircdocs.horse/#invite-message): Invite a client to an invite-only channel (mode +i)
- [TOPIC](https://modern.ircdocs.horse/#topic-message): Change the channel topic in a mode +t channel


## Communication Types

- [One-to-one communication](https://modern.ircdocs.horse/#one-to-one-communication)
- [One-to-many communication](https://modern.ircdocs.horse/#one-to-many-communication)
	- [To A Channel](https://modern.ircdocs.horse/#to-a-channel)
	- [To A Host/Server Mask](https://modern.ircdocs.horse/#to-a-hostserver-mask)
	- [To A List](https://modern.ircdocs.horse/#to-a-list)
- [One-To-All](https://modern.ircdocs.horse/#one-to-all)
	- [Client-to-Client](https://modern.ircdocs.horse/#client-to-client)
	- [Client-to-Server](https://modern.ircdocs.horse/#client-to-server)
	- [Server-to-Server](https://modern.ircdocs.horse/#server-to-server)

## [Client-to-Server Protocol Structure](https://modern.ircdocs.horse/#client-to-server-protocol-structure)

While a client is connected to a server, they send a stream of bytes to each other. This stream contains messages separated by CR ('\r', 0x0D) and LF ('\n', 0x0A). These messages may be sent at any time from either side, and may generate zero or more reply messages.

**Character encoding** :  **SHOULD** use [UTF-8](http://tools.ietf.org/html/rfc3629). With fallbacks as described in the [Character Encodings](https://modern.ircdocs.horse/#character-encodings) implementation considerations appendix.

**casemapped in IRC** :

- Names of IRC entities (clients, servers, channels) are casemapped. This prevents, for example, someone having the nickname 'Dan' and someone else having the nickname 'dan', confusing other users. Servers MUST advertise the casemapping they use in the [RPL_ISUPPORT](https://modern.ircdocs.horse/#feature-advertisement) numeric that’s sent when connection registration has completed.

### [Message Format](https://modern.ircdocs.horse/#message-format)

An IRC message is a single line, delimited by a pair of CR ('\r', 0x0D) and LF ('\n', 0x0A) characters.
- Only parse and process a message once you encounter the \r\n at the end of it. If you encounter an empty message, silently ignore it.
- When sending messages, ensure that a pair of \r\n characters follows every single message your software sends out.

Message format : 

```txt
['@' <tags> SPACE] [':' <source> SPACE] <command> <parameters> <crlf>
```

Where:
- **SPACE** : space character(s) (can be more than 1) . Code : %x20
- **crlf** : "carriage return" "linefeed" . Codes: %x0D %x0A

The specific parts of an IRC message are:

- [tags](https://modern.ircdocs.horse/#tags): Optional metadata on a message, starting with ('@', 0x40).
- [source](https://modern.ircdocs.horse/#source): Optional note of where the message came from, starting with (':', 0x3A).
- [command](https://modern.ircdocs.horse/#command): The specific command this message represents.
- [parameters](https://modern.ircdocs.horse/#parameters): If it exists, data relevant to this specific command.

Most IRC servers limit messages to 512 bytes in length, including the trailing CR-LF characters. Implementations which include [message tags](https://ircv3.net/specs/extensions/message-tags.html) need to allow additional bytes for the tags section of a message; clients must allow 8191 additional bytes and servers must allow 4096 additional bytes.

Example of messages:

1. `:irc.example.com CAP LS * :multi-prefix extended-join sasl`
2. `@id=234AB :dan!d@localhost PRIVMSG #chan :Hey what's up!` . Here `id=234AB` is a **tag**.
3. `CAP REQ :sasl`

#### [TAGS](https://modern.ircdocs.horse/#tags) (Optional but enebled by **a capability**)

For more info see the [IRCv3 Message Tags specification](http://ircv3.net/specs/core/message-tags-3.2.html).

> The tags part is optional, and **MUST NOT** be sent unless explicitly enabled by [a capability](https://modern.ircdocs.horse/#capability-negotiation). This message part starts with a leading ('@', 0x40) character, which MUST be the first character of the message itself.

Tags is a serie of *tag* (or serie of **key** segments) separated by *;*. Format : `<tag> [';' <tag>]*`

- **tag format** : `<key> ['=' <escaped value>]`
- **key format** : `[ <client_prefix> ] [ <vendor> '/' ] <sequence of letters, digits, hyphens (`-`)>`

Where:
- **client_prefix** : `+`
- **escaped value** : `<sequence of any characters except NUL, CR, LF, semicolon (`;`) and SPACE>`
- **vendor format** : `<host>`

Tags examples and how they could be represented as [JSON](https://www.json.org/) objects:

1. `@id=123AB;rose         ->  {"id": "123AB", "rose": ""}`
2. `@url=;netsplit=tur,ty  ->  {"url": "", "netsplit": "tur,ty"}`

#### [SOURCE](https://modern.ircdocs.horse/#source) or **PREFIX** ( Optional)

> Clients **MUST NOT** include a source when sending a message. 

> Servers **MAY** include a source on any message, and **MAY** leave a source off of any message. Clients **MUST** be able to process any given message the same way whether it contains a source or does not contain one.

Source starts with a (':', 0x3A) character and if there are no tags it MUST be the first character of the message itself.

### [Command](https://modern.ircdocs.horse/#message-format)

The command must either be a valid IRC command or a numeric (a three-digit number represented as text). Format : `letter* / 3digit`

More info in [Client Messages](https://modern.ircdocs.horse/#client-messages) and [Numerics](https://modern.ircdocs.horse/#numerics) sections.

#### [Parameters](https://modern.ircdocs.horse/#parameters)

Parameters (or ‘params’) are extra pieces of information added to the end of a message and mean changes for every single message.

Example format: 

```txt
*( SPACE middle ) [ SPACE ":" trailing ]
```

Where:
- **SPACE** : space character(s) (can be more than 1) . Code : %x20
- **middle**:  `nospcrlfcl *( ":" / nospcrlfcl )`
- **trailing**: `*( ":" / " " / nospcrlfcl )`
- **nospcrlfcl**: sequence of any characters except NUL, CR, LF, colon (`:`) and SPACE>

Examples of messages and how the parameters would be represented as JSON lists:

1. `:irc.example.com CAP * LIST            ->   ["\*", "LIST", ""]`
2. `CAP * LS :multi-prefix sasl            ->   ["\*", "LS", "multi-prefix sasl"]`
3. `CAP REQ :sasl message-tags foo         ->   ["REQ", "sasl message-tags foo"]`
4. `:dan!d@localhost PRIVMSG #chan :Hey!   ->   ["#chan", "Hey!"]`
5. `:dan!d@localhost PRIVMSG #chan Hey!    ->   ["#chan", "Hey!"]`
6. `:dan!d@localhost PRIVMSG #chan ::-)    ->   ["#chan", ":-)"]`

> As these examples show, a trailing parameter (a final parameter with a preceding `:`) has the same semantics as any other parameter, and MUST NOT be treated specially or stored separately once the `:` is stripped.

However, this syntax is insufficient in two cases:
- a parameter that contains one or more spaces, and an empty parameter. To permit such parameters, the final parameter can be prepended with a (':', 0x3A) character, in which case that character is stripped and the rest of the message is treated as the final parameter, including any spaces it contains.
- Parameters that contain spaces, are empty, or begin with a ':' character **MUST** be sent with a preceding ':'
- in other cases the use of a preceding ':' on the final parameter is **OPTIONAL**

> Older clients limit to manage 15 parameters . But **MUST** parse incoming messages with any number of them. So Software **SHOULD AVOID** sending more than 15 parameters.

#### [Compatibility with incorrect software](https://modern.ircdocs.horse/#compatibility-with-incorrect-software)

- single **\n** : Servers **SHOULD** handle it.
- single **\r** : Servers **MAY** handle it.
- **\r\n** : Servers and clients **MUST** handle it.
- **empty lines**: Servers and clients SHOULD
- **messages over the 512-bytes limit**: Servers SHOULD gracefully handle. Options to do that:
	1. Send an error numeric back, preferably **ERR_INPUTTOOLONG (417)**. (my comment : **ALTERMATIVE TO NEXT**)
    2. Truncate on the 510th byte (and add \r\n at the end) or, preferably, on the last UTF-8 character or grapheme that fits. (my comment : **PREFERABLE**)
	3. Ignore the message or close the connection – but this may be confusing to users of buggy clients. (my comment : **AVOID**)

- **SPACE** : clients and servers **SHOULD NOT** use more than one space.

### [Numeric Replies](https://modern.ircdocs.horse/#numeric-replies)

See [Numerics](https://modern.ircdocs.horse/#numerics) section.

### [Wildcard Expressions](https://modern.ircdocs.horse/#wildcard-expressions) or **mask**

Format: `*( nowild / noesc wildone / noesc wildmany )`

Where:
- **wildone** : `?` (0x3F)
- **wildmany** : `*`(0x2A)
- **nowild** : any octet except `NUL`, `*`, `?`
- **noesc** : any octet except `NUL` and `\`

Examples:
- `a?c` : Matches any string of 3 characters in length starting with `a` and ending with `c`.
- `a*c` ; Matches any string of 2 or more characters in length starting with `a` and ending with `c`. 

## [Connection Registration](https://modern.ircdocs.horse/#connection-registration)

The recommended order of commands during registration is as follows:

1. CAP LS 302    // client supports [version 302](https://ircv3.net/specs/extensions/capability-negotiation.html#cap-ls-version) of client capability negotiation
2. [PASS](https://modern.ircdocs.horse/#pass-message)			// No es requerido . Si se pone ha de estar antes de NICK y USER
3. [NICK](https://modern.ircdocs.horse/#nick-message) and [USER](https://modern.ircdocs.horse/#user-message)
- If server supports [capability negotiation](https://modern.ircdocs.horse/#capability-negotiation)
	4. [Capability Negotiation](https://modern.ircdocs.horse/#capability-negotiation) .The client should request advertised capabilities it wishes to enable here.
	5. SASL (if negotiated)  // If the client supports [SASL authentication](https://modern.ircdocs.horse/#authenticate-message) and wishes to authenticate with the server, it should attempt this after a successful [CAP ACK](https://modern.ircdocs.horse/#cap-message) of the sasl capability is received and while registration is suspended.
	6. [CAP END](https://modern.ircdocs.horse/#cap-message)       //The registration process is resumed
- else
	2. [PASS](https://modern.ircdocs.horse/#pass-message)			// No es requerido . Si se pone ha de estar antes de NICK y USER
	3. [NICK](https://modern.ircdocs.horse/#nick-message) and [USER](https://modern.ircdocs.horse/#user-message)

Where **NICK** is *nickname* and **USER** is *real name*.

> Servers **SHOULD** set a reasonable timeout for waiting to complete a lookup of client information (such as hostname or ident for a username) during registration.  

> Additionally, some servers also send a [PING](https://modern.ircdocs.horse/#ping-message) and require a matching [PONG](https://modern.ircdocs.horse/#pong-message) from the client before continuing. This exchange may happen immediately on connection and at any time during connection registration, so clients **MUST** respond correctly to it.

To complete the registration process, server **MUST** send : ( message examples extrated from [chirc by UChicago](https://chi.cs.uchicago.edu/chirc/irc_examples.html)
1. `001` in [RPL_WELCOME](https://modern.ircdocs.horse/#rplwelcome-001) format. Command example : `:bar.example.com 001 amy :Welcome to the Internet Relay Network amy!amy@foo.example.com`
2. `002` in [RPL_YOURHOST](https://modern.ircdocs.horse/#rplyourhost-002) format.
3. `003` in [RPL_CREATED](https://modern.ircdocs.horse/#rplcreated-003) format.
4. `004` in [RPL_MYINFO](https://modern.ircdocs.horse/#rplmyinfo-004) format.
5. At least one `005` in [RPL_ISUPPORT](https://modern.ircdocs.horse/#rplisupport-005) format.
	- this command is designed to advertise many different IRC features, limits, and protocol options that clients should be aware of. See [Feature Advertisement](https://modern.ircdocs.horse/#motd-message)
	- when is necessary to send more than one , the consecutive **RPL_ISUPPORT** numerics **SHOULD** be sent adjacent to each other.
	- A list of **RPL_ISUPPORT** parameters is available in the [RPL_ISUPPORT Parameters](https://modern.ircdocs.horse/#rplisupport-parameters) section.
6. The server **MAY** then send other numerics and messages.
7. The server **SHOULD** then respond as though the client sent the [LUSERS](https://modern.ircdocs.horse/#lusers-message) command and return the appropriate numerics.
8. The server MUST then respond with one of these options:
	- sucessful Message of the Day numerics
	- [ERR_NOMOTD](https://modern.ircdocs.horse/#errnomotd-422) (422) numeric. 

## [Capability Negotiation](https://modern.ircdocs.horse/#motd-message)

Capability Negotiation is a mechanism for the negotiation of protocol extensions, known as client capabilities, that makes sure servers implementing backwards-incompatible protocol extensions still interoperate with existing clients, and vice-versa.

Clients and servers should implement capability negotiation and the **CAP** command based on the [Capability Negotiation specification](). Updates, improvements, and new versions of capability negotiation are managed by the [IRCv3 Working Group](9http://ircv3.net/irc/).

## [Client Messages](https://modern.ircdocs.horse/#client-messages)

> **There are 40 commands** 

- **Command Examples** : client to server
- **Message Examples** : server to a client

If a command is sent from a client to a server with less parameters than the command requires to be processed, the server will reply with an [ERR_NEEDMOREPARAMS](https://modern.ircdocs.horse/#errneedmoreparams-461) (461) numeric and the command will fail.

Groups of commands:
- [Connection Messages](https://modern.ircdocs.horse/#connection-messages). See also [Capability Negotiation specification](https://ircv3.net/specs/extensions/capability-negotiation.html)
- [Channel Operations](https://modern.ircdocs.horse/#channel-operations)
	- This group of messages is concerned with manipulating channels, their properties (channel modes), and their contents (typically clients).
- [Server Queries and Commands](https://modern.ircdocs.horse/#server-queries-and-commands)
- [Sending Messages](https://modern.ircdocs.horse/#sending-messages)
- [User-Based Queries](https://modern.ircdocs.horse/#user-based-queries)
- [Operator Messages](https://modern.ircdocs.horse/#operator-messages) **Required by Mandatory part**
- [Optional Messages](https://modern.ircdocs.horse/#optional-messages)

## [Channel Types](https://modern.ircdocs.horse/#channel-types)

- [Regular Channels (#)](https://modern.ircdocs.horse/#regular-channels-)
- [Local Channels (&)](https://modern.ircdocs.horse/#local-channels-). Generally, the concept of channel ownership is not supported for local channels.

## [Modes](https://modern.ircdocs.horse/#modes)

For more extensive lists (including conflicting and obsolete modes), see the external irc-defs [client](https://defs.ircdocs.horse/defs/usermodes.html) and [channel](https://defs.ircdocs.horse/defs/chanmodes.html) mode lists.

- [User Modes](https://modern.ircdocs.horse/#user-modes)
	- Standard (defined in the official IRC specification documents)
		- [Invisible User Mode](https://modern.ircdocs.horse/#invisible-user-mode)
		- [Oper User Mode](https://modern.ircdocs.horse/#oper-user-mode)
		- [Local Oper User Mode](https://modern.ircdocs.horse/#local-oper-user-mode)
		- [WALLOPS User Mode](https://modern.ircdocs.horse/#wallops-user-mode)
	- widely-used:
		- [Registered User Mode](https://modern.ircdocs.horse/#registered-user-mode)
- [Channel Modes](https://modern.ircdocs.horse/#channel-modes)
	- Standard (defined in the official IRC specification documents)
		- [Ban Channel Mode](https://modern.ircdocs.horse/#ban-channel-mode)
		- [Client Limit Channel Mode](https://modern.ircdocs.horse/#client-limit-channel-mode)
		- [Invite-Only Channel Mode](https://modern.ircdocs.horse/#invite-only-channel-mode)
		- [Key Channel Mode](https://modern.ircdocs.horse/#key-channel-mode)
		- [Moderated Channel Mode](https://modern.ircdocs.horse/#moderated-channel-mode)
		- [Secret Channel Mode](https://modern.ircdocs.horse/#secret-channel-mode)
		- [Protected Topic Mode](https://modern.ircdocs.horse/#protected-topic-mode)
		- [No External Messages Mode](https://modern.ircdocs.horse/#no-external-messages-mode)
	- used in almost all IRC software today
		- [Exception Channel Mode](https://modern.ircdocs.horse/#exception-channel-mode)
		- [Invite-Exception Channel Mode](https://modern.ircdocs.horse/#invite-exception-channel-mode)
- [Channel Membership Prefixes](https://modern.ircdocs.horse/#channel-membership-prefixes)
	- Standard (defined in the official IRC specification documents)
		- [Operator Prefix](https://modern.ircdocs.horse/#operator-prefix)
		- [Voice Prefi](https://modern.ircdocs.horse/#voice-prefix)
	- is used in a large number of networks
		- [Founder Prefix](https://modern.ircdocs.horse/#founder-prefix)
		- [Protected Prefix](https://modern.ircdocs.horse/#protected-prefix)
	- is widely used in networks today
		- [Halfop Prefix](https://modern.ircdocs.horse/#halfop-prefix)


## [Numerics](https://modern.ircdocs.horse/#numerics)

- `[<optional>]` : Optional parameter. – this means clients MUST NOT assume they will receive this parameter from all servers, and that servers SHOULD send this parameter unless otherwise specified in the numeric description
- `{ <repeating>}`: may be repeated zero or more times

The next data has been extracted form data in [rfc2812](https://datatracker.ietf.org/doc/html/rfc2812#section-5)

Range | Description
 ---  | -------
from 001 to 099 | client-server connections.
from 200 to 399 | Replies generated in the response to commands
from 400 to 599 | Error replies

[Reserved numerics in rfc2812](https://datatracker.ietf.org/doc/html/rfc2812#section-5.3) are not described.

## [RPL_ISUPPORT Parameters](https://modern.ircdocs.horse/#rplisupport-parameters)

Used to [advertise features](https://modern.ircdocs.horse/#feature-advertisement) to clients, the [RPL_ISUPPORT](https://modern.ircdocs.horse/#rplisupport-005) (005) numeric lists parameters that let the client know which features are active and their value, if any.

## [Implementation Notes](https://modern.ircdocs.horse/#implementation-notes)

### [Character Encodings](https://modern.ircdocs.horse/#character-encodings)
Use [UTF-8](http://tools.ietf.org/html/rfc3629) for decoding and falling back to [Latin-1](https://en.wikipedia.org/wiki/Windows-1252) (what has been called the Hybrid encoding).

### [Message Parsing and Assembly](https://modern.ircdocs.horse/#message-parsing-and-assembly)

> Expected security issues and general runtime problems

**Message Parsing** is turning raw IRC messages into the various message parts (tags, prefix, command, parameters).
**Message Assembly** is the opposite – taking the various message parts and creating an IRC line to be sent over the wire. 

#### [Trailing](https://modern.ircdocs.horse/#trailing)

Right way :

```txt
Message
    .Tags
    .Source
    .Verb
    .Params (including all normal params, and the trailing param if it exists)
``` 

#### [Direct String Comparisons on IRC Lines](https://modern.ircdocs.horse/#direct-string-comparisons-on-irc-lines)

Here explains best practices to procces incoming lines.

### [Casemapping](https://modern.ircdocs.horse/#casemapping)

> Casemapping, at least right now, is a topic where implementations differ greatly.

#### [Servers](https://modern.ircdocs.horse/#servers)

Does your server use "rfc1459" or "rfc1459-strict" casemapping? If so, can you use a casemapping with less ambiguity such as "ascii"?

Does your server store state using nicks/channel names as keys? If so, is your server written in such a way that keys are casefolded automatically, or that ensures keys are casefolded before using them in this way?

#### [Clients](https://modern.ircdocs.horse/#clients)

Does your client store state using nicks/channel names as keys, and if so do you casefold those keys appropriately?

Does your client discover the casemapping to use from the [CASEMAPPING RPL_ISUPPORT](https://modern.ircdocs.horse/#casemapping-parameter) parameter on connection? If so, does your client use the appropriate casemapping based on it?



