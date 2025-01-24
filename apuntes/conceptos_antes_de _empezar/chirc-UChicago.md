



## [Example IRC Communications](https://chi.cs.uchicago.edu/chirc/irc_examples.html#)

### [Logging into an IRC server](https://chi.cs.uchicago.edu/chirc/irc_examples.html#logging-into-an-irc-server)

(. is no significat)

Example accept Nick:

IRC CLIENT | Dir | IRC Server
 --------  | --- | ---------
NICK amy   | ->  | .
USER amy * * :Amy Pond | -> | . 
.          | <-  | :bar.example.com 001 amy :Welcome to the Internet Relay Network amy!amy@foo.exemple.com

Example refuse Nick:

IRC CLIENT | Dir | IRC Server
 --------  | --- | ---------
NICK amy   | ->  | .
.          | <-  | :bar.example.com 443 * amy :Nickname is already in use.

### [Messaging between users](https://chi.cs.uchicago.edu/chirc/irc_examples.html#messaging-between-users)
### [Joining, talking in, and leaving a channel](https://chi.cs.uchicago.edu/chirc/irc_examples.html#joining-talking-in-and-leaving-a-channel)


